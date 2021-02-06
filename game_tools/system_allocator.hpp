#pragma once

#include <stddef.h>
#include <stdint.h>

#include "game_tools/allocator.hpp"

namespace wpieterse2825::scrapbook::game_tools {
    class SystemAllocator : public Allocator {
      public:
        virtual void* Allocate(size_t buffer_size) override;
        virtual void  Deallocate(void* buffer) override;
    };
} // namespace wpieterse2825::scrapbook::game_tools
