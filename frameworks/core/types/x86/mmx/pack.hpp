#pragma once

#include <immintrin.h>

#include "frameworks/core/types/x86/general/pack.hpp"

namespace next_mode::core::types::detail {
    struct Pack_X86_MMX : public Pack_X86_General {
        using Super = Pack_X86_General;

        using Pack_Signed8_8    = __m64;
        using Pack_Signed16_4   = __m64;
        using Pack_Signed32_2   = __m64;
        using Pack_Signed64_1   = __m64;
        using Pack_Unsigned8_8  = __m64;
        using Pack_Unsigned16_4 = __m64;
        using Pack_Unsigned32_2 = __m64;
        using Pack_Unsigned64_1 = __m64;
        using Pack_Decimal32_2  = __m64;
        using Pack_Decimal64_1  = __m64;
    };
} // namespace next_mode::core::types::detail
