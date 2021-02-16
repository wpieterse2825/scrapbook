#pragma once

#include "learning/math/vector/benches/shared.hpp"

using NegateFixture_1 = SingleItemFixture<DataType, 1>;
using NegateFixture_2 = SingleItemFixture<DataType, 2>;
using NegateFixture_3 = SingleItemFixture<DataType, 3>;
using NegateFixture_4 = SingleItemFixture<DataType, 4>;
using NegateFixture_5 = SingleItemFixture<DataType, 5>;
using NegateFixture_6 = SingleItemFixture<DataType, 6>;

BASELINE_F(Negate, Elements_1, NegateFixture_1, SampleCount, IterationCount) {
    auto output = Negate(this->item);

    celero::DoNotOptimizeAway(output.elements[0] == DataType{0});
}

BENCHMARK_F(Negate, Elements_2, NegateFixture_2, SampleCount, IterationCount) {
    auto output = Negate(this->item);

    celero::DoNotOptimizeAway(output.elements[0] == DataType{0});
}

BENCHMARK_F(Negate, Elements_3, NegateFixture_3, SampleCount, IterationCount) {
    auto output = Negate(this->item);

    celero::DoNotOptimizeAway(output.elements[0] == DataType{0});
}

BENCHMARK_F(Negate, Elements_4, NegateFixture_4, SampleCount, IterationCount) {
    auto output = Negate(this->item);

    celero::DoNotOptimizeAway(output.elements[0] == DataType{0});
}

BENCHMARK_F(Negate, Elements_5, NegateFixture_5, SampleCount, IterationCount) {
    auto output = Negate(this->item);

    celero::DoNotOptimizeAway(output.elements[0] == DataType{0});
}

BENCHMARK_F(Negate, Elements_6, NegateFixture_6, SampleCount, IterationCount) {
    auto output = Negate(this->item);

    celero::DoNotOptimizeAway(output.elements[0] == DataType{0});
}
