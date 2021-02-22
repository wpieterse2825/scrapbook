#include "learning/math/vector/benches/shared.hpp"

using CompareEpsilonFixture = DoubleItemFixture<DataType, detail::DefaultBenchDimensions>;

BASELINE_F(CompareEpsilon, Geeneral, CompareEpsilonFixture, detail::DefaultBenchSampleCount, detail::DefaultBenchIterationCount) {
    auto output = detail::vector::general::Compare(this->lhs, this->rhs, MathConstants<DataType>::Epsilon);

    celero::DoNotOptimizeAway(output == false);
}

BENCHMARK_F(CompareEpsilon, SSE_1, CompareEpsilonFixture, detail::DefaultBenchSampleCount, detail::DefaultBenchIterationCount) {
    auto output = detail::vector::sse_1::Compare(this->lhs, this->rhs, MathConstants<DataType>::Epsilon);

    celero::DoNotOptimizeAway(output == false);
}

BENCHMARK_F(CompareEpsilon, SSE_2, CompareEpsilonFixture, detail::DefaultBenchSampleCount, detail::DefaultBenchIterationCount) {
    auto output = detail::vector::sse_2::Compare(this->lhs, this->rhs, MathConstants<DataType>::Epsilon);

    celero::DoNotOptimizeAway(output == false);
}

BENCHMARK_F(CompareEpsilon, AVX_1, CompareEpsilonFixture, detail::DefaultBenchSampleCount, detail::DefaultBenchIterationCount) {
    auto output = detail::vector::avx_1::Compare(this->lhs, this->rhs, MathConstants<DataType>::Epsilon);

    celero::DoNotOptimizeAway(output == false);
}
