#pragma once

#include "frameworks/core/simd/x86/mmx/arithmetic.hpp"

namespace next_mode::core::simd::detail {
    struct Arithmetic_X86_SSE_1 : public Arithmetic_X86_MMX {
        using Super = Arithmetic_X86_MMX;

        template <typename ElementType, int Width>
        static inline auto AddVertical(const Pack<ElementType, Width>& lhs, const Pack<ElementType, Width>& rhs)
          -> Pack<ElementType, Width> {
            if constexpr (std::is_same<ElementType, Decimal32>::value) {
                if constexpr (Width == 4) {
                    return _mm_add_ps(lhs, rhs);
                }
            }

            return Super::AddVertical(lhs, rhs);
        }
    };
} // namespace next_mode::core::simd::detail
