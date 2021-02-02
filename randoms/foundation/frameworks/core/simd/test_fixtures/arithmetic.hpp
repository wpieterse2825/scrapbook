#pragma once

#include "randoms/foundation/frameworks/core/simd/test_fixtures/internal.hpp"

namespace next_mode::core::simd::tests {
    template <typename Parameter>
    class ArithmeticTest : public ::testing::Test {};

    TYPED_TEST_SUITE_P(ArithmeticTest);

    TYPED_TEST_P(ArithmeticTest, AddVerticalPositivePositive) {
        using Implementation = TypeParam::Implementation;
        using ElementType    = TypeParam::ElementType;

        constexpr auto Width = TypeParam::Width;

        auto lhs = Pack<ElementType, Width> {};
        auto rhs = Pack<ElementType, Width> {};

        for (auto index = 0; index < Width; index++) {
            const auto computed_value = (ElementType)(index % 4);

            lhs.elements[index] = +computed_value;
            rhs.elements[index] = +computed_value;
        }

        auto result = Implementation::AddVertical(lhs, rhs);

        for (auto index = 0; index < Width; index++) {
            const auto lhs_value      = lhs.elements[index];
            const auto rhs_value      = rhs.elements[index];
            const auto computed_value = (ElementType)(lhs_value + rhs_value);
            const auto result_value   = result.elements[index];

            EXPECT_EQ(computed_value, result_value);
        }
    }

    TYPED_TEST_P(ArithmeticTest, AddVerticalPositiveNegative) {
        using Implementation = TypeParam::Implementation;
        using ElementType    = TypeParam::ElementType;

        constexpr auto Width = TypeParam::Width;

        auto lhs = Pack<ElementType, Width> {};
        auto rhs = Pack<ElementType, Width> {};

        for (auto index = 0; index < Width; index++) {
            const auto computed_value = (ElementType)(index % 4);

            lhs.elements[index] = +computed_value;
            rhs.elements[index] = -computed_value;
        }

        auto result = Implementation::AddVertical(lhs, rhs);

        for (auto index = 0; index < Width; index++) {
            const auto lhs_value      = lhs.elements[index];
            const auto rhs_value      = rhs.elements[index];
            const auto computed_value = (ElementType)(lhs_value + rhs_value);
            const auto result_value   = result.elements[index];

            EXPECT_EQ(computed_value, result_value);
        }
    }

    TYPED_TEST_P(ArithmeticTest, AddVerticalNegativePositive) {
        using Implementation = TypeParam::Implementation;
        using ElementType    = TypeParam::ElementType;

        constexpr auto Width = TypeParam::Width;

        auto lhs = Pack<ElementType, Width> {};
        auto rhs = Pack<ElementType, Width> {};

        for (auto index = 0; index < Width; index++) {
            const auto computed_value = (ElementType)(index % 4);

            lhs.elements[index] = -computed_value;
            rhs.elements[index] = +computed_value;
        }

        auto result = Implementation::AddVertical(lhs, rhs);

        for (auto index = 0; index < Width; index++) {
            const auto lhs_value      = lhs.elements[index];
            const auto rhs_value      = rhs.elements[index];
            const auto computed_value = (ElementType)(lhs_value + rhs_value);
            const auto result_value   = result.elements[index];

            EXPECT_EQ(computed_value, result_value);
        }
    }

    TYPED_TEST_P(ArithmeticTest, AddVerticalNegativeNegative) {
        using Implementation = TypeParam::Implementation;
        using ElementType    = TypeParam::ElementType;

        constexpr auto Width = TypeParam::Width;

        auto lhs = Pack<ElementType, Width> {};
        auto rhs = Pack<ElementType, Width> {};

        for (auto index = 0; index < Width; index++) {
            const auto computed_value = (ElementType)(index % 4);

            lhs.elements[index] = -computed_value;
            rhs.elements[index] = -computed_value;
        }

        auto result = Implementation::AddVertical(lhs, rhs);

        for (auto index = 0; index < Width; index++) {
            const auto lhs_value      = lhs.elements[index];
            const auto rhs_value      = rhs.elements[index];
            const auto computed_value = (ElementType)(lhs_value + rhs_value);
            const auto result_value   = result.elements[index];

            EXPECT_EQ(computed_value, result_value);
        }
    }

    REGISTER_TYPED_TEST_SUITE_P(
      ArithmeticTest, AddVerticalPositivePositive, AddVerticalPositiveNegative, AddVerticalNegativePositive, AddVerticalNegativeNegative);
} // namespace next_mode::core::simd::tests
