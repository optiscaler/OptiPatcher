// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#include "Util.h"
#include "Patcher.h"
#include "Scanner.h"

static std::optional<bool> _patchResult = false;

extern "C" __declspec(dllexport) bool PatchResult() { return _patchResult.has_value() && _patchResult.value(); }
extern "C" __declspec(dllexport) void InitializeASI() { return; }

// Common patch for common UE patterns is { 0x0C, 0x01 }

// offset 34
std::string_view commonUEpattern1("B8 04 00 00 00 74 03 49 8B C7 "
                                  "8B 34 30 4C 89 A4 24 78 02 00 "
                                  "00 4C 89 B4 24 38 02 00 00 E8 "
                                  "? ? ? ? 84 C0 75");

// offset 17
std::string_view commonUEpattern2("49 8B C7 74 03 49 8B C5 46 8B 34 30 E8 ? ? ? ? 84 C0 75");

// offset 15
std::string_view commonUEpattern3("48 85 C9 74 05 E8 ? ? ? ? E8 ? ? ? ? 84 C0 75");

// offset 37, aiming at 84 C0
std::string_view commonUEpattern4(
    "4C 8B 6D E0 33 C0 48 8B 4D 40 4C 89 6D C0 48 89 45 E0 48 89 45 E8 48 85 C9 74 05 E8 ? ? ? ? E8 ? ? ? ? 84 C0 75");

// offset 17
std::string_view commonUEpattern5("49 8B C6 74 03 49 8B C5 46 8B 3C 38 E8 ? ? ? ? 84 C0 75");

enum class StringCompareType
{
    exactMatch,
    startsWith
};

struct ApplicationPatch
{
    StringCompareType compareType;
    std::string_view nameToMatch;
    std::string_view pattern;
    ptrdiff_t offset;
    std::vector<BYTE> patch;
    bool lastPattern = true; // set to false if this is not the last required pattern to match for this game
};

#define NOT_LAST_REQUIRED_PATTERN false

static const ApplicationPatch applicationPatches[] = {
    // Deep Rock Galactic, old pattern
    { StringCompareType::startsWith,
      "fsd-win",
      "4C 8B 75 00 33 C0 48 8B 4D 50 4C 89 75 D0 48 89 45 00 48 89 45 08 48 85 C9 74 05 E8 ? ? ? ? E8 ? ? ? ? 84 C0 75",
      37,
      { 0x0C, 0x01 } },

    // Deep Rock Galactic
    { StringCompareType::startsWith, "fsd-win", commonUEpattern4, 37, { 0x0C, 0x01 } },

    // Black Myth: Wukong benchmark
    { StringCompareType::startsWith, "b1-win", commonUEpattern5, 17, { 0x0C, 0x01 } },

    // Black Myth: Wukong
    { StringCompareType::startsWith,
      "b1-win",
      "E8 ? ? ? ? 84 C0 49 8B C4 74 03 49 8B C6 8B 34 30 89 75 80 E8 ? ? ? ? 84 C0 75",
      26,
      { 0x0C, 0x01 } },

    // Forgive Me Father 2
    { StringCompareType::startsWith, "fmf2-win", commonUEpattern1, 34, { 0x0C, 0x01 } },

    // The Midnight Walk
    { StringCompareType::startsWith, "themidnightwalk-win", commonUEpattern1, 34, { 0x0C, 0x01 } },

    // The Elder Scrolls IV: Oblivion Remastered
    { StringCompareType::startsWith, "oblivionremastered-win", commonUEpattern1, 34, { 0x0C, 0x01 } },

    // 171
    { StringCompareType::startsWith, "bgg-win", commonUEpattern2, 17, { 0x0C, 0x01 } },

    // Clair Obscur: Expedition 33
    { StringCompareType::startsWith, "sandfall-win", commonUEpattern2, 17, { 0x0C, 0x01 } },

    // Ranch Simulator
    { StringCompareType::startsWith, "ranch_simulator-win", commonUEpattern2, 17, { 0x0C, 0x01 } },

    // The Talos Principle 2
    { StringCompareType::startsWith,
      "talos2-win",
      "49 8B F4 EB 02 33 F6 42 8B 34 36 E8 ? ? ? ? 84 C0 75",
      16,
      { 0x0C, 0x01 } },

    // Witchfire
    { StringCompareType::startsWith, "witchfire-win", commonUEpattern4, 37, { 0x0C, 0x01 } },

    // The Persistence
    { StringCompareType::startsWith,
      "persistence-win",
      "33 C9 3B ? ? ? ? ? 0F 95 C1 EB 02 33 C9 8B 1C 8B E8 ? ? ? ? 84 C0 75",
      23,
      { 0x0C, 0x01 } },

    // Lost Records: Bloom & Rage
    { StringCompareType::exactMatch, "bloom&rage.exe", commonUEpattern5, 17, { 0x0C, 0x01 } },

    // Banishers: Ghosts of New Eden
    // inline patch
    { StringCompareType::startsWith,
      "banishers-win",
      "45 33 C9 C7 44 24 20 03 00 00 00 48 8D ? ? ? ? ? 48 8D 8D B0 00 00 00 45 8D 41 05 E8 ? ? ? ? 48 8B 4D 30 48 85 "
      "C9 74 05 E8 ? ? ? ? 81 3D ? ? ? ? DE 10 00 00 74", // aiming at 81 3D
      48,
      { 0x39, 0xC0, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 } },

    // Lies of P
    // inline patch
    { StringCompareType::startsWith,
      "lop-win",
      "41 B9 1B 00 00 00 C7 44 24 20 02 00 00 00 48 8D ? ? ? ? ? 48 8D 4D 68 45 8D 41 E9 E8 ? ? ? ? 48 8B 4D 10 48 85 "
      "C9 74 05 E8 ? ? ? ? 81 3D ? ? ? ? ? ? ? ? 74 0D",
      48,
      { 0x39, 0xC0, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 } },

    // ARK: Survival Ascended
    // inline patch
    { StringCompareType::exactMatch,
      "arkascended.exe",
      "E8 ? ? ? ? 84 C0 74 02 B0 01 84 C0 49 8B C5 74 03 49 8B C4 81 3D ? ? ? ? ? ? ? ? 44 8B 04 30",
      21,
      { 0x39, 0xC0, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 } },

    // Alone in the Dark 2024
    { StringCompareType::startsWith,
      "aloneinthedark-win",
      "4C 8B 65 F0 33 C0 48 8B 4D 48 4C 89 65 C0 48 89 45 F0 48 89 45 F8 48 85 C9 74 05 E8 ? ? ? ? E8 ? ? ? ? 84 C0 75",
      37,
      { 0x0C, 0x01 } },

    // Atomic Heart
    { StringCompareType::startsWith,
      "atomicheart-win",
      "4C 8B 7D F0 33 C0 48 8B 4D 40 4C 89 7D C0 48 89 45 F0 48 89 45 F8 48 85 C9 74 05 E8 ? ? ? ? E8 ? ? ? ? 84 C0 75",
      37,
      { 0x0C, 0x01 } },

    // The Alters
    { StringCompareType::startsWith,
      "thealters-win",
      "E8 ? ? ? ? 84 C0 75 0C E8 ? ? ? ? 84 C0 49 8B C7 74 03 49 8B C6 8B 34 30 E8 ? ? ? ? 84 C0 75",
      32,
      { 0x0C, 0x01 } },

    // WUCHANG: Fallen Feathers
    { StringCompareType::startsWith,
      "project_plague-win",
      "75 0C E8 ? ? ? ? 84 C0 49 8B C7 74 03 49 8B C6 8B 34 30 89 75 80 E8 ? ? ? ? 84 C0 75",
      28,
      { 0x0C, 0x01 } },

    // Enotria: The Last Song
    { StringCompareType::startsWith,
      "enotria-win",
      "84 C0 49 8B C7 74 03 49 8B C5 46 8B 34 30 E8 ? ? ? ? 84 C0 75",
      19,
      { 0x0C, 0x01 } },

    // The Ascent
    { StringCompareType::startsWith,
      "theascent-win",
      "48 85 C9 74 05 E8 ? ? ? ? 45 33 ED E9 ? ? ? ? E8 ? ? ? ? 84 C0",
      23,
      { 0x0C, 0x01 } },

    // Ghostrunner
    { StringCompareType::startsWith, "ghostrunner-win", "75 14 44 88 6F 30", 0, { 0xEB } },

    // Ghostrunner 2
    { StringCompareType::startsWith, "ghostrunner2-win", commonUEpattern3, 15, { 0x0C, 0x01 } },

    // Deadlink
    { StringCompareType::startsWith, "deadlink-win", commonUEpattern3, 15, { 0x0C, 0x01 } },

    // Amid Evil
    { StringCompareType::startsWith,
      "amidevil-win",
      "48 85 DB 74 08 48 8B CB E8 ? ? ? ? E8 ? ? ? ? 84 C0 75",
      18,
      { 0x0C, 0x01 } },

    // Severed Steel
    { StringCompareType::startsWith, "thankyouverycool-win", commonUEpattern3, 15, { 0x0C, 0x01 } },

    // Achilles: Legends Untold
    { StringCompareType::startsWith, "achilles-win", commonUEpattern3, 15, { 0x0C, 0x01 } },

    // LEGO® Builder's Journey
    { StringCompareType::exactMatch,
      "unityplayer.exe",
      "48 8D 15 ? ? ? ? 48 89 D9 E8 ? ? ? ? 48 83 F8 FF",
      15,
      { 0xB8, 0x00, 0x00, 0x00, 0x00 } },

    // Titan Quest II
    { StringCompareType::startsWith,
      "tq2-win",
      "84 C0 49 8B C6 74 03 49 8B C4 8B 34 30 E8 ? ? ? ? 84 C0 75 25",
      18,
      { 0x0C, 0x01 } },

    // Still Wakes the Deep
    else if (exeName == "stillwakesthedeep.exe")
    {
        std::string_view pattern("74 03 49 8B C7 8B 34 30 4C 89 "
                                 "A4 24 78 02 00 00 4C 89 B4 24 "
                                 "38 02 00 00 E8 ? ? ? ? 84 "
                                 "C0 75");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 29);
        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // Hogwarts Legacy
    else if (exeName == "hogwartslegacy.exe")
    {
        std::string_view pattern("48 8B 4D 48 4C 89 6D B0 48 89 "
                                 "45 E8 48 89 45 F0 48 85 C9 74 "
                                 "05 E8 ? ? ? ? E8 ? ? ? "
                                 "? 84 C0 75");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 31);
        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // RoboCop: Rogue City
    { StringCompareType::startsWith,
      "robocop-win",
      "83 F8 03 0F 85 ? ? ? ? E8 ? ? ? ? 84 C0 0F 84", // XeFG
      14,
      { 0x0C, 0x01 },
      NOT_LAST_REQUIRED_PATTERN }, // match DLSS as well
    { StringCompareType::startsWith,
      "robocop-win",
      "74 03 49 8B C5 46 8B 3C 38 E8 ? ? ? ? 84 C0 75", // DLSS
      14,
      { 0x0C, 0x01 } },

    // RoboCop: Unfinished Business
    else if (exeName == "robocopunfinishedbusiness-win64-shipping.exe" ||
             exeName == "robocopunfinishedbusiness-wingdk-shipping.exe")
    {
        std::string_view pattern("84 C0 49 8B C7 74 03 49 8B C5 46 8B 34 30 E8 ? ? ? ? 84 C0 75");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 19);
        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // The Talos Principle: Reawakened
    else if (exeName == "talos1-win64-shipping.exe" || exeName == "talos1-wingdk-shipping.exe")
    {
        std::string_view pattern("84 C0 49 8B C6 74 03 49 8B C4 "
                                 "8B 34 06 E8 ? ? ? ? 84 C0 "
                                 "75 25");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 18);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // Mafia: The Old Country
    else if (exeName == "mafiatheoldcountry.exe")
    {
        std::string_view pattern("E8 ? ? ? ? 34 01 0F B6 C0 "
                                 "8B 3C 87 E8 ? ? ? ? 84 C0 "
                                 "0F 84");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 18);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // Palworld
    else if (exeName == "palworld-win64-shipping.exe" || exeName == "palworld-wingdk-shipping.exe")
    {
        std::string_view pattern("49 8B C6 74 03 49 8B C5 46 8B 3C 38 E8 ? ? ? ? 84 C0 75");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 17);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }

        // Disable dilated MVs
        std::string_view pattern2("83 FE ? 0F B6 C8");
        auto patchAddress2 = (void*) scanner::GetAddress(exeModule, pattern2, 2);

        if (patchAddress2 != nullptr)
        {
            std::vector<BYTE> patch = { 0x00 };
            patcher::PatchAddress(patchAddress2, &patch);
        }
    }

    // DOOM Eternal
    // just nops a line for main game exe
    { StringCompareType::exactMatch,
      "doometernalx64vk.exe",
      "80 3D ? ? ? ? ? 66 C7 05 ? ? ? ? ? ? 48 C7 05 ? ? ? ? ? ? ? ? 0F 84 ? ? ? ? 80 3D ? ? ? ? ? 0F 84 ? ? ? ? 48 8B "
      "? ? ? ? ? 48 8D", // aiming at the second 0F 84
      40,
      { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 } },

    // DOOM Eternal - Sandbox
    // nops a line for sandbox exe
    { StringCompareType::exactMatch,
      "doomsandbox64vk.exe",
      "48 C7 05 ? ? ? ? ? ? ? ? 0F 84 ? ? ? ? 80 3D ? ? ? ? ? 0F 84 ? ? ? ? 48 8B ? ? ? ? ? 48 8D",
      24,
      { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 } },

    // Red Dead Redemption 2
    // Thanks to 0x-FADED
    // https://github.com/0x-FADED/RDR2-NVNGX-Loader
    { StringCompareType::exactMatch,
      "rdr2.exe",
      "E8 ? ? ? ? 4C 8B CB 48 8D 54 24 60",
      -13,
      { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 },
      NOT_LAST_REQUIRED_PATTERN },
    { StringCompareType::exactMatch, "rdr2.exe", "80 3D ? ? ? ? ? 75 ? 41 8B CF", 6, { 0x01 } },
};

static void CheckForPatch()
{
    auto exeName = Util::ExePath().filename().string();
    std::transform(exeName.begin(), exeName.end(), exeName.begin(), ::tolower);
    auto exeModule = GetModuleHandle(nullptr);

    // First successful matched patten with lastPattern == true will end matching
    for (auto const& applicationPatch : applicationPatches)
    {
        if ((applicationPatch.compareType == StringCompareType::exactMatch &&
             exeName == applicationPatch.nameToMatch) ||
            (applicationPatch.compareType == StringCompareType::startsWith &&
             exeName.starts_with(applicationPatch.nameToMatch)))
        {
            auto patchAddress =
                (void*) scanner::GetAddress(exeModule, applicationPatch.pattern, applicationPatch.offset);
            if (patchAddress != nullptr)
            {
                patcher::PatchAddress(patchAddress, &applicationPatch.patch);

                if (applicationPatch.lastPattern)
                {
                    if (_patchResult.has_value() && !_patchResult.value()) // last patch was not successful
                        _patchResult = false;
                    else // first patch or previous patch was successful
                        _patchResult = true;

                    return;
                }
            }
            else
            {
                _patchResult = false;
            }
        }
    }

    if (!_patchResult.has_value())
        _patchResult = false;
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
