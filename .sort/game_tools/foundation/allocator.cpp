// SPDX-License-Identifier: GPL-3.0

#include "foundation/allocator.hpp"

#include "foundation/internal/system_allocator.hpp"

namespace wpieterse2825::game_tools {
    static internal::FSystemAllocator system_allocator {};

    FAllocator* GetSystemAllocator() {
        return &system_allocator;
    }
} // namespace wpieterse2825::game_tools
