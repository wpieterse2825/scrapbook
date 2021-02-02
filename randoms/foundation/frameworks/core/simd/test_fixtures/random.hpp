#pragma once

#include "randoms/foundation/frameworks/core/simd/test_fixtures/internal.hpp"

namespace next_mode::core::simd::tests {
    template <typename Parameter>
    class RandomTest : public ::testing::Test {};

    TYPED_TEST_SUITE_P(RandomTest);

    TYPED_TEST_P(RandomTest, Empty) {
    }

    REGISTER_TYPED_TEST_SUITE_P(RandomTest, Empty);
} // namespace next_mode::core::simd::tests
