#pragma once

#include <stdint.h>

#include "game_tools/virtual_base.hpp"
#include "game_tools/archive_reader.hpp"

#include "game_tools/doom/shared.hpp"

namespace wpieterse2825::scrapbook::game_tools::doom {
    class DoomWadBuilder : public VirtualBase {
      public:
        virtual void Signature(DoomWadSignature signature)        = 0;
        virtual void Entry(uint64_t name, ArchiveReader& archive) = 0;
    };
} // namespace wpieterse2825::scrapbook::game_tools::doom
