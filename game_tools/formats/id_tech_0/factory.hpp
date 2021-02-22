// SPDX-License-Identifier: GPL-3.0

#pragma once

#include "foundation/virtual_base.hpp"
#include "foundation/allocator.hpp"
#include "foundation/archive_reader.hpp"

#include "formats/id_tech_0/wad/reader.hpp"
#include "formats/id_tech_0/wad/builder_archive.hpp"

namespace wpieterse2825::game_tools::formats::id_tech_0 {
    class FFactory : public FVirtualBase {
      public:
        virtual wad::FReader*         CreateWADReader(FAllocator* allocator, FArchiveReader& archive) = 0;
        virtual wad::FBuilderArchive* CreateWADBuilderArchive(FAllocator* allocator)                  = 0;
    };

    FFactory* GetFactory();
} // namespace wpieterse2825::game_tools::formats::id_tech_0
