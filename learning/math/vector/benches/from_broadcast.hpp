#pragma once

#include "learning/math/vector/benches/shared.hpp"

constexpr auto Value = DataType {1};

BASELINE(FromBroadcast, Plain, SampleCount, IterationCount) {
    auto output = detail::vector::base::VectorFromBroadcast<DataType, Elements>(Value);

    celero::DoNotOptimizeAway(output.elements[0] == 0.0f);
}

BENCHMARK(FromBroadcast, SSE_1, SampleCount, IterationCount) {
    auto output = detail::vector::sse_1::VectorFromBroadcast<DataType, Elements>(Value);

    celero::DoNotOptimizeAway(output.elements[0] == 0.0f);
}

BENCHMARK(FromBroadcast, SSE_2, SampleCount, IterationCount) {
    auto output = detail::vector::sse_2::VectorFromBroadcast<DataType, Elements>(Value);

    celero::DoNotOptimizeAway(output.elements[0] == 0.0f);
}

BENCHMARK(FromBroadcast, AVX_1, SampleCount, IterationCount) {
    auto output = detail::vector::avx_1::VectorFromBroadcast<DataType, Elements>(Value);

    celero::DoNotOptimizeAway(output.elements[0] == 0.0f);
}
