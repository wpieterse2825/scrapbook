#pragma once

#include "frameworks/core/simd/test_fixtures/internal.hpp"

namespace next_mode::core::simd::tests {
    template <typename Parameter>
    class StringTest : public ::testing::Test {};

    TYPED_TEST_SUITE_P(StringTest);

    TYPED_TEST_P(StringTest, Empty) {
    }

    REGISTER_TYPED_TEST_SUITE_P(StringTest, Empty);
} // namespace next_mode::core::simd::tests