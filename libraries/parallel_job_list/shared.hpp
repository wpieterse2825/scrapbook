#pragma once

#include <assert.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <new>

#define CONST_ISPOWEROFTWO(x)             (((x) & ((x)-1)) == 0 && (x) > 0)
#define ASSERT_ENUM_STRING(string, index) (1 / (int)!(string - index)) ? #string : ""
#define BIT(num)                          (1ULL << (num))

template <class T>
T Maximum(T x, T y) {
    return (x > y) ? x : y;
}

template <class T>
T Minimum(T x, T y) {
    return (x < y) ? x : y;
}

uint64_t Sys_Microseconds();
