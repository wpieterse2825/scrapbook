#pragma once

#include "frameworks/core/types/test_fixtures/internal.hpp"

namespace next_mode::core::types::tests {
    template <typename Parameter>
    class AuxiliaryTest : public ::testing::Test {};

    TYPED_TEST_SUITE_P(AuxiliaryTest);

    TYPED_TEST_P(AuxiliaryTest, Empty) {
    }

    REGISTER_TYPED_TEST_SUITE_P(AuxiliaryTest, Empty);
} // namespace next_mode::core::types::tests
