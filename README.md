## OptiPatcher
An ASI Plugin for OptiScaler to enable DLSS without spoofing in supported games. 

Currently supported games:
* 171
* Banishers
* Black Myth: Wukong
* Clair Obscure
* Deep Rock Galactic
* Forgive Me Father 2
* Oblivion Remastered
* Persistence
* Red Dead Redemtion 2 (thanks to **0x-FADED**)
* Talos Principle 2
* The Midnight Walk (Opti can't catch DLSS input yet)
* Witchfire
  
### Installation
Create a `plugins` folder and put `OptiPatcher.asi` in this folder. 
Enable ASI loading from `OptiScaler.ini` and disable Dxgi spoofing.
```ini
Dxgi=false
LoadAsiPlugins=true
```

It should help Intel Arc users most because with newer versions of Unreal Engine spoofing have issues, causing D3D12 not supported errors.

**Warning** I have double checked patch patterns from my notes but crashes might occur.
