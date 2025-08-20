// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#include "Util.h"
#include "Patcher.h"
#include "Scanner.h"

static bool _patchResult = false;

extern "C" __declspec(dllexport) bool PatchResult() { return _patchResult; }
extern "C" __declspec(dllexport) void InitializeASI() { return; }

static void CheckForPatch()
{
    auto exeName = Util::ExePath().filename().string();
    auto exeNameLower = std::transform(exeName.begin(), exeName.end(), exeName.begin(), ::tolower);
    auto exeModule = GetModuleHandle(nullptr);

    // Forgive Me Father 2, The Midnight Walk
    if (exeName == "fmf2-win64-shipping.exe" || exeName == "fmf2-wingdk-shipping.exe" ||
        exeName == "themidnightwalk-win64-shipping.exe" || exeName == "themidnightwalk-wingdk-shipping.exe")
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

    // Clair Obscur: Expedition 33, Deep Rock Galactic, Palworld, Tokyo Xtreme Racer/Shutokou Battle, Hogwarts Legacy
    else if (exeName == "sandfall-win64-shipping.exe" || exeName == "sandfall-wingdk-shipping.exe" ||
             exeName == "fsd-win64-shipping.exe" || exeName == "fsd-wingdk-shipping.exe" ||
             exeName == "palworld-win64-shipping.exe" || exeName == "palworld-wingdk-shipping.exe" ||
             exeName == "tokyoxtremeracer-win64-shipping.exe" || exeName == "tokyoxtremeracer-wingdk-shipping.exe" ||
             exeName == "hogwartslegacy.exe")
    {
        std::string_view pattern("C6 47 ? ? E9 ? ? ? ? 45 85 ? 7E ? 33 D2 45 8B ? 8D 4A");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, -2);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0xEB };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // The Elder Scrolls IV: Oblivion Remastered
    else if (exeName == "oblivionremastered-win64-shipping.exe" || exeName == "oblivionremastered-wingdk-shipping.exe")
    {
        std::string_view pattern("C6 47 ? ? E9 ? ? ? ? 85 ? 7E ? 33 D2 44 8B ? 8D 4A");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, -2);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0xEB };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // Automation
    else if (exeName == "automationgame-win64-shipping.exe" || exeName == "automationgame-wingdk-shipping.exe")
    {
        std::string_view pattern("E8 ? ? ? ? 84 C0 75 ? 80 3D ? ? ? ? ? 72 ? 48 8D 05 ? ? ? ? 41 B9 ? ? ? ? 4C 8D 05 ? "
                                 "? ? ? 48 89 44 24 ? 33 D2 33 C9 E8 ? ? ? ? 48 8D 77");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 7);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0xEB };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // 171, Ranch Simulator
    else if (exeName == "bgg-win64-shipping.exe" || exeName == "bgg-wingdk-shipping.exe" ||
             exeName == "ranch_simulator-win64-shipping.exe" || exeName == "ranch_simulator-wingdk-shipping.exe")
    {
        std::string_view pattern("49 8B C7 74 03 49 8B C5 46 8B "
                                 "34 30 E8 ? ? ? ? 84 C0 75");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 17);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // The Talos Principle 2
    else if (exeName == "talos2-win64-shipping.exe" || exeName == "talos2-wingdk-shipping.exe")
    {
        std::string_view pattern("42 8B 34 36 E8 ? ? ? ? 84 C0 75");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 11);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0xEB };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // Witchfire
    else if (exeName == "witchfire-win64-shipping.exe" || exeName == "witchfire-wingdk-shipping.exe")
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
    else if (exeName == "persistence-win64-shipping.exe" || exeName == "persistence-wingdk-shipping.exe")
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

    // Lost Records: Bloom & Rage
    else if (exeName == "bloom&rage.exe")
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

    // Black Myth: Wukong
    else if (exeName == "b1-win64-shipping.exe" || exeName == "b1-wingdk-shipping.exe")
    {
        std::string_view pattern("E8 ? ? ? ? 84 C0 49 8B C4 "
                                 "74 03 49 8B C6 8B 34 30 89 75 "
                                 "80 E8 ? ? ? ? 84 C0 75");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 26);

        // Check for benchmark
        if (patchAddress == nullptr)
        {
            std::string_view pattern2("49 8B C6 74 03 49 8B C5 46 8B "
                                      "3C 38 E8 ? ? ? ? 84 C0 75");
            patchAddress = (void*) scanner::GetAddress(exeModule, pattern2, 17);
        }

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // Banishers: Ghosts of New Eden
    // inline patch
    else if (exeName == "banishers-win64-shipping.exe" || exeName == "banishers-wingdk-shipping.exe")
    {
        std::string_view pattern("C6 00 ? E9 ? ? ? ? 85 ? 7E ? 33 D2 44 8B ? 8D 4A");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, -11);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0xEB };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // Lies of P
    // inline patch
    else if (exeName == "lop-win64-shipping.exe" || exeName == "lop-wingdk-shipping.exe")
    {
        std::string_view pattern("41 B9 1B 00 00 00 C7 44 24 20 "
                                 "02 00 00 00 48 8D ? ? ? ? "
                                 "? 48 8D 4D 68 45 8D 41 E9 E8 "
                                 "? ? ? ? 48 8B 4D 10 48 85 "
                                 "C9 74 05 E8 ? ? ? ? 81 3D "
                                 "? ? ? ? ? ? ? ? 74 0D");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 48);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x39, 0xC0, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // ARK: Survival Ascended
    // inline patch
    else if (exeName == "arkascended.exe")
    {
        std::string_view pattern("E8 ? ? ? ? 84 C0 74 02 B0 "
                                 "01 84 C0 49 8B C5 74 03 49 8B "
                                 "C4 81 3D ? ? ? ? ? ? ? "
                                 "? 44 8B 04 30");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 21);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x39, 0xC0, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // Alone in the Dark 2024
    else if (exeName == "aloneinthedark-win64-shipping.exe" || exeName == "aloneinthedark-wingdk-shipping.exe")
    {
        std::string_view pattern("4C 8B 65 F0 33 C0 48 8B 4D 48 "
                                 "4C 89 65 C0 48 89 45 F0 48 89 "
                                 "45 F8 48 85 C9 74 05 E8 ? ? "
                                 "? ? E8 ? ? ? ? 84 C0 75");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 37);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // Atomic Heart
    else if (exeName == "atomicheart-win64-shipping.exe" || exeName == "atomicheart-wingdk-shipping.exe")
    {
        std::string_view pattern("4C 8B 7D F0 33 C0 48 8B 4D 40 "
                                 "4C 89 7D C0 48 89 45 F0 48 89 "
                                 "45 F8 48 85 C9 74 05 E8 ? ? "
                                 "? ? E8 ? ? ? ? 84 C0 75");

        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 37);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // The Alters
    else if (exeName == "thealters-win64-shipping.exe" || exeName == "thealters-wingdk-shipping.exe")
    {
        std::string_view pattern("E8 ? ? ? ? 84 C0 75 0C E8 "
                                 "? ? ? ? 84 C0 49 8B C7 74 "
                                 "03 49 8B C6 8B 34 30 E8 ? ? "
                                 "? ? 84 C0 75");

        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 32);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // WUCHANG: Fallen Feathers
    else if (exeName == "project_plague-win64-shipping.exe" || exeName == "project_plague-wingdk-shipping.exe")
    {
        std::string_view pattern("75 0C E8 ? ? ? ? 84 C0 49 "
                                 "8B C7 74 03 49 8B C6 8B 34 30 "
                                 "89 75 80 E8 ? ? ? ? 84 C0 "
                                 "75");

        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 28);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // Enotria: The Last Song
    else if (exeName == "enotria-win64-shipping.exe" || exeName == "enotria-wingdk-shipping.exe")
    {
        std::string_view pattern("84 C0 49 8B C7 74 03 49 8B C5 "
                                 "46 8B 34 30 E8 ? ? ? ? 84 "
                                 "C0 75");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 19);
        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // The Ascent
    else if (exeName == "theascent-win64-shipping.exe" || exeName == "theascent-wingdk-shipping.exe")
    {
        std::string_view pattern("48 85 C9 74 05 E8 ? ? ? ? "
                                 "45 33 ED E9 ? ? ? ? E8 ? "
                                 "? ? ? 84 C0");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 23);
        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // Ghostrunner
    else if (exeName == "ghostrunner-win64-shipping.exe" || exeName == "ghostrunner-wingdk-shipping.exe")
    {
        std::string_view pattern("75 14 44 88 6F 30");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 0);
        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0xEB };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // Ghostrunner 2
    else if (exeName == "ghostrunner2-win64-shipping.exe" || exeName == "ghostrunner2-wingdk-shipping.exe")
    {
        std::string_view pattern("48 85 C9 74 05 E8 ? ? ? ? "
                                 "E8 ? ? ? ? 84 C0 75 ");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 15);
        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // Deadlink
    else if (exeName == "deadlink-win64-shipping.exe" || exeName == "deadlink-wingdk-shipping.exe")
    {
        std::string_view pattern("48 85 C9 74 05 E8 ? ? ? ? "
                                 "E8 ? ? ? ? 84 C0 75");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 15);
        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // Amid Evil
    else if (exeName == "amidevil-win64-shipping.exe" || exeName == "amidevil-wingdk-shipping.exe")
    {
        std::string_view pattern("48 85 DB 74 08 48 8B CB E8 ? "
                                 "? ? ? E8 ? ? ? ? 84 C0 75");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 18);
        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // Severed Steel
    else if (exeName == "thankyouverycool-win64-shipping.exe" || exeName == "thankyouverycool-wingdk-shipping.exe")
    {
        std::string_view pattern("48 85 C9 74 05 E8 ? ? ? ? E8 ? ? ? ? 84 C0 75 ");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 15);
        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // Achilles: Legends Untold
    else if (exeName == "achilles-win64-shipping.exe" || exeName == "achilles-wingdk-shipping.exe")
    {
        std::string_view pattern("48 85 C9 74 05 E8 ? ? ? ? E8 ? ? ? ? 84 C0 75");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 15);
        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // LEGO® Builder's Journey
    else if (exeName == "unityplayer.exe")
    {
        std::string_view pattern("48 8D 15 ? ? ? ? 48 89 D9 E8 ? ? ? ? 48 83 F8 FF");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 15);
        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0xB8, 0x00, 0x00, 0x00, 0x00 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // Titan Quest II
    else if (exeName == "tq2-win64-shipping.exe" || exeName == "tq2-wingdk-shipping.exe")
    {
        std::string_view pattern("84 C0 49 8B C6 74 03 49 8B C4 "
                                 "8B 34 30 E8 ? ? ? ? 84 C0 "
                                 "75 25");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 18);
        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

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
    else if (exeName == "robocop-win64-shipping.exe" || exeName == "robocop-wingdk-shipping.exe")
    {
        std::string_view patternDLSSCheck("74 03 49 8B C5 46 8B 3C 38 E8 "
                                          "? ? ? ? 84 C0 75");
        auto patchAddressDLSSCheck = (void*) scanner::GetAddress(exeModule, patternDLSSCheck, 14);

        if (patchAddressDLSSCheck != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddressDLSSCheck, &patch);
        }

        std::string_view patternXeFGCheck("83 F8 03 0F 85 ? ? ? ? E8 "
                                          "? ? ? ? 84 C0 0F 84");
        auto patchAddressXeFGCheck = (void*) scanner::GetAddress(exeModule, patternXeFGCheck, 14);

        if (patchAddressXeFGCheck != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddressXeFGCheck, &patch);
        }

        _patchResult = patchAddressDLSSCheck != nullptr;
    }

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

    // Supraworld
    else if (exeName == "supraworld-win64-shipping.exe" || exeName == "supraworld-wingdk-shipping.exe")
    {
        std::string_view pattern("49 8B C7 74 03 49 8B C5 46 8B "
                                 "34 30 E8 ? ? ? ? 84 C0 75");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 17);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // REMNANT II
    else if (exeName == "remnant2-win64-shipping.exe" || exeName == "remnant2-wingdk-shipping.exe")
    {
        std::string_view pattern("74 03 49 8B C4 46 8B 34 30 E8 "
                                 "? ? ? ? 84 C0 75");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 14);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // METAL EDEN demo
    else if (exeName == "metaleden-win64-shipping.exe" || exeName == "metaleden-wingdk-shipping.exe")
    {
        std::string_view pattern("74 03 49 8B C4 8B 34 30 E8 ? "
                                 "? ? ? 84 C0 75");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 13);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // DOOM Eternal
    // just nops a line for main game exe
    else if (exeName == "doometernalx64vk.exe")
    {
        std::string_view pattern("80 3D ? ? ? ? ? 66 C7 05 "
                                 "? ? ? ? ? ? 48 C7 05 ? "
                                 "? ? ? ? ? ? ? 0F 84 ? "
                                 "? ? ? 80 3D ? ? ? ? ? "
                                 "0F 84 ? ? ? ? 48 8B ? ? " // aiming at 0F 84
                                 "? ? ? 48 8D");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 40);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // DOOM Eternal - Sandbox
    // nops a line for sandbox exe
    else if (exeName == "doomsandbox64vk.exe")
    {
        std::string_view pattern("48 C7 05 ? ? ? ? ? ? ? "
                                 "? 0F 84 ? ? ? ? 80 3D ? "
                                 "? ? ? ? 0F 84 ? ? ? ? "
                                 "48 8B ? ? ? ? ? 48 8D");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 24);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // Red Dead Redemption 2
    // Thanks to 0x-FADED
    // https://github.com/0x-FADED/RDR2-NVNGX-Loader
    else if (exeName == "rdr2.exe")
    {
        std::string_view patternGPUCheck("E8 ? ? ? ? 4C 8B CB 48 8D 54 24 60");
        auto patchAddressGPU = (void*) scanner::GetAddress(exeModule, patternGPUCheck, -13);

        if (patchAddressGPU != nullptr)
        {
            std::vector<BYTE> patch = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
            patcher::PatchAddress(patchAddressGPU, &patch);
        }

        std::string_view patternSigCheck("80 3D ? ? ? ? ? 75 ? 41 8B CF");
        auto patchAddressSigCheck = (void*) scanner::GetAddress(exeModule, patternSigCheck, 6);

        if (patchAddressSigCheck != nullptr)
        {
            std::vector<BYTE> patch = { 0x01 };
            patcher::PatchAddress(patchAddressSigCheck, &patch);
        }

        _patchResult = patchAddressGPU != nullptr && patchAddressSigCheck != nullptr;
    }

    // DLSSG / Extra

    // DLSSG
    // Clair Obscur: Expedition 33, The Talos Principle 2, Hell is Us demo, Robocop: Rogue City,
    // Supraworld, The Talos Principle Reawakened, REMNANT II , The Elder Scrolls IV: Oblivion Remastered, Tokyo Xtreme
    // Racer/Shutokou Battle, Titan Quest II, 171, Hogwarts Legacy, Still Wakes the Deep, WUCHANG: Fallen
    // Feathers, RoboCop: Unfinished Business, Forgive me Father 2, Metal Eden demo, Enotria: The Last Song, Bloom&Rage
    if (exeName == "sandfall-win64-shipping.exe" || exeName == "sandfall-wingdk-shipping.exe" ||
        exeName == "talos2-win64-shipping.exe" || exeName == "talos2-wingdk-shipping.exe" ||
        exeName == "hellisus-win64-shipping.exe" || exeName == "hellisus-wingdk-shipping.exe" ||
        exeName == "robocop-win64-shipping.exe" || exeName == "robocop-wingdk-shipping.exe" ||
        exeName == "supraworld-win64-shipping.exe" || exeName == "supraworld-wingdk-shipping.exe" ||
        exeName == "talos1-win64-shipping.exe" || exeName == "talos1-wingdk-shipping.exe" ||
        exeName == "remnant2-win64-shipping.exe" || exeName == "remnant2-wingdk-shipping.exe" ||
        exeName == "oblivionremastered-win64-shipping.exe" || exeName == "oblivionremastered-wingdk-shipping.exe" ||
        exeName == "tokyoxtremeracer-win64-shipping.exe" || exeName == "tokyoxtremeracer-wingdk-shipping.exe" ||
        exeName == "tq2-win64-shipping.exe" || exeName == "tq2-wingdk-shipping.exe" ||
        exeName == "bgg-win64-shipping.exe" || exeName == "bgg-wingdk-shipping.exe" ||
        exeName == "stillwakesthedeep.exe" || exeName == "hogwartslegacy.exe" ||
        exeName == "project_plague-win64-shipping.exe" || exeName == "project_plague-wingdk-shipping.exe" ||
        exeName == "robocopunfinishedbusiness-win64-shipping.exe" ||
        exeName == "robocopunfinishedbusiness-wingdk-shipping.exe" || exeName == "bloom&rage.exe" ||
        exeName == "fmf2-win64-shipping.exe" || exeName == "fmf2-wingdk-shipping.exe" ||
        exeName == "metaleden-win64-shipping.exe" || exeName == "metaleden-wingdk-shipping.exe" ||
        exeName == "enotria-win64-shipping.exe" || exeName == "enotria-wingdk-shipping.exe")
    {
        std::string_view pattern("75 ? C7 05 ? ? ? ? 02 00 00 00 B8 02 00 00 00");
        uintptr_t start = 0;
        void* patchAddress = nullptr;
        do
        {
            patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 0, start);
            if (patchAddress != nullptr)
            {
                std::vector<BYTE> patch = { 0xEB };
                patcher::PatchAddress(patchAddress, &patch);
                start = (uintptr_t) patchAddress;
            }
        } while (patchAddress != nullptr);
    }

    // DLSSG, Deep Rock Galactic, Black Myth: Wukong
    else if (exeName == "fsd-win64-shipping.exe" || exeName == "fsd-wingdk-shipping.exe" ||
             exeName == "b1-win64-shipping.exe" || exeName == "b1-wingdk-shipping.exe")
    {
        std::string_view pattern2("75 ? B9 ? ? ? ? C6 05 ? ? ? ? ? 89 0D");
        auto patchAddress2 = (void*) scanner::GetAddress(exeModule, pattern2, 0);

        if (patchAddress2 != nullptr)
        {
            std::vector<BYTE> patch = { 0xEB };
            patcher::PatchAddress(patchAddress2, &patch);
        }
    }

    // DLSSG, Banishers
    else if (exeName == "banishers-win64-shipping.exe" || exeName == "banishers-wingdk-shipping.exe")
    {
        // Makes the game always tag resources, this means that DLSSG inputs work but Nukem's mod doesn't
        std::string_view pattern2("48 83 EC ? E8 ? ? ? ? 84 C0 75 ? 48 83 C4 ? C3 65 48 8B 04 25 ? ? ? ? BA");
        auto patchAddress2 = (void*) scanner::GetAddress(exeModule, pattern2, 11);

        if (patchAddress2 != nullptr)
        {
            std::vector<BYTE> patch = { 0x90, 0x90 };
            patcher::PatchAddress(patchAddress2, &patch);
        }
    }

    // Disable dilated MVs, Palworld
    else if (exeName == "palworld-win64-shipping.exe" || exeName == "palworld-wingdk-shipping.exe")
    {
        std::string_view pattern2("83 FE ? 0F B6 C8");
        auto patchAddress2 = (void*) scanner::GetAddress(exeModule, pattern2, 2);

        if (patchAddress2 != nullptr)
        {
            std::vector<BYTE> patch = { 0x00 };
            patcher::PatchAddress(patchAddress2, &patch);
        }
    }

    // DLSSG, Witchfire, Ghostrunner 2
    else if (exeName == "witchfire-win64-shipping.exe" || exeName == "witchfire-wingdk-shipping.exe" ||
             exeName == "ghostrunner2-win64-shipping.exe" || exeName == "ghostrunner2-wingdk-shipping.exe")
    {
        std::string_view patternDLSSGCheck1("75 11 B8 02 00 00 00 C6 05 ? "
                                            "? ? ? ? E9 ? ? ? ? E8 "
                                            "? ? ? ? 84");
        auto patchAddressDLSSGCheck1 = (void*) scanner::GetAddress(exeModule, patternDLSSGCheck1, 0);

        if (patchAddressDLSSGCheck1 != nullptr)
        {
            std::vector<BYTE> patch = { 0xEB };
            patcher::PatchAddress(patchAddressDLSSGCheck1, &patch);
        }

        std::string_view patternDLSSGCheck2("75 19 B9 02 00 00 00 C6 05 ? "
                                            "? ? ? ? 89 ? ? ? ? ? "
                                            "8B C1 48 83 C4 28 C3 E8 ? ? "
                                            "? ? 84");
        auto patchAddressDLSSGCheck2 = (void*) scanner::GetAddress(exeModule, patternDLSSGCheck2, 0);

        if (patchAddressDLSSGCheck2 != nullptr)
        {
            std::vector<BYTE> patch = { 0xEB };
            patcher::PatchAddress(patchAddressDLSSGCheck2, &patch);
        }

        _patchResult = patchAddressDLSSGCheck1 != nullptr;
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
