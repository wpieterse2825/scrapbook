#pragma once

#include "frameworks/core/simd/test_fixtures/internal.hpp"

namespace next_mode::core::simd::tests {
    template <typename Parameter>
    class CryptographyTest : public ::testing::Test {};

    TYPED_TEST_SUITE_P(CryptographyTest);

    TYPED_TEST_P(CryptographyTest, Empty) {
    }

    REGISTER_TYPED_TEST_SUITE_P(CryptographyTest, Empty);
} // namespace next_mode::core::simd::tests
