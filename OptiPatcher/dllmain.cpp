// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#include "Util.h"
#include "Patcher.h"
#include "Scanner.h"

static bool _patchResult = false;

extern "C" __declspec(dllexport) bool PatchResult() { return _patchResult; }
extern "C" __declspec(dllexport) void InitializeASI() { return; }

#define CHECK_UE(name) exeName == (#name "-win64-shipping.exe") || exeName == (#name "-wingdk-shipping.exe")

static void CheckForPatch()
{
    auto exeName = Util::ExePath().filename().string();
    auto exeNameLower = std::transform(exeName.begin(), exeName.end(), exeName.begin(), ::tolower);
    auto exeModule = GetModuleHandle(nullptr);

    // Forgive Me Father 2, The Midnight Walk
    if (CHECK_UE(fmf2) || CHECK_UE(themidnightwalk))
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
    else if (CHECK_UE(sandfall) || CHECK_UE(fsd) || CHECK_UE(palworld) || CHECK_UE(tokyoxtremeracer) ||
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
    // else if (CHECK_UE(oblivionremastered))
    //{
    //    std::string_view pattern("C6 47 ? ? E9 ? ? ? ? 85 ? 7E ? 33 D2 44 8B ? 8D 4A");
    //    auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, -2);

    //    if (patchAddress != nullptr)
    //    {
    //        std::vector<BYTE> patch = { 0xEB };
    //        patcher::PatchAddress(patchAddress, &patch);
    //        _patchResult = true;
    //    }
    //}

    // Automation
    else if (CHECK_UE(automationgame))
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
    else if (CHECK_UE(bgg) || CHECK_UE(ranch_simulator))
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
    else if (CHECK_UE(talos2))
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
    else if (CHECK_UE(witchfire))
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
    else if (CHECK_UE(persistence))
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
    else if (CHECK_UE(b1))
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
    else if (CHECK_UE(banishers))
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
    else if (CHECK_UE(lop))
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

    // Ghostwire: Tokyo
    // inline patch, double test
    else if (exeName == "gwt.exe")
    {
        std::string_view pattern("E8 ? ? ? ? 84 C0 0F 84 ? "
                                 "? ? ? 81 3D ? ? ? ? ? "
                                 "? ? ? 0F 85 ? ? ? ? 85");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 13);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x39, 0xC0, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // Atomic Heart
    // inline patch
    else if (CHECK_UE(atomicheart))
    {
        std::string_view pattern("48 8B 4D 10 48 85 C9 74 05 E8 "
                                 "? ? ? ? 81 3D ? ? ? ? "
                                 "? ? ? ? 74");

        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 14);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x39, 0xC0, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // METAL GEAR SOLID Δ: SNAKE EATER
    // inline patch
    else if (CHECK_UE(mgsdelta))
    {
        std::string_view pattern("49 8B C5 74 03 49 8B C4 81 3D "
                                 "? ? ? ? ? ? ? ? 44 8B "
                                 "04 30");

        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 8);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x39, 0xC0, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // EVERSPACE 2
    // inline patch
    else if (CHECK_UE(es2))
    {
        std::string_view pattern("48 8D ? ? ? ? ? E8 ? ? "
                                 "? ? 81 3D ? ? ? ? ? ? "
                                 "? ? 0F 85 ? ? ? ? 85");

        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 12);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x39, 0xC0, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // Alone in the Dark 2024
    else if (CHECK_UE(aloneinthedark))
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

    // The Alters
    else if (CHECK_UE(thealters))
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
    else if (CHECK_UE(project_plague))
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
    else if (CHECK_UE(enotria))
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
    else if (CHECK_UE(theascent))
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
    else if (CHECK_UE(ghostrunner))
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
    else if (CHECK_UE(ghostrunner2))
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
    else if (CHECK_UE(deadlink))
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
    else if (CHECK_UE(amidevil))
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

    // Severed Steel demo, Achilles: Legends Untold, System Shock (2023), Trepang2, Pacific Drive, Frozenheim,
    // Loopmancer, Blacktail, The Lord of the Rings: Gollum™
    else if (CHECK_UE(thankyouverycool) || CHECK_UE(achilles) || CHECK_UE(systemreshock) || CHECK_UE(cppfps) ||
             CHECK_UE(pendriverpro) || CHECK_UE(frozenheim) || CHECK_UE(loopmancer) || CHECK_UE(blacktail) ||
             CHECK_UE(tom))
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
    else if (CHECK_UE(tq2))
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
    else if (CHECK_UE(robocop))
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

    // RoboCop: Unfinished Business, Ready or Not, NINJA GAIDEN 2 Black, Hell is Us (+ demo), Brothers: A Tale of Two Sons Remake
    else if (CHECK_UE(robocopunfinishedbusiness) || exeName == "readyornotsteam-win64-shipping.exe" ||
             exeName == "readyornot-wingdk-shipping.exe" || CHECK_UE(ninjagaiden2black) || CHECK_UE(hellisus) ||
             CHECK_UE(brothers))
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
    else if (CHECK_UE(talos1))
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
    else if (CHECK_UE(supraworld))
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
    else if (CHECK_UE(remnant2))
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
    else if (CHECK_UE(metaleden))
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

    // The First Berserker: Khazan
    else if (CHECK_UE(bbq))
    {
        std::string_view pattern("0F 84 ? ? ? ? E8 ? ? ? "
                                 "? E9 ? ? ? ? E8 ? ? ? "
                                 "? 84 C0 75");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 21);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // Sifu
    else if (CHECK_UE(sifu))
    {
        std::string_view pattern("74 05 E8 ? ? ? ? 45 33 F6 "
                                 "E9 ? ? ? ? E8 ? ? ? ? "
                                 "84 C0 75");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 20);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // Shadow Warrior 3: Definitive Edition
    else if (exeName == "sw3.exe")
    {
        std::string_view pattern("48 85 C9 74 05 E8 ? ? ? ? "
                                 "0F B6 47 30 E9 ? ? ? ? E8 "
                                 "? ? ? ? 84 C0 75 0B C6 47");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 24);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // Evil West
    else if (CHECK_UE(highmoon))
    {
        std::string_view pattern("74 05 E8 ? ? ? ? 4C 8D ? "
                                 "? ? ? ? EB 52 E8 ? ? ? "
                                 "? 84 C0 75");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 21);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // S.T.A.L.K.E.R. 2: Heart of Chornobyl
    else if (CHECK_UE(stalker2))
    {
        std::string_view pattern("84 C0 49 8B C6 74 03 49 8B C5 "
                                 "46 8B 3C 38 E8 ? ? ? ? 84 "
                                 "C0 75");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 19);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // VOID/BREAKER
    else if (CHECK_UE(voidbreaker))
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

    // SILENT HILL 2 Remake
    else if (CHECK_UE(shproto))
    {
        std::string_view pattern("84 C0 49 8B C6 74 03 49 8B C4 "
                                 "46 8B 3C 38 E8 ? ? ? ? 84 "
                                 "C0 75");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 19);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // Lords of the Fallen 2023
    else if (CHECK_UE(lotf2))
    {
        std::string_view pattern("84 C0 49 8B C6 74 03 49 8B C5 "
                                 "46 8B 3C 38 E8 ? ? ? ? 84 "
                                 "C0 75");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 19);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // Flintlock: The Siege of Dawn
    else if (CHECK_UE(saltpeter))
    {
        std::string_view pattern("0F 84 ? ? ? ? E8 ? ? ? "
                                 "? E9 ? ? ? ? E8 ? ? ? "
                                 "? 84 C0 75");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 21);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // Avowed
    else if (CHECK_UE(avowed))
    {
        std::string_view pattern("4C 89 AC 24 40 02 00 00 4C 89 "
                                 "B4 24 38 02 00 00 E8 ? ? ? "
                                 "? 84 C0 75");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 21);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // Eternal Strands
    else if (CHECK_UE(eternalstrandssteam))
    {
        std::string_view pattern("4C 89 A4 24 78 02 00 00 4C 89 "
                                 "B4 24 38 02 00 00 E8 ? ? ? "
                                 "? 84 C0 75");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 21);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // Lost Souls Aside
    else if (CHECK_UE(projectlsasteam))
    {
        std::string_view pattern("48 8B 4D 00 48 8B 44 24 40 48 "
                                 "89 45 E8 48 85 C9 74 05 E8 ? "
                                 "? ? ? E8 ? ? ? ? 84 C0 "
                                 "75 ");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 28);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // Ad Infinitum, INDIKA, High On Life, The Lord of the Rings: Return to Moria™
    else if (CHECK_UE(adinfinitum) || CHECK_UE(indika) || CHECK_UE(oregon) || CHECK_UE(moria))
    {
        std::string_view pattern("48 85 C9 74 05 E8 ? ? ? ? E8 "
                                 "? ? ? ? 84 C0 75");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 15);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // TEKKEN 8
    else if (CHECK_UE(polaris))
    {
        std::string_view pattern("49 8B C5 46 8B 3C 38 E8 ? ? "
                                 "? ? 84 C0 75");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 12);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }

    // Land of the Vikings
    else if (CHECK_UE(vikingoyunu))
    {
        std::string_view pattern("4C 8D ? ? ? ? ? E9 ? ? "
                                 "? ? E8 ? ? ? ? 84 C0 75");
        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 17);

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
    // Clair Obscur: Expedition 33, The Talos Principle 2, Hell is Us (+demo), Robocop: Rogue City,
    // Supraworld, The Talos Principle Reawakened, REMNANT II , The Elder Scrolls IV: Oblivion Remastered, Tokyo Xtreme
    // Racer/Shutokou Battle, Titan Quest II, 171, Hogwarts Legacy, Still Wakes the Deep, WUCHANG: Fallen
    // Feathers, RoboCop: Unfinished Business, Forgive me Father 2, Metal Eden demo, Enotria: The Last Song, Bloom&Rage,
    // The Alters, Ready or Not, S.T.A.L.K.E.R. 2: Heart of Chornobyl, VOID/BREAKER, SILENT HILL 2 Remake, NINJA GAIDEN
    // 2 Black, Flintlock: The Siege of Dawn, Avowed, Eternal Strands, Lost Souls Aside
    if (CHECK_UE(sandfall) || CHECK_UE(talos2) || CHECK_UE(hellisus) || CHECK_UE(robocop) || CHECK_UE(supraworld) ||
        CHECK_UE(talos1) || CHECK_UE(remnant2) || CHECK_UE(oblivionremastered) || CHECK_UE(tokyoxtremeracer) ||
        CHECK_UE(tq2) || CHECK_UE(bgg) || exeName == "stillwakesthedeep.exe" || exeName == "hogwartslegacy.exe" ||
        CHECK_UE(project_plague) || CHECK_UE(robocopunfinishedbusiness) || exeName == "bloom&rage.exe" ||
        CHECK_UE(fmf2) || CHECK_UE(metaleden) || CHECK_UE(enotria) || CHECK_UE(thealters) ||
        exeName == "readyornotsteam-win64-shipping.exe" || exeName == "readyornot-wingdk-shipping.exe" ||
        CHECK_UE(stalker2) || CHECK_UE(voidbreaker) || CHECK_UE(shproto) || CHECK_UE(ninjagaiden2black) ||
        CHECK_UE(saltpeter) || CHECK_UE(avowed) || CHECK_UE(eternalstrandssteam) || CHECK_UE(projectlsasteam))
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

    // DLSSG, Deep Rock Galactic, Black Myth: Wukong, Lords of the Fallen 2023
    else if (CHECK_UE(fsd) || CHECK_UE(b1) || CHECK_UE(lotf2))
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
    else if (CHECK_UE(banishers))
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
    else if (CHECK_UE(palworld))
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
    else if (CHECK_UE(witchfire) || CHECK_UE(ghostrunner2))
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

    // DLSSG, The First Berserker: Khazan
    else if (CHECK_UE(bbq))
    {
        std::string_view patternDLSSGCheck1("75 21 C7 05 ? ? ? ? ? ? "
                                            "? ? C6 05 ? ? ? ? ? B8 "
                                            "02 00 00 00 48 8B 5C 24 30 48 "
                                            "83 C4 20 5F C3 E8 ? ? ? ?");
        auto patchAddressDLSSGCheck1 = (void*) scanner::GetAddress(exeModule, patternDLSSGCheck1, 0);

        if (patchAddressDLSSGCheck1 != nullptr)
        {
            std::vector<BYTE> patch = { 0xEB };
            patcher::PatchAddress(patchAddressDLSSGCheck1, &patch);
        }

        std::string_view patternDLSSGCheck2("75 1B C7 05 ? ? ? ? ? ? "
                                            "? ? C6 05 ? ? ? ? ? B8 "
                                            "02 00 00 00 E9 ? ? ? ? E8 "
                                            "? ? ? ? 84");
        auto patchAddressDLSSGCheck2 = (void*) scanner::GetAddress(exeModule, patternDLSSGCheck2, 0);

        if (patchAddressDLSSGCheck2 != nullptr)
        {
            std::vector<BYTE> patch = { 0xEB };
            patcher::PatchAddress(patchAddressDLSSGCheck2, &patch);
        }

        _patchResult = patchAddressDLSSGCheck1 != nullptr;
    }

    // DLSSG, EVERSPACE 2
    else if (CHECK_UE(es2))
    {
        // DLSSG, Deep DVC
        std::string_view patternDLSSGCheck1("81 3D ? ? ? ? ? ? ? ? 0F 85 ? ? ? ? E8 ? ? ? ? 84 C0");
        auto patchAddressDLSSGCheck1 = (void*) scanner::GetAddress(exeModule, patternDLSSGCheck1, 0);

        if (patchAddressDLSSGCheck1 != nullptr)
        {
            std::vector<BYTE> patch = { 0x39, 0xC0, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
            patcher::PatchAddress(patchAddressDLSSGCheck1, &patch);
        }

        // Reflex
        std::string_view patternDLSSGCheck2("81 3D ? ? ? ? ? ? ? ? 75 78 E8 ? ? ? ? 84 C0");
        auto patchAddressDLSSGCheck2 = (void*) scanner::GetAddress(exeModule, patternDLSSGCheck2, 0);

        if (patchAddressDLSSGCheck2 != nullptr)
        {
            std::vector<BYTE> patch = { 0x39, 0xC0, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
            patcher::PatchAddress(patchAddressDLSSGCheck2, &patch);
        }

        // Late Warp
        std::string_view patternDLSSGCheck3("81 3D ? ? ? ? ? ? ? ? 75 57 E8 ? ? ? ? 84 C0");
        auto patchAddressDLSSGCheck3 = (void*) scanner::GetAddress(exeModule, patternDLSSGCheck3, 0);

        if (patchAddressDLSSGCheck3 != nullptr)
        {
            std::vector<BYTE> patch = { 0x39, 0xC0, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
            patcher::PatchAddress(patchAddressDLSSGCheck3, &patch);
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
