#pragma once

#include "randoms/foundation/frameworks/core/simd/x86/sse_4_2/arithmetic.hpp"

namespace next_mode::core::simd::detail {
    struct Arithmetic_X86_AVX_1 : public Arithmetic_X86_SSE_4_2 {
        using Super = Arithmetic_X86_SSE_4_2;

        template <typename ElementType, int Width>
        static inline auto AddVertical(const Pack<ElementType, Width>& lhs, const Pack<ElementType, Width>& rhs)
          -> Pack<ElementType, Width> {
            if constexpr (std::is_same<ElementType, Decimal32>::value) {
                if constexpr (Width == 8) {
                    return _mm256_add_ps(lhs, rhs);
                }
            }

            if constexpr (std::is_same<ElementType, Decimal64>::value) {
                if constexpr (Width == 4) {
                    return _mm256_add_pd(lhs, rhs);
                }
            }

            return Super::AddVertical(lhs, rhs);
        }
    };
} // namespace next_mode::core::simd::detail
