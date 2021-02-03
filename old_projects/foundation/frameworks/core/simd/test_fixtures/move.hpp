#pragma once

#include "randoms/foundation/frameworks/core/simd/test_fixtures/internal.hpp"

namespace next_mode::core::simd::tests {
    template <typename Parameter>
    class MoveTest : public ::testing::Test {};

    TYPED_TEST_SUITE_P(MoveTest);

    TYPED_TEST_P(MoveTest, Empty) {
    }

    REGISTER_TYPED_TEST_SUITE_P(MoveTest, Empty);
} // namespace next_mode::core::simd::tests