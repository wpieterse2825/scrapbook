#pragma once

#include "randoms/foundation/frameworks/core/simd/test_fixtures/internal.hpp"

namespace next_mode::core::simd::tests {
    template <typename Parameter>
    class CastTest : public ::testing::Test {};

    TYPED_TEST_SUITE_P(CastTest);

    TYPED_TEST_P(CastTest, Empty) {
    }

    REGISTER_TYPED_TEST_SUITE_P(CastTest, Empty);
} // namespace next_mode::core::simd::tests
