// SPDX-License-Identifier: GPL-3.0

#pragma once

#include <stdint.h>

#include <array>

namespace wpieterse2825::game_tools::formats::id_tech_0::wad {
    uint64_t            StringToName(const char* name);
    std::array<char, 9> NameToString(uint64_t name);
} // namespace wpieterse2825::game_tools::formats::id_tech_0::wad
