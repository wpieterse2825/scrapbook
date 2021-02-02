#pragma once

#include "randoms/foundation/frameworks/core/simd/test_fixtures/internal.hpp"

namespace next_mode::core::simd::tests {
    template <typename Parameter>
    class StatisticsTest : public ::testing::Test {};

    TYPED_TEST_SUITE_P(StatisticsTest);

    TYPED_TEST_P(StatisticsTest, Empty) {
    }

    REGISTER_TYPED_TEST_SUITE_P(StatisticsTest, Empty);
} // namespace next_mode::core::simd::tests
