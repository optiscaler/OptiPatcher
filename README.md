## OptiPatcher
An **ASI Plugin for OptiScaler** to enable DLSS without spoofing in supported games.  

It should help Intel Arc users most because with newer versions of Unreal Engine spoofing has issues, causing D3D12 not supported errors.  

### Installation
* Create a `plugins` folder where Opti is installed and put `OptiPatcher.asi` in this folder.  
* Enable ASI loading from `OptiScaler.ini` and disable Dxgi spoofing (_Opti automatically does this part since 0.7.7-pre13_0731 so `Dxgi=false` isn't needed_).
```ini
Dxgi=false
LoadAsiPlugins=true
```
<img width="1246" height="250" alt="Untitled" src="https://github.com/user-attachments/assets/08fa4617-50ab-4837-a6c5-a8bda365abb5" />


> [!NOTE]
> _**Shouldn't be required with latest Nightly 0731 anymore**_
> * ~There's a bug in OptiScaler currently where you have to set the plugin path for it to properly locate them~  
> * ~Set `Path=plugins` in OptiScaler.ini (option right above `LoadAsiPlugins`)~

**Warning** I have double checked patch patterns from my notes, but crashes might occur.

---

### Currently supported games:
* 171
* Achilles: Legends Untold
* Alone in the Dark 2024 (needs testing)
* Amid Evil
* ARK: Survival Ascended  
* Atomic Heart (needs testing)
* Banishers: Ghosts of New Eden
* Black Myth: Wukong
* Clair Obscur: Expedition 33
* Deadlink (only dx12 no XeSS mode)
* Deep Rock Galactic
* DOOM Eternal (+ Sandbox)
* Enotria: The Last Song
* Forgive Me Father 2
* Ghostrunner
* Ghostrunner 2
* Hogwarts Legacy
* LEGO® Builder's Journey (unlock DLSS entry, but no inputs to Opti, needs testing)
* Lies of P
* Lost Records: Bloom & Rage
* Ranch Simulator
* Red Dead Redemption 2 (thanks to **0x-FADED**)
* Robocop Rogue City (XeFG and DLSS check patched, but check [special notes](#special-notes))
* Severed Steel
* Still Wakes the Deep
* The Alters
* The Ascent
* The Elder Scrolls IV: Oblivion Remastered
* The Midnight Walk (Opti can't catch DLSS input yet)
* The Persistence
* The Talos Principle 2
* Titan Quest II
* Witchfire
* WUCHANG: Fallen Feathers

  
> [!NOTE]
> ### Special notes
> * Robocop Rogue City DLSS plugin is patched, but due to extra checks when not spoofing, requires setting `UpscalingMethod=2` in **GameUserSettings.ini** in `AppData\Local\RoboCop\Saved\Config\Windows` (also maybe `NvidiaReflexLowLatency=1` if it isn't exposed already)  
> * To get XeFG 2.1 for non-Intel GPUs, just replace the XeSS files in `Robocop Rogue City\Engine\Plugins\Runtime\Intel\XeSS\Binaries\ThirdParty\Win64`  
