#pragma once

#include <benchmark/benchmark.h>

#define BENCHMARK_ENUMERATE(Function)                                                                                                      \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Unsigned8, 1);                                                                  \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Unsigned8, 2);                                                                  \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Unsigned8, 4);                                                                  \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Unsigned8, 8);                                                                  \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Unsigned8, 16);                                                                 \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Unsigned8, 32);                                                                 \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Unsigned8, 64);                                                                 \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Unsigned16, 1);                                                                 \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Unsigned16, 2);                                                                 \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Unsigned16, 4);                                                                 \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Unsigned16, 8);                                                                 \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Unsigned16, 16);                                                                \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Unsigned16, 32);                                                                \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Unsigned32, 1);                                                                 \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Unsigned32, 2);                                                                 \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Unsigned32, 4);                                                                 \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Unsigned32, 8);                                                                 \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Unsigned32, 16);                                                                \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Unsigned64, 1);                                                                 \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Unsigned64, 2);                                                                 \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Unsigned64, 4);                                                                 \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Unsigned64, 8);                                                                 \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Signed8, 1);                                                                    \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Signed8, 2);                                                                    \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Signed8, 4);                                                                    \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Signed8, 8);                                                                    \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Signed8, 16);                                                                   \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Signed8, 32);                                                                   \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Signed8, 64);                                                                   \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Signed16, 1);                                                                   \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Signed16, 2);                                                                   \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Signed16, 4);                                                                   \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Signed16, 8);                                                                   \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Signed16, 16);                                                                  \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Signed16, 32);                                                                  \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Signed32, 1);                                                                   \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Signed32, 2);                                                                   \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Signed32, 4);                                                                   \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Signed32, 8);                                                                   \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Signed32, 16);                                                                  \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Signed64, 1);                                                                   \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Signed64, 2);                                                                   \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Signed64, 4);                                                                   \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Signed64, 8);                                                                   \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Decimal32, 1);                                                                  \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Decimal32, 2);                                                                  \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Decimal32, 4);                                                                  \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Decimal32, 8);                                                                  \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Decimal32, 16);                                                                 \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Decimal64, 1);                                                                  \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Decimal64, 2);                                                                  \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Decimal64, 4);                                                                  \
    BENCHMARK_TEMPLATE(Function, BENCHMARK_IMPLEMENTATION, Decimal64, 8);
