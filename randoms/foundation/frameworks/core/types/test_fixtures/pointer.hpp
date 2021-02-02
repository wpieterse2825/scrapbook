#pragma once

#include "randoms/foundation/frameworks/core/types/test_fixtures/internal.hpp"

namespace next_mode::core::types::tests {
    template <typename Parameter>
    class PointerTest : public ::testing::Test {};

    TYPED_TEST_SUITE_P(PointerTest);

    TYPED_TEST_P(PointerTest, VerifySignedPointerSizes) {
        using Implementation = TypeParam::Implementation;

        if constexpr (Implementation::Is8BitPlatform) {
            EXPECT_EQ(sizeof(typename Implementation::SignedPointer), 1);
            EXPECT_EQ(sizeof(typename Implementation::SignedIndex), 1);
            EXPECT_EQ(sizeof(typename Implementation::SignedSize), 1);
        }

        if constexpr (Implementation::Is16BitPlatform) {
            EXPECT_EQ(sizeof(typename Implementation::SignedPointer), 2);
            EXPECT_EQ(sizeof(typename Implementation::SignedIndex), 2);
            EXPECT_EQ(sizeof(typename Implementation::SignedSize), 2);
        }

        if constexpr (Implementation::Is32BitPlatform) {
            EXPECT_EQ(sizeof(typename Implementation::SignedPointer), 4);
            EXPECT_EQ(sizeof(typename Implementation::SignedIndex), 4);
            EXPECT_EQ(sizeof(typename Implementation::SignedSize), 4);
        }

        if constexpr (Implementation::Is64BitPlatform) {
            EXPECT_EQ(sizeof(typename Implementation::SignedPointer), 8);
            EXPECT_EQ(sizeof(typename Implementation::SignedIndex), 8);
            EXPECT_EQ(sizeof(typename Implementation::SignedSize), 8);
        }

        if constexpr (Implementation::Is128BitPlatform) {
            EXPECT_EQ(sizeof(typename Implementation::SignedPointer), 16);
            EXPECT_EQ(sizeof(typename Implementation::SignedIndex), 16);
            EXPECT_EQ(sizeof(typename Implementation::SignedSize), 16);
        }
    }

    TYPED_TEST_P(PointerTest, VerifyUnsignedPointerSizes) {
        using Implementation = TypeParam::Implementation;

        if constexpr (Implementation::Is8BitPlatform) {
            EXPECT_EQ(sizeof(typename Implementation::UnsignedPointer), 1);
            EXPECT_EQ(sizeof(typename Implementation::UnsignedIndex), 1);
            EXPECT_EQ(sizeof(typename Implementation::UnsignedSize), 1);
        }

        if constexpr (Implementation::Is16BitPlatform) {
            EXPECT_EQ(sizeof(typename Implementation::UnsignedPointer), 2);
            EXPECT_EQ(sizeof(typename Implementation::UnsignedIndex), 2);
            EXPECT_EQ(sizeof(typename Implementation::UnsignedSize), 2);
        }

        if constexpr (Implementation::Is32BitPlatform) {
            EXPECT_EQ(sizeof(typename Implementation::UnsignedPointer), 4);
            EXPECT_EQ(sizeof(typename Implementation::UnsignedIndex), 4);
            EXPECT_EQ(sizeof(typename Implementation::UnsignedSize), 4);
        }

        if constexpr (Implementation::Is64BitPlatform) {
            EXPECT_EQ(sizeof(typename Implementation::UnsignedPointer), 8);
            EXPECT_EQ(sizeof(typename Implementation::UnsignedIndex), 8);
            EXPECT_EQ(sizeof(typename Implementation::UnsignedSize), 8);
        }

        if constexpr (Implementation::Is128BitPlatform) {
            EXPECT_EQ(sizeof(typename Implementation::UnsignedPointer), 16);
            EXPECT_EQ(sizeof(typename Implementation::UnsignedIndex), 16);
            EXPECT_EQ(sizeof(typename Implementation::UnsignedSize), 16);
        }
    }

    REGISTER_TYPED_TEST_SUITE_P(PointerTest, VerifySignedPointerSizes, VerifyUnsignedPointerSizes);
} // namespace next_mode::core::types::tests
