#pragma once

#include <immintrin.h>

#include "frameworks/core/types/x86/mmx/pack.hpp"

namespace next_mode::core::types::detail {
    struct Pack_X86_SSE_1 : public Pack_X86_MMX {
        using Super = Pack_X86_MMX;

        using Pack_Signed8_16   = __m128i;
        using Pack_Signed16_8   = __m128i;
        using Pack_Signed32_4   = __m128i;
        using Pack_Signed64_2   = __m128i;
        using Pack_Unsigned8_16 = __m128i;
        using Pack_Unsigned16_8 = __m128i;
        using Pack_Unsigned32_4 = __m128i;
        using Pack_Unsigned64_2 = __m128i;
        using Pack_Decimal32_4  = __m128;
        using Pack_Decimal64_2  = __m128d;
    };
} // namespace next_mode::core::types::detail
