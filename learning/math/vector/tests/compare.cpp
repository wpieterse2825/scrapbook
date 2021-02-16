#include "learning/math/vector/tests/shared.hpp"

template <typename Type>
class CompareTest : public testing::Test {};

TYPED_TEST_SUITE(CompareTest, TestTypeCollection);

template <typename DataType, size_t Dimensions>
static auto AssertCompareImplementations(const Vector<DataType, Dimensions>& lhs,
                                         const Vector<DataType, Dimensions>& rhs,
                                         bool                                expected_result) -> void {
    if constexpr (VectorSIMDEnabled == true) {
        if constexpr (VectorSIMDUseAVX1 == true) {
            const auto computed_result_avx_1 = detail::vector::avx_1::Compare(lhs, rhs);

            EXPECT_EQ(computed_result_avx_1, expected_result) << "Implementation - AVX 1";
        }

        if constexpr (VectorSIMDUseSSE2 == true) {
            const auto computed_result_sse_2 = detail::vector::sse_2::Compare(lhs, rhs);

            EXPECT_EQ(computed_result_sse_2, expected_result) << "Implementation - SSE 2";
        }

        if constexpr (VectorSIMDUseSSE1 == true) {
            const auto computed_result_sse_1 = detail::vector::sse_1::Compare(lhs, rhs);

            EXPECT_EQ(computed_result_sse_1, expected_result) << "Implementation - SSE 1";
        }
    }

    const auto computed_result = detail::vector::base::Compare(lhs, rhs);

    EXPECT_EQ(computed_result, expected_result) << "Implementation - General";
}

TYPED_TEST(CompareTest, BaselinePassAllElementsPositive) {
    using Type = TypeParam::Type;

    constexpr auto Dimensions = TypeParam::Dimensions;

    constexpr auto positive_value  = Affirm((Type)Dimensions);

    auto lhs = VectorFromZero<Type, Dimensions>();
    auto rhs = VectorFromZero<Type, Dimensions>();

    for (auto index = size_t {0}; index < Dimensions; index++) {
        Write(lhs, index, positive_value);
        Write(rhs, index, positive_value);
    }

    AssertCompareImplementations(lhs, rhs, true);
}

TYPED_TEST(CompareTest, BaselinePassLastElementPositive) {
    using Type = TypeParam::Type;

    constexpr auto Dimensions = TypeParam::Dimensions;

    constexpr auto last_element    = Minus(Dimensions, size_t {1});
    constexpr auto positive_value  = Affirm((Type)Dimensions);

    auto lhs = VectorFromZero<Type, Dimensions>();
    auto rhs = VectorFromZero<Type, Dimensions>();

    Write(lhs, last_element, positive_value);
    Write(rhs, last_element, positive_value);

    AssertCompareImplementations(lhs, rhs, true);
}

TYPED_TEST(CompareTest, BaselinePassAllElementsNegative) {
    using Type = TypeParam::Type;

    constexpr auto Dimensions = TypeParam::Dimensions;

    constexpr auto negative_value  = Negate((Type)Dimensions);

    auto lhs = VectorFromZero<Type, Dimensions>();
    auto rhs = VectorFromZero<Type, Dimensions>();

    for (auto index = size_t {0}; index < Dimensions; index++) {
        Write(lhs, index, negative_value);
        Write(rhs, index, negative_value);
    }

    AssertCompareImplementations(lhs, rhs, true);
}

TYPED_TEST(CompareTest, BaselinePassLastElementNegative) {
    using Type = TypeParam::Type;

    constexpr auto Dimensions = TypeParam::Dimensions;

    constexpr auto last_element    = Minus(Dimensions, size_t {1});
    constexpr auto negative_value  = Negate((Type)Dimensions);

    auto lhs = VectorFromZero<Type, Dimensions>();
    auto rhs = VectorFromZero<Type, Dimensions>();

    Write(lhs, last_element, negative_value);
    Write(rhs, last_element, negative_value);

    AssertCompareImplementations(lhs, rhs, true);
}

TYPED_TEST(CompareTest, BaselineFailAllElementsOpposite) {
    using Type = TypeParam::Type;

    constexpr auto Dimensions = TypeParam::Dimensions;

    constexpr auto positive_value  = Affirm((Type)Dimensions);
    constexpr auto negative_value  = Negate((Type)Dimensions);

    auto lhs = VectorFromZero<Type, Dimensions>();
    auto rhs = VectorFromZero<Type, Dimensions>();

    for (auto index = size_t {0}; index < Dimensions; index++) {
        Write(lhs, index, positive_value);
        Write(rhs, index, negative_value);
    }

    AssertCompareImplementations(lhs, rhs, false);
}

TYPED_TEST(CompareTest, BaselineFailLastElementOpposite) {
    using Type = TypeParam::Type;

    constexpr auto Dimensions = TypeParam::Dimensions;

    constexpr auto last_element    = Minus(Dimensions, size_t {1});
    constexpr auto positive_value  = Affirm((Type)Dimensions);
    constexpr auto negative_value  = Negate((Type)Dimensions);

    auto lhs = VectorFromZero<Type, Dimensions>();
    auto rhs = VectorFromZero<Type, Dimensions>();

    Write(lhs, last_element, positive_value);
    Write(rhs, last_element, negative_value);

    AssertCompareImplementations(lhs, rhs, false);
}
