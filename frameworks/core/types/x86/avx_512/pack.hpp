#pragma once

#include <immintrin.h>

#include "frameworks/core/types/x86/avx_2/pack.hpp"

namespace next_mode::core::types::detail {
    struct Pack_X86_AVX_512 : public Pack_X86_AVX_2 {
        using Super = Pack_X86_AVX_2;

        using Pack_Signed8_64    = __m512i;
        using Pack_Signed16_32   = __m512i;
        using Pack_Signed32_16   = __m512i;
        using Pack_Signed64_8    = __m512i;
        using Pack_Unsigned8_64  = __m512i;
        using Pack_Unsigned16_32 = __m512i;
        using Pack_Unsigned32_16 = __m512i;
        using Pack_Unsigned64_8  = __m512i;
        using Pack_Decimal32_16  = __m512;
        using Pack_Decimal64_8   = __m512d;
        using Pack_Mask8         = __mmask8;
        using Pack_Mask16        = __mmask16;
        using Pack_Mask32        = __mmask32;
        using Pack_Mask64        = __mmask64;
    };
} // namespace next_mode::core::types::detail
