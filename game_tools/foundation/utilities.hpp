// SPDX-License-Identifier: GPL-3.0

#pragma once

#include <stdint.h>

#include <array>
#include <iostream>

#include "foundation/allocator.hpp"

namespace wpieterse2825::game_tools {
    uint8_t* ReadCompleteFile(FAllocator* allocator, const char* filename, size_t* buffer_size);
} // namespace wpieterse2825::game_tools
