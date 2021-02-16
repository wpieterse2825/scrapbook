#pragma once

#include "learning/math/vector/benches/shared.hpp"

using CompareFixture = DoubleItemFixture<DataType, Elements>;

BASELINE_F(Compare, Plain, CompareFixture, SampleCount, IterationCount) {
    auto output = detail::vector::base::Compare(this->lhs, this->rhs);

    celero::DoNotOptimizeAway(output == false);
}

BENCHMARK_F(Compare, SSE_1, CompareFixture, SampleCount, IterationCount) {
    auto output = detail::vector::sse_1::Compare(this->lhs, this->rhs);

    celero::DoNotOptimizeAway(output == false);
}

BENCHMARK_F(Compare, SSE_2, CompareFixture, SampleCount, IterationCount) {
    auto output = detail::vector::sse_2::Compare(this->lhs, this->rhs);

    celero::DoNotOptimizeAway(output == false);
}

BENCHMARK_F(Compare, AVX_1, CompareFixture, SampleCount, IterationCount) {
    auto output = detail::vector::avx_1::Compare(this->lhs, this->rhs);

    celero::DoNotOptimizeAway(output == false);
}
