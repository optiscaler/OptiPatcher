# General Unreal Engine Pattern Finding Guide

## Used tools
* [x64dbg](https://x64dbg.com/)
* Nukem's [SwissArmyKnife](https://github.com/Nukem9/SwissArmyKnife) plugin for **x64dbg**

## Steps

### 1. Open games `Shipping` exe with **x64dbg**  
<img width="340" height="109" alt="image" src="https://github.com/user-attachments/assets/8b33c109-160f-402f-b12d-927f1d204a8d" />


### 2. Open module view
<img width="341" height="507" alt="image" src="https://github.com/user-attachments/assets/23c5f77f-5734-4ea4-9646-c9aa1b0da83e" />

### 3. Select games exe from list (double click it)
<img width="631" height="128" alt="image" src="https://github.com/user-attachments/assets/0520cf67-37d8-4cc9-aa53-ce631a05b24c" />

### 4. Finding IsNvidia() method
Open search pattern window  
<img width="673" height="442" alt="image" src="https://github.com/user-attachments/assets/1ef79d97-92d1-4c5a-b2d0-480f91f15c32" />

Paste `81 3D ?? ?? ?? ?? DE 10 00 00` and search
<img width="774" height="631" alt="image" src="https://github.com/user-attachments/assets/24ed17f0-81bf-4711-9145-79d5cfc164ee" />

Check results for the find correct method  
<img width="600" height="108" alt="image" src="https://github.com/user-attachments/assets/f5f9ccc6-06c5-4dde-9404-ca0c7c03d5ad" />

Correct method looks like this  
<img width="677" height="69" alt="image" src="https://github.com/user-attachments/assets/5eaf1865-9cbe-4a41-8111-101d2197a465" />

### 5. Finding the location of DLSS plugin call
Find the callers of this method first  
<img width="988" height="769" alt="image" src="https://github.com/user-attachments/assets/1b0ca019-503a-41ca-949f-1a03f4410cf9" />

Now boring part, we will check all these referances one by one  
<img width="596" height="748" alt="image" src="https://github.com/user-attachments/assets/6b96c0e8-675b-443b-94f2-4f695d8ab143" />

Correct calling point is not so hard to understand. Usually have a message like this just below  
<img width="1586" height="164" alt="image" src="https://github.com/user-attachments/assets/6c05b070-a660-4cc3-9374-e849d63e1c34" />

And usually one page above mention of ThirdParty plugins like this  
<img width="1561" height="578" alt="image" src="https://github.com/user-attachments/assets/5678c937-86e9-451c-b95b-a083151bf293" />

### 6. Generating the pattern
Select from 6-7 lines above call to jump after call like below  
<img width="848" height="159" alt="image" src="https://github.com/user-attachments/assets/4d866bac-d92e-4ded-b46b-5f169e99660d" />

Use **SwissArmyKnife** to generate pattern  
<img width="359" height="266" alt="image" src="https://github.com/user-attachments/assets/2084748f-60d3-4387-a8b8-7cc118f94cf0" />

Select **IDA** style  
<img width="683" height="217" alt="image" src="https://github.com/user-attachments/assets/70ae89b2-bb18-43e8-b383-6af1d9e27aa5" />

### 7. Finding the offset
I usually truncate last byte so final pattern will be like this.  
`84 C0 49 8B C7 74 03 49 8B C6 8B 34 30 89 75 80 E8 ? ? ? ? 84 C0 75`

We will patch the `84 C0` part so need to find offset of that.
```
00: 84 C0 49 8B C7 74 03 49 8B C6
10: 8B 34 30 89 75 80 E8 ?  ?  ?
20: ?  84 C0 75
       ^ 21th byte
```
Looks like it's 21th byte in pattern.

### 8. Generating code for patch
According to all the info we collected new if condution will be like below. 
**Exe name should be written in all lower case!**

```c++
    // WUCHANG: Fallen Feathers
    else if (exeName == "project_plague-win64-shipping.exe")
    {
        std::string_view pattern("84 C0 49 8B C7 74 03 49 8B C6 "
                                 "8B 34 30 89 75 80 E8 ?? ?? ?? "
                                 "?? 84 C0 75");

        auto patchAddress = (void*) scanner::GetAddress(exeModule, pattern, 21);

        if (patchAddress != nullptr)
        {
            std::vector<BYTE> patch = { 0x0C, 0x01 };
            patcher::PatchAddress(patchAddress, &patch);
            _patchResult = true;
        }
    }
```

### Happy hunting!
