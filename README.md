# OptiPatcher
An **ASI Plugin for OptiScaler** for exposing DLSS/DLSS-FG inputs without spoofing in supported games.  

> [!NOTE]
> * It should help Intel Arc users most because with newer versions of Unreal Engine spoofing has issues, causing `D3D12 not supported` errors.  
> * Now with DLSSG patching, all AMD/Intel users benefit too.  

## Currently supported games
* Check the [Game Support list](GameSupport.md)

## Installation
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

**Warning** We have double checked patch patterns, but crashes might occur.
