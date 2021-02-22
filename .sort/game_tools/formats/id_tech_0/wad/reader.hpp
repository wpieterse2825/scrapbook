// SPDX-License-Identifier: GPL-3.0

#pragma once

#include <stdint.h>

#include "foundation/virtual_base.hpp"
#include "foundation/memory_archive_reader.hpp"

#include "formats/id_tech_0/wad/signature.hpp"

namespace wpieterse2825::game_tools::formats::id_tech_0::wad {
    constexpr auto SInvalidEntry = uint32_t {0xFFFFFFFF};

    class FReader : public FVirtualBase {
      public:
        virtual ESignature Signature()  = 0;
        virtual uint32_t   EntryCount() = 0;

        virtual uint32_t IndexForName(uint64_t name)                                                     = 0;
        virtual uint32_t IndexForNameAfter(uint64_t name, uint64_t start_name)                           = 0;
        virtual uint32_t IndexForNameBetween(uint64_t name, uint64_t prefix_name, uint64_t postfix_name) = 0;

        virtual uint64_t             IndexName(uint32_t index)    = 0;
        virtual uint32_t             IndexSize(uint32_t index)    = 0;
        virtual FMemoryArchiveReader IndexArchive(uint32_t index) = 0;
    };
} // namespace wpieterse2825::game_tools::formats::id_tech_0::wad
