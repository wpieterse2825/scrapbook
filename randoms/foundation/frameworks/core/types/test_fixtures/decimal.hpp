#pragma once

#include "randoms/foundation/frameworks/core/types/test_fixtures/internal.hpp"

namespace next_mode::core::types::tests {
    template <typename Parameter>
    class DecimalTest : public ::testing::Test {};

    TYPED_TEST_SUITE_P(DecimalTest);

    TYPED_TEST_P(DecimalTest, VerifyDecimalSizes) {
        using Implementation = TypeParam::Implementation;

        EXPECT_EQ(sizeof(typename Implementation::Decimal32), 4);
        EXPECT_EQ(sizeof(typename Implementation::Decimal64), 8);
    }

    REGISTER_TYPED_TEST_SUITE_P(DecimalTest, VerifyDecimalSizes);
} // namespace next_mode::core::types::tests
