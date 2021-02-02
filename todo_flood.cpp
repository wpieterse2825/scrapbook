#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <immintrin.h>
#include <iostream>
#include <bitset>
// #include "iacaMarks.h"

struct RunCommandCondition {
    const char* command;
    const char* condition;
    uint16_t    status;
    uint8_t     command_length;
    uint8_t     condition_length;

    RunCommandCondition()
      : command {nullptr}
      , condition {nullptr}
      , status {0}
      , command_length {0}
      , condition_length {0} {
    }
};

void Parse(const char* buffer, RunCommandCondition* parsed) {
    // IACA_START

    const __m256i  buffer_vector    = _mm256_loadu_si256((const __m256i*)buffer);
    const __m256i  zero_vector      = _mm256_set1_epi8('\0');
    const __m256i  zero_comparison  = _mm256_cmpeq_epi8(zero_vector, buffer_vector);
    const uint32_t zero_mask        = _mm256_movemask_epi8(zero_comparison);
    const __m256i  colon_vector     = _mm256_set1_epi8(':');
    const __m256i  colon_comparison = _mm256_cmpeq_epi8(colon_vector, buffer_vector);
    const uint32_t colon_mask       = _mm256_movemask_epi8(colon_comparison);

    if (colon_mask == 0) {
        parsed->command = buffer;

        if (zero_mask == 0) {
            parsed->command_length = 32;
        } else {
            parsed->command_length = __builtin_ctz(zero_mask);
        }
    } else {
        const uint32_t colon_count = __builtin_popcount(colon_mask);
        if (colon_count > 1) {
            parsed->status = 1;
        } else {
            parsed->command        = buffer;
            parsed->command_length = __builtin_ctz(colon_mask);

            parsed->condition = buffer + parsed->command_length + 1;
            if (zero_mask == 0) {
                parsed->condition_length = 32 - parsed->command_length - 1;
            } else {
                parsed->condition_length = 32 - parsed->command_length - 1 - __builtin_clz(~zero_mask);
            }
        }
    }

    // IACA_END
}

int main(int argument_count, const char** arguments) {
    // const char*         run_condition_line = "build:test\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
    const char*         run_condition_line = "my_very_long_command:mycondition";
    RunCommandCondition run_condition      = {};

    Parse(run_condition_line, &run_condition);

    std::cout << (uint32_t)run_condition.status << std::endl;
    std::cout << (uint32_t)run_condition.command_length << std::endl;
    for (uint8_t index = 0; index < run_condition.command_length; index++) {
        std::cout << run_condition.command[index];
    }

    std::cout << std::endl;
    std::cout << (uint32_t)run_condition.condition_length << std::endl;
    for (uint8_t index = 0; index < run_condition.condition_length; index++) {
        std::cout << run_condition.condition[index];
    }

    std::cout << std::endl;
    return 0;
}
