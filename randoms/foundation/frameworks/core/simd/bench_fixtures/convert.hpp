#pragma once

#include "randoms/foundation/frameworks/core/simd/bench_fixtures/internal.hpp"

namespace next_mode::core::simd::benches {
    template <typename Implementation, typename ElementType, uint8_t Dimensions>
    static inline void Convert_(benchmark::State& state) {
        for (auto _ : state) {}
    }

    BENCHMARK_ENUMERATE(Convert_);
} // namespace next_mode::core::simd::benches
