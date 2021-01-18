#pragma once

#include "frameworks/core/simd/test_fixtures/internal.hpp"

namespace next_mode::core::simd::tests {
    template <typename Parameter>
    class TrigonometryTest : public ::testing::Test {};

    TYPED_TEST_SUITE_P(TrigonometryTest);

    TYPED_TEST_P(TrigonometryTest, Empty) {
    }

    REGISTER_TYPED_TEST_SUITE_P(TrigonometryTest, Empty);
} // namespace next_mode::core::simd::tests
