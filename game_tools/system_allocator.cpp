#include <assert.h>
#include <stdlib.h>

#include "game_tools/system_allocator.hpp"

namespace wpieterse2825::scrapbook::game_tools {
    void* SystemAllocator::Allocate(size_t buffer_size) {
        auto result = ::malloc(buffer_size);

        assert(result != nullptr);
        return result;
    }

    void SystemAllocator::Deallocate(void* buffer) {
        assert(buffer != nullptr);

        ::free(buffer);
    }
} // namespace wpieterse2825::scrapbook::game_tools
