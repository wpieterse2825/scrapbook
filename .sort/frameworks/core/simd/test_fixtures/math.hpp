#pragma once

#include "frameworks/core/simd/test_fixtures/internal.hpp"

namespace next_mode::core::simd::tests {
    template <typename Parameter>
    class MathTest : public ::testing::Test {};

    TYPED_TEST_SUITE_P(MathTest);

    TYPED_TEST_P(MathTest, Empty) {
    }

    REGISTER_TYPED_TEST_SUITE_P(MathTest, Empty);
} // namespace next_mode::core::simd::tests
