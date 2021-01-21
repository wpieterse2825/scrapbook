#pragma once

#include "frameworks/core/types/internal.hpp"

namespace next_mode::core::types::detail {
    struct Character_Common_General {
        using ASCIICharacter = char;
        using WideCharacter  = wchar_t;
        using UTF8Character  = unsigned char;
        using UTF16Character = unsigned short;
        using UTF32Character = unsigned int;
    };
} // namespace next_mode::core::types::detail
