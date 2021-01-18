#pragma once

#include "frameworks/core/types/internal.hpp"

namespace next_mode::core::types::detail {
    struct Pack_Common_General {
        using Pack_Signed8_1     = std::array<signed char, 1>;
        using Pack_Signed8_2     = std::array<signed char, 2>;
        using Pack_Signed8_4     = std::array<signed char, 4>;
        using Pack_Signed8_8     = std::array<signed char, 8>;
        using Pack_Signed8_16    = std::array<signed char, 16>;
        using Pack_Signed8_32    = std::array<signed char, 32>;
        using Pack_Signed8_64    = std::array<signed char, 64>;
        using Pack_Signed16_1    = std::array<signed short, 1>;
        using Pack_Signed16_2    = std::array<signed short, 2>;
        using Pack_Signed16_4    = std::array<signed short, 4>;
        using Pack_Signed16_8    = std::array<signed short, 8>;
        using Pack_Signed16_16   = std::array<signed short, 16>;
        using Pack_Signed16_32   = std::array<signed short, 32>;
        using Pack_Signed32_1    = std::array<signed int, 1>;
        using Pack_Signed32_2    = std::array<signed int, 2>;
        using Pack_Signed32_4    = std::array<signed int, 4>;
        using Pack_Signed32_8    = std::array<signed int, 8>;
        using Pack_Signed32_16   = std::array<signed int, 16>;
        using Pack_Signed64_1    = std::array<signed long long, 1>;
        using Pack_Signed64_2    = std::array<signed long long, 2>;
        using Pack_Signed64_4    = std::array<signed long long, 4>;
        using Pack_Signed64_8    = std::array<signed long long, 8>;
        using Pack_Unsigned8_1   = std::array<unsigned char, 1>;
        using Pack_Unsigned8_2   = std::array<unsigned char, 2>;
        using Pack_Unsigned8_4   = std::array<unsigned char, 4>;
        using Pack_Unsigned8_8   = std::array<unsigned char, 8>;
        using Pack_Unsigned8_16  = std::array<unsigned char, 16>;
        using Pack_Unsigned8_32  = std::array<unsigned char, 32>;
        using Pack_Unsigned8_64  = std::array<unsigned char, 64>;
        using Pack_Unsigned16_1  = std::array<unsigned short, 1>;
        using Pack_Unsigned16_2  = std::array<unsigned short, 2>;
        using Pack_Unsigned16_4  = std::array<unsigned short, 4>;
        using Pack_Unsigned16_8  = std::array<unsigned short, 8>;
        using Pack_Unsigned16_16 = std::array<unsigned short, 16>;
        using Pack_Unsigned16_32 = std::array<unsigned short, 32>;
        using Pack_Unsigned32_1  = std::array<unsigned int, 1>;
        using Pack_Unsigned32_2  = std::array<unsigned int, 2>;
        using Pack_Unsigned32_4  = std::array<unsigned int, 4>;
        using Pack_Unsigned32_8  = std::array<unsigned int, 8>;
        using Pack_Unsigned32_16 = std::array<unsigned int, 16>;
        using Pack_Unsigned64_1  = std::array<unsigned long long, 1>;
        using Pack_Unsigned64_2  = std::array<unsigned long long, 2>;
        using Pack_Unsigned64_4  = std::array<unsigned long long, 4>;
        using Pack_Unsigned64_8  = std::array<unsigned long long, 8>;
        using Pack_Decimal32_1   = std::array<float, 1>;
        using Pack_Decimal32_2   = std::array<float, 2>;
        using Pack_Decimal32_4   = std::array<float, 4>;
        using Pack_Decimal32_8   = std::array<float, 8>;
        using Pack_Decimal32_16  = std::array<float, 16>;
        using Pack_Decimal64_1   = std::array<double, 1>;
        using Pack_Decimal64_2   = std::array<double, 2>;
        using Pack_Decimal64_4   = std::array<double, 4>;
        using Pack_Decimal64_8   = std::array<double, 8>;
        using Pack_Mask8         = unsigned char;
        using Pack_Mask16        = unsigned short;
        using Pack_Mask32        = unsigned int;
        using Pack_Mask64        = unsigned long long;
    };
} // namespace next_mode::core::types::detail
