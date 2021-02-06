#pragma once

#include <cstdint>
#include <array>
#include <iostream>

template <std::size_t ArraySize>
inline std::ostream& operator<<(std::ostream& stream, const std::array<char, ArraySize>& array) {
    stream << array.begin();

    return stream;
}

namespace wpieterse2825::scrapbook::game_tools {
    struct ReadFileResult {
        uint8_t* buffer;
        size_t   buffer_size;
    };

    ReadFileResult ReadFile(const char* name);
} // namespace wpieterse2825::scrapbook::game_tools
