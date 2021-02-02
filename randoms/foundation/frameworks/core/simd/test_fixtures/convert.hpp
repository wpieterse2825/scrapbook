#pragma once

#include "randoms/foundation/frameworks/core/simd/test_fixtures/internal.hpp"

namespace next_mode::core::simd::tests {
    template <typename Parameter>
    class ConvertTest : public ::testing::Test {};

    TYPED_TEST_SUITE_P(ConvertTest);

    TYPED_TEST_P(ConvertTest, Empty) {
    }

    REGISTER_TYPED_TEST_SUITE_P(ConvertTest, Empty);
} // namespace next_mode::core::simd::tests
