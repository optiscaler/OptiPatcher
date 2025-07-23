#include "pch.h"

#include "Patcher.h"

void patcher::PatchAddress(void* address, const std::vector<BYTE>* patch)
{
    DWORD oldProtect;

    VirtualProtect(address, patch->size(), PAGE_EXECUTE_READWRITE, &oldProtect);

    std::memcpy(address, patch->data(), patch->size());

    VirtualProtect(address, patch->size(), oldProtect, &oldProtect);

    FlushInstructionCache(GetCurrentProcess(), address, patch->size());
}
