// SPDX-License-Identifier: GPL-3.0

#include <stdlib.h>

#include "g3log/g3log.hpp"

#include "foundation/internal/system_allocator.hpp"

namespace wpieterse2825::game_tools::internal {
    void* FSystemAllocator::Allocate(size_t buffer_size) {
        auto result = ::malloc(buffer_size);

        CHECK(result != nullptr) << "Failed to allocate memory.";
        return result;
    }

    void FSystemAllocator::Deallocate(void* buffer) {
        CHECK(buffer != nullptr) << "Cannot deallocate a null pointer.";

        ::free(buffer);
    }
} // namespace wpieterse2825::game_tools::internal
