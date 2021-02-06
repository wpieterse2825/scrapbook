#include <assert.h>
#include <string.h>

#include "game_tools/doom/shared.hpp"

namespace wpieterse2825::scrapbook::game_tools::doom {
    uint64_t StringToDoomName(const char* name) {
        auto name_length    = strlen(name);
        auto name_converted = std::array<uint8_t, 8> {};

        assert(name_length <= 8);

        for (auto name_index = size_t {0}; name_index < name_length; name_index++) {
            name_converted[name_index] = name[name_index];
        }

        auto part_0 = uint64_t {name_converted[0]} << 0;
        auto part_1 = uint64_t {name_converted[1]} << 8;
        auto part_2 = uint64_t {name_converted[2]} << 16;
        auto part_3 = uint64_t {name_converted[3]} << 24;
        auto part_4 = uint64_t {name_converted[4]} << 32;
        auto part_5 = uint64_t {name_converted[5]} << 40;
        auto part_6 = uint64_t {name_converted[6]} << 48;
        auto part_7 = uint64_t {name_converted[7]} << 56;

        return part_0 | part_1 | part_2 | part_3 | part_4 | part_5 | part_6 | part_7;
    }

    std::array<char, 9> DoomNameToString(uint64_t name) {
        auto name_converted = std::array<char, 9> {};

        name_converted[0] = (name >> 0) & 0xFF;
        name_converted[1] = (name >> 8) & 0xFF;
        name_converted[2] = (name >> 16) & 0xFF;
        name_converted[3] = (name >> 24) & 0xFF;
        name_converted[4] = (name >> 32) & 0xFF;
        name_converted[5] = (name >> 40) & 0xFF;
        name_converted[6] = (name >> 48) & 0xFF;
        name_converted[7] = (name >> 56) & 0xFF;

        return name_converted;
    }
} // namespace wpieterse2825::scrapbook::game_tools::doom
