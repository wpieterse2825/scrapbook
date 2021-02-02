#pragma once

#include "frameworks/core/types/test_fixtures/internal.hpp"

namespace next_mode::core::types::tests {
    template <typename Parameter>
    class PackTest : public ::testing::Test {};

    TYPED_TEST_SUITE_P(PackTest);

    TYPED_TEST_P(PackTest, VerifySigned8Sizes) {
        using Implementation = TypeParam::Implementation;

        EXPECT_EQ(sizeof(typename Implementation::Pack_Signed8_1), 1);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Signed8_2), 2);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Signed8_4), 4);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Signed8_8), 8);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Signed8_16), 16);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Signed8_32), 32);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Signed8_64), 64);
    }

    TYPED_TEST_P(PackTest, VerifySigned16Sizes) {
        using Implementation = TypeParam::Implementation;

        EXPECT_EQ(sizeof(typename Implementation::Pack_Signed16_1), 2);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Signed16_2), 4);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Signed16_4), 8);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Signed16_8), 16);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Signed16_16), 32);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Signed16_32), 64);
    }

    TYPED_TEST_P(PackTest, VerifySigned32Sizes) {
        using Implementation = TypeParam::Implementation;

        EXPECT_EQ(sizeof(typename Implementation::Pack_Signed32_1), 4);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Signed32_2), 8);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Signed32_4), 16);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Signed32_8), 32);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Signed32_16), 64);
    }

    TYPED_TEST_P(PackTest, VerifySigned64Sizes) {
        using Implementation = TypeParam::Implementation;

        EXPECT_EQ(sizeof(typename Implementation::Pack_Signed64_1), 8);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Signed64_2), 16);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Signed64_4), 32);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Signed64_8), 64);
    }

    TYPED_TEST_P(PackTest, VerifyUnsigned8Sizes) {
        using Implementation = TypeParam::Implementation;

        EXPECT_EQ(sizeof(typename Implementation::Pack_Unsigned8_1), 1);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Unsigned8_2), 2);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Unsigned8_4), 4);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Unsigned8_8), 8);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Unsigned8_16), 16);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Unsigned8_32), 32);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Unsigned8_64), 64);
    }

    TYPED_TEST_P(PackTest, VerifyUnsigned16Sizes) {
        using Implementation = TypeParam::Implementation;

        EXPECT_EQ(sizeof(typename Implementation::Pack_Unsigned16_1), 2);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Unsigned16_2), 4);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Unsigned16_4), 8);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Unsigned16_8), 16);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Unsigned16_16), 32);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Unsigned16_32), 64);
    }

    TYPED_TEST_P(PackTest, VerifyUnsigned32Sizes) {
        using Implementation = TypeParam::Implementation;

        EXPECT_EQ(sizeof(typename Implementation::Pack_Unsigned32_1), 4);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Unsigned32_2), 8);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Unsigned32_4), 16);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Unsigned32_8), 32);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Unsigned32_16), 64);
    }

    TYPED_TEST_P(PackTest, VerifyUnsigned64Sizes) {
        using Implementation = TypeParam::Implementation;

        EXPECT_EQ(sizeof(typename Implementation::Pack_Unsigned64_1), 8);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Unsigned64_2), 16);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Unsigned64_4), 32);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Unsigned64_8), 64);
    }

    TYPED_TEST_P(PackTest, VerifyDecimal32Sizes) {
        using Implementation = TypeParam::Implementation;

        EXPECT_EQ(sizeof(typename Implementation::Pack_Decimal32_1), 4);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Decimal32_2), 8);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Decimal32_4), 16);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Decimal32_8), 32);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Decimal32_16), 64);
    }

    TYPED_TEST_P(PackTest, VerifyDecimal64Sizes) {
        using Implementation = TypeParam::Implementation;

        EXPECT_EQ(sizeof(typename Implementation::Pack_Decimal64_1), 8);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Decimal64_2), 16);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Decimal64_4), 32);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Decimal64_8), 64);
    }

    TYPED_TEST_P(PackTest, VerifyMaskSizes) {
        using Implementation = TypeParam::Implementation;

        EXPECT_EQ(sizeof(typename Implementation::Pack_Mask8), 1);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Mask16), 2);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Mask32), 4);
        EXPECT_EQ(sizeof(typename Implementation::Pack_Mask64), 8);
    }

    REGISTER_TYPED_TEST_SUITE_P(PackTest,
                                VerifySigned8Sizes,
                                VerifySigned16Sizes,
                                VerifySigned32Sizes,
                                VerifySigned64Sizes,
                                VerifyUnsigned8Sizes,
                                VerifyUnsigned16Sizes,
                                VerifyUnsigned32Sizes,
                                VerifyUnsigned64Sizes,
                                VerifyDecimal32Sizes,
                                VerifyDecimal64Sizes,
                                VerifyMaskSizes);
} // namespace next_mode::core::types::tests
