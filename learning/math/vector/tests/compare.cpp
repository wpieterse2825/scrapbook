#include "learning/math/vector/tests/shared.hpp"

template <typename Type>
class CompareTest : public testing::Test {};

TYPED_TEST_SUITE(CompareTest, TestTypeCollection);

template <typename Type, size_t Dimensions>
static auto Compare(const Vector<Type, Dimensions>& lhs, const Vector<Type, Dimensions>& rhs, bool outcome) -> void {
    constexpr auto simd_enabled       = MathSIMDEnabled;
    constexpr auto simd_enabled_avx_1 = MathSIMDEnableAVX1;
    constexpr auto simd_enabled_sse_2 = MathSIMDEnableSSE2;
    constexpr auto simd_enabled_sse_1 = MathSIMDEnableSSE1;
    constexpr auto simd_use_avx_1     = simd_enabled == true && simd_enabled_avx_1 == true;
    constexpr auto simd_use_sse_2     = simd_enabled == true && simd_enabled_sse_2 == true;
    constexpr auto simd_use_sse_1     = simd_enabled == true && simd_enabled_sse_1 == true;

    if constexpr (simd_use_avx_1 == true) {
        const auto computed_avx_1 = detail::vector::avx_1::Compare(lhs, rhs);

        EXPECT_EQ(computed_avx_1, outcome) << "Implementation - AVX 1";
    }

    if constexpr (simd_use_sse_2 == true) {
        const auto computed_sse_2 = detail::vector::sse_2::Compare(lhs, rhs);

        EXPECT_EQ(computed_sse_2, outcome) << "Implementation - SSE 2";
    }

    if constexpr (simd_use_sse_1 == true) {
        const auto computed_sse_1 = detail::vector::sse_1::Compare(lhs, rhs);

        EXPECT_EQ(computed_sse_1, outcome) << "Implementation - SSE 1";
    }

    const auto computed_general = detail::vector::general::Compare(lhs, rhs);

    EXPECT_EQ(computed_general, outcome) << "Implementation - General";
}

TYPED_TEST(CompareTest, BaselinePassAllElementsPositive) {
    using Type = TypeParam::Type;

    constexpr auto Dimensions = TypeParam::Dimensions;

    constexpr auto positive_value = Affirm((Type)Dimensions);

    auto lhs = VectorFromZero<Type, Dimensions>();
    auto rhs = VectorFromZero<Type, Dimensions>();

    for (auto index = size_t {0}; index < Dimensions; index++) {
        Write(lhs, index, positive_value);
        Write(rhs, index, positive_value);
    }

    Compare(lhs, rhs, true);
}

TYPED_TEST(CompareTest, BaselinePassLastElementPositive) {
    using Type = TypeParam::Type;

    constexpr auto Dimensions = TypeParam::Dimensions;

    constexpr auto last_element   = Minus(Dimensions, size_t {1});
    constexpr auto positive_value = Affirm((Type)Dimensions);

    auto lhs = VectorFromZero<Type, Dimensions>();
    auto rhs = VectorFromZero<Type, Dimensions>();

    Write(lhs, last_element, positive_value);
    Write(rhs, last_element, positive_value);

    Compare(lhs, rhs, true);
}

TYPED_TEST(CompareTest, BaselinePassAllElementsNegative) {
    using Type = TypeParam::Type;

    constexpr auto Dimensions = TypeParam::Dimensions;

    constexpr auto negative_value = Negate((Type)Dimensions);

    auto lhs = VectorFromZero<Type, Dimensions>();
    auto rhs = VectorFromZero<Type, Dimensions>();

    for (auto index = size_t {0}; index < Dimensions; index++) {
        Write(lhs, index, negative_value);
        Write(rhs, index, negative_value);
    }

    Compare(lhs, rhs, true);
}

TYPED_TEST(CompareTest, BaselinePassLastElementNegative) {
    using Type = TypeParam::Type;

    constexpr auto Dimensions = TypeParam::Dimensions;

    constexpr auto last_element   = Minus(Dimensions, size_t {1});
    constexpr auto negative_value = Negate((Type)Dimensions);

    auto lhs = VectorFromZero<Type, Dimensions>();
    auto rhs = VectorFromZero<Type, Dimensions>();

    Write(lhs, last_element, negative_value);
    Write(rhs, last_element, negative_value);

    Compare(lhs, rhs, true);
}

TYPED_TEST(CompareTest, BaselineFailAllElementsOpposite) {
    using Type = TypeParam::Type;

    constexpr auto Dimensions = TypeParam::Dimensions;

    constexpr auto positive_value = Affirm((Type)Dimensions);
    constexpr auto negative_value = Negate((Type)Dimensions);

    auto lhs = VectorFromZero<Type, Dimensions>();
    auto rhs = VectorFromZero<Type, Dimensions>();

    for (auto index = size_t {0}; index < Dimensions; index++) {
        Write(lhs, index, positive_value);
        Write(rhs, index, negative_value);
    }

    Compare(lhs, rhs, false);
}

TYPED_TEST(CompareTest, BaselineFailLastElementOpposite) {
    using Type = TypeParam::Type;

    constexpr auto Dimensions = TypeParam::Dimensions;

    constexpr auto last_element   = Minus(Dimensions, size_t {1});
    constexpr auto positive_value = Affirm((Type)Dimensions);
    constexpr auto negative_value = Negate((Type)Dimensions);

    auto lhs = VectorFromZero<Type, Dimensions>();
    auto rhs = VectorFromZero<Type, Dimensions>();

    Write(lhs, last_element, positive_value);
    Write(rhs, last_element, negative_value);

    Compare(lhs, rhs, false);
}
