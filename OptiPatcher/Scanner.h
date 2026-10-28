#pragma once

#include "pch.h"

#include <cstdint>
#include <vector>
#include <algorithm>
#include <string_view>

namespace scanner
{
uintptr_t GetAddress(const std::wstring_view moduleName, const std::string_view pattern, ptrdiff_t offset = 0,
                     uintptr_t startAddress = 0);
uintptr_t GetAddress(HMODULE module, const std::string_view pattern, ptrdiff_t offset = 0, uintptr_t startAddress = 0);
uintptr_t GetAddressFromWholeModule(HMODULE module, const std::string_view pattern, ptrdiff_t offset,
                                    uintptr_t startAddress = 0);
// Scans every committed, readable region of the module image (no reliance on PE section flags, never touches
// unreadable pages). For packed/protected executables whose code is only decrypted at runtime.
uintptr_t GetAddressSafe(HMODULE module, const std::string_view pattern, ptrdiff_t offset = 0);
uintptr_t GetOffsetFromInstruction(HMODULE module, const std::string_view pattern, ptrdiff_t offset);
} // namespace scanner
