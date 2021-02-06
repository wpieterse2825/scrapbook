#include "game_tools/doom/doom_wad_reader_internal.hpp"
#include "game_tools/doom/doom_wad_builder_archive_internal.hpp"

#include "game_tools/doom/doom_factory_internal.hpp"

namespace wpieterse2825::scrapbook::game_tools::doom {
    DoomWadReader* DoomFactoryInternal::CreateWADReader(Allocator* allocator, ArchiveReader& archive) {
        return allocator->AllocateObject<DoomWadReaderInternal>(allocator, archive);
    }

    DoomWadBuilderArchive* DoomFactoryInternal::CreateWADBuilderArchive(Allocator* allocator) {
        return allocator->AllocateObject<DoomWadBuilderArchiveInternal>(allocator);
    }

} // namespace wpieterse2825::scrapbook::game_tools::doom
