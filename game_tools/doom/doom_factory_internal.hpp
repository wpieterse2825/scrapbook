#pragma once

#include "game_tools/doom/doom_factory.hpp"

namespace wpieterse2825::scrapbook::game_tools::doom {
    class DoomFactoryInternal : public DoomFactory {
      public:
        virtual DoomWadReader* CreateReader(Allocator* allocator, ArchiveReader& archive) override;
        virtual DoomWadBuilderArchive* CreateBuilderArchive(Allocator* allocator) override;
    };
} // namespace wpieterse2825::scrapbook::game_tools::doom
