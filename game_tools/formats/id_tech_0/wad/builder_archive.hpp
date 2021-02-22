// SPDX-License-Identifier: GPL-3.0

#pragma once

#include <stddef.h>

#include "foundation/archive_writer.hpp"

#include "formats/id_tech_0/wad/builder.hpp"

namespace wpieterse2825::game_tools::formats::id_tech_0::wad {
    class FBuilderArchive : public FBuilder {
      public:
        virtual size_t GetSize() = 0;

        virtual void Finalize(FArchiveWriter& archive) = 0;
        virtual void Reset()                           = 0;
    };
} // namespace wpieterse2825::game_tools::formats::id_tech_0::wad
