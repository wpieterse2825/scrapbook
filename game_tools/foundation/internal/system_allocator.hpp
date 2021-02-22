// SPDX-License-Identifier: GPL-3.0

#pragma once

#include <stddef.h>
#include <stdint.h>

#include "foundation/allocator.hpp"

namespace wpieterse2825::game_tools::internal {
    class FSystemAllocator : public FAllocator {
      public:
        virtual void* Allocate(size_t buffer_size) override;
        virtual void  Deallocate(void* buffer) override;
    };
} // namespace wpieterse2825::game_tools::internal
