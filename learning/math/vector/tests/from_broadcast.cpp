#include "learning/math/vector/tests/shared.hpp"

template <typename Type>
class FromBroadcastTest : public testing::Test {};

TYPED_TEST_SUITE(FromBroadcastTest, TestTypeCollection);

template <typename Type, size_t Dimensions>
static auto FromBroadcast(const Type& value, bool all_elements) -> void {
    constexpr auto last_element = Dimensions - 1;

    constexpr auto simd_enabled       = MathSIMDEnabled;
    constexpr auto simd_enabled_avx_1 = MathSIMDEnableAVX1;
    constexpr auto simd_enabled_sse_2 = MathSIMDEnableSSE2;
    constexpr auto simd_enabled_sse_1 = MathSIMDEnableSSE1;
    constexpr auto simd_use_avx_1     = simd_enabled == true && simd_enabled_avx_1 == true;
    constexpr auto simd_use_sse_2     = simd_enabled == true && simd_enabled_sse_2 == true;
    constexpr auto simd_use_sse_1     = simd_enabled == true && simd_enabled_sse_1 == true;

    if constexpr (simd_use_avx_1 == true) {
        const auto output_avx_1 = detail::vector::avx_1::VectorFromBroadcast<Type, Dimensions>(value);

        if (all_elements == true) {
            for (auto index_avx_1 = size_t {0}; index_avx_1 < Dimensions; index_avx_1++) {
                const auto inner_value_avx_1 = Read(output_avx_1, index_avx_1);
                const bool is_equal_avx_1    = Equal(inner_value_avx_1, value);

                EXPECT_EQ(is_equal_avx_1, true) << "Index : " << index_avx_1 << " - Implementation - AVX 1";
            }
        } else {
            const auto inner_value_avx_1 = Read(output_avx_1, last_element);
            const bool is_equal_avx_1    = Equal(inner_value_avx_1, value);

            EXPECT_EQ(is_equal_avx_1, true) << "Index : " << last_element << " - Implementation - AVX 1";
        }
    }

    if constexpr (simd_use_sse_2 == true) {
        const auto output_sse_2 = detail::vector::sse_2::VectorFromBroadcast<Type, Dimensions>(value);

        if (all_elements == true) {
            for (auto index_sse_2 = size_t {0}; index_sse_2 < Dimensions; index_sse_2++) {
                const auto inner_value_sse_2 = Read(output_sse_2, index_sse_2);
                const bool is_equal_sse_2    = Equal(inner_value_sse_2, value);

                EXPECT_EQ(is_equal_sse_2, true) << "Index : " << index_sse_2 << " - Implementation - SSE 2";
            }
        } else {
            const auto inner_value_sse_2 = Read(output_sse_2, last_element);
            const bool is_equal_sse_2    = Equal(inner_value_sse_2, value);

            EXPECT_EQ(is_equal_sse_2, true) << "Index : " << last_element << " - Implementation - SSE 2";
        }
    }

    if constexpr (simd_use_sse_1 == true) {
        const auto output_sse_1 = detail::vector::sse_1::VectorFromBroadcast<Type, Dimensions>(value);

        if (all_elements == true) {
            for (auto index_sse_1 = size_t {0}; index_sse_1 < Dimensions; index_sse_1++) {
                const auto inner_value_sse_1 = Read(output_sse_1, index_sse_1);
                const bool is_equal_sse_1    = Equal(inner_value_sse_1, value);

                EXPECT_EQ(is_equal_sse_1, true) << "Index : " << index_sse_1 << " - Implementation - SSE 1";
            }
        } else {
            const auto inner_value_sse_1 = Read(output_sse_1, last_element);
            const bool is_equal_sse_1    = Equal(inner_value_sse_1, value);

            EXPECT_EQ(is_equal_sse_1, true) << "Index : " << last_element << " - Implementation - SSE 1";
        }
    }

    const auto output_general = detail::vector::general::VectorFromBroadcast<Type, Dimensions>(value);

    if (all_elements == true) {
        for (auto index_general = size_t {0}; index_general < Dimensions; index_general++) {
            const auto inner_value_general = Read(output_general, index_general);
            const bool is_equal_general    = Equal(inner_value_general, value);

            EXPECT_EQ(is_equal_general, true) << "Index : " << index_general << " - Implementation - General";
        }
    } else {
        const auto inner_value_general = Read(output_general, last_element);
        const bool is_equal_general    = Equal(inner_value_general, value);

        EXPECT_EQ(is_equal_general, true) << "Index : " << last_element << " - Implementation - General";
    }
}

TYPED_TEST(FromBroadcastTest, PassWithValueZeroAllElements) {
    using Type = TypeParam::Type;

    constexpr auto Dimensions = TypeParam::Dimensions;

    constexpr auto zero          = MathConstants<Type>::Zero;
    constexpr auto positive_zero = Affirm(zero);

    FromBroadcast<Type, Dimensions>(positive_zero, true);
}

TYPED_TEST(FromBroadcastTest, PassWithValueZeroLastElement) {
    using Type = TypeParam::Type;

    constexpr auto Dimensions = TypeParam::Dimensions;

    constexpr auto zero          = MathConstants<Type>::Zero;
    constexpr auto positive_zero = Affirm(zero);

    FromBroadcast<Type, Dimensions>(positive_zero, false);
}

TYPED_TEST(FromBroadcastTest, PassWithValuePositiveOneAllElements) {
    using Type = TypeParam::Type;

    constexpr auto Dimensions = TypeParam::Dimensions;

    constexpr auto one          = MathConstants<Type>::One;
    constexpr auto positive_one = Affirm(one);

    FromBroadcast<Type, Dimensions>(positive_one, true);
}

TYPED_TEST(FromBroadcastTest, PassWithValuePositiveOneLastElement) {
    using Type = TypeParam::Type;

    constexpr auto Dimensions = TypeParam::Dimensions;

    constexpr auto one          = MathConstants<Type>::One;
    constexpr auto positive_one = Affirm(one);

    FromBroadcast<Type, Dimensions>(positive_one, false);
}

TYPED_TEST(FromBroadcastTest, PassWithValueNegativeOneAllElements) {
    using Type = TypeParam::Type;

    constexpr auto Dimensions = TypeParam::Dimensions;

    constexpr auto one          = MathConstants<Type>::One;
    constexpr auto negative_one = Negate(one);

    FromBroadcast<Type, Dimensions>(negative_one, true);
}

TYPED_TEST(FromBroadcastTest, PassWithValueNegativeOneLastElement) {
    using Type = TypeParam::Type;

    constexpr auto Dimensions = TypeParam::Dimensions;

    constexpr auto one          = MathConstants<Type>::One;
    constexpr auto negative_one = Negate(one);

    FromBroadcast<Type, Dimensions>(negative_one, false);
}
