// SPDX-License-Identifier: GPL-3.0

#pragma once

#include <stddef.h>
#include <stdint.h>

#include "foundation/archive.hpp"

#include "formats/id_tech_0/wad/signature.hpp"

namespace wpieterse2825::game_tools::formats::id_tech_0::wad::internal {
    constexpr auto SMaximumFileSize   = size_t {2} * 1024 * 1024 * 2014;
    constexpr auto SMaximumEntryCount = size_t {2} * 1024 * 1024 * 1024;

    struct FHeader {
        ESignature signature;
        uint32_t   file_table_entries;
        uint32_t   file_table_offset;
    };

    static inline FArchive& operator&(FArchive& archive, ESignature& value) {
        archive.Serialize(&value, sizeof(value));

        return archive;
    }

    static inline FArchive& operator&(FArchive& archive, FHeader& value) {
        archive& value.signature;
        archive& value.file_table_entries;
        archive& value.file_table_offset;

        return archive;
    }
} // namespace wpieterse2825::game_tools::formats::id_tech_0::wad::internal
