#pragma once

#include <stddef.h>
#include <stdint.h>

#include <array>

namespace wpieterse2825::scrapbook::game_tools::doom {
    constexpr auto DoomWadInvalidEntry   = uint32_t {0xFFFFFFFF};
    constexpr auto DoomWadMaximumEntries = size_t {2} * 1024 * 1024 * 1024;
    constexpr auto DoomWadMaximumSize    = size_t {2} * 1024 * 1024 * 2014;

    enum class DoomWadSignature : uint32_t {
        Base      = 0x44415749,
        Extension = 0x44415750,
    };

    uint64_t StringToDoomName(const char* name);
    std::array<char, 9> DoomNameToString(uint64_t name);
} // namespace wpieterse2825::scrapbook::game_tools::doom
