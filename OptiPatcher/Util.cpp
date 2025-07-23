#include "pch.h"

#include "Util.h"

std::filesystem::path Util::DllPath(HMODULE dllModule)
{
    static std::filesystem::path dll;

    if (dll.empty())
    {
        wchar_t dllPath[MAX_PATH];
        GetModuleFileNameW(dllModule, dllPath, MAX_PATH);
        dll = std::filesystem::path(dllPath);
    }

    return dll;
}

std::filesystem::path Util::ExePath()
{
    static std::filesystem::path exe;

    if (exe.empty())
    {
        wchar_t exePath[MAX_PATH];
        GetModuleFileNameW(nullptr, exePath, MAX_PATH);
        exe = std::filesystem::path(exePath);
    }

    return exe;
}
