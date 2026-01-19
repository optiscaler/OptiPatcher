# OptiPatcher
An **ASI Plugin for OptiScaler** for exposing DLSS/DLSS-FG inputs without spoofing in **supported games**.  

> [!NOTE]
> * **For AMD and Intel users!**
> * _Helps Intel Arc users a lot because newer versions of Unreal Engine have issues with spoofing, causing `D3D12 not supported` errors._
> * **OptiPatcher helps avoid performance overhead or crashes/artifacts caused by Dxgi spoofing!**
> * _All patches are made for the **latest game version** at the time of committing!_

<div align="center">
  <a href="https://discord.gg/wEyd9w4hG5"><img src="https://img.shields.io/badge/OptiScaler-blue?style=for-the-badge&logo=discord&logoColor=white&logoSize=auto&color=5865F2" alt="Discord invite"></a>
  <a href="https://github.com/optiscaler/OptiPatcher/blob/main/GameSupport.md"><img src="https://img.shields.io/badge/Supported%20games-blue?style=for-the-badge&logo=gitbook&logoColor=white&logoSize=auto" alt="Supported games"></a>
  <a href="https://github.com/optiscaler/OptiPatcher/releases"><img src="https://img.shields.io/badge/Releases-download-green?style=for-the-badge&logo=github&logoSize=auto" alt="Release"></a>
  <a href="https://github.com/optiscaler/OptiPatcher/releases"><img src="https://img.shields.io/github/downloads/optiscaler/optipatcher/total?style=for-the-badge&logo=gitextensions&logoSize=auto&label=Total" alt="Total DL"></a>
  <a href="https://github.com/optiscaler/OptiPatcher/stargazers"><img src="https://img.shields.io/github/stars/optiscaler/optipatcher?style=for-the-badge&logo=githubsponsors&logoColor=white&label=S.T.A.R.S." alt="Stars"></a>
</div>

## Currently supported games
* Check the [Game Support list](GameSupport.md)

## Installation
_**Recommended to use OptiScaler 0.7.8 or above**_
* Create a `plugins` folder where Opti is installed and put `OptiPatcher.asi` in this folder.  
* Enable ASI loading from `OptiScaler.ini`

```ini
LoadAsiPlugins=true
```

<img width="1237" height="294" alt="pluginsmerged" src="https://github.com/user-attachments/assets/08206326-3ba8-4a8d-928f-b1c29dcd9f19" />
<img width="744" height="181" alt="loadasiplugins" src="https://github.com/user-attachments/assets/79003cee-7238-4be0-b47e-55f16123e53c" />

**Warning** We have double checked patch patterns, but crashes might occur.

## Example of properly applied patch
* With OptiScaler **0.7.9 and newer**, when OptiPatcher applies properly, the game title will have an **(OP)** mention and **Spoof** will say **OFF**
  * _Opti 0.7.8 won't have the OP part in the title, but Spoof will still be OFF_

![OptiPatcher](https://github.com/user-attachments/assets/ecb581fe-3aa2-4e10-a21b-af9c973f1ba7)

