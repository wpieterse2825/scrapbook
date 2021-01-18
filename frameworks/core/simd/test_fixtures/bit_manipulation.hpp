#pragma once

#include "frameworks/core/simd/test_fixtures/internal.hpp"

namespace next_mode::core::simd::tests {
    template <typename Parameter>
    class BitManipulationTest : public ::testing::Test {};

    TYPED_TEST_SUITE_P(BitManipulationTest);

    TYPED_TEST_P(BitManipulationTest, Empty) {
    }

    REGISTER_TYPED_TEST_SUITE_P(BitManipulationTest, Empty);
} // namespace next_mode::core::simd::tests
