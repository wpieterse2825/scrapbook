// SPDX-License-Identifier: GPL-3.0

#pragma once

#include <stdint.h>

#include "foundation/virtual_base.hpp"
#include "foundation/archive_reader.hpp"

#include "formats/id_tech_0/wad/signature.hpp"

namespace wpieterse2825::game_tools::formats::id_tech_0::wad {
    class FBuilder : public FVirtualBase {
      public:
        virtual void Signature(ESignature signature)               = 0;
        virtual void Entry(uint64_t name, FArchiveReader& archive) = 0;
    };
} // namespace wpieterse2825::game_tools::formats::id_tech_0::wad
