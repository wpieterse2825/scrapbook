// SPDX-License-Identifier: GPL-3.0

#include "formats/id_tech_0/internal/factory.hpp"

#include "g3log/g3log.hpp"

#include "formats/id_tech_0/wad/internal/reader.hpp"
#include "formats/id_tech_0/wad/internal/builder_archive.hpp"

namespace wpieterse2825::game_tools::formats::id_tech_0::internal {
    wad::FReader* FFactoryInternal::CreateWADReader(FAllocator* allocator, FArchiveReader& archive) {
        CHECK(allocator != nullptr) << "Allocator cannot be null.";

        return allocator->AllocateObject<wad::internal::FReaderInternal>(allocator, archive);
    }

    wad::FBuilderArchive* FFactoryInternal::CreateWADBuilderArchive(FAllocator* allocator) {
        CHECK(allocator != nullptr) << "Allocator cannot be null.";

        return allocator->AllocateObject<wad::internal::FBuilderArchiveInternal>(allocator);
    }
} // namespace wpieterse2825::game_tools::formats::id_tech_0::internal
