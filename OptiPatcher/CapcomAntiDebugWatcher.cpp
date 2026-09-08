#include "pch.h"

#include "CapcomAntiDebugWatcher.h"

#include "Util.h"

#include <algorithm>
#include <array>
#include <atomic>
#include <cctype>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <exception>
#include <mutex>
#include <string>
#include <thread>

namespace
{
constexpr SIZE_T kBaselineSize = 32;
constexpr DWORD kUnsupportedProtectionFlags = PAGE_GUARD | PAGE_NOCACHE | PAGE_WRITECOMBINE;

struct HookInfo
{
    SIZE_T length = 0;
    uintptr_t target = 0;
    std::array<BYTE, 6> bytes{};
    const char* type = nullptr;
};

std::atomic<bool> g_started = false;
std::atomic<bool> g_stopRequested = false;
std::mutex g_lifecycleMutex;
void* g_dbgUiRemoteBreakin = nullptr;
std::array<BYTE, kBaselineSize> g_baseline{};
std::array<BYTE, kBaselineSize> g_lastObserved{};
bool g_haveLastObserved = false;

void Log(const char* format, ...)
{
    char buffer[512]{};
    va_list args;
    va_start(args, format);
    _vsnprintf_s(buffer, sizeof(buffer), _TRUNCATE, format, args);
    va_end(args);

    OutputDebugStringA(buffer);
    OutputDebugStringA("\n");
}

std::string CurrentExeName()
{
    auto name = Util::ExePath().filename().string();
    std::transform(name.begin(), name.end(), name.begin(), [](unsigned char value) {
        return static_cast<char>(std::tolower(value));
    });
    return name;
}

bool IsSupportedExecutable(const std::string& exeName)
{
    return exeName == "monsterhunterwilds.exe" || exeName == "dd2.exe" || exeName == "re9.exe" ||
           exeName == "pragmata.exe";
}

bool HasUnsupportedProtectionFlags(DWORD protection)
{
    return (protection & kUnsupportedProtectionFlags) != 0;
}

DWORD BaseProtection(DWORD protection)
{
    return protection & 0xffu;
}

bool IsExecutableProtection(DWORD protection)
{
    if (protection == 0 || HasUnsupportedProtectionFlags(protection))
    {
        return false;
    }

    switch (BaseProtection(protection))
    {
    case PAGE_EXECUTE:
    case PAGE_EXECUTE_READ:
    case PAGE_EXECUTE_READWRITE:
    case PAGE_EXECUTE_WRITECOPY:
        return true;
    default:
        return false;
    }
}

bool IsReadableProtection(DWORD protection)
{
    if (protection == 0 || HasUnsupportedProtectionFlags(protection))
    {
        return false;
    }

    switch (BaseProtection(protection))
    {
    case PAGE_READONLY:
    case PAGE_READWRITE:
    case PAGE_WRITECOPY:
    case PAGE_EXECUTE_READ:
    case PAGE_EXECUTE_READWRITE:
    case PAGE_EXECUTE_WRITECOPY:
        return true;
    default:
        return false;
    }
}

bool QueryRange(const void* address, SIZE_T size, bool requireReadable, MEMORY_BASIC_INFORMATION& information)
{
    if (address == nullptr || size == 0)
    {
        return false;
    }

    const uintptr_t start = reinterpret_cast<uintptr_t>(address);
    if (size - 1 > UINTPTR_MAX - start)
    {
        return false;
    }

    if (VirtualQuery(address, &information, sizeof(information)) != sizeof(information))
    {
        return false;
    }

    const uintptr_t regionStart = reinterpret_cast<uintptr_t>(information.BaseAddress);
    if (information.RegionSize == 0 || information.RegionSize - 1 > UINTPTR_MAX - regionStart)
    {
        return false;
    }

    const uintptr_t regionEnd = regionStart + information.RegionSize;
    const uintptr_t requestedEnd = start + size;
    if (start < regionStart || requestedEnd > regionEnd || information.State != MEM_COMMIT)
    {
        return false;
    }

    return !requireReadable || IsReadableProtection(information.Protect);
}

bool ReadBytes(const void* address, void* destination, SIZE_T size)
{
    MEMORY_BASIC_INFORMATION information{};
    if (!QueryRange(address, size, true, information))
    {
        return false;
    }

    SIZE_T bytesRead = 0;
    return ReadProcessMemory(GetCurrentProcess(), address, destination, size, &bytesRead) != FALSE &&
           bytesRead == size;
}

bool CalculateRelativeTarget(uintptr_t instruction, SIZE_T instructionLength, int32_t relative, uintptr_t& target)
{
    const int64_t delta = static_cast<int64_t>(instructionLength) + static_cast<int64_t>(relative);
    if (delta >= 0)
    {
        const auto unsignedDelta = static_cast<uint64_t>(delta);
        if (unsignedDelta > UINTPTR_MAX - instruction)
        {
            return false;
        }

        target = instruction + static_cast<uintptr_t>(unsignedDelta);
        return true;
    }

    const auto magnitude = static_cast<uint64_t>(-delta);
    if (magnitude > instruction)
    {
        return false;
    }

    target = instruction - static_cast<uintptr_t>(magnitude);
    return true;
}

bool ResolveHook(const std::array<BYTE, kBaselineSize>& current, HookInfo& hook)
{
    const uintptr_t instruction = reinterpret_cast<uintptr_t>(g_dbgUiRemoteBreakin);

    if (current[0] == 0xe9)
    {
        int32_t relative = 0;
        std::memcpy(&relative, current.data() + 1, sizeof(relative));
        if (!CalculateRelativeTarget(instruction, 5, relative, hook.target))
        {
            return false;
        }

        hook.length = 5;
        hook.type = "E9";
        std::memcpy(hook.bytes.data(), current.data(), hook.length);
        return true;
    }

    if (current[0] == 0xff && current[1] == 0x25)
    {
        int32_t relative = 0;
        std::memcpy(&relative, current.data() + 2, sizeof(relative));

        uintptr_t slot = 0;
        if (!CalculateRelativeTarget(instruction, 6, relative, slot))
        {
            return false;
        }

        MEMORY_BASIC_INFORMATION slotInformation{};
        if (!QueryRange(reinterpret_cast<const void*>(slot), sizeof(uintptr_t), true, slotInformation))
        {
            return false;
        }

        if (!ReadBytes(reinterpret_cast<const void*>(slot), &hook.target, sizeof(hook.target)))
        {
            return false;
        }

        hook.length = 6;
        hook.type = "FF25";
        std::memcpy(hook.bytes.data(), current.data(), hook.length);
        return true;
    }

    return false;
}

bool QueryPrivateExecutableTarget(uintptr_t target, MEMORY_BASIC_INFORMATION& information)
{
    if (!QueryRange(reinterpret_cast<const void*>(target), 1, false, information))
    {
        return false;
    }

    return information.Type == MEM_PRIVATE && IsExecutableProtection(information.Protect);
}

bool NeutralizePayload(const MEMORY_BASIC_INFORMATION& information)
{
    if (information.BaseAddress == nullptr || information.RegionSize == 0 || information.Type != MEM_PRIVATE ||
        !IsExecutableProtection(information.Protect))
    {
        return false;
    }

    DWORD oldProtection = 0;
    if (!VirtualProtect(information.BaseAddress, information.RegionSize, PAGE_EXECUTE_READWRITE, &oldProtection))
    {
        Log("[CapcomAntiDebug] failed to change memory protection");
        return false;
    }

    bool wrote = true;
    __try
    {
        std::memset(information.BaseAddress, 0xc3, information.RegionSize);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        wrote = false;
    }

    DWORD ignoredProtection = 0;
    const bool restoredProtection =
        VirtualProtect(information.BaseAddress, information.RegionSize, oldProtection, &ignoredProtection) != FALSE;
    const bool flushed = FlushInstructionCache(GetCurrentProcess(), information.BaseAddress, information.RegionSize) != FALSE;

    if (!wrote || !restoredProtection || !flushed)
    {
        Log("[CapcomAntiDebug] failed to neutralize executable private payload");
        return false;
    }

    Log("[CapcomAntiDebug] neutralized executable private payload");
    return true;
}

bool RestoreEntry(const HookInfo& hook)
{
    std::array<BYTE, 6> current{};
    if (!ReadBytes(g_dbgUiRemoteBreakin, current.data(), hook.length) ||
        std::memcmp(current.data(), hook.bytes.data(), hook.length) != 0)
    {
        Log("[CapcomAntiDebug] DbgUiRemoteBreakin changed before restore; leaving it untouched");
        return false;
    }

    MEMORY_BASIC_INFORMATION information{};
    if (!QueryRange(g_dbgUiRemoteBreakin, g_baseline.size(), false, information) ||
        !IsExecutableProtection(information.Protect))
    {
        Log("[CapcomAntiDebug] failed to validate DbgUiRemoteBreakin before restore");
        return false;
    }

    DWORD oldProtection = 0;
    if (!VirtualProtect(g_dbgUiRemoteBreakin, g_baseline.size(), PAGE_EXECUTE_READWRITE, &oldProtection))
    {
        Log("[CapcomAntiDebug] failed to change DbgUiRemoteBreakin protection");
        return false;
    }

    bool wrote = true;
    __try
    {
        std::memcpy(g_dbgUiRemoteBreakin, g_baseline.data(), g_baseline.size());
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        wrote = false;
    }

    DWORD ignoredProtection = 0;
    const bool restoredProtection =
        VirtualProtect(g_dbgUiRemoteBreakin, g_baseline.size(), oldProtection, &ignoredProtection) != FALSE;
    const bool flushed = FlushInstructionCache(GetCurrentProcess(), g_dbgUiRemoteBreakin, g_baseline.size()) != FALSE;

    if (!wrote || !restoredProtection || !flushed)
    {
        Log("[CapcomAntiDebug] failed to restore DbgUiRemoteBreakin");
        return false;
    }

    Log("[CapcomAntiDebug] restored DbgUiRemoteBreakin");
    return true;
}

void CheckDbgUiRemoteBreakin()
{
    std::array<BYTE, kBaselineSize> current{};
    if (!ReadBytes(g_dbgUiRemoteBreakin, current.data(), current.size()))
    {
        return;
    }

    if (std::memcmp(current.data(), g_baseline.data(), current.size()) == 0)
    {
        g_haveLastObserved = false;
        return;
    }

    const bool newlyObserved =
        !g_haveLastObserved || std::memcmp(current.data(), g_lastObserved.data(), current.size()) != 0;
    if (newlyObserved)
    {
        g_lastObserved = current;
        g_haveLastObserved = true;
        Log("[CapcomAntiDebug] DbgUiRemoteBreakin modification detected");
    }

    HookInfo hook;
    if (!ResolveHook(current, hook))
    {
        if (newlyObserved)
        {
            Log("[CapcomAntiDebug] unsupported DbgUiRemoteBreakin hook form");
        }
        return;
    }

    Log("[CapcomAntiDebug] hook type=%s target=%p", hook.type, reinterpret_cast<void*>(hook.target));

    MEMORY_BASIC_INFORMATION targetInformation{};
    if (!QueryPrivateExecutableTarget(hook.target, targetInformation))
    {
        if (newlyObserved)
        {
            Log("[CapcomAntiDebug] target is not ready or is not an executable MEM_PRIVATE region");
        }
        return;
    }

    if (newlyObserved)
    {
        Log("[CapcomAntiDebug] target region base=%p size=0x%zx type=MEM_PRIVATE protect=0x%08lx",
            targetInformation.BaseAddress,
            targetInformation.RegionSize,
            targetInformation.Protect);
    }

    if (NeutralizePayload(targetInformation))
    {
        if (RestoreEntry(hook))
        {
            g_haveLastObserved = false;
        }
    }
}

void WatchLoop()
{
    while (!g_stopRequested.load())
    {
        CheckDbgUiRemoteBreakin();
        Sleep(500);
    }
}
} // namespace

namespace capcom_antidebug
{
bool IsSupportedGame()
{
    return IsSupportedExecutable(CurrentExeName());
}

bool Initialize()
{
    const auto exeName = CurrentExeName();
    if (!IsSupportedExecutable(exeName))
    {
        return false;
    }

    std::lock_guard lifecycleLock(g_lifecycleMutex);
    if (g_started.load())
    {
        return true;
    }

    Log("[CapcomAntiDebug] enabled for %s", exeName.c_str());

    HMODULE ntdll = GetModuleHandleW(L"ntdll.dll");
    if (ntdll == nullptr)
    {
        Log("[CapcomAntiDebug] failed to locate ntdll.dll");
        return false;
    }

    g_dbgUiRemoteBreakin = reinterpret_cast<void*>(GetProcAddress(ntdll, "DbgUiRemoteBreakin"));
    if (g_dbgUiRemoteBreakin == nullptr ||
        !ReadBytes(g_dbgUiRemoteBreakin, g_baseline.data(), g_baseline.size()))
    {
        Log("[CapcomAntiDebug] failed to locate or capture DbgUiRemoteBreakin");
        g_dbgUiRemoteBreakin = nullptr;
        return false;
    }

    Log("[CapcomAntiDebug] captured DbgUiRemoteBreakin baseline");

    HMODULE pinnedModule = nullptr;
    if (!GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_PIN,
                            reinterpret_cast<LPCWSTR>(&g_started),
                            &pinnedModule))
    {
        Log("[CapcomAntiDebug] failed to pin watcher module");
        g_dbgUiRemoteBreakin = nullptr;
        return false;
    }

    g_stopRequested.store(false);
    g_haveLastObserved = false;
    try
    {
        std::thread(WatchLoop).detach();
    }
    catch (const std::exception&)
    {
        Log("[CapcomAntiDebug] failed to start watcher thread");
        g_dbgUiRemoteBreakin = nullptr;
        return false;
    }

    g_started.store(true);
    return true;
}

void Shutdown()
{
    g_stopRequested.store(true);
}
} // namespace capcom_antidebug
