#pragma once

#include <stdint.h>

#include "game_tools/archive.hpp"

#include "game_tools/doom/shared.hpp"

namespace wpieterse2825::scrapbook::game_tools::doom {
    struct DoomWadHeader {
        DoomWadSignature signature;
        uint32_t         file_table_entries;
        uint32_t         file_table_offset;
    };

    struct DoomWadEntry {
        uint32_t offset;
        uint32_t size;
        uint64_t name;
    };

    static inline Archive& operator&(Archive& archive, DoomWadSignature& value) {
        archive.Serialize(&value, sizeof(value));

        return archive;
    }

    static inline Archive& operator&(Archive& archive, DoomWadHeader& value) {
        archive& value.signature;
        archive& value.file_table_entries;
        archive& value.file_table_offset;

        return archive;
    }

    static inline Archive& operator&(Archive& archive, DoomWadEntry& value) {
        archive& value.offset;
        archive& value.size;
        archive& value.name;

        return archive;
    }
} // namespace wpieterse2825::scrapbook::game_tools::doom
