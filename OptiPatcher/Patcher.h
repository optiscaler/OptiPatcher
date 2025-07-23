#pragma once

#include "pch.h"

#include <vector>

namespace patcher
{
void PatchAddress(void* address, const std::vector<BYTE>* patch);
} // namespace patcher
