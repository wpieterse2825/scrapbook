#include "game_tools/system_allocator.hpp"

#include "game_tools/allocator.hpp"

namespace wpieterse2825::scrapbook::game_tools {
    static SystemAllocator system_allocator{};

    Allocator* GetSystemAllocator() {
        return &system_allocator;
    }
} // namespace wpieterse2825::scrapbook::game_tools
