#pragma once

#include "randoms/foundation/frameworks/core/simd/test_fixtures/internal.hpp"

namespace next_mode::core::simd::tests {
    template <typename Parameter>
    class LoadTest : public ::testing::Test {};

    TYPED_TEST_SUITE_P(LoadTest);

    TYPED_TEST_P(LoadTest, Empty) {
    }

    REGISTER_TYPED_TEST_SUITE_P(LoadTest, Empty);
} // namespace next_mode::core::simd::tests
