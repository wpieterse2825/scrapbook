#pragma once

#include "randoms/foundation/frameworks/core/simd/x86/general/arithmetic.hpp"

namespace next_mode::core::simd::detail {
    struct Arithmetic_X86_MMX : public Arithmetic_X86_General {
        using Super = Arithmetic_X86_General;

        template <typename ElementType, int Width>
        static inline auto AddVertical(const Pack<ElementType, Width>& lhs, const Pack<ElementType, Width>& rhs)
          -> Pack<ElementType, Width> {
            if constexpr (std::is_same<ElementType, Signed8>::value) {
                if constexpr (Width == 8) {
                    return _mm_add_pi8(lhs, rhs);
                }
            }

            if constexpr (std::is_same<ElementType, Unsigned8>::value) {
                if constexpr (Width == 8) {
                    return _mm_add_pi8(lhs, rhs);
                }
            }

            if constexpr (std::is_same<ElementType, Signed16>::value) {
                if constexpr (Width == 4) {
                    return _mm_add_pi16(lhs, rhs);
                }
            }

            if constexpr (std::is_same<ElementType, Unsigned16>::value) {
                if constexpr (Width == 4) {
                    return _mm_add_pi16(lhs, rhs);
                }
            }

            if constexpr (std::is_same<ElementType, Signed32>::value) {
                if constexpr (Width == 2) {
                    return _mm_add_pi32(lhs, rhs);
                }
            }

            if constexpr (std::is_same<ElementType, Unsigned32>::value) {
                if constexpr (Width == 2) {
                    return _mm_add_pi32(lhs, rhs);
                }
            }

            return Super::AddVertical(lhs, rhs);
        }
    };
} // namespace next_mode::core::simd::detail
