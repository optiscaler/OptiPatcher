// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#include "Util.h"
#include "Patcher.h"
#include "Scanner.h"

static bool _patchResult = false;

extern "C" __declspec(dllexport) bool PatchResult() { return _patchResult; }

static void CheckForPatch()
{
    auto exeName = Util::ExePath().filename().string();
    auto exeNameLower = std::transform(exeName.begin(), exeName.end(), exeName.begin(), ::tolower);
    auto exeModule = GetModuleHandle(nullptr);

    // Deep Rock Galactic
    if (exeName == "fsd-win64-shipping.exe")
    {
        std::string_view pattern("4C 8B 75 00 33 C0 48 8B 4D 50 4C 89 75 D0 48 89 45 00 48 89 45 08 48 85 C9 74 05 E8 "
                                 "? ? ? ? E8 ? ? ? ? 84 C0 75");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 37);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }
    // Forgive Me Father 2, The Midnight Walk, Oblivion Remastered
    else if (exeName == "fmf2-win64-shipping.exe" || exeName == "themidnightwalk-win64-shipping.exe" ||
             exeName == "oblivionremastered-win64-shipping.exe")
    {
        std::string_view pattern("B8 04 00 00 00 74 03 49 8B C7 "
                                 "8B 34 30 4C 89 A4 24 78 02 00 "
                                 "00 4C 89 B4 24 38 02 00 00 E8 "
                                 "? ? ? ? 84 C0 75");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 34);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }
    // Talos Principle 2
    else if (exeName == "talos2-win64-shipping.exe")
    {
        std::string_view pattern("49 8B F4 EB 02 33 F6 42 8B 34 "
                                 "36 E8 ? ? ? ? 84 C0 75");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 16);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }
    // Witchfire
    else if (exeName == "witchfire-win64-shipping.exe")
    {
        std::string_view pattern("4C 8B 6D E0 33 C0 48 8B 4D 40 "
                                 "4C 89 6D C0 48 89 45 E0 48 89 "
                                 "45 E8 48 85 C9 74 05 E8 ? ? "
                                 "? ? E8 ? ? ? ? 84 C0 75");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 37);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }
    // The Persistence
    else if (exeName == "persistence-win64-shipping.exe")
    {
        std::string_view pattern("33 C9 3B ? ? ? ? ? 0F 95 "
                                 "C1 EB 02 33 C9 8B 1C 8B E8 ? "
                                 "? ? ? 84 C0 75");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 23);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }
    // Black Myth: Wukong
    else if (exeName == "b1-win64-shipping.exe")
    {
        std::string_view pattern("49 8B C6 74 03 49 8B C5 46 8B "
                                 "3C 38 E8 ? ? ? ? 84 C0 75");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 17);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }
    // Banishers
    else if (exeName == "banishers-win64-shipping.exe")
    {
        std::string_view pattern("45 33 C9 C7 44 24 20 03 00 00 "
                                 "00 48 8D ? ? ? ? ? 48 8D "
                                 "8D B0 00 00 00 45 8D 41 05 E8 "
                                 "? ? ? ? 48 8B 4D 30 48 85 "
                                 "C9 74 05 E8 ? ? ? ? 81 3D "
                                 "? ? ? ? DE 10 00 00 74");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 48);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x39, 0xC0, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        CheckForPatch();
        break;

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }

    return TRUE;
}
