#pragma once

#include "pch.h"

#include <filesystem>

namespace Util
{
std::filesystem::path ExePath();
std::filesystem::path DllPath(HMODULE dllModule);
} // namespace Util
