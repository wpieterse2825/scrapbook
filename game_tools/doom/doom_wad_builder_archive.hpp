#pragma once

#include <stddef.h>

#include "game_tools/archive_writer.hpp"

#include "game_tools/doom/doom_wad_builder.hpp"

namespace wpieterse2825::scrapbook::game_tools::doom {
    class DoomWadBuilderArchive : public DoomWadBuilder {
      public:
        virtual size_t GetSize() = 0;

        virtual void Finalize(ArchiveWriter& archive) = 0;
        virtual void Reset()                          = 0;
    };
} // namespace wpieterse2825::scrapbook::game_tools::doom
