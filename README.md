## OptiPatcher
An **ASI Plugin for OptiScaler** for exposing DLSS/DLSS-FG inputs without spoofing in supported games.  

> [!NOTE]
> * It should help Intel Arc users most because with newer versions of Unreal Engine spoofing has issues, causing `D3D12 not supported` errors.  
> * Now with DLSSG patching, all AMD/Intel users benefit too.  


### Installation
* Create a `plugins` folder where Opti is installed and put `OptiPatcher.asi` in this folder.  
* Enable ASI loading from `OptiScaler.ini`
* ~and disable Dxgi spoofing~ (_Opti automatically does this part since 0.7.7-pre13_0731 so `Dxgi=false` isn't needed anymore_).

```ini
LoadAsiPlugins=true
```
<img width="1246" height="250" alt="Untitled" src="https://github.com/user-attachments/assets/08fa4617-50ab-4837-a6c5-a8bda365abb5" />


> [!NOTE]
> _**Shouldn't be required with latest Nightly 0731 anymore**_
> * ~There's a bug in OptiScaler currently where you have to set the plugin path for it to properly locate them~  
> * ~Set `Path=plugins` in OptiScaler.ini (option right above `LoadAsiPlugins`)~

**Warning** I have double checked patch patterns from my notes, but crashes might occur.

---

### Currently supported games with DLSS patch:
* 171
* Achilles: Legends Untold
* Alone in the Dark 2024 - _needs testing_
* Amid Evil
* ARK: Survival Ascended  
* Atomic Heart - _needs testing_
* Automation - The Car Company Tycoon Game
* Banishers: Ghosts of New Eden
* Black Myth: Wukong
* Clair Obscur: Expedition 33 - _both DLSS and DLSS-FG_
* Deadlink - _only dx12, no XeSS mode_
* Deep Rock Galactic - _both DLSS and DLSS-FG_
* DOOM Eternal (+ Sandbox)
* Enotria: The Last Song
* Forgive Me Father 2
* Ghostrunner
* Ghostrunner 2 - _both DLSS and DLSS-FG (requires retoggling FG on every boot if not working)_
* Hell is Us demo - _both DLSS and DLSS-FG_
* Hogwarts Legacy - _both DLSS and DLSS-FG_
* LEGO® Builder's Journey - _unlock DLSS entry, but no inputs to Opti, needs testing_
* Lies of P
* Lost Records: Bloom & Rage
* Mafia: The Old Country
* Palworld
* Ranch Simulator
* Red Dead Redemption 2 (thanks to **0x-FADED**)
* REMNANT II - _both DLSS and DLSS-FG_
* Robocop Rogue City - _XeFG and DLSS/DLSS-FG check patched, but check [special notes](#special-notes)_
* Robocop Unfinished Business - _DLSS check patched, but check [special notes](#special-notes)_
* Severed Steel
* Still Wakes the Deep
* Supraworld - _both DLSS and DLSS-FG_
* The Alters
* The Ascent
* The Elder Scrolls IV: Oblivion Remastered
* The Midnight Walk - _Opti can't catch DLSS input yet_
* The Persistence
* The Talos Principle 2 - _both DLSS and DLSS-FG_
* The Talos Principle: Reawakened - _both DLSS and DLSS-FG_
* Titan Quest II - _both DLSS and DLSS-FG_
* Tokyo Xtreme Racer/Shutokou Battle - _both DLSS and DLSS-FG_
* Witchfire - _both DLSS and DLSS-FG_
* WUCHANG: Fallen Feathers

  
> [!NOTE]
> ### Special notes
> * Robocop Rogue City and Unfinished Business DLSS plugin is patched, but due to extra checks when not spoofing, to expose DLSS/DLSS-FG properly, requires setting `UpscalingMethod=2` in **GameUserSettings.ini** in `AppData\Local\RoboCop\Saved\Config\Windows` (also maybe `NvidiaReflexLowLatency=1` if it isn't exposed already)  
> * To get XeFG 2.1 for non-Intel GPUs, just replace the XeSS files in `Robocop Rogue City\Engine\Plugins\Runtime\Intel\XeSS\Binaries\ThirdParty\Win64`  
