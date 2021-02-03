#pragma once

#include "randoms/foundation/frameworks/core/simd/test_fixtures/internal.hpp"

namespace next_mode::core::simd::tests {
    template <typename Parameter>
    class MiscellaneousTest : public ::testing::Test {};

    TYPED_TEST_SUITE_P(MiscellaneousTest);

    TYPED_TEST_P(MiscellaneousTest, Empty) {
    }

    REGISTER_TYPED_TEST_SUITE_P(MiscellaneousTest, Empty);
} // namespace next_mode::core::simd::tests
