// SPDX-License-Identifier: GPL-3.0

#pragma once

#include <stdint.h>

namespace wpieterse2825::game_tools::formats::id_tech_0::wad {
    enum class ESignature : uint32_t {
        Base      = 0x44415749,
        Extension = 0x44415750,
    };
} // namespace wpieterse2825::game_tools::formats::id_tech_0::wad
