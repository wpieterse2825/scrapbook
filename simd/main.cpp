#include <stdint.h>
#include <cmath>
#include <immintrin.h>

struct FPlane {
    float x;
    float y;
    float z;
    float distance;
};

struct FPlaneSet {
    float x[32];
    float y[32];
    float z[32];
    float distance[32];

    FPlaneSet()
      : x {0.0f}
      , y {0.0f}
      , z {0.0f}
      , distance {0.0f} {
    }
};

FPlane planes[] = {
  {-1.0f, +0.0f, +0.0f, 10.0f},
  {+0.0f, +1.0f, +0.0f, 10.0f},
  {+1.0f, +0.0f, +0.0f, 10.0f},
  {+0.0f, -1.0f, +0.0f, 10.0f},
  {+0.0f, +0.0f, +1.0f, 10.0f},
  {+0.0f, +0.0f, -1.0f, 10.0f},
};

#define CROSS_PRODUCT(a, b)                                                                                                                                    \
    _mm256_permute4x64_pd(                                                                                                                                     \
      _mm256_sub_pd(_mm256_mul_pd(a, _mm256_permute4x64_pd(b, _MM_SHUFFLE(3, 0, 2, 1))), _mm256_mul_pd(b, _mm256_permute4x64_pd(a, _MM_SHUFFLE(3, 0, 2, 1)))), \
      _MM_SHUFFLE(3, 0, 2, 1))

inline __m256d CrossProduct(const __m256d& lhs, const __m256d& rhs) {
    return CROSS_PRODUCT(lhs, rhs);
}

inline __m256 Vector_Axis_Scale(__m256 scale, __m256 axis) {
    auto axis_scaled = _mm256_mul_ps(scale, axis);

    return axis_scaled;
}

inline void Vector_Scale(__m256 scale, __m256 axis_x, __m256 axis_y, __m256 axis_z, __m256& result_x, __m256& result_y, __m256& result_z) {
    result_x = Vector_Axis_Scale(scale, axis_x);
    result_y = Vector_Axis_Scale(scale, axis_y);
    result_z = Vector_Axis_Scale(scale, axis_z);
}

inline __m256 Vector_Axis_ScaledAdd(__m256 scale, __m256 lhs, __m256 rhs) {
    auto rhs_scaled = _mm256_mul_ps(scale, rhs);
    auto axis_add   = _mm256_add_ps(lhs, rhs_scaled);

    return axis_add;
}

inline void Vector_ScaledAdd(
  __m256 scale, __m256 lhs_x, __m256 lhs_y, __m256 lhs_z, __m256 rhs_x, __m256 rhs_y, __m256 rhs_z, __m256& result_x, __m256& result_y, __m256& result_z) {
    result_x = Vector_Axis_ScaledAdd(scale, lhs_x, rhs_x);
    result_y = Vector_Axis_ScaledAdd(scale, lhs_y, rhs_y);
    result_z = Vector_Axis_ScaledAdd(scale, lhs_z, rhs_z);
}

inline __m256 Vector_DotProduct(__m256 lhs_x, __m256 lhs_y, __m256 lhs_z, __m256 rhs_x, __m256 rhs_y, __m256 rhs_z) {
    auto x_multiplied = _mm256_mul_ps(lhs_x, rhs_x);
    auto y_multiplied = _mm256_mul_ps(lhs_y, rhs_y);
    auto z_multiplied = _mm256_mul_ps(lhs_z, rhs_z);

    auto xy_plus  = _mm256_add_ps(x_multiplied, y_multiplied);
    auto xyz_plus = _mm256_add_ps(xy_plus, z_multiplied);

    return xyz_plus;
}

inline __m256 Absolute(const __m256 input) {
    static const auto sign_mask = _mm256_set1_ps(-0.0f);

    return _mm256_andnot_ps(sign_mask, input);
}

inline void Vector_Normalize(const __m256 in_x, const __m256 in_y, const __m256 in_z, __m256& out_x, __m256& out_y, __m256& out_z) {
    auto x_times_x = _mm256_mul_ps(in_x, in_x);
    auto y_times_y = _mm256_mul_ps(in_y, in_y);
    auto z_times_z = _mm256_mul_ps(in_z, in_z);

    auto x_plus_y  = _mm256_add_ps(x_times_x, y_times_y);
    auto xy_plus_z = _mm256_add_ps(x_plus_y, z_times_z);

    auto length = _mm256_sqrt_ps(xy_plus_z);

    out_x = _mm256_div_ps(in_x, length);
    out_y = _mm256_div_ps(in_y, length);
    out_z = _mm256_div_ps(in_z, length);
}

inline void Vector_Normalize2(const __m256* in_x, const __m256* in_y, __m256* out_x, __m256* out_y) {
    // TODO(wpieterse): This should be part of a parameter somewhere, and not allocated like this.
    const uint64_t vectors   = 256;
    __m256*        x_times_x = static_cast<__m256*>(::malloc(sizeof(__m256) * vectors));
    __m256*        y_times_y = static_cast<__m256*>(::malloc(sizeof(__m256) * vectors));
    __m256*        x_plus_y  = static_cast<__m256*>(::malloc(sizeof(__m256) * vectors));
    __m256*        length    = static_cast<__m256*>(::malloc(sizeof(__m256) * vectors));

    for (uint64_t index = 0; index < vectors; index++) {
        x_times_x[index] = _mm256_mul_ps(in_x[index], in_x[index]);
        y_times_y[index] = _mm256_mul_ps(in_y[index], in_y[index]);
    }

    for (uint64_t index = 0; index < vectors; index++) {
        x_plus_y[index] = _mm256_add_ps(x_times_x[index], y_times_y[index]);
    }

    for (uint64_t index = 0; index < vectors; index++) {
        length[index] = _mm256_sqrt_ps(x_plus_y[index]);
    }

    for (uint64_t index = 0; index < vectors; index++) {
        out_x[index] = _mm256_div_ps(in_x[index], length[index]);
        out_y[index] = _mm256_div_ps(in_y[index], length[index]);
    }

    free(length);
    free(x_plus_y);
    free(y_times_y);
    free(x_times_x);
}

struct FNormalizeData {
    float x[16];
    float y[16];
    float z[16];

    float x_times_x[16];
    float y_times_y[16];
    float z_times_z[16];
    float x_plus_y[16];
    float xy_plus_z[16];
    float length[16];
};

static_assert(sizeof(FNormalizeData) == 576);

struct FPoint2D {
    __m256 x;
    __m256 y;
};

struct FPlane2D {
    __m256 x;
    __m256 y;
    __m256 distance;
};

FPlane2D Plane2DFromPoints(const FPoint2D start, const FPoint2D end) {
    FPlane2D result {};

    result.x = _mm256_sub_ps(start.y, end.y);
    result.y = _mm256_sub_ps(end.x, start.x);

    __m256 s_mul_p_x = _mm256_mul_ps(start.x, result.x);
    __m256 s_mul_p_y = _mm256_mul_ps(start.y, result.y);
    __m256 x_plus_y  = _mm256_add_ps(s_mul_p_x, s_mul_p_y);

    result.distance = _mm256_xor_ps(x_plus_y, _mm256_set1_ps(-0.0f));
    return result;
}

struct FPlaneSIMDSet {
    float x[8];
    float y[8];
    float z[8];
    float distance[8];
};

FPlane  global_planes[8 * 1024] = {};
int64_t global_planes_count     = 0;

FPlane  compressed_planes[8 * 1024] = {};
int64_t compressed_planes_count     = 0;

#define NORMAL_EPSILON   0.00001f
#define DISTANCE_EPSILON 0.01f

bool Compare(FPlane lhs, FPlane rhs, float normal_epsilon, float distance_epsilon) {
    auto lhs_x        = lhs.x;
    auto lhs_y        = lhs.y;
    auto lhs_z        = lhs.z;
    auto lhs_distance = lhs.distance;

    auto rhs_x        = rhs.x;
    auto rhs_y        = rhs.y;
    auto rhs_z        = rhs.z;
    auto rhs_distance = rhs.distance;

    auto x_value = lhs_x - rhs_x;
    if (fabsf(x_value) > normal_epsilon) {
        return false;
    }

    auto y_value = lhs_y - rhs_y;
    if (fabsf(y_value) > normal_epsilon) {
        return false;
    }

    auto z_value = lhs_z - rhs_z;
    if (fabsf(z_value) > normal_epsilon) {
        return false;
    }

    auto distance_value = lhs_distance - rhs_distance;
    if (fabsf(distance_value) > distance_epsilon) {
        return false;
    }

    return true;
}

size_t BitmaskDecode(uint64_t* bitmap, size_t bitmapsize, uint32_t* out) {
    size_t   pos = 0;
    uint64_t bitset;
    for (size_t k = 0; k < bitmapsize; ++k) {
        bitset = bitmap[k];
        while (bitset != 0) {
            uint64_t      t = bitset & -bitset;
            unsigned long r = __builtin_ctzll(bitset);
            out[pos++]      = k * 64 + r;
            bitset ^= t;
        }
    }
    return pos;
}

void CompressPlanes() {
    for (int64_t global_index = 0; global_index < global_planes_count; global_index++) {
        FPlane  global_plane     = global_planes[global_index];
        int64_t compressed_index = 0;

        for (compressed_index = 0; compressed_index < compressed_planes_count; compressed_index++) {
            FPlane compressed_plane = compressed_planes[compressed_index];

            if (Compare(global_plane, compressed_plane, NORMAL_EPSILON, DISTANCE_EPSILON) == true) {
                break;
            }
        }

        if (compressed_index == compressed_planes_count) {
            compressed_planes[compressed_planes_count] = global_plane;
            compressed_planes_count++;
        }
    }
}

uint8_t ComparePlanes(FPlane comparend, FPlaneSIMDSet comparitor) {
    __m256i sign_mask_value  = _mm256_set1_epi32(0x80000000);
    __m256  sign_mask        = _mm256_castsi256_ps(sign_mask_value);
    __m256  normal_epsilon   = _mm256_set1_ps(NORMAL_EPSILON);
    __m256  distance_epsilon = _mm256_set1_ps(DISTANCE_EPSILON);

    __m256 comparend_x = _mm256_set1_ps(comparend.x);
    __m256 comparend_y = _mm256_set1_ps(comparend.y);
    __m256 comparend_z = _mm256_set1_ps(comparend.z);
    __m256 comparend_d = _mm256_set1_ps(comparend.distance);

    __m256 comparitor_x = _mm256_loadu_ps(comparitor.x);
    __m256 comparitor_y = _mm256_loadu_ps(comparitor.y);
    __m256 comparitor_z = _mm256_loadu_ps(comparitor.z);
    __m256 comparitor_d = _mm256_loadu_ps(comparitor.distance);

    __m256 difference_x = _mm256_sub_ps(comparend_x, comparitor_x);
    __m256 difference_y = _mm256_sub_ps(comparend_y, comparitor_y);
    __m256 difference_z = _mm256_sub_ps(comparend_z, comparitor_z);
    __m256 difference_d = _mm256_sub_ps(comparend_d, comparitor_d);

    __m256 absolute_x = _mm256_andnot_ps(sign_mask, difference_x);
    __m256 absolute_y = _mm256_andnot_ps(sign_mask, difference_y);
    __m256 absolute_z = _mm256_andnot_ps(sign_mask, difference_z);
    __m256 absolute_d = _mm256_andnot_ps(sign_mask, difference_d);

    __m256 comparison_x = _mm256_cmp_ps(absolute_x, normal_epsilon, _CMP_LE_OQ);
    __m256 comparison_y = _mm256_cmp_ps(absolute_y, normal_epsilon, _CMP_LE_OQ);
    __m256 comparison_z = _mm256_cmp_ps(absolute_z, normal_epsilon, _CMP_LE_OQ);
    __m256 comparison_d = _mm256_cmp_ps(absolute_d, distance_epsilon, _CMP_LE_OQ);

    int mask_x = _mm256_movemask_ps(comparison_x);
    int mask_y = _mm256_movemask_ps(comparison_y);
    int mask_z = _mm256_movemask_ps(comparison_z);
    int mask_d = _mm256_movemask_ps(comparison_d);

    int mask_final = mask_x & mask_y & mask_z & mask_d;

    return mask_final;
}

inline int32_t GetValue(uint8_t definition) {
    const auto lookup  = _mm256_setr_epi8(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31);
    const auto vector  = _mm256_set1_epi8(definition);
    const auto mask    = _mm256_cmpeq_epi8(lookup, vector);
    const auto bitmask = _mm256_movemask_epi8(mask);

    if (bitmask != 0) {
        return __builtin_ctz(bitmask);
    }

    return -1;
}

enum class Color : int32_t {
    Red   = 0x00ff0000,
    Green = 0x0000ff00,
    Blue  = 0x000000ff,
    White = 0x00ffffff,
    Black = 0x00000000,
};

inline int32_t PaletteForANSI(Color color) {
    const int32_t result[6] = {31, 32, 34, 37, 30, -1};

    const auto lookup =
      _mm256_setr_epi32((int32_t)Color::Red, (int32_t)Color::Green, (int32_t)Color::Blue, (int32_t)Color::White, (int32_t)Color::Black, -1, -1, -1);

    const auto tester  = _mm256_set1_epi32((int32_t)color);
    const auto mask    = _mm256_cmpeq_epi32(lookup, tester);
    const auto bitmask = _mm256_movemask_ps((__m256)mask) | (1 << 5);
    const auto index   = __builtin_ctz(bitmask);

    return result[index];
}

#include <iostream>
#include <bitset>

int main() {
    // std::cout << GetValue(0) << std::endl;

    std::cout << PaletteForANSI(Color::Red) << std::endl;
    std::cout << PaletteForANSI(Color::Green) << std::endl;
    std::cout << PaletteForANSI(Color::Blue) << std::endl;
    std::cout << PaletteForANSI(Color::White) << std::endl;
    std::cout << PaletteForANSI(Color::Black) << std::endl;
    std::cout << PaletteForANSI((Color)0xfefefefe) << std::endl;

    return 0;
}
