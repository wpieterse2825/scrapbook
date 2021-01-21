#pragma once

#include "frameworks/core/simd/bench_fixtures/internal.hpp"

namespace next_mode::core::simd::benches {
    template <typename Implementation, typename ElementType, uint8_t Dimensions>
    static inline void Cryptography_(benchmark::State& state) {
        for (auto _ : state) {}
    }

    BENCHMARK_ENUMERATE(Cryptography_);
} // namespace next_mode::core::simd::benches
