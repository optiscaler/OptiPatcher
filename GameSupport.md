## Currently supported games

---

<!--
TEMPLATE FOR NEW ENTRIES
| GAME NAME           | ✔️/❌ | ✅/⛔ | Notes go here                | 
-->

| Game | DLSS | DLSS-FG | Notes  | 
| ---- | :--: | :-----: | ------ |
| 171 | ✔️ |  |  |
| Achilles: Legends Untold | ✔️ |  |  |
| Alone in the Dark 2024 | ✔️ |  | _needs testing_ | 
| Amid Evil | ✔️ |  |  |
| ARK: Survival Ascended | ✔️ |  |  |
| Atomic Heart | ✔️ |  | _needs testing_ | 
| Automation - The Car Company Tycoon Game | ✔️ |  |  |
| Banishers: Ghosts of New Eden | ✔️ |  |  |
| Black Myth: Wukong | ✔️ |  |  |
| Clair Obscur: Expedition 33 | ✔️ | ✅ |  |
| Deadlink | ✔️ |  | _only dx12, no XeSS mode_ |
| Deep Rock Galactic | ✔️ | ✅ |  |
| DOOM Eternal (+ Sandbox) | ✔️ | N/A |  |
| Enotria: The Last Song | ✔️ |  |  |
| Forgive Me Father 2 | ✔️ |  |  |
| Ghostrunner | ✔️ |  |  |
| Ghostrunner 2 | ✔️ | ✅ | _requires retoggling FG on every boot if not working_ | 
| Hell is Us demo | ✔️ | ✅ |  | 
| Hogwarts Legacy | ✔️ | ✅ |  |
| LEGO® Builder's Journey | ✔️ |  | _unlock DLSS entry, but no inputs to Opti, needs testing_ |
| Lies of P | ✔️ | N/A |  |
| Lost Records: Bloom & Rage | ✔️ |  |  |
| Mafia: The Old Country | ✔️ |  |  |
| Palworld | ✔️ |  |  |
| Ranch Simulator | ✔️ |  |  |
| Red Dead Redemption 2 | ✔️ | N/A | _thanks to 0x-FADED_ |
| REMNANT II | ✔️ | ✅ |  |
| Robocop Rogue City | ✔️ | ✅ | _XeFG and DLSS/DLSS-FG check patched, but check [special notes](#special-notes)_ | 
| Robocop Unfinished Business | ✔️ |  | _DLSS check patched, but check [special notes](#special-notes)_ | 
| Severed Steel | ✔️ |  |  |
| Still Wakes the Deep | ✔️ |  |  |
| Supraworld | ✔️ | ✅ |  |
| The Alters | ✔️ |  |  |
| The Ascent | ✔️ |  |  |
| The Elder Scrolls IV: Oblivion Remastered | ✔️ |  |  |
| The Midnight Walk | ✔️ |  | _Opti can't catch DLSS input yet_ | 
| The Persistence | ✔️ |  |  |
| The Talos Principle 2 | ✔️ | ✅ |  |
| The Talos Principle: Reawakened | ✔️ | ✅ |  |
| Titan Quest II | ✔️ | ✅ |  |
| Tokyo Xtreme Racer/Shutokou Battle | ✔️ | ✅ |  |
| Witchfire | ✔️ | ✅ |  |
| WUCHANG: Fallen Feathers | ✔️ |  |  |

---

> [!NOTE]
> ### Special notes
> * Robocop Rogue City and Unfinished Business DLSS plugin is patched, but due to extra checks when not spoofing, to expose DLSS/DLSS-FG properly, requires setting `UpscalingMethod=2` in **GameUserSettings.ini** in `AppData\Local\RoboCop\Saved\Config\Windows` (also maybe `NvidiaReflexLowLatency=1` if it isn't exposed already)  
> * To get XeFG 2.1 for non-Intel GPUs, just replace the XeSS files in `Robocop Rogue City\Engine\Plugins\Runtime\Intel\XeSS\Binaries\ThirdParty\Win64`  
