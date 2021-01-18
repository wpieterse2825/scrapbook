#pragma once

#include "frameworks/core/simd/test_fixtures/internal.hpp"

namespace next_mode::core::simd::tests {
    template <typename Parameter>
    class CompareTest : public ::testing::Test {};

    TYPED_TEST_SUITE_P(CompareTest);

    TYPED_TEST_P(CompareTest, Empty) {
    }

    REGISTER_TYPED_TEST_SUITE_P(CompareTest, Empty);
} // namespace next_mode::core::simd::tests
