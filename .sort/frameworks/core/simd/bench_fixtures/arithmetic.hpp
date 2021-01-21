#pragma once

#include "frameworks/core/simd/bench_fixtures/internal.hpp"

namespace next_mode::core::simd::benches {
    template <typename Implementation, typename ElementType, int Width>
    static inline void Arithmetic_AddVertical(benchmark::State& state) {
        auto lhs = Pack<ElementType, Width> {};
        auto rhs = Pack<ElementType, Width> {};

        for (auto index = 0; index < Width; index++) {
            const auto computed_value = (ElementType)(index % 4);

            lhs.elements[index] = +computed_value;
            rhs.elements[index] = +computed_value;
        }

        for (auto _ : state) {
            const auto result = Implementation::AddVertical(lhs, rhs);
            benchmark::DoNotOptimize(result);
        }
    }

    BENCHMARK_ENUMERATE(Arithmetic_AddVertical);
} // namespace next_mode::core::simd::benches
