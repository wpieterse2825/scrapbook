#pragma once

#include "randoms/foundation/frameworks/core/simd/internal.hpp"

namespace next_mode::core::simd::detail {
    struct Arithmetic_Common_General {
        template <typename ElementType, int Width>
        static inline auto AddVertical(const Pack<ElementType, Width>& lhs, const Pack<ElementType, Width>& rhs)
          -> Pack<ElementType, Width>;
    };

    template <typename ElementType, int Width>
    auto Arithmetic_Common_General::AddVertical(const Pack<ElementType, Width>& lhs, const Pack<ElementType, Width>& rhs)
      -> Pack<ElementType, Width> {
        auto result = Pack<ElementType, Width> {};

        for (auto index = 0; index < Width; index++) {
            const auto lhs_value = lhs.elements[index];
            const auto rhs_value = rhs.elements[index];
            const auto computed  = lhs_value + rhs_value;

            result.elements[index] = computed;
        }

        return result;
    }
} // namespace next_mode::core::simd::detail
