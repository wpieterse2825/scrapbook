#pragma once

#include <stdint.h>

#include "game_tools/allocator.hpp"
#include "game_tools/archive_reader.hpp"
#include "game_tools/memory_archive_reader.hpp"

#include "game_tools/doom/shared.hpp"
#include "game_tools/doom/internal.hpp"
#include "game_tools/doom/doom_wad_reader.hpp"

namespace wpieterse2825::scrapbook::game_tools::doom {
    class DoomWadReaderInternal : public DoomWadReader {
      public:
        DoomWadReaderInternal(Allocator* allocator, ArchiveReader& archive);
        virtual ~DoomWadReaderInternal();

        virtual DoomWadSignature Signature() override;
        virtual uint32_t         EntryCount() override;

        virtual uint32_t IndexForName(uint64_t name) override;
        virtual uint32_t IndexForNameAfter(uint64_t name, uint64_t start_name) override;
        virtual uint32_t IndexForNameBetween(uint64_t name, uint64_t prefix_name, uint64_t postfix_name) override;

        virtual uint64_t            IndexName(uint32_t index) override;
        virtual uint32_t            IndexSize(uint32_t index) override;
        virtual MemoryArchiveReader IndexArchive(uint32_t index) override;

      private:
        Allocator* _allocator;

        DoomWadHeader _header;
        DoomWadEntry* _entries;
        uint8_t*      _data;
        size_t        _data_size;
    };
} // namespace wpieterse2825::scrapbook::game_tools::doom
