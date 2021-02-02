#pragma once

#include <immintrin.h>

#include "randoms/foundation/frameworks/core/types/x86/sse_4_2/pack.hpp"

namespace next_mode::core::types::detail {
    struct Pack_X86_AVX_1 : public Pack_X86_SSE_4_2 {
        using Super = Pack_X86_SSE_4_2;

        using Pack_Signed8_32    = __m256i;
        using Pack_Signed16_16   = __m256i;
        using Pack_Signed32_8    = __m256i;
        using Pack_Signed64_4    = __m256i;
        using Pack_Unsigned8_32  = __m256i;
        using Pack_Unsigned16_16 = __m256i;
        using Pack_Unsigned32_8  = __m256i;
        using Pack_Unsigned64_4  = __m256i;
        using Pack_Decimal32_8   = __m256;
        using Pack_Decimal64_4   = __m256d;
    };
} // namespace next_mode::core::types::detail
