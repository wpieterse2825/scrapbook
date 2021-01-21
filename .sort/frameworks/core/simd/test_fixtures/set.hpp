#pragma once

#include "frameworks/core/simd/test_fixtures/internal.hpp"

namespace next_mode::core::simd::tests {
    template <typename Parameter>
    class SetTest : public ::testing::Test {};

    TYPED_TEST_SUITE_P(SetTest);

    TYPED_TEST_P(SetTest, Empty) {
    }

    REGISTER_TYPED_TEST_SUITE_P(SetTest, Empty);
} // namespace next_mode::core::simd::tests
