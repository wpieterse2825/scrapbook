#include "learning/math/vector/benches/shared.hpp"

constexpr auto Value = DataType {1};

BASELINE(FromBroadcast, General, detail::DefaultBenchSampleCount, detail::DefaultBenchIterationCount) {
    auto output = detail::vector::general::VectorFromBroadcast<DataType, detail::DefaultBenchDimensions>(Value);

    celero::DoNotOptimizeAway(output.elements[detail::DefaultBenchDimensions - 1] == Value);
}

BENCHMARK(FromBroadcast, SSE_1, detail::DefaultBenchSampleCount, detail::DefaultBenchIterationCount) {
    auto output = detail::vector::sse_1::VectorFromBroadcast<DataType, detail::DefaultBenchDimensions>(Value);

    celero::DoNotOptimizeAway(output.elements[detail::DefaultBenchDimensions - 1] == Value);
}

BENCHMARK(FromBroadcast, SSE_2, detail::DefaultBenchSampleCount, detail::DefaultBenchIterationCount) {
    auto output = detail::vector::sse_2::VectorFromBroadcast<DataType, detail::DefaultBenchDimensions>(Value);

    celero::DoNotOptimizeAway(output.elements[detail::DefaultBenchDimensions - 1] == Value);
}

BENCHMARK(FromBroadcast, AVX_1, detail::DefaultBenchSampleCount, detail::DefaultBenchIterationCount) {
    auto output = detail::vector::avx_1::VectorFromBroadcast<DataType, detail::DefaultBenchDimensions>(Value);

    celero::DoNotOptimizeAway(output.elements[detail::DefaultBenchDimensions - 1] == Value);
}
