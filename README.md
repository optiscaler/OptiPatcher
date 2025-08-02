## OptiPatcher
An **ASI Plugin for OptiScaler** to enable DLSS without spoofing in supported games. 

Currently supported games:
* 171
* Alone in the Dark 2024 (needs testing)
* Atomic Heart (needs testing)
* Banishers: Ghosts of New Eden
* Black Myth: Wukong
* Clair Obscur: Expedition 33
* Deadlink(only dx12 no XeSS mode)
* Deep Rock Galactic
* DOOM Eternal (+ Sandbox)
* Enotria: The Last Song
* Forgive Me Father 2
* Ghostrunner
* Ghostrunner 2
* Lies of P
* Lost Records: Bloom & Rage
* Ranch Simulator
* Red Dead Redemption 2 (thanks to **0x-FADED**)
* The Alters
* The Ascent
* The Elder Scrolls IV: Oblivion Remastered
* The Midnight Walk (Opti can't catch DLSS input yet)
* The Persistence
* The Talos Principle 2
* Witchfire
* WUCHANG: Fallen Feathers

  
### Installation
* Create a `plugins` folder where Opti is installed and put `OptiPatcher.asi` in this folder.  
* Enable ASI loading from `OptiScaler.ini` and disable Dxgi spoofing.
```ini
Dxgi=false
LoadAsiPlugins=true
```
<img width="1246" height="250" alt="Untitled" src="https://github.com/user-attachments/assets/08fa4617-50ab-4837-a6c5-a8bda365abb5" />


> [!NOTE]
> * There's a bug in OptiScaler currently where you have to set the plugin path for it to properly locate them  
> * Set `Path=plugins` in OptiScaler.ini (option right above `LoadAsiPlugins`)  

It should help Intel Arc users most because with newer versions of Unreal Engine spoofing has issues, causing D3D12 not supported errors.

**Warning** I have double checked patch patterns from my notes, but crashes might occur.
