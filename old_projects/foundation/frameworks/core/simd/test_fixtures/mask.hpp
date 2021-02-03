#pragma once

#include "randoms/foundation/frameworks/core/simd/test_fixtures/internal.hpp"

namespace next_mode::core::simd::tests {
    template <typename Parameter>
    class MaskTest : public ::testing::Test {};

    TYPED_TEST_SUITE_P(MaskTest);

    TYPED_TEST_P(MaskTest, Empty) {
    }

    REGISTER_TYPED_TEST_SUITE_P(MaskTest, Empty);
} // namespace next_mode::core::simd::tests
