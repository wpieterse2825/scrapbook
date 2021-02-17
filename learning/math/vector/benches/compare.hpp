#include "learning/math/vector/benches/shared.hpp"

using CompareFixture = DoubleItemFixture<DataType, detail::DefaultBenchDimensions>;

BASELINE_F(Compare, General, CompareFixture, detail::DefaultBenchSampleCount, detail::DefaultBenchIterationCount) {
    auto output = detail::vector::general::Compare(this->lhs, this->rhs);

    celero::DoNotOptimizeAway(output == false);
}

BENCHMARK_F(Compare, SSE_1, CompareFixture, detail::DefaultBenchSampleCount, detail::DefaultBenchIterationCount) {
    auto output = detail::vector::sse_1::Compare(this->lhs, this->rhs);

    celero::DoNotOptimizeAway(output == false);
}

BENCHMARK_F(Compare, SSE_2, CompareFixture, detail::DefaultBenchSampleCount, detail::DefaultBenchIterationCount) {
    auto output = detail::vector::sse_2::Compare(this->lhs, this->rhs);

    celero::DoNotOptimizeAway(output == false);
}

BENCHMARK_F(Compare, AVX_1, CompareFixture, detail::DefaultBenchSampleCount, detail::DefaultBenchIterationCount) {
    auto output = detail::vector::avx_1::Compare(this->lhs, this->rhs);

    celero::DoNotOptimizeAway(output == false);
}
