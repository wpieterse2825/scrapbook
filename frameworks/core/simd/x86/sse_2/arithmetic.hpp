#pragma once

#include "frameworks/core/simd/x86/sse_1/arithmetic.hpp"

namespace next_mode::core::simd::detail {
    struct Arithmetic_X86_SSE_2 : public Arithmetic_X86_SSE_1 {
        using Super = Arithmetic_X86_SSE_1;

        template <typename ElementType, int Width>
        static inline auto AddVertical(const Pack<ElementType, Width>& lhs, const Pack<ElementType, Width>& rhs)
          -> Pack<ElementType, Width> {
            if constexpr (std::is_same<ElementType, Signed8>::value) {
                if constexpr (Width == 16) {
                    return _mm_add_epi8(lhs, rhs);
                }
            }

            if constexpr (std::is_same<ElementType, Unsigned8>::value) {
                if constexpr (Width == 16) {
                    return _mm_add_epi8(lhs, rhs);
                }
            }

            if constexpr (std::is_same<ElementType, Signed16>::value) {
                if constexpr (Width == 8) {
                    return _mm_add_epi16(lhs, rhs);
                }
            }

            if constexpr (std::is_same<ElementType, Unsigned16>::value) {
                if constexpr (Width == 8) {
                    return _mm_add_epi16(lhs, rhs);
                }
            }

            if constexpr (std::is_same<ElementType, Signed32>::value) {
                if constexpr (Width == 4) {
                    return _mm_add_epi32(lhs, rhs);
                }
            }

            if constexpr (std::is_same<ElementType, Unsigned32>::value) {
                if constexpr (Width == 4) {
                    return _mm_add_epi32(lhs, rhs);
                }
            }

            if constexpr (std::is_same<ElementType, Signed64>::value) {
                if constexpr (Width == 1) {
                    return _mm_add_si64(lhs, rhs);
                }

                if constexpr (Width == 2) {
                    return _mm_add_epi64(lhs, rhs);
                }
            }

            if constexpr (std::is_same<ElementType, Unsigned64>::value) {
                if constexpr (Width == 1) {
                    return _mm_add_si64(lhs, rhs);
                }

                if constexpr (Width == 2) {
                    return _mm_add_epi64(lhs, rhs);
                }
            }

            if constexpr (std::is_same<ElementType, Decimal64>::value) {
                if constexpr (Width == 2) {
                    return _mm_add_pd(lhs, rhs);
                }
            }

            return Super::AddVertical(lhs, rhs);
        }
    };
} // namespace next_mode::core::simd::detail
