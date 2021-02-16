#pragma once

#include "learning/math/vector/benches/shared.hpp"

using CompareFixture = DoubleItemFixture<DataType, DefaultBenchDimensions>;

BASELINE_F(Compare, Plain, CompareFixture, DefaultBenchSampleCount, DefaultBenchIterationCount) {
    auto output = detail::vector::base::Compare(this->lhs, this->rhs);

    celero::DoNotOptimizeAway(output == false);
}

BENCHMARK_F(Compare, SSE_1, CompareFixture, DefaultBenchSampleCount, DefaultBenchIterationCount) {
    auto output = detail::vector::sse_1::Compare(this->lhs, this->rhs);

    celero::DoNotOptimizeAway(output == false);
}

BENCHMARK_F(Compare, SSE_2, CompareFixture, DefaultBenchSampleCount, DefaultBenchIterationCount) {
    auto output = detail::vector::sse_2::Compare(this->lhs, this->rhs);

    celero::DoNotOptimizeAway(output == false);
}

BENCHMARK_F(Compare, AVX_1, CompareFixture, DefaultBenchSampleCount, DefaultBenchIterationCount) {
    auto output = detail::vector::avx_1::Compare(this->lhs, this->rhs);

    celero::DoNotOptimizeAway(output == false);
}
