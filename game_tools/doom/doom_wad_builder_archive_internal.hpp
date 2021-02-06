#pragma once

#include <stddef.h>
#include <stdint.h>

#include "game_tools/allocator.hpp"
#include "game_tools/archive_reader.hpp"
#include "game_tools/archive_writer.hpp"

#include "game_tools/doom/shared.hpp"
#include "game_tools/doom/internal.hpp"
#include "game_tools/doom/doom_wad_builder_archive.hpp"

namespace wpieterse2825::scrapbook::game_tools::doom {
    class DoomWadBuilderArchiveInternal : public DoomWadBuilderArchive {
      public:
        DoomWadBuilderArchiveInternal(Allocator* allocator);
        virtual ~DoomWadBuilderArchiveInternal();

        virtual void Signature(DoomWadSignature signature) override;
        virtual void Entry(uint64_t name, ArchiveReader& archive) override;

        virtual size_t GetSize() override;

        virtual void Finalize(ArchiveWriter& archive) override;
        virtual void Reset() override;

      private:
        Allocator* _allocator;

        DoomWadHeader _header;
        DoomWadEntry* _entries;
        uint8_t*      _data;

        size_t _data_offset;
        size_t _file_offset;
    };
} // namespace wpieterse2825::scrapbook::game_tools::doom
