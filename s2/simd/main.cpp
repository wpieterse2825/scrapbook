#include <stdint.h>
#include <immintrin.h>

inline int32_t GetValue(uint8_t definition) {
    const auto lookup = _mm256_setr_epi8(
      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31);
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

    const auto lookup = _mm256_setr_epi32(
      (int32_t)Color::Red, (int32_t)Color::Green, (int32_t)Color::Blue, (int32_t)Color::White, (int32_t)Color::Black, -1, -1, -1);

    const auto tester  = _mm256_set1_epi32((int32_t)color);
    const auto mask    = _mm256_cmpeq_epi32(lookup, tester);
    const auto bitmask = _mm256_movemask_ps((__m256)mask) | (1 << 5);
    const auto index   = __builtin_ctz(bitmask);

    return result[index];
}

#include <iostream>
#include <bitset>

int main() {
    //std::cout << GetValue(0) << std::endl;

    std::cout << PaletteForANSI(Color::Red) << std::endl;
    std::cout << PaletteForANSI(Color::Green) << std::endl;
    std::cout << PaletteForANSI(Color::Blue) << std::endl;
    std::cout << PaletteForANSI(Color::White) << std::endl;
    std::cout << PaletteForANSI(Color::Black) << std::endl;
    std::cout << PaletteForANSI((Color)0xfefefefe) << std::endl;

    return 0;
}
