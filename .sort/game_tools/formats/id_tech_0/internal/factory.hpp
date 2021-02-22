// SPDX-License-Identifier: GPL-3.0

#pragma once

#include "foundation/allocator.hpp"
#include "foundation/archive_reader.hpp"

#include "formats/id_tech_0/factory.hpp"
#include "formats/id_tech_0/wad/reader.hpp"
#include "formats/id_tech_0/wad/builder_archive.hpp"

namespace wpieterse2825::game_tools::formats::id_tech_0::internal {
    class FFactoryInternal : public FFactory {
      public:
        virtual wad::FReader*         CreateWADReader(FAllocator* allocator, FArchiveReader& archive) override;
        virtual wad::FBuilderArchive* CreateWADBuilderArchive(FAllocator* allocator) override;
    };
} // namespace wpieterse2825::game_tools::formats::id_tech_0::internal
