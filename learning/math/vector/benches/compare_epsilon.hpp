#pragma once

#include "learning/math/vector/benches/shared.hpp"

constexpr auto Epsilon = DataType {0.1};

using CompareEpsilonFixture = DoubleItemFixture<DataType, DefaultBenchDimensions>;

BASELINE_F(CompareEpsilon, Plain, CompareEpsilonFixture, DefaultBenchSampleCount, DefaultBenchIterationCount) {
    auto output = detail::vector::base::Compare(this->lhs, this->rhs, Epsilon);

    celero::DoNotOptimizeAway(output == false);
}

BENCHMARK_F(CompareEpsilon, SSE_1, CompareEpsilonFixture, DefaultBenchSampleCount, DefaultBenchIterationCount) {
    auto output = detail::vector::sse_1::Compare(this->lhs, this->rhs, Epsilon);

    celero::DoNotOptimizeAway(output == false);
}

BENCHMARK_F(CompareEpsilon, SSE_2, CompareEpsilonFixture, DefaultBenchSampleCount, DefaultBenchIterationCount) {
    auto output = detail::vector::sse_2::Compare(this->lhs, this->rhs, Epsilon);

    celero::DoNotOptimizeAway(output == false);
}

BENCHMARK_F(CompareEpsilon, AVX_1, CompareEpsilonFixture, DefaultBenchSampleCount, DefaultBenchIterationCount) {
    auto output = detail::vector::avx_1::Compare(this->lhs, this->rhs, Epsilon);

    celero::DoNotOptimizeAway(output == false);
}
