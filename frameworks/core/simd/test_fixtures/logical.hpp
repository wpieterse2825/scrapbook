#pragma once

#include "frameworks/core/simd/test_fixtures/internal.hpp"

namespace next_mode::core::simd::tests {
    template <typename Parameter>
    class LogicalTest : public ::testing::Test {};

    TYPED_TEST_SUITE_P(LogicalTest);

    TYPED_TEST_P(LogicalTest, Empty) {
    }

    REGISTER_TYPED_TEST_SUITE_P(LogicalTest, Empty);
} // namespace next_mode::core::simd::tests
