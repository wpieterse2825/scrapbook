#pragma once

#include "randoms/foundation/frameworks/core/simd/test_fixtures/internal.hpp"

namespace next_mode::core::simd::tests {
    template <typename Parameter>
    class SwizzleTest : public ::testing::Test {};

    TYPED_TEST_SUITE_P(SwizzleTest);

    TYPED_TEST_P(SwizzleTest, Empty) {
    }

    REGISTER_TYPED_TEST_SUITE_P(SwizzleTest, Empty);
} // namespace next_mode::core::simd::tests
