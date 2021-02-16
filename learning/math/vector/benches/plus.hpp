#pragma once

#include "learning/math/vector/benches/shared.hpp"

using PlusFixture_1 = DoubleItemFixture<DataType, 1>;
using PlusFixture_2 = DoubleItemFixture<DataType, 2>;
using PlusFixture_3 = DoubleItemFixture<DataType, 3>;
using PlusFixture_4 = DoubleItemFixture<DataType, 4>;
using PlusFixture_5 = DoubleItemFixture<DataType, 5>;
using PlusFixture_6 = DoubleItemFixture<DataType, 6>;

BASELINE_F(Plus, Elements_1, PlusFixture_1, SampleCount, IterationCount) {
    auto output = Plus(this->lhs, this->rhs);

    celero::DoNotOptimizeAway(output.elements[0] == DataType{0});
}

BENCHMARK_F(Plus, Elements_2, PlusFixture_2, SampleCount, IterationCount) {
    auto output = Plus(this->lhs, this->rhs);

    celero::DoNotOptimizeAway(output.elements[0] == DataType{0});
}

BENCHMARK_F(Plus, Elements_3, PlusFixture_3, SampleCount, IterationCount) {
    auto output = Plus(this->lhs, this->rhs);

    celero::DoNotOptimizeAway(output.elements[0] == DataType{0});
}

BENCHMARK_F(Plus, Elements_4, PlusFixture_4, SampleCount, IterationCount) {
    auto output = Plus(this->lhs, this->rhs);

    celero::DoNotOptimizeAway(output.elements[0] == DataType{0});
}

BENCHMARK_F(Plus, Elements_5, PlusFixture_5, SampleCount, IterationCount) {
    auto output = Plus(this->lhs, this->rhs);

    celero::DoNotOptimizeAway(output.elements[0] == DataType{0});
}

BENCHMARK_F(Plus, Elements_6, PlusFixture_6, SampleCount, IterationCount) {
    auto output = Plus(this->lhs, this->rhs);

    celero::DoNotOptimizeAway(output.elements[0] == DataType{0});
}
