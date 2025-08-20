## Currently supported games

---

<!--
TEMPLATE FOR NEW ENTRIES
| GAME NAME           | ✔️/❌ | ✅/⛔ | Notes go here                | 
-->

| Game | DLSS | DLSS-FG | Notes  | 
| ---- | :--: | :-----: | ------ |
| 171 | ✔️ | ✅ |  |
| Achilles: Legends Untold | ✔️ | N/A |  |
| Alone in the Dark 2024 | ✔️ | N/A | _Needs testing_ | 
| Amid Evil | ✔️ | N/A |  |
| ARK: Survival Ascended | ✔️ |  |  |
| Atomic Heart | ✔️ |  | _Needs testing_ | 
| Automation - The Car Company Tycoon Game | ✔️ | N/A |  |
| Banishers: Ghosts of New Eden | ✔️ |  |  |
| Black Myth: Wukong | ✔️ |  |  |
| Clair Obscur: Expedition 33 | ✔️ | ✅ |  |
| Cyberpunk 2077 | ✔️ | N/A | Needs CyberEngineTweaks to load ASI |
| Deadlink | ✔️ | N/A | _Only DX12, no XeSS mode_ |
| Deep Rock Galactic | ✔️ | ✅ |  |
| DOOM Eternal (+ Sandbox) | ✔️ | N/A | _Sandbox exe also supported, RT working_ |
| Enotria: The Last Song | ✔️ | ✅ |  |
| Forgive Me Father 2 | ✔️ | ✅ |  |
| Ghostrunner | ✔️ | N/A |  |
| Ghostrunner 2 | ✔️ | ✅ | _Requires retoggling FG on every boot if not working_ | 
| Hell is Us demo | ✔️ | ✅ |  | 
| Hogwarts Legacy | ✔️ | ✅ |  |
| LEGO® Builder's Journey | ✔️ | N/A | _Unlocks DLSS entry, but no inputs to Opti, needs testing_ |
| Lies of P | ✔️ | N/A |  |
| Lost Records: Bloom & Rage | ✔️ | ✅ |  |
| Mafia: The Old Country | ✔️ |  |  |
| Metal Eden demo | ✔️ | ✅ |  |
| Palworld | ✔️ | N/A |  |
| Ranch Simulator | ✔️ | N/A |  |
| Red Dead Redemption 2 | ✔️ | N/A | _Check [link](https://github.com/optiscaler/OptiScaler/issues/388#issuecomment-3173010106) for install, thanks to 0x-FADED_ |
| REMNANT II | ✔️ | ✅ |  |
| Robocop Rogue City | ✔️ | ✅ | _XeFG and DLSS/DLSS-FG check patched, but check [special notes](#special-notes)_ | 
| Robocop Unfinished Business | ✔️ | ✅ | _DLSS/DLSS-FG check patched, but check [special notes](#special-notes)_ | 
| Severed Steel | ✔️ | N/A |  |
| Still Wakes the Deep | ✔️ | ✅ |  |
| Supraworld | ✔️ | ✅ |  |
| The Alters | ✔️ |  |  |
| The Ascent | ✔️ | N/A |  |
| The Elder Scrolls IV: Oblivion Remastered | ✔️ |  |  |
| The Midnight Walk | ✔️ |  | _Opti can't catch DLSS input yet_ | 
| The Persistence | ✔️ | N/A |  |
| The Talos Principle 2 | ✔️ | ✅ |  |
| The Talos Principle: Reawakened | ✔️ | ✅ |  |
| Titan Quest II | ✔️ | ✅ |  |
| Tokyo Xtreme Racer/Shutokou Battle | ✔️ | ✅ |  |
| Witchfire | ✔️ | ✅ |  |
| WUCHANG: Fallen Feathers | ✔️ | ✅ |  |

---

> [!NOTE]
> ### Special notes
> * Robocop Rogue City and Unfinished Business DLSS plugin is patched, but due to extra checks when not spoofing, to expose DLSS/DLSS-FG properly, requires setting `UpscalingMethod=2` in **GameUserSettings.ini** in `AppData\Local\RoboCop\Saved\Config\Windows` (also maybe `NvidiaReflexLowLatency=1` if it isn't exposed already) - for Robocop Unfinished Business `AppData\Local\RoboCopUnfinishedBusiness\Saved\Config\Windows`  
> * To get XeFG 2.1 for non-Intel GPUs, just replace the XeSS files in `Robocop Rogue City\Engine\Plugins\Runtime\Intel\XeSS\Binaries\ThirdParty\Win64`  
