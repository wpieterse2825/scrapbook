// SPDX-License-Identifier: GPL-3.0

#pragma once

#include <stdint.h>

#include "foundation/archive.hpp"

namespace wpieterse2825::game_tools::formats::id_tech_0::wad::internal {
    struct FEntry {
        uint32_t offset;
        uint32_t size;
        uint64_t name;
    };

    static inline FArchive& operator&(FArchive& archive, FEntry& value) {
        archive& value.offset;
        archive& value.size;
        archive& value.name;

        return archive;
    }
} // namespace wpieterse2825::game_tools::formats::id_tech_0::wad::internal
