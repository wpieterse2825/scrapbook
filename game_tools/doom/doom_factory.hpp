#pragma once

#include "game_tools/virtual_base.hpp"
#include "game_tools/allocator.hpp"
#include "game_tools/archive_reader.hpp"

#include "game_tools/doom/doom_wad_reader.hpp"
#include "game_tools/doom/doom_wad_builder_archive.hpp"

namespace wpieterse2825::scrapbook::game_tools::doom {
    class DoomFactory : public VirtualBase {
      public:
        virtual DoomWadReader*         CreateWADReader(Allocator* allocator, ArchiveReader& archive) = 0;
        virtual DoomWadBuilderArchive* CreateWADBuilderArchive(Allocator* allocator)                 = 0;
    };

    DoomFactory* GetDoomFactory();
} // namespace wpieterse2825::scrapbook::game_tools::doom
