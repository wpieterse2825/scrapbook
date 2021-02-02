#pragma once

#include "randoms/foundation/frameworks/core/types/test_fixtures/internal.hpp"

namespace next_mode::core::types::tests {
    template <typename Parameter>
    class CharacterTest : public ::testing::Test {};

    TYPED_TEST_SUITE_P(CharacterTest);

    TYPED_TEST_P(CharacterTest, VerifyCharacterSizes) {
        using Implementation = TypeParam::Implementation;

        EXPECT_EQ(sizeof(typename Implementation::ASCIICharacter), 1);
    }

    TYPED_TEST_P(CharacterTest, VerifyUTFSizes) {
        using Implementation = TypeParam::Implementation;

        EXPECT_EQ(sizeof(typename Implementation::UTF8Character), 1);
        EXPECT_EQ(sizeof(typename Implementation::UTF16Character), 2);
        EXPECT_EQ(sizeof(typename Implementation::UTF32Character), 4);
    }

    REGISTER_TYPED_TEST_SUITE_P(CharacterTest, VerifyCharacterSizes, VerifyUTFSizes);
} // namespace next_mode::core::types::tests
