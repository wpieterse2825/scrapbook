#include <stdint.h>

#define __OPTIMIZE__ 1
#include <immintrin.h>
#undef __OPTIMIZE__

#include <iostream>

#define FORCE_INLINE inline

namespace simd {
    using rd_32_256 = __m256;
    using rd_64_256 = __m256d;
    using ri_32_256 = __m256i;

    FORCE_INLINE rd_32_256 load_value(float fill) {
        return ::_mm256_set1_ps(fill);
    }

    FORCE_INLINE rd_64_256 load_value(double fill) {
        return ::_mm256_set1_pd(fill);
    }

    FORCE_INLINE ri_32_256 load_value_i32(int32_t fill) {
        return ::_mm256_set1_epi32(fill);
    }

    FORCE_INLINE rd_32_256 load_from(float const* source) {
        return ::_mm256_loadu_ps(source);
    }

    FORCE_INLINE rd_64_256 load_from(double const* source) {
        return ::_mm256_loadu_pd(source);
    }

    FORCE_INLINE ri_32_256 load_from(int32_t const* source) {
        return ::_mm256_loadu_si256((const __m256i*)source);
    }

    FORCE_INLINE ri_32_256 load_from(uint32_t const* source) {
        return ::_mm256_loadu_si256((const __m256i*)source);
    }

    FORCE_INLINE rd_32_256 load_from_masked(float const* source, rd_32_256 fill, ri_32_256 mask) {
        // TODO(wpieterse): Do the actual masked load with fill.
        return ::_mm256_maskload_ps(source, mask);
    }

    FORCE_INLINE rd_32_256 load_from_masked(float const* source, float fill, ri_32_256 mask) {
        const auto fill_register = load_value(fill);

        return load_from_masked(source, fill_register, mask);
    }

    FORCE_INLINE rd_64_256 load_from_masked(double const* source, rd_64_256 fill, ri_32_256 mask) {
        // TODO(wpieterse): Do the actual masked load with fill.
        return ::_mm256_maskload_pd(source, mask);
    }

    FORCE_INLINE rd_64_256 load_from_masked(double const* source, double fill, ri_32_256 mask) {
        const auto fill_register = load_value(fill);

        return load_from_masked(source, fill_register, mask);
    }

    FORCE_INLINE ri_32_256 load_from_masked(int32_t const* source, ri_32_256 fill, ri_32_256 mask) {
        // TODO(wpieterse): Do the actual masked load with fill.
        return ::_mm256_maskload_epi32(source, mask);
    }

    FORCE_INLINE ri_32_256 load_from_masked(int32_t const* source, int32_t fill, ri_32_256 mask) {
        const auto fill_register = load_value_i32(fill);

        return load_from_masked(source, fill_register, mask);
    }

    FORCE_INLINE void save_to(rd_32_256 source, float* destination) {
        ::_mm256_storeu_ps(destination, source);
    }

    FORCE_INLINE void save_to(rd_64_256 source, double* destination) {
        ::_mm256_storeu_pd(destination, source);
    }

    FORCE_INLINE void save_to(ri_32_256 source, int32_t* destination) {
        ::_mm256_storeu_si256((__m256i*)destination, source);
    }

    FORCE_INLINE void save_to(ri_32_256 source, uint32_t* destination) {
        ::_mm256_storeu_si256((__m256i*)destination, source);
    }

    FORCE_INLINE void save_to_masked(rd_32_256 source, ri_32_256 mask, float* destination) {
        ::_mm256_maskstore_ps(destination, mask, source);
    }

    FORCE_INLINE void save_to_masked(rd_64_256 source, ri_32_256 mask, double* destination) {
        ::_mm256_maskstore_pd(destination, mask, source);
    }

    FORCE_INLINE void save_to_masked(ri_32_256 source, ri_32_256 mask, int32_t* destination) {
        ::_mm256_maskstore_epi32(destination, mask, source);
    }

    /*
    FORCE_INLINE rd_32_256 blend(rd_32_256 lhs, rd_32_256 rhs, const uint32_t mask) {
        return ::_mm256_blend_ps(lhs, rhs, mask);
    }

    FORCE_INLINE rd_64_256 blend(rd_64_256 lhs, rd_64_256 rhs, const uint32_t mask) {
        return ::_mm256_blend_pd(lhs, rhs, mask);
    }

    FORCE_INLINE ri_32_256 blend(ri_32_256 lhs, ri_32_256 rhs, const uint32_t mask) {
        return ::_mm256_blend_epi32(lhs, rhs, mask);
    }
    */

    template <uint32_t element_a, uint32_t element_b, uint32_t element_c, uint32_t element_d>
    FORCE_INLINE uint32_t make_permutation_mask_integer() {
        static_assert(element_a < 4);
        static_assert(element_b < 4);
        static_assert(element_c < 4);
        static_assert(element_d < 4);

        return (element_d << 6) | (element_c << 4) | (element_b << 2) | element_a;
    }

    template <uint32_t element_a,
              uint32_t element_b,
              uint32_t element_c,
              uint32_t element_d,
              uint32_t element_e,
              uint32_t element_f,
              uint32_t element_g,
              uint32_t element_h>
    FORCE_INLINE ri_32_256 make_permutation_mask_register() {
        static_assert(element_a < 8);
        static_assert(element_b < 8);
        static_assert(element_c < 8);
        static_assert(element_d < 8);
        static_assert(element_e < 8);
        static_assert(element_f < 8);
        static_assert(element_g < 8);
        static_assert(element_h < 8);

        return ::_mm256_setr_epi32(element_a, element_b, element_c, element_d, element_e, element_f, element_g, element_h);
    }

    FORCE_INLINE rd_32_256 permute(rd_32_256 source, ri_32_256 permutation) {
        return ::_mm256_permutevar8x32_ps(source, permutation);
    }

    /*
    FORCE_INLINE rd_64_256 permute(rd_64_256 source, uint32_t permutation) {
        return ::_mm256_permute4x64_pd(source, permutation);
    }
    */

    FORCE_INLINE ri_32_256 permute(ri_32_256 source, ri_32_256 permutation) {
        return ::_mm256_permutevar8x32_epi32(source, permutation);
    }

    FORCE_INLINE rd_32_256 permute_masked(rd_32_256 lhs, rd_32_256 rhs, ri_32_256 permutation, ri_32_256 mask) {
        // TODO(wpieterse): Do the actual masked load with fill.
        return permute(lhs, permutation);
    }

    /*
    FORCE_INLINE rd_64_256 permute_masked(rd_64_256 lhs, rd_64_256 rhs, uint32_t permutation, ri_32_256 mask) {
        // TODO(wpieterse): Do the actual masked load with fill.
        return permute(lhs, permutation);
    }
    */

    FORCE_INLINE ri_32_256 permute_masked(ri_32_256 lhs, ri_32_256 rhs, ri_32_256 permutation, ri_32_256 mask) {
        // TODO(wpieterse): Do the actual masked load with fill.
        return permute(lhs, permutation);
    }

    template <int32_t offset>
    FORCE_INLINE rd_32_256 rotate(rd_32_256 input) {
        if constexpr ((offset % 8) == 0) {
            return input;
        } else {
            constexpr auto bias = (offset > 0) ? (8 - (offset % 8)) : -offset;

            constexpr auto element_a = (bias + 0) % 8;
            constexpr auto element_b = (bias + 1) % 8;
            constexpr auto element_c = (bias + 2) % 8;
            constexpr auto element_d = (bias + 3) % 8;
            constexpr auto element_e = (bias + 4) % 8;
            constexpr auto element_f = (bias + 5) % 8;
            constexpr auto element_g = (bias + 6) % 8;
            constexpr auto element_h = (bias + 7) % 8;

            const auto permutation = make_permutation_mask_register<element_a, element_b, element_c, element_d, element_e, element_f, element_g, element_h>();

            return permute(input, permutation);
        }
    }

    template <int32_t offset>
    FORCE_INLINE rd_32_256 rotate_down(rd_32_256 input) {
        static_assert(offset >= 0);

        return rotate<-offset>(input);
    }

    template <int32_t offset>
    FORCE_INLINE rd_32_256 rotate_up(rd_32_256 input) {
        static_assert(offset >= 0);

        return rotate<offset>(input);
    }

    template <int32_t offset>
    FORCE_INLINE rd_64_256 rotate(rd_64_256 input) {
        if constexpr ((offset % 4) == 0) {
            return input;
        } else {
            constexpr auto bias = (offset > 0) ? (4 - (offset % 4)) : -offset;

            constexpr auto element_a = (bias + 0) % 4;
            constexpr auto element_b = (bias + 1) % 4;
            constexpr auto element_c = (bias + 2) % 4;
            constexpr auto element_d = (bias + 3) % 4;

            const auto permutation = make_permutation_mask_integer<element_a, element_b, element_c, element_d>();

            return permute(input, permutation);
        }
    }

    template <int32_t offset>
    FORCE_INLINE rd_64_256 rotate_down(rd_64_256 input) {
        static_assert(offset >= 0);

        return rotate<-offset>(input);
    }

    template <int32_t offset>
    FORCE_INLINE rd_64_256 rotate_up(rd_64_256 input) {
        static_assert(offset >= 0);

        return rotate<offset>(input);
    }

    template <int32_t offset>
    FORCE_INLINE ri_32_256 rotate(ri_32_256 input) {
        if constexpr ((offset % 8) == 0) {
            return input;
        } else {
            constexpr auto bias = (offset > 0) ? (8 - (offset % 8)) : -offset;

            constexpr auto element_a = (bias + 0) % 8;
            constexpr auto element_b = (bias + 1) % 8;
            constexpr auto element_c = (bias + 2) % 8;
            constexpr auto element_d = (bias + 3) % 8;
            constexpr auto element_e = (bias + 4) % 8;
            constexpr auto element_f = (bias + 5) % 8;
            constexpr auto element_g = (bias + 6) % 8;
            constexpr auto element_h = (bias + 7) % 8;

            const auto permutation = make_permutation_mask_register<element_a, element_b, element_c, element_d, element_e, element_f, element_g, element_h>();

            return permute(input, permutation);
        }
    }

    template <int32_t offset>
    FORCE_INLINE ri_32_256 rotate_down(ri_32_256 input) {
        static_assert(offset >= 0);

        return rotate<-offset>(input);
    }

    template <int32_t offset>
    FORCE_INLINE ri_32_256 rotate_up(ri_32_256 input) {
        static_assert(offset >= 0);

        return rotate<offset>(input);
    }

    template <int32_t offset>
    FORCE_INLINE constexpr uint32_t shift_down_blend_mask() {
        static_assert(offset >= 0 && offset <= 8);

        if constexpr (offset == 0) {
            return 0b00000000;
        }

        if constexpr (offset == 1) {
            return 0b00000001;
        }

        if constexpr (offset == 2) {
            return 0b00000011;
        }

        if constexpr (offset == 3) {
            return 0b00000111;
        }

        if constexpr (offset == 4) {
            return 0b00001111;
        }

        if constexpr (offset == 5) {
            return 0b00011111;
        }

        if constexpr (offset == 6) {
            return 0b00111111;
        }

        if constexpr (offset == 7) {
            return 0b01111111;
        }
    }

    template <int32_t offset>
    FORCE_INLINE rd_32_256 shift_down(rd_32_256 input) {
        static_assert(offset >= 0);
        static_assert(offset <= 8);

        const auto input_rotated    = rotate_down<offset>(input);
        const auto shift_in_value   = load_value(0.0f);
        const auto shift_blend_mask = shift_down_blend_mask<offset>();

        return ::_mm256_blend_ps(input_rotated, shift_in_value, shift_blend_mask);
    }

    template <int32_t offset>
    FORCE_INLINE ri_32_256 shift_down(ri_32_256 input) {
        static_assert(offset >= 0 && offset <= 8);

        const auto input_rotated     = rotate_down<offset>(input);
        const auto shift_in_value    = load_value_i32(0.0);
        const auto shift_blend_mask  = shift_down_blend_mask<offset>();
        const auto input_rotated_ps  = ::_mm256_cvtepi32_ps(input_rotated);
        const auto shift_in_value_ps = ::_mm256_cvtepi32_ps(shift_in_value);
        const auto result            = ::_mm256_blend_ps(input_rotated_ps, shift_in_value_ps, shift_blend_mask);
        const auto result_epi32      = ::_mm256_cvtps_epi32(result);

        return result_epi32;
    }

    // y = x & (-x)
    FORCE_INLINE ri_32_256 isolate_rightmost_set_bit(ri_32_256 input) {
        const auto sign_bit = ::_mm256_set1_epi32(1 << 31);
        const auto negated  = ::_mm256_or_si256(input, sign_bit);
        const auto isolated = ::_mm256_and_si256(input, negated);

        return isolated;
    }

    // y = ~x & (x+1)
    FORCE_INLINE ri_32_256 isolate_rightmost_cleared_bit(ri_32_256 input) {
        const auto one            = ::_mm256_set1_epi32(1);
        const auto input_plus_one = ::_mm256_add_epi32(input, one);
        const auto and_not        = ::_mm256_andnot_si256(input, input_plus_one);

        return and_not;
    }

    // y = x | (x+1)
    FORCE_INLINE ri_32_256 set_rightmost_cleared_bit(ri_32_256 input) {
        const auto one            = ::_mm256_set1_epi32(1);
        const auto input_plus_one = ::_mm256_add_epi32(input, one);
        const auto result         = ::_mm256_or_si256(input, input_plus_one);

        return result;
    }
} // namespace simd

void PrintSIMDRegister(const simd::ri_32_256& simd_register) {
    int32_t output[8] = {0};
    simd::save_to(simd_register, output);

    std::cout << " - [ ";
    for (auto index = 0; index < 8; index++) {
        std::cout << index << "/" << output[index];

        if (index != 7) {
            std::cout << ", ";
        }
    }

    std::cout << " ]" << std::endl;
}

void RotateDown() {
    int32_t input[8] = {0, 1, 2, 3, 4, 5, 6, 7};

    auto input_register   = simd::load_from(input);

    auto rotated_by_0_register = simd::rotate_down<0>(input_register);
    auto rotated_by_1_register = simd::rotate_down<1>(input_register);
    auto rotated_by_2_register = simd::rotate_down<2>(input_register);
    auto rotated_by_3_register = simd::rotate_down<3>(input_register);
    auto rotated_by_4_register = simd::rotate_down<4>(input_register);
    auto rotated_by_5_register = simd::rotate_down<5>(input_register);
    auto rotated_by_6_register = simd::rotate_down<6>(input_register);
    auto rotated_by_7_register = simd::rotate_down<7>(input_register);
    auto rotated_by_8_register = simd::rotate_down<8>(input_register);

    PrintSIMDRegister(rotated_by_0_register);
    PrintSIMDRegister(rotated_by_1_register);
    PrintSIMDRegister(rotated_by_2_register);
    PrintSIMDRegister(rotated_by_3_register);
    PrintSIMDRegister(rotated_by_4_register);
    PrintSIMDRegister(rotated_by_5_register);
    PrintSIMDRegister(rotated_by_6_register);
    PrintSIMDRegister(rotated_by_7_register);
    PrintSIMDRegister(rotated_by_8_register);
}

void RotateUp() {
    int32_t input[8] = {0, 1, 2, 3, 4, 5, 6, 7};

    auto input_register   = simd::load_from(input);

    auto rotated_by_0_register = simd::rotate_up<0>(input_register);
    auto rotated_by_1_register = simd::rotate_up<1>(input_register);
    auto rotated_by_2_register = simd::rotate_up<2>(input_register);
    auto rotated_by_3_register = simd::rotate_up<3>(input_register);
    auto rotated_by_4_register = simd::rotate_up<4>(input_register);
    auto rotated_by_5_register = simd::rotate_up<5>(input_register);
    auto rotated_by_6_register = simd::rotate_up<6>(input_register);
    auto rotated_by_7_register = simd::rotate_up<7>(input_register);
    auto rotated_by_8_register = simd::rotate_up<8>(input_register);

    PrintSIMDRegister(rotated_by_0_register);
    PrintSIMDRegister(rotated_by_1_register);
    PrintSIMDRegister(rotated_by_2_register);
    PrintSIMDRegister(rotated_by_3_register);
    PrintSIMDRegister(rotated_by_4_register);
    PrintSIMDRegister(rotated_by_5_register);
    PrintSIMDRegister(rotated_by_6_register);
    PrintSIMDRegister(rotated_by_7_register);
    PrintSIMDRegister(rotated_by_8_register);
}

int main() {
    std::cout << "==================================================" << std::endl;
    std::cout << "SIMD (Rotate Down):" << std::endl;
    RotateDown();
    std::cout << "==================================================" << std::endl;

    std::cout << std::endl;

    std::cout << "==================================================" << std::endl;
    std::cout << "SIMD (Rotate Up):" << std::endl;
    RotateUp();
    std::cout << "==================================================" << std::endl;

    return 0;
}
