#include "learning/math/vector/tests/shared.hpp"

template <typename Type>
class CompareEpsilonTest : public testing::Test {};

TYPED_TEST_SUITE(CompareEpsilonTest, TestTypeCollection);

template <typename DataType, size_t Dimensions>
static auto AssertCompareImplementations(const Vector<DataType, Dimensions>& lhs,
                                         const Vector<DataType, Dimensions>& rhs,
                                         const DataType&                     epsilon,
                                         bool                                expected_result) -> void {
    if constexpr (VectorSIMDEnabled == true) {
        if constexpr (VectorSIMDUseAVX1 == true) {
            const auto computed_result_avx_1 = detail::vector::avx_1::Compare(lhs, rhs, epsilon);

            EXPECT_EQ(computed_result_avx_1, expected_result) << "Implementation - AVX 1";
        }

        if constexpr (VectorSIMDUseSSE2 == true) {
            const auto computed_result_sse_2 = detail::vector::sse_2::Compare(lhs, rhs, epsilon);

            EXPECT_EQ(computed_result_sse_2, expected_result) << "Implementation - SSE 2";
        }

        if constexpr (VectorSIMDUseSSE1 == true) {
            const auto computed_result_sse_1 = detail::vector::sse_1::Compare(lhs, rhs, epsilon);

            EXPECT_EQ(computed_result_sse_1, expected_result) << "Implementation - SSE 1";
        }
    }

    const auto computed_result = detail::vector::base::Compare(lhs, rhs, epsilon);

    EXPECT_EQ(computed_result, expected_result) << "Implementation - General";
}

TYPED_TEST(CompareEpsilonTest, BaselinePassAllElementsPositive) {
    using Type = TypeParam::Type;

    constexpr auto Dimensions = TypeParam::Dimensions;

    constexpr auto zero            = MathConstants<Type>::Zero;
    constexpr auto positive_value  = Affirm((Type)Dimensions);
    constexpr auto compare_epsilon = zero;

    auto lhs = VectorFromZero<Type, Dimensions>();
    auto rhs = VectorFromZero<Type, Dimensions>();

    for (auto index = size_t {0}; index < Dimensions; index++) {
        Write(lhs, index, positive_value);
        Write(rhs, index, positive_value);
    }

    AssertCompareImplementations(lhs, rhs, compare_epsilon, true);
}

TYPED_TEST(CompareEpsilonTest, BaselinePassLastElementPositive) {
    using Type = TypeParam::Type;

    constexpr auto Dimensions = TypeParam::Dimensions;

    constexpr auto zero            = MathConstants<Type>::Zero;
    constexpr auto last_element    = Minus(Dimensions, size_t {1});
    constexpr auto positive_value  = Affirm((Type)Dimensions);
    constexpr auto compare_epsilon = zero;

    auto lhs = VectorFromZero<Type, Dimensions>();
    auto rhs = VectorFromZero<Type, Dimensions>();

    Write(lhs, last_element, positive_value);
    Write(rhs, last_element, positive_value);

    AssertCompareImplementations(lhs, rhs, compare_epsilon, true);
}

TYPED_TEST(CompareEpsilonTest, BaselinePassAllElementsNegative) {
    using Type = TypeParam::Type;

    constexpr auto Dimensions = TypeParam::Dimensions;

    constexpr auto zero            = MathConstants<Type>::Zero;
    constexpr auto negative_value  = Negate((Type)Dimensions);
    constexpr auto compare_epsilon = zero;

    auto lhs = VectorFromZero<Type, Dimensions>();
    auto rhs = VectorFromZero<Type, Dimensions>();

    for (auto index = size_t {0}; index < Dimensions; index++) {
        Write(lhs, index, negative_value);
        Write(rhs, index, negative_value);
    }

    AssertCompareImplementations(lhs, rhs, compare_epsilon, true);
}

TYPED_TEST(CompareEpsilonTest, BaselinePassLastElementNegative) {
    using Type = TypeParam::Type;

    constexpr auto Dimensions = TypeParam::Dimensions;

    constexpr auto zero            = MathConstants<Type>::Zero;
    constexpr auto last_element    = Minus(Dimensions, size_t {1});
    constexpr auto negative_value  = Negate((Type)Dimensions);
    constexpr auto compare_epsilon = zero;

    auto lhs = VectorFromZero<Type, Dimensions>();
    auto rhs = VectorFromZero<Type, Dimensions>();

    Write(lhs, last_element, negative_value);
    Write(rhs, last_element, negative_value);

    AssertCompareImplementations(lhs, rhs, compare_epsilon, true);
}

TYPED_TEST(CompareEpsilonTest, BaselineFailAllElementsOpposite) {
    using Type = TypeParam::Type;

    constexpr auto Dimensions = TypeParam::Dimensions;

    constexpr auto zero            = MathConstants<Type>::Zero;
    constexpr auto positive_value  = Affirm((Type)Dimensions);
    constexpr auto negative_value  = Negate((Type)Dimensions);
    constexpr auto compare_epsilon = zero;

    auto lhs = VectorFromZero<Type, Dimensions>();
    auto rhs = VectorFromZero<Type, Dimensions>();

    for (auto index = size_t {0}; index < Dimensions; index++) {
        Write(lhs, index, positive_value);
        Write(rhs, index, negative_value);
    }

    AssertCompareImplementations(lhs, rhs, compare_epsilon, false);
}

TYPED_TEST(CompareEpsilonTest, BaselineFailLastElementOpposite) {
    using Type = TypeParam::Type;

    constexpr auto Dimensions = TypeParam::Dimensions;

    constexpr auto zero            = MathConstants<Type>::Zero;
    constexpr auto last_element    = Minus(Dimensions, size_t {1});
    constexpr auto positive_value  = Affirm((Type)Dimensions);
    constexpr auto negative_value  = Negate((Type)Dimensions);
    constexpr auto compare_epsilon = zero;

    auto lhs = VectorFromZero<Type, Dimensions>();
    auto rhs = VectorFromZero<Type, Dimensions>();

    Write(lhs, last_element, positive_value);
    Write(rhs, last_element, negative_value);

    AssertCompareImplementations(lhs, rhs, compare_epsilon, false);
}

TYPED_TEST(CompareEpsilonTest, PassEpsilonAllElementsClosePossitve) {
    using Type = TypeParam::Type;

    constexpr auto Dimensions = TypeParam::Dimensions;

    constexpr auto zero            = MathConstants<Type>::Zero;
    constexpr auto below_epsilon   = MathConstants<Type>::BelowEpsilon;
    constexpr auto lhs_value       = Plus((Type)Dimensions, zero);
    constexpr auto rhs_value       = Plus((Type)Dimensions, below_epsilon);
    constexpr auto epsilon         = MathConstants<Type>::Epsilon;
    constexpr auto compare_epsilon = epsilon;

    auto lhs = VectorFromZero<Type, Dimensions>();
    auto rhs = VectorFromZero<Type, Dimensions>();

    for (auto index = size_t {0}; index < Dimensions; index++) {
        Write(lhs, index, lhs_value);
        Write(rhs, index, rhs_value);
    }

    AssertCompareImplementations(lhs, rhs, compare_epsilon, true);
}

TYPED_TEST(CompareEpsilonTest, PassEpsilonLastElementClosePossitve) {
    using Type = TypeParam::Type;

    constexpr auto Dimensions = TypeParam::Dimensions;

    constexpr auto last_element    = Minus(Dimensions, size_t {1});
    constexpr auto zero            = MathConstants<Type>::Zero;
    constexpr auto below_epsilon   = MathConstants<Type>::BelowEpsilon;
    constexpr auto lhs_value       = Plus((Type)Dimensions, zero);
    constexpr auto rhs_value       = Plus((Type)Dimensions, below_epsilon);
    constexpr auto epsilon         = MathConstants<Type>::Epsilon;
    constexpr auto compare_epsilon = epsilon;

    auto lhs = VectorFromZero<Type, Dimensions>();
    auto rhs = VectorFromZero<Type, Dimensions>();

    Write(lhs, last_element, lhs_value);
    Write(rhs, last_element, rhs_value);

    AssertCompareImplementations(lhs, rhs, compare_epsilon, true);
}

TYPED_TEST(CompareEpsilonTest, PassEpsilonAllElementsCloseNegative) {
    using Type = TypeParam::Type;

    constexpr auto Dimensions = TypeParam::Dimensions;

    constexpr auto zero            = MathConstants<Type>::Zero;
    constexpr auto below_epsilon   = MathConstants<Type>::BelowEpsilon;
    constexpr auto lhs_value       = Plus((Type)Dimensions, zero);
    constexpr auto rhs_value       = Plus((Type)Dimensions, below_epsilon);
    constexpr auto epsilon         = MathConstants<Type>::Epsilon;
    constexpr auto compare_epsilon = epsilon;

    auto lhs = VectorFromZero<Type, Dimensions>();
    auto rhs = VectorFromZero<Type, Dimensions>();

    for (auto index = size_t {0}; index < Dimensions; index++) {
        Write(lhs, index, lhs_value);
        Write(rhs, index, rhs_value);
    }

    AssertCompareImplementations(lhs, rhs, compare_epsilon, true);
}

TYPED_TEST(CompareEpsilonTest, PassEpsilonLastElementCloseNegative) {
    using Type = TypeParam::Type;

    constexpr auto Dimensions = TypeParam::Dimensions;

    constexpr auto last_element    = Minus(Dimensions, size_t {1});
    constexpr auto zero            = MathConstants<Type>::Zero;
    constexpr auto below_epsilon   = MathConstants<Type>::BelowEpsilon;
    constexpr auto lhs_value       = Plus((Type)Dimensions, zero);
    constexpr auto rhs_value       = Plus((Type)Dimensions, below_epsilon);
    constexpr auto epsilon         = MathConstants<Type>::Epsilon;
    constexpr auto compare_epsilon = epsilon;

    auto lhs = VectorFromZero<Type, Dimensions>();
    auto rhs = VectorFromZero<Type, Dimensions>();

    Write(lhs, last_element, lhs_value);
    Write(rhs, last_element, rhs_value);

    AssertCompareImplementations(lhs, rhs, compare_epsilon, true);
}

TYPED_TEST(CompareEpsilonTest, PassEpsilonAllElementsCloseOpposite) {
    using Type = TypeParam::Type;

    constexpr auto Dimensions = TypeParam::Dimensions;

    constexpr auto two             = MathConstants<Type>::Two;
    constexpr auto below_epsilon   = MathConstants<Type>::BelowEpsilon;
    constexpr auto lhs_value       = Plus((Type)Dimensions, below_epsilon);
    constexpr auto rhs_value       = Minus((Type)Dimensions, below_epsilon);
    constexpr auto epsilon         = MathConstants<Type>::Epsilon;
    constexpr auto compare_epsilon = epsilon * two;

    auto lhs = VectorFromZero<Type, Dimensions>();
    auto rhs = VectorFromZero<Type, Dimensions>();

    for (auto index = size_t {0}; index < Dimensions; index++) {
        Write(lhs, index, lhs_value);
        Write(rhs, index, rhs_value);
    }

    AssertCompareImplementations(lhs, rhs, compare_epsilon, true);
}

TYPED_TEST(CompareEpsilonTest, PassEpsilonLastElementCloseOpposite) {
    using Type = TypeParam::Type;

    constexpr auto Dimensions = TypeParam::Dimensions;

    constexpr auto last_element    = Minus(Dimensions, size_t {1});
    constexpr auto two             = MathConstants<Type>::Two;
    constexpr auto below_epsilon   = MathConstants<Type>::BelowEpsilon;
    constexpr auto lhs_value       = Plus((Type)Dimensions, below_epsilon);
    constexpr auto rhs_value       = Minus((Type)Dimensions, below_epsilon);
    constexpr auto epsilon         = MathConstants<Type>::Epsilon;
    constexpr auto compare_epsilon = epsilon * two;

    auto lhs = VectorFromZero<Type, Dimensions>();
    auto rhs = VectorFromZero<Type, Dimensions>();

    Write(lhs, last_element, lhs_value);
    Write(rhs, last_element, rhs_value);

    AssertCompareImplementations(lhs, rhs, compare_epsilon, true);
}

TYPED_TEST(CompareEpsilonTest, FailEpsilonAllElementsLittleOverPossitve) {
    using Type = TypeParam::Type;

    constexpr auto Dimensions = TypeParam::Dimensions;

    constexpr auto zero            = MathConstants<Type>::Zero;
    constexpr auto two             = MathConstants<Type>::Two;
    constexpr auto epsilon         = MathConstants<Type>::Epsilon;
    constexpr auto epsilon_double  = Multiply(epsilon, two);
    constexpr auto lhs_value       = Plus((Type)Dimensions, zero);
    constexpr auto rhs_value       = Plus((Type)Dimensions, epsilon_double);
    constexpr auto compare_epsilon = epsilon;

    auto lhs = VectorFromZero<Type, Dimensions>();
    auto rhs = VectorFromZero<Type, Dimensions>();

    for (auto index = size_t {0}; index < Dimensions; index++) {
        Write(lhs, index, lhs_value);
        Write(rhs, index, rhs_value);
    }

    AssertCompareImplementations(lhs, rhs, compare_epsilon, false);
}

TYPED_TEST(CompareEpsilonTest, FailEpsilonLastElementLittleOverPossitve) {
    using Type = TypeParam::Type;

    constexpr auto Dimensions = TypeParam::Dimensions;

    constexpr auto last_element    = Minus(Dimensions, size_t {1});
    constexpr auto zero            = MathConstants<Type>::Zero;
    constexpr auto two             = MathConstants<Type>::Two;
    constexpr auto epsilon         = MathConstants<Type>::Epsilon;
    constexpr auto epsilon_double  = Multiply(epsilon, two);
    constexpr auto lhs_value       = Plus((Type)Dimensions, zero);
    constexpr auto rhs_value       = Plus((Type)Dimensions, epsilon_double);
    constexpr auto compare_epsilon = epsilon;

    auto lhs = VectorFromZero<Type, Dimensions>();
    auto rhs = VectorFromZero<Type, Dimensions>();

    Write(lhs, last_element, lhs_value);
    Write(rhs, last_element, rhs_value);

    AssertCompareImplementations(lhs, rhs, compare_epsilon, false);
}

TYPED_TEST(CompareEpsilonTest, FailEpsilonAllElementsLittleBelowNegative) {
    using Type = TypeParam::Type;

    constexpr auto Dimensions = TypeParam::Dimensions;

    constexpr auto zero            = MathConstants<Type>::Zero;
    constexpr auto two             = MathConstants<Type>::Two;
    constexpr auto epsilon         = MathConstants<Type>::Epsilon;
    constexpr auto epsilon_double  = Multiply(epsilon, two);
    constexpr auto lhs_value       = Minus((Type)Dimensions, zero);
    constexpr auto rhs_value       = Minus((Type)Dimensions, epsilon_double);
    constexpr auto compare_epsilon = epsilon;

    auto lhs = VectorFromZero<Type, Dimensions>();
    auto rhs = VectorFromZero<Type, Dimensions>();

    for (auto index = size_t {0}; index < Dimensions; index++) {
        Write(lhs, index, lhs_value);
        Write(rhs, index, rhs_value);
    }

    AssertCompareImplementations(lhs, rhs, compare_epsilon, false);
}

TYPED_TEST(CompareEpsilonTest, FailEpsilonLastElementLittleBelowNegative) {
    using Type = TypeParam::Type;

    constexpr auto Dimensions = TypeParam::Dimensions;

    constexpr auto last_element    = Minus(Dimensions, size_t {1});
    constexpr auto zero            = MathConstants<Type>::Zero;
    constexpr auto two             = MathConstants<Type>::Two;
    constexpr auto epsilon         = MathConstants<Type>::Epsilon;
    constexpr auto epsilon_double  = Multiply(epsilon, two);
    constexpr auto lhs_value       = Minus((Type)Dimensions, zero);
    constexpr auto rhs_value       = Minus((Type)Dimensions, epsilon_double);
    constexpr auto compare_epsilon = epsilon;

    auto lhs = VectorFromZero<Type, Dimensions>();
    auto rhs = VectorFromZero<Type, Dimensions>();

    Write(lhs, last_element, lhs_value);
    Write(rhs, last_element, rhs_value);

    AssertCompareImplementations(lhs, rhs, compare_epsilon, false);
}

TYPED_TEST(CompareEpsilonTest, FailEpsilonAllElementsWithLittleOpposite) {
    using Type = TypeParam::Type;

    constexpr auto Dimensions = TypeParam::Dimensions;

    constexpr auto epsilon         = MathConstants<Type>::Epsilon;
    constexpr auto lhs_value       = Plus((Type)Dimensions, epsilon);
    constexpr auto rhs_value       = Minus((Type)Dimensions, epsilon);
    constexpr auto compare_epsilon = epsilon;

    auto lhs = VectorFromZero<Type, Dimensions>();
    auto rhs = VectorFromZero<Type, Dimensions>();

    for (auto index = size_t {0}; index < Dimensions; index++) {
        Write(lhs, index, lhs_value);
        Write(rhs, index, rhs_value);
    }

    AssertCompareImplementations(lhs, rhs, compare_epsilon, false);
}

TYPED_TEST(CompareEpsilonTest, FailEpsilonLastElementWithLittleOpposite) {
    using Type = TypeParam::Type;

    constexpr auto Dimensions = TypeParam::Dimensions;

    constexpr auto last_element    = Minus(Dimensions, size_t {1});
    constexpr auto epsilon         = MathConstants<Type>::Epsilon;
    constexpr auto lhs_value       = Plus((Type)Dimensions, epsilon);
    constexpr auto rhs_value       = Minus((Type)Dimensions, epsilon);
    constexpr auto compare_epsilon = epsilon;

    auto lhs = VectorFromZero<Type, Dimensions>();
    auto rhs = VectorFromZero<Type, Dimensions>();

    Write(lhs, last_element, lhs_value);
    Write(rhs, last_element, rhs_value);

    AssertCompareImplementations(lhs, rhs, compare_epsilon, false);
}
