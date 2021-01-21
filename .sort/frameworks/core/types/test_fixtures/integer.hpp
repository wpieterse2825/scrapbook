#pragma once

#include "frameworks/core/types/test_fixtures/internal.hpp"

namespace next_mode::core::types::tests {
    template <typename Parameter>
    class IntegerTest : public ::testing::Test {};

    TYPED_TEST_SUITE_P(IntegerTest);

    TYPED_TEST_P(IntegerTest, VerifySignedSizes) {
        using Implementation = TypeParam::Implementation;

        EXPECT_EQ(sizeof(typename Implementation::Signed8), 1);
        EXPECT_EQ(sizeof(typename Implementation::Signed16), 2);
        EXPECT_EQ(sizeof(typename Implementation::Signed32), 4);
        EXPECT_EQ(sizeof(typename Implementation::Signed64), 8);
    }

    TYPED_TEST_P(IntegerTest, VerifyUnsignedSizes) {
        using Implementation = TypeParam::Implementation;

        EXPECT_EQ(sizeof(typename Implementation::Unsigned8), 1);
        EXPECT_EQ(sizeof(typename Implementation::Unsigned16), 2);
        EXPECT_EQ(sizeof(typename Implementation::Unsigned32), 4);
        EXPECT_EQ(sizeof(typename Implementation::Unsigned64), 8);
    }

    REGISTER_TYPED_TEST_SUITE_P(IntegerTest, VerifySignedSizes, VerifyUnsignedSizes);
} // namespace next_mode::core::types::tests
