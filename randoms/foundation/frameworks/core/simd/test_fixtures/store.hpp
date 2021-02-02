#pragma once

#include "frameworks/core/simd/test_fixtures/internal.hpp"

namespace next_mode::core::simd::tests {
    template <typename Parameter>
    class StoreTest : public ::testing::Test {};

    TYPED_TEST_SUITE_P(StoreTest);

    TYPED_TEST_P(StoreTest, Empty) {
    }

    REGISTER_TYPED_TEST_SUITE_P(StoreTest, Empty);
} // namespace next_mode::core::simd::tests
