#pragma once

#include <stdint.h>

#include "game_tools/virtual_base.hpp"
#include "game_tools/memory_archive_reader.hpp"

#include "game_tools/doom/shared.hpp"

namespace wpieterse2825::scrapbook::game_tools::doom {
    class DoomWadReader : public VirtualBase {
      public:
        virtual DoomWadSignature Signature()  = 0;
        virtual uint32_t         EntryCount() = 0;

        virtual uint32_t IndexForName(uint64_t name)                                                     = 0;
        virtual uint32_t IndexForNameAfter(uint64_t name, uint64_t start_name)                           = 0;
        virtual uint32_t IndexForNameBetween(uint64_t name, uint64_t prefix_name, uint64_t postfix_name) = 0;

        virtual uint64_t            IndexName(uint32_t index)    = 0;
        virtual uint32_t            IndexSize(uint32_t index)    = 0;
        virtual MemoryArchiveReader IndexArchive(uint32_t index) = 0;
    };
} // namespace wpieterse2825::scrapbook::game_tools::doom
