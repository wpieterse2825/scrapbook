#include <string.h>
#include <immintrin.h>

#include <celero/Celero.h>

CELERO_MAIN

enum class TokenType {
    WhiteSpace,
    Dollar,
    Alpha,
    Number,
    Unknown,
};

struct Token {
    TokenType type;
};

bool IsAlpha(char character) {
    return (character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z');
}

bool IsNumber(char character) {
    return character >= '0' && character <= '9';
}

inline void ParseSimple(const char* buffer, size_t buffer_length, Token* tokens) {
    for (auto index = size_t {0}; index < buffer_length; index++) {
        auto current_character = buffer[index];

        if (current_character == ' ') {
            tokens[index].type = TokenType::WhiteSpace;
        } else if (current_character == '$') {
            tokens[index].type = TokenType::Dollar;
        } else if (IsAlpha(current_character)) {
            tokens[index].type = TokenType::Alpha;
        } else if (IsNumber(current_character)) {
            tokens[index].type = TokenType::Number;
        } else {
            tokens[index].type = TokenType::Unknown;
        }
    }
}

inline void SetTokens(uint32_t mask, Token* tokens, TokenType type) {
    while (mask != 0) {
        auto index = __builtin_ctz(mask);

        tokens[index].type = type;

        mask = mask & (mask - 1);
    }
}

inline void ParseSIMD(const char* buffer, size_t buffer_length, Token* tokens) {
    auto buffer_simd = ::_mm256_loadu_si256((const __m256i_u*)buffer);

    auto compare_whitespace = ::_mm256_cmpeq_epi8(buffer_simd, ::_mm256_set1_epi8(' '));
    auto compare_dollar     = ::_mm256_cmpeq_epi8(buffer_simd, ::_mm256_set1_epi8('$'));

    SetTokens(::_mm256_movemask_epi8(compare_whitespace), tokens, TokenType::WhiteSpace);
    SetTokens(::_mm256_movemask_epi8(compare_dollar), tokens, TokenType::Dollar);

    auto compare_0 = ::_mm256_cmpeq_epi8(buffer_simd, ::_mm256_set1_epi8('0'));
    auto compare_1 = ::_mm256_cmpeq_epi8(buffer_simd, ::_mm256_set1_epi8('1'));
    auto compare_2 = ::_mm256_cmpeq_epi8(buffer_simd, ::_mm256_set1_epi8('2'));
    auto compare_3 = ::_mm256_cmpeq_epi8(buffer_simd, ::_mm256_set1_epi8('3'));
    auto compare_4 = ::_mm256_cmpeq_epi8(buffer_simd, ::_mm256_set1_epi8('4'));
    auto compare_5 = ::_mm256_cmpeq_epi8(buffer_simd, ::_mm256_set1_epi8('5'));
    auto compare_6 = ::_mm256_cmpeq_epi8(buffer_simd, ::_mm256_set1_epi8('6'));
    auto compare_7 = ::_mm256_cmpeq_epi8(buffer_simd, ::_mm256_set1_epi8('7'));
    auto compare_8 = ::_mm256_cmpeq_epi8(buffer_simd, ::_mm256_set1_epi8('8'));
    auto compare_9 = ::_mm256_cmpeq_epi8(buffer_simd, ::_mm256_set1_epi8('9'));

    SetTokens(::_mm256_movemask_epi8(compare_0), tokens, TokenType::Number);
    SetTokens(::_mm256_movemask_epi8(compare_1), tokens, TokenType::Number);
    SetTokens(::_mm256_movemask_epi8(compare_2), tokens, TokenType::Number);
    SetTokens(::_mm256_movemask_epi8(compare_3), tokens, TokenType::Number);
    SetTokens(::_mm256_movemask_epi8(compare_4), tokens, TokenType::Number);
    SetTokens(::_mm256_movemask_epi8(compare_5), tokens, TokenType::Number);
    SetTokens(::_mm256_movemask_epi8(compare_6), tokens, TokenType::Number);
    SetTokens(::_mm256_movemask_epi8(compare_7), tokens, TokenType::Number);
    SetTokens(::_mm256_movemask_epi8(compare_8), tokens, TokenType::Number);
    SetTokens(::_mm256_movemask_epi8(compare_9), tokens, TokenType::Number);

    auto compare_a = ::_mm256_cmpeq_epi8(buffer_simd, ::_mm256_set1_epi8('a'));
    auto compare_b = ::_mm256_cmpeq_epi8(buffer_simd, ::_mm256_set1_epi8('b'));
    auto compare_c = ::_mm256_cmpeq_epi8(buffer_simd, ::_mm256_set1_epi8('c'));
    auto compare_d = ::_mm256_cmpeq_epi8(buffer_simd, ::_mm256_set1_epi8('d'));
    auto compare_e = ::_mm256_cmpeq_epi8(buffer_simd, ::_mm256_set1_epi8('e'));
    auto compare_f = ::_mm256_cmpeq_epi8(buffer_simd, ::_mm256_set1_epi8('f'));
    auto compare_g = ::_mm256_cmpeq_epi8(buffer_simd, ::_mm256_set1_epi8('g'));
    auto compare_h = ::_mm256_cmpeq_epi8(buffer_simd, ::_mm256_set1_epi8('h'));
    auto compare_i = ::_mm256_cmpeq_epi8(buffer_simd, ::_mm256_set1_epi8('i'));
    auto compare_j = ::_mm256_cmpeq_epi8(buffer_simd, ::_mm256_set1_epi8('j'));
    auto compare_k = ::_mm256_cmpeq_epi8(buffer_simd, ::_mm256_set1_epi8('k'));
    auto compare_l = ::_mm256_cmpeq_epi8(buffer_simd, ::_mm256_set1_epi8('l'));
    auto compare_m = ::_mm256_cmpeq_epi8(buffer_simd, ::_mm256_set1_epi8('m'));
    auto compare_n = ::_mm256_cmpeq_epi8(buffer_simd, ::_mm256_set1_epi8('n'));
    auto compare_o = ::_mm256_cmpeq_epi8(buffer_simd, ::_mm256_set1_epi8('o'));
    auto compare_p = ::_mm256_cmpeq_epi8(buffer_simd, ::_mm256_set1_epi8('p'));
    auto compare_q = ::_mm256_cmpeq_epi8(buffer_simd, ::_mm256_set1_epi8('q'));
    auto compare_r = ::_mm256_cmpeq_epi8(buffer_simd, ::_mm256_set1_epi8('r'));
    auto compare_s = ::_mm256_cmpeq_epi8(buffer_simd, ::_mm256_set1_epi8('s'));
    auto compare_t = ::_mm256_cmpeq_epi8(buffer_simd, ::_mm256_set1_epi8('t'));
    auto compare_u = ::_mm256_cmpeq_epi8(buffer_simd, ::_mm256_set1_epi8('u'));
    auto compare_v = ::_mm256_cmpeq_epi8(buffer_simd, ::_mm256_set1_epi8('v'));
    auto compare_w = ::_mm256_cmpeq_epi8(buffer_simd, ::_mm256_set1_epi8('w'));
    auto compare_x = ::_mm256_cmpeq_epi8(buffer_simd, ::_mm256_set1_epi8('x'));
    auto compare_y = ::_mm256_cmpeq_epi8(buffer_simd, ::_mm256_set1_epi8('y'));
    auto compare_z = ::_mm256_cmpeq_epi8(buffer_simd, ::_mm256_set1_epi8('z'));

    SetTokens(::_mm256_movemask_epi8(compare_a), tokens, TokenType::Alpha);
    SetTokens(::_mm256_movemask_epi8(compare_b), tokens, TokenType::Alpha);
    SetTokens(::_mm256_movemask_epi8(compare_c), tokens, TokenType::Alpha);
    SetTokens(::_mm256_movemask_epi8(compare_d), tokens, TokenType::Alpha);
    SetTokens(::_mm256_movemask_epi8(compare_e), tokens, TokenType::Alpha);
    SetTokens(::_mm256_movemask_epi8(compare_f), tokens, TokenType::Alpha);
    SetTokens(::_mm256_movemask_epi8(compare_g), tokens, TokenType::Alpha);
    SetTokens(::_mm256_movemask_epi8(compare_h), tokens, TokenType::Alpha);
    SetTokens(::_mm256_movemask_epi8(compare_i), tokens, TokenType::Alpha);
    SetTokens(::_mm256_movemask_epi8(compare_j), tokens, TokenType::Alpha);
    SetTokens(::_mm256_movemask_epi8(compare_k), tokens, TokenType::Alpha);
    SetTokens(::_mm256_movemask_epi8(compare_l), tokens, TokenType::Alpha);
    SetTokens(::_mm256_movemask_epi8(compare_m), tokens, TokenType::Alpha);
    SetTokens(::_mm256_movemask_epi8(compare_n), tokens, TokenType::Alpha);
    SetTokens(::_mm256_movemask_epi8(compare_o), tokens, TokenType::Alpha);
    SetTokens(::_mm256_movemask_epi8(compare_p), tokens, TokenType::Alpha);
    SetTokens(::_mm256_movemask_epi8(compare_q), tokens, TokenType::Alpha);
    SetTokens(::_mm256_movemask_epi8(compare_r), tokens, TokenType::Alpha);
    SetTokens(::_mm256_movemask_epi8(compare_s), tokens, TokenType::Alpha);
    SetTokens(::_mm256_movemask_epi8(compare_t), tokens, TokenType::Alpha);
    SetTokens(::_mm256_movemask_epi8(compare_u), tokens, TokenType::Alpha);
    SetTokens(::_mm256_movemask_epi8(compare_v), tokens, TokenType::Alpha);
    SetTokens(::_mm256_movemask_epi8(compare_w), tokens, TokenType::Alpha);
    SetTokens(::_mm256_movemask_epi8(compare_x), tokens, TokenType::Alpha);
    SetTokens(::_mm256_movemask_epi8(compare_y), tokens, TokenType::Alpha);
    SetTokens(::_mm256_movemask_epi8(compare_z), tokens, TokenType::Alpha);
}

const char* message = "This is a very long message 123 $";

BASELINE(Parser, Plain, 10, 10000000) {
    Token tokens[32] = {};

    ParseSimple(message, strlen(message), tokens);

    celero::DoNotOptimizeAway(tokens[31].type == TokenType::Dollar);
}

BENCHMARK(Parser, AVX_2, 10, 10000000) {
    Token tokens[32] = {};

    ParseSIMD(message, strlen(message), tokens);

    celero::DoNotOptimizeAway(tokens[31].type == TokenType::Dollar);
}
