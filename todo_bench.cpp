#include <benchmark/benchmark.h>

#include <stdint.h>
#include <string.h>
#include <immintrin.h>

void ThingCallback(const char* name) {
    benchmark::DoNotOptimize(name);
}

#define XSTR(s) STR(s)
#define STR(s)  #s

#define GPA_SIMPLE()                                                                                                                       \
    if (!strcmp(name, "vkSomething" XSTR(__COUNTER__)))                                                                                    \
        return nullptr;

void* GetProcAddressSimple(const char* name) {
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();
    GPA_SIMPLE();

    if (!strcmp(name, "vkCallback")) {
        return (void*)&ThingCallback;
    }

    return nullptr;
}

inline constexpr uint32_t MurmurHash2(const void* key, int32_t len, uint32_t seed) {
    const unsigned int   m    = 0x5bd1e995;
    const int            r    = 24;
    unsigned int         h    = seed ^ len;
    const unsigned char* data = (const unsigned char*)key;

    while (len >= 4) {
        unsigned int k = *(unsigned int*)data;

        k *= m;
        k ^= k >> r;
        k *= m;

        h *= m;
        h ^= k;

        data += 4;
        len -= 4;
    }

    switch (len) {
        case 3:
            h ^= data[2] << 16;
        case 2:
            h ^= data[1] << 8;
        case 1:
            h ^= data[0];
            h *= m;
    };

    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;
    return h;
}

#define HASH_SIMD() MurmurHash2("vkSomething" XSTR(__COUNTER__), strlen("vkSomething" XSTR(__COUNTER__)), 0)

uint32_t hashes[] = {HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),
                     HASH_SIMD(),

                     MurmurHash2("vkCallback", strlen("vkCallback"), 0)};

void* result[] = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, (void*)&ThingCallback};

const auto hash_vector_1 = _mm256_set_epi32(hashes[0], hashes[1], hashes[2], hashes[3], hashes[4], hashes[5], hashes[6], hashes[7]);
const auto hash_vector_2 = _mm256_set_epi32(hashes[8], hashes[9], hashes[10], hashes[11], hashes[12], hashes[13], hashes[14], hashes[15]);
const auto hash_vector_3 = _mm256_set_epi32(hashes[16], hashes[17], hashes[18], hashes[19], hashes[20], hashes[21], hashes[22], hashes[23]);
const auto hash_vector_4 = _mm256_set_epi32(hashes[24], hashes[25], hashes[26], hashes[27], hashes[28], hashes[29], hashes[30], hashes[31]);
const auto hash_vector_5 = _mm256_set_epi32(hashes[32], hashes[33], hashes[34], hashes[35], hashes[36], hashes[37], hashes[38], hashes[39]);
const auto hash_vector_6 = _mm256_set_epi32(hashes[40], hashes[41], hashes[42], hashes[43], hashes[44], hashes[45], hashes[46], hashes[47]);
const auto hash_vector_7 = _mm256_set_epi32(hashes[48], hashes[49], hashes[50], hashes[51], hashes[52], hashes[53], hashes[54], hashes[55]);
const auto hash_vector_8 = _mm256_set_epi32(hashes[56], hashes[57], hashes[58], hashes[59], hashes[60], hashes[61], hashes[62], hashes[63]);
const auto hash_vector_9 = _mm256_set_epi32(hashes[64], hashes[65], hashes[66], hashes[67], hashes[68], hashes[69], hashes[70], hashes[71]);
const auto hash_vector_10 =
  _mm256_set_epi32(hashes[72], hashes[73], hashes[74], hashes[75], hashes[76], hashes[77], hashes[78], hashes[79]);
const auto hash_vector_11 =
  _mm256_set_epi32(hashes[80], hashes[81], hashes[82], hashes[83], hashes[84], hashes[85], hashes[86], hashes[87]);
const auto hash_vector_12 =
  _mm256_set_epi32(hashes[88], hashes[89], hashes[90], hashes[91], hashes[92], hashes[93], hashes[94], hashes[95]);
const auto hash_vector_13 =
  _mm256_set_epi32(hashes[96], hashes[97], hashes[98], hashes[99], hashes[100], hashes[101], hashes[102], hashes[103]);
const auto hash_vector_14 =
  _mm256_set_epi32(hashes[104], hashes[105], hashes[106], hashes[107], hashes[108], hashes[109], hashes[110], hashes[111]);
const auto hash_vector_15 =
  _mm256_set_epi32(hashes[112], hashes[113], hashes[114], hashes[115], hashes[116], hashes[117], hashes[118], hashes[119]);
const auto hash_vector_16 =
  _mm256_set_epi32(hashes[120], hashes[121], hashes[122], hashes[123], hashes[124], hashes[125], hashes[126], hashes[127]);
const auto hash_vector_17 =
  _mm256_set_epi32(hashes[128], hashes[129], hashes[130], hashes[131], hashes[132], hashes[133], hashes[134], hashes[135]);
const auto hash_vector_18 =
  _mm256_set_epi32(hashes[136], hashes[137], hashes[138], hashes[139], hashes[140], hashes[141], hashes[142], hashes[143]);
const auto hash_vector_19 =
  _mm256_set_epi32(hashes[144], hashes[145], hashes[146], hashes[147], hashes[148], hashes[149], hashes[150], hashes[151]);
const auto hash_vector_20 =
  _mm256_set_epi32(hashes[152], hashes[153], hashes[154], hashes[155], hashes[156], hashes[157], hashes[158], hashes[159]);
const auto hash_vector_21 =
  _mm256_set_epi32(hashes[160], hashes[161], hashes[162], hashes[163], hashes[164], hashes[165], hashes[166], hashes[167]);
const auto hash_vector_22 =
  _mm256_set_epi32(hashes[168], hashes[169], hashes[170], hashes[171], hashes[172], hashes[173], hashes[174], hashes[175]);
const auto hash_vector_23 =
  _mm256_set_epi32(hashes[176], hashes[177], hashes[178], hashes[179], hashes[180], hashes[181], hashes[182], hashes[183]);
const auto hash_vector_24 =
  _mm256_set_epi32(hashes[184], hashes[185], hashes[186], hashes[187], hashes[188], hashes[189], hashes[190], hashes[191]);
const auto hash_vector_25 =
  _mm256_set_epi32(hashes[192], hashes[193], hashes[194], hashes[195], hashes[196], hashes[197], hashes[198], hashes[199]);
const auto hash_vector_26 =
  _mm256_set_epi32(hashes[200], hashes[201], hashes[202], hashes[203], hashes[204], hashes[205], hashes[206], hashes[207]);
const auto hash_vector_27 =
  _mm256_set_epi32(hashes[208], hashes[209], hashes[210], hashes[211], hashes[212], hashes[213], hashes[214], hashes[215]);
const auto hash_vector_28 =
  _mm256_set_epi32(hashes[216], hashes[217], hashes[218], hashes[219], hashes[220], hashes[221], hashes[222], hashes[223]);
const auto hash_vector_29 =
  _mm256_set_epi32(hashes[224], hashes[225], hashes[226], hashes[227], hashes[228], hashes[229], hashes[230], hashes[231]);
const auto hash_vector_30 =
  _mm256_set_epi32(hashes[232], hashes[233], hashes[234], hashes[235], hashes[236], hashes[237], hashes[238], hashes[239]);
const auto hash_vector_31 =
  _mm256_set_epi32(hashes[240], hashes[241], hashes[242], hashes[243], hashes[244], hashes[245], hashes[246], hashes[247]);
const auto hash_vector_32 =
  _mm256_set_epi32(hashes[248], hashes[249], hashes[250], hashes[251], hashes[252], hashes[253], hashes[254], hashes[255]);
const auto hash_vector_33 =
  _mm256_set_epi32(hashes[256], hashes[257], hashes[258], hashes[259], hashes[260], hashes[261], hashes[262], hashes[263]);
const auto hash_vector_34 =
  _mm256_set_epi32(hashes[264], hashes[265], hashes[266], hashes[267], hashes[268], hashes[269], hashes[270], hashes[271]);
const auto hash_vector_35 =
  _mm256_set_epi32(hashes[272], hashes[273], hashes[274], hashes[275], hashes[276], hashes[277], hashes[278], hashes[279]);
const auto hash_vector_36 =
  _mm256_set_epi32(hashes[280], hashes[281], hashes[282], hashes[283], hashes[284], hashes[285], hashes[286], hashes[287]);
const auto hash_vector_37 =
  _mm256_set_epi32(hashes[288], hashes[289], hashes[290], hashes[291], hashes[292], hashes[293], hashes[294], hashes[295]);
const auto hash_vector_38 =
  _mm256_set_epi32(hashes[296], hashes[297], hashes[298], hashes[299], hashes[300], hashes[301], hashes[302], hashes[303]);
const auto hash_vector_39 =
  _mm256_set_epi32(hashes[304], hashes[305], hashes[306], hashes[307], hashes[308], hashes[309], hashes[310], hashes[311]);
const auto hash_vector_40 =
  _mm256_set_epi32(hashes[312], hashes[313], hashes[314], hashes[315], hashes[316], hashes[317], hashes[318], hashes[319]);
const auto hash_vector_41 =
  _mm256_set_epi32(hashes[320], hashes[321], hashes[322], hashes[323], hashes[324], hashes[325], hashes[326], hashes[327]);
const auto hash_vector_42 =
  _mm256_set_epi32(hashes[328], hashes[329], hashes[330], hashes[331], hashes[332], hashes[333], hashes[334], hashes[335]);
const auto hash_vector_43 =
  _mm256_set_epi32(hashes[336], hashes[337], hashes[338], hashes[339], hashes[340], hashes[341], hashes[342], hashes[343]);
const auto hash_vector_44 =
  _mm256_set_epi32(hashes[344], hashes[345], hashes[346], hashes[347], hashes[348], hashes[349], hashes[350], hashes[351]);
const auto hash_vector_45 =
  _mm256_set_epi32(hashes[352], hashes[353], hashes[354], hashes[355], hashes[356], hashes[357], hashes[358], hashes[359]);
const auto hash_vector_46 =
  _mm256_set_epi32(hashes[360], hashes[361], hashes[362], hashes[363], hashes[364], hashes[365], hashes[366], hashes[367]);
const auto hash_vector_47 =
  _mm256_set_epi32(hashes[368], hashes[369], hashes[370], hashes[371], hashes[372], hashes[373], hashes[374], hashes[375]);
const auto hash_vector_48 =
  _mm256_set_epi32(hashes[376], hashes[377], hashes[378], hashes[379], hashes[380], hashes[381], hashes[382], hashes[383]);
const auto hash_vector_49 =
  _mm256_set_epi32(hashes[384], hashes[385], hashes[386], hashes[387], hashes[388], hashes[389], hashes[390], hashes[391]);
const auto hash_vector_50 =
  _mm256_set_epi32(hashes[392], hashes[393], hashes[394], hashes[395], hashes[396], hashes[397], hashes[398], hashes[399]);
const auto hash_vector_51 =
  _mm256_set_epi32(hashes[400], hashes[401], hashes[402], hashes[403], hashes[404], hashes[405], hashes[406], hashes[407]);
const auto hash_vector_52 =
  _mm256_set_epi32(hashes[408], hashes[409], hashes[410], hashes[411], hashes[412], hashes[413], hashes[414], hashes[415]);
const auto hash_vector_53 =
  _mm256_set_epi32(hashes[416], hashes[417], hashes[418], hashes[419], hashes[420], hashes[421], hashes[422], hashes[423]);
const auto hash_vector_54 =
  _mm256_set_epi32(hashes[424], hashes[425], hashes[426], hashes[427], hashes[428], hashes[429], hashes[430], hashes[431]);
const auto hash_vector_55 =
  _mm256_set_epi32(hashes[432], hashes[433], hashes[434], hashes[435], hashes[436], hashes[437], hashes[438], hashes[439]);
const auto hash_vector_56 =
  _mm256_set_epi32(hashes[440], hashes[441], hashes[442], hashes[443], hashes[444], hashes[445], hashes[446], hashes[447]);
const auto hash_vector_57 =
  _mm256_set_epi32(hashes[448], hashes[449], hashes[450], hashes[451], hashes[452], hashes[453], hashes[454], hashes[455]);
const auto hash_vector_58 =
  _mm256_set_epi32(hashes[456], hashes[457], hashes[458], hashes[459], hashes[460], hashes[461], hashes[462], hashes[463]);
const auto hash_vector_59 =
  _mm256_set_epi32(hashes[464], hashes[465], hashes[466], hashes[467], hashes[468], hashes[469], hashes[470], hashes[471]);
const auto hash_vector_60 =
  _mm256_set_epi32(hashes[472], hashes[473], hashes[474], hashes[475], hashes[476], hashes[477], hashes[478], hashes[479]);
const auto hash_vector_61 =
  _mm256_set_epi32(hashes[480], hashes[481], hashes[482], hashes[483], hashes[484], hashes[485], hashes[486], hashes[487]);
const auto hash_vector_62 =
  _mm256_set_epi32(hashes[488], hashes[489], hashes[490], hashes[491], hashes[492], hashes[493], hashes[494], hashes[495]);
const auto hash_vector_63 =
  _mm256_set_epi32(hashes[496], hashes[497], hashes[498], hashes[499], hashes[500], hashes[501], hashes[502], hashes[503]);
const auto hash_vector_64 =
  _mm256_set_epi32(hashes[504], hashes[505], hashes[506], hashes[507], hashes[508], hashes[509], hashes[510], hashes[511]);

void* GetProcAddressSIMD(const char* name) {
    const auto name_hash   = MurmurHash2(name, strlen(name), 0);
    const auto name_vector = _mm256_set1_epi32(name_hash);

    const auto hash_compare_1  = _mm256_cmpeq_epi32(name_vector, hash_vector_1);
    const auto hash_compare_2  = _mm256_cmpeq_epi32(name_vector, hash_vector_2);
    const auto hash_compare_3  = _mm256_cmpeq_epi32(name_vector, hash_vector_3);
    const auto hash_compare_4  = _mm256_cmpeq_epi32(name_vector, hash_vector_4);
    const auto hash_compare_5  = _mm256_cmpeq_epi32(name_vector, hash_vector_5);
    const auto hash_compare_6  = _mm256_cmpeq_epi32(name_vector, hash_vector_6);
    const auto hash_compare_7  = _mm256_cmpeq_epi32(name_vector, hash_vector_7);
    const auto hash_compare_8  = _mm256_cmpeq_epi32(name_vector, hash_vector_8);
    const auto hash_compare_9  = _mm256_cmpeq_epi32(name_vector, hash_vector_9);
    const auto hash_compare_10 = _mm256_cmpeq_epi32(name_vector, hash_vector_10);
    const auto hash_compare_11 = _mm256_cmpeq_epi32(name_vector, hash_vector_11);
    const auto hash_compare_12 = _mm256_cmpeq_epi32(name_vector, hash_vector_12);
    const auto hash_compare_13 = _mm256_cmpeq_epi32(name_vector, hash_vector_13);
    const auto hash_compare_14 = _mm256_cmpeq_epi32(name_vector, hash_vector_14);
    const auto hash_compare_15 = _mm256_cmpeq_epi32(name_vector, hash_vector_15);
    const auto hash_compare_16 = _mm256_cmpeq_epi32(name_vector, hash_vector_16);
    const auto hash_compare_17 = _mm256_cmpeq_epi32(name_vector, hash_vector_17);
    const auto hash_compare_18 = _mm256_cmpeq_epi32(name_vector, hash_vector_18);
    const auto hash_compare_19 = _mm256_cmpeq_epi32(name_vector, hash_vector_19);
    const auto hash_compare_20 = _mm256_cmpeq_epi32(name_vector, hash_vector_20);
    const auto hash_compare_21 = _mm256_cmpeq_epi32(name_vector, hash_vector_21);
    const auto hash_compare_22 = _mm256_cmpeq_epi32(name_vector, hash_vector_22);
    const auto hash_compare_23 = _mm256_cmpeq_epi32(name_vector, hash_vector_23);
    const auto hash_compare_24 = _mm256_cmpeq_epi32(name_vector, hash_vector_24);
    const auto hash_compare_25 = _mm256_cmpeq_epi32(name_vector, hash_vector_25);
    const auto hash_compare_26 = _mm256_cmpeq_epi32(name_vector, hash_vector_26);
    const auto hash_compare_27 = _mm256_cmpeq_epi32(name_vector, hash_vector_27);
    const auto hash_compare_28 = _mm256_cmpeq_epi32(name_vector, hash_vector_28);
    const auto hash_compare_29 = _mm256_cmpeq_epi32(name_vector, hash_vector_29);
    const auto hash_compare_30 = _mm256_cmpeq_epi32(name_vector, hash_vector_30);
    const auto hash_compare_31 = _mm256_cmpeq_epi32(name_vector, hash_vector_31);
    const auto hash_compare_32 = _mm256_cmpeq_epi32(name_vector, hash_vector_32);
    const auto hash_compare_33 = _mm256_cmpeq_epi32(name_vector, hash_vector_33);
    const auto hash_compare_34 = _mm256_cmpeq_epi32(name_vector, hash_vector_34);
    const auto hash_compare_35 = _mm256_cmpeq_epi32(name_vector, hash_vector_35);
    const auto hash_compare_36 = _mm256_cmpeq_epi32(name_vector, hash_vector_36);
    const auto hash_compare_37 = _mm256_cmpeq_epi32(name_vector, hash_vector_37);
    const auto hash_compare_38 = _mm256_cmpeq_epi32(name_vector, hash_vector_38);
    const auto hash_compare_39 = _mm256_cmpeq_epi32(name_vector, hash_vector_39);
    const auto hash_compare_40 = _mm256_cmpeq_epi32(name_vector, hash_vector_40);
    const auto hash_compare_41 = _mm256_cmpeq_epi32(name_vector, hash_vector_41);
    const auto hash_compare_42 = _mm256_cmpeq_epi32(name_vector, hash_vector_42);
    const auto hash_compare_43 = _mm256_cmpeq_epi32(name_vector, hash_vector_43);
    const auto hash_compare_44 = _mm256_cmpeq_epi32(name_vector, hash_vector_44);
    const auto hash_compare_45 = _mm256_cmpeq_epi32(name_vector, hash_vector_45);
    const auto hash_compare_46 = _mm256_cmpeq_epi32(name_vector, hash_vector_46);
    const auto hash_compare_47 = _mm256_cmpeq_epi32(name_vector, hash_vector_47);
    const auto hash_compare_48 = _mm256_cmpeq_epi32(name_vector, hash_vector_48);
    const auto hash_compare_49 = _mm256_cmpeq_epi32(name_vector, hash_vector_49);
    const auto hash_compare_50 = _mm256_cmpeq_epi32(name_vector, hash_vector_50);
    const auto hash_compare_51 = _mm256_cmpeq_epi32(name_vector, hash_vector_51);
    const auto hash_compare_52 = _mm256_cmpeq_epi32(name_vector, hash_vector_52);
    const auto hash_compare_53 = _mm256_cmpeq_epi32(name_vector, hash_vector_53);
    const auto hash_compare_54 = _mm256_cmpeq_epi32(name_vector, hash_vector_54);
    const auto hash_compare_55 = _mm256_cmpeq_epi32(name_vector, hash_vector_55);
    const auto hash_compare_56 = _mm256_cmpeq_epi32(name_vector, hash_vector_56);
    const auto hash_compare_57 = _mm256_cmpeq_epi32(name_vector, hash_vector_57);
    const auto hash_compare_58 = _mm256_cmpeq_epi32(name_vector, hash_vector_58);
    const auto hash_compare_59 = _mm256_cmpeq_epi32(name_vector, hash_vector_59);
    const auto hash_compare_60 = _mm256_cmpeq_epi32(name_vector, hash_vector_60);
    const auto hash_compare_61 = _mm256_cmpeq_epi32(name_vector, hash_vector_61);
    const auto hash_compare_62 = _mm256_cmpeq_epi32(name_vector, hash_vector_62);
    const auto hash_compare_63 = _mm256_cmpeq_epi32(name_vector, hash_vector_63);
    const auto hash_compare_64 = _mm256_cmpeq_epi32(name_vector, hash_vector_64);

    const auto mask_1  = _mm256_movemask_ps((__m256)hash_compare_1);
    const auto mask_2  = _mm256_movemask_ps((__m256)hash_compare_2);
    const auto mask_3  = _mm256_movemask_ps((__m256)hash_compare_3);
    const auto mask_4  = _mm256_movemask_ps((__m256)hash_compare_4);
    const auto mask_5  = _mm256_movemask_ps((__m256)hash_compare_5);
    const auto mask_6  = _mm256_movemask_ps((__m256)hash_compare_6);
    const auto mask_7  = _mm256_movemask_ps((__m256)hash_compare_7);
    const auto mask_8  = _mm256_movemask_ps((__m256)hash_compare_8);
    const auto mask_9  = _mm256_movemask_ps((__m256)hash_compare_9);
    const auto mask_10 = _mm256_movemask_ps((__m256)hash_compare_10);
    const auto mask_11 = _mm256_movemask_ps((__m256)hash_compare_11);
    const auto mask_12 = _mm256_movemask_ps((__m256)hash_compare_12);
    const auto mask_13 = _mm256_movemask_ps((__m256)hash_compare_13);
    const auto mask_14 = _mm256_movemask_ps((__m256)hash_compare_14);
    const auto mask_15 = _mm256_movemask_ps((__m256)hash_compare_15);
    const auto mask_16 = _mm256_movemask_ps((__m256)hash_compare_16);
    const auto mask_17 = _mm256_movemask_ps((__m256)hash_compare_17);
    const auto mask_18 = _mm256_movemask_ps((__m256)hash_compare_18);
    const auto mask_19 = _mm256_movemask_ps((__m256)hash_compare_19);
    const auto mask_20 = _mm256_movemask_ps((__m256)hash_compare_20);
    const auto mask_21 = _mm256_movemask_ps((__m256)hash_compare_21);
    const auto mask_22 = _mm256_movemask_ps((__m256)hash_compare_22);
    const auto mask_23 = _mm256_movemask_ps((__m256)hash_compare_23);
    const auto mask_24 = _mm256_movemask_ps((__m256)hash_compare_24);
    const auto mask_25 = _mm256_movemask_ps((__m256)hash_compare_25);
    const auto mask_26 = _mm256_movemask_ps((__m256)hash_compare_26);
    const auto mask_27 = _mm256_movemask_ps((__m256)hash_compare_27);
    const auto mask_28 = _mm256_movemask_ps((__m256)hash_compare_28);
    const auto mask_29 = _mm256_movemask_ps((__m256)hash_compare_29);
    const auto mask_30 = _mm256_movemask_ps((__m256)hash_compare_30);
    const auto mask_31 = _mm256_movemask_ps((__m256)hash_compare_31);
    const auto mask_32 = _mm256_movemask_ps((__m256)hash_compare_32);
    const auto mask_33 = _mm256_movemask_ps((__m256)hash_compare_33);
    const auto mask_34 = _mm256_movemask_ps((__m256)hash_compare_34);
    const auto mask_35 = _mm256_movemask_ps((__m256)hash_compare_35);
    const auto mask_36 = _mm256_movemask_ps((__m256)hash_compare_36);
    const auto mask_37 = _mm256_movemask_ps((__m256)hash_compare_37);
    const auto mask_38 = _mm256_movemask_ps((__m256)hash_compare_38);
    const auto mask_39 = _mm256_movemask_ps((__m256)hash_compare_39);
    const auto mask_40 = _mm256_movemask_ps((__m256)hash_compare_40);
    const auto mask_41 = _mm256_movemask_ps((__m256)hash_compare_41);
    const auto mask_42 = _mm256_movemask_ps((__m256)hash_compare_42);
    const auto mask_43 = _mm256_movemask_ps((__m256)hash_compare_43);
    const auto mask_44 = _mm256_movemask_ps((__m256)hash_compare_44);
    const auto mask_45 = _mm256_movemask_ps((__m256)hash_compare_45);
    const auto mask_46 = _mm256_movemask_ps((__m256)hash_compare_46);
    const auto mask_47 = _mm256_movemask_ps((__m256)hash_compare_47);
    const auto mask_48 = _mm256_movemask_ps((__m256)hash_compare_48);
    const auto mask_49 = _mm256_movemask_ps((__m256)hash_compare_49);
    const auto mask_50 = _mm256_movemask_ps((__m256)hash_compare_50);
    const auto mask_51 = _mm256_movemask_ps((__m256)hash_compare_51);
    const auto mask_52 = _mm256_movemask_ps((__m256)hash_compare_52);
    const auto mask_53 = _mm256_movemask_ps((__m256)hash_compare_53);
    const auto mask_54 = _mm256_movemask_ps((__m256)hash_compare_54);
    const auto mask_55 = _mm256_movemask_ps((__m256)hash_compare_55);
    const auto mask_56 = _mm256_movemask_ps((__m256)hash_compare_56);
    const auto mask_57 = _mm256_movemask_ps((__m256)hash_compare_57);
    const auto mask_58 = _mm256_movemask_ps((__m256)hash_compare_58);
    const auto mask_59 = _mm256_movemask_ps((__m256)hash_compare_59);
    const auto mask_60 = _mm256_movemask_ps((__m256)hash_compare_60);
    const auto mask_61 = _mm256_movemask_ps((__m256)hash_compare_61);
    const auto mask_62 = _mm256_movemask_ps((__m256)hash_compare_62);
    const auto mask_63 = _mm256_movemask_ps((__m256)hash_compare_63);
    const auto mask_64 = _mm256_movemask_ps((__m256)hash_compare_64);

    if (mask_1 != 0)
        return result[__builtin_clz(mask_1) + (0 * 8 - 24)];
    if (mask_2 != 0)
        return result[__builtin_clz(mask_2) + (1 * 8 - 24)];
    if (mask_3 != 0)
        return result[__builtin_clz(mask_3) + (2 * 8 - 24)];
    if (mask_4 != 0)
        return result[__builtin_clz(mask_4) + (3 * 8 - 24)];
    if (mask_5 != 0)
        return result[__builtin_clz(mask_5) + (4 * 8 - 24)];
    if (mask_6 != 0)
        return result[__builtin_clz(mask_6) + (5 * 8 - 24)];
    if (mask_7 != 0)
        return result[__builtin_clz(mask_7) + (6 * 8 - 24)];
    if (mask_8 != 0)
        return result[__builtin_clz(mask_8) + (7 * 8 - 24)];
    if (mask_9 != 0)
        return result[__builtin_clz(mask_9) + (8 * 8 - 24)];
    if (mask_10 != 0)
        return result[__builtin_clz(mask_10) + (9 * 8 - 24)];
    if (mask_11 != 0)
        return result[__builtin_clz(mask_11) + (10 * 8 - 24)];
    if (mask_12 != 0)
        return result[__builtin_clz(mask_12) + (11 * 8 - 24)];
    if (mask_13 != 0)
        return result[__builtin_clz(mask_13) + (12 * 8 - 24)];
    if (mask_14 != 0)
        return result[__builtin_clz(mask_14) + (13 * 8 - 24)];
    if (mask_15 != 0)
        return result[__builtin_clz(mask_15) + (14 * 8 - 24)];
    if (mask_16 != 0)
        return result[__builtin_clz(mask_16) + (15 * 8 - 24)];
    if (mask_17 != 0)
        return result[__builtin_clz(mask_17) + (16 * 8 - 24)];
    if (mask_18 != 0)
        return result[__builtin_clz(mask_18) + (17 * 8 - 24)];
    if (mask_19 != 0)
        return result[__builtin_clz(mask_19) + (18 * 8 - 24)];
    if (mask_20 != 0)
        return result[__builtin_clz(mask_20) + (19 * 8 - 24)];
    if (mask_21 != 0)
        return result[__builtin_clz(mask_21) + (20 * 8 - 24)];
    if (mask_22 != 0)
        return result[__builtin_clz(mask_22) + (21 * 8 - 24)];
    if (mask_23 != 0)
        return result[__builtin_clz(mask_23) + (22 * 8 - 24)];
    if (mask_24 != 0)
        return result[__builtin_clz(mask_24) + (23 * 8 - 24)];
    if (mask_25 != 0)
        return result[__builtin_clz(mask_25) + (24 * 8 - 24)];
    if (mask_26 != 0)
        return result[__builtin_clz(mask_26) + (25 * 8 - 24)];
    if (mask_27 != 0)
        return result[__builtin_clz(mask_27) + (26 * 8 - 24)];
    if (mask_28 != 0)
        return result[__builtin_clz(mask_28) + (27 * 8 - 24)];
    if (mask_29 != 0)
        return result[__builtin_clz(mask_29) + (28 * 8 - 24)];
    if (mask_30 != 0)
        return result[__builtin_clz(mask_30) + (29 * 8 - 24)];
    if (mask_31 != 0)
        return result[__builtin_clz(mask_31) + (30 * 8 - 24)];
    if (mask_32 != 0)
        return result[__builtin_clz(mask_32) + (31 * 8 - 24)];
    if (mask_33 != 0)
        return result[__builtin_clz(mask_33) + (32 * 8 - 24)];
    if (mask_34 != 0)
        return result[__builtin_clz(mask_34) + (33 * 8 - 24)];
    if (mask_35 != 0)
        return result[__builtin_clz(mask_35) + (34 * 8 - 24)];
    if (mask_36 != 0)
        return result[__builtin_clz(mask_36) + (35 * 8 - 24)];
    if (mask_37 != 0)
        return result[__builtin_clz(mask_37) + (36 * 8 - 24)];
    if (mask_38 != 0)
        return result[__builtin_clz(mask_38) + (37 * 8 - 24)];
    if (mask_39 != 0)
        return result[__builtin_clz(mask_39) + (38 * 8 - 24)];
    if (mask_40 != 0)
        return result[__builtin_clz(mask_40) + (39 * 8 - 24)];
    if (mask_41 != 0)
        return result[__builtin_clz(mask_41) + (40 * 8 - 24)];
    if (mask_42 != 0)
        return result[__builtin_clz(mask_42) + (41 * 8 - 24)];
    if (mask_43 != 0)
        return result[__builtin_clz(mask_43) + (42 * 8 - 24)];
    if (mask_44 != 0)
        return result[__builtin_clz(mask_44) + (43 * 8 - 24)];
    if (mask_45 != 0)
        return result[__builtin_clz(mask_45) + (44 * 8 - 24)];
    if (mask_46 != 0)
        return result[__builtin_clz(mask_46) + (45 * 8 - 24)];
    if (mask_47 != 0)
        return result[__builtin_clz(mask_47) + (46 * 8 - 24)];
    if (mask_48 != 0)
        return result[__builtin_clz(mask_48) + (47 * 8 - 24)];
    if (mask_49 != 0)
        return result[__builtin_clz(mask_49) + (48 * 8 - 24)];
    if (mask_50 != 0)
        return result[__builtin_clz(mask_50) + (49 * 8 - 24)];
    if (mask_51 != 0)
        return result[__builtin_clz(mask_51) + (50 * 8 - 24)];
    if (mask_52 != 0)
        return result[__builtin_clz(mask_52) + (51 * 8 - 24)];
    if (mask_53 != 0)
        return result[__builtin_clz(mask_53) + (52 * 8 - 24)];
    if (mask_54 != 0)
        return result[__builtin_clz(mask_54) + (53 * 8 - 24)];
    if (mask_55 != 0)
        return result[__builtin_clz(mask_55) + (54 * 8 - 24)];
    if (mask_56 != 0)
        return result[__builtin_clz(mask_56) + (55 * 8 - 24)];
    if (mask_57 != 0)
        return result[__builtin_clz(mask_57) + (56 * 8 - 24)];
    if (mask_58 != 0)
        return result[__builtin_clz(mask_58) + (57 * 8 - 24)];
    if (mask_59 != 0)
        return result[__builtin_clz(mask_59) + (58 * 8 - 24)];
    if (mask_60 != 0)
        return result[__builtin_clz(mask_60) + (59 * 8 - 24)];
    if (mask_61 != 0)
        return result[__builtin_clz(mask_61) + (60 * 8 - 24)];
    if (mask_62 != 0)
        return result[__builtin_clz(mask_62) + (61 * 8 - 24)];
    if (mask_63 != 0)
        return result[__builtin_clz(mask_63) + (62 * 8 - 24)];
    if (mask_64 != 0)
        return result[__builtin_clz(mask_64) + (63 * 8 - 24)];

    return nullptr;
}

void* GetProcAddressSIMDStraight(uint32_t hash) {
    const auto name_vector = _mm256_set1_epi32(hash);

    const auto hash_compare_1  = _mm256_cmpeq_epi32(name_vector, hash_vector_1);
    const auto hash_compare_2  = _mm256_cmpeq_epi32(name_vector, hash_vector_2);
    const auto hash_compare_3  = _mm256_cmpeq_epi32(name_vector, hash_vector_3);
    const auto hash_compare_4  = _mm256_cmpeq_epi32(name_vector, hash_vector_4);
    const auto hash_compare_5  = _mm256_cmpeq_epi32(name_vector, hash_vector_5);
    const auto hash_compare_6  = _mm256_cmpeq_epi32(name_vector, hash_vector_6);
    const auto hash_compare_7  = _mm256_cmpeq_epi32(name_vector, hash_vector_7);
    const auto hash_compare_8  = _mm256_cmpeq_epi32(name_vector, hash_vector_8);
    const auto hash_compare_9  = _mm256_cmpeq_epi32(name_vector, hash_vector_9);
    const auto hash_compare_10 = _mm256_cmpeq_epi32(name_vector, hash_vector_10);
    const auto hash_compare_11 = _mm256_cmpeq_epi32(name_vector, hash_vector_11);
    const auto hash_compare_12 = _mm256_cmpeq_epi32(name_vector, hash_vector_12);
    const auto hash_compare_13 = _mm256_cmpeq_epi32(name_vector, hash_vector_13);
    const auto hash_compare_14 = _mm256_cmpeq_epi32(name_vector, hash_vector_14);
    const auto hash_compare_15 = _mm256_cmpeq_epi32(name_vector, hash_vector_15);
    const auto hash_compare_16 = _mm256_cmpeq_epi32(name_vector, hash_vector_16);
    const auto hash_compare_17 = _mm256_cmpeq_epi32(name_vector, hash_vector_17);
    const auto hash_compare_18 = _mm256_cmpeq_epi32(name_vector, hash_vector_18);
    const auto hash_compare_19 = _mm256_cmpeq_epi32(name_vector, hash_vector_19);
    const auto hash_compare_20 = _mm256_cmpeq_epi32(name_vector, hash_vector_20);
    const auto hash_compare_21 = _mm256_cmpeq_epi32(name_vector, hash_vector_21);
    const auto hash_compare_22 = _mm256_cmpeq_epi32(name_vector, hash_vector_22);
    const auto hash_compare_23 = _mm256_cmpeq_epi32(name_vector, hash_vector_23);
    const auto hash_compare_24 = _mm256_cmpeq_epi32(name_vector, hash_vector_24);
    const auto hash_compare_25 = _mm256_cmpeq_epi32(name_vector, hash_vector_25);
    const auto hash_compare_26 = _mm256_cmpeq_epi32(name_vector, hash_vector_26);
    const auto hash_compare_27 = _mm256_cmpeq_epi32(name_vector, hash_vector_27);
    const auto hash_compare_28 = _mm256_cmpeq_epi32(name_vector, hash_vector_28);
    const auto hash_compare_29 = _mm256_cmpeq_epi32(name_vector, hash_vector_29);
    const auto hash_compare_30 = _mm256_cmpeq_epi32(name_vector, hash_vector_30);
    const auto hash_compare_31 = _mm256_cmpeq_epi32(name_vector, hash_vector_31);
    const auto hash_compare_32 = _mm256_cmpeq_epi32(name_vector, hash_vector_32);
    const auto hash_compare_33 = _mm256_cmpeq_epi32(name_vector, hash_vector_33);
    const auto hash_compare_34 = _mm256_cmpeq_epi32(name_vector, hash_vector_34);
    const auto hash_compare_35 = _mm256_cmpeq_epi32(name_vector, hash_vector_35);
    const auto hash_compare_36 = _mm256_cmpeq_epi32(name_vector, hash_vector_36);
    const auto hash_compare_37 = _mm256_cmpeq_epi32(name_vector, hash_vector_37);
    const auto hash_compare_38 = _mm256_cmpeq_epi32(name_vector, hash_vector_38);
    const auto hash_compare_39 = _mm256_cmpeq_epi32(name_vector, hash_vector_39);
    const auto hash_compare_40 = _mm256_cmpeq_epi32(name_vector, hash_vector_40);
    const auto hash_compare_41 = _mm256_cmpeq_epi32(name_vector, hash_vector_41);
    const auto hash_compare_42 = _mm256_cmpeq_epi32(name_vector, hash_vector_42);
    const auto hash_compare_43 = _mm256_cmpeq_epi32(name_vector, hash_vector_43);
    const auto hash_compare_44 = _mm256_cmpeq_epi32(name_vector, hash_vector_44);
    const auto hash_compare_45 = _mm256_cmpeq_epi32(name_vector, hash_vector_45);
    const auto hash_compare_46 = _mm256_cmpeq_epi32(name_vector, hash_vector_46);
    const auto hash_compare_47 = _mm256_cmpeq_epi32(name_vector, hash_vector_47);
    const auto hash_compare_48 = _mm256_cmpeq_epi32(name_vector, hash_vector_48);
    const auto hash_compare_49 = _mm256_cmpeq_epi32(name_vector, hash_vector_49);
    const auto hash_compare_50 = _mm256_cmpeq_epi32(name_vector, hash_vector_50);
    const auto hash_compare_51 = _mm256_cmpeq_epi32(name_vector, hash_vector_51);
    const auto hash_compare_52 = _mm256_cmpeq_epi32(name_vector, hash_vector_52);
    const auto hash_compare_53 = _mm256_cmpeq_epi32(name_vector, hash_vector_53);
    const auto hash_compare_54 = _mm256_cmpeq_epi32(name_vector, hash_vector_54);
    const auto hash_compare_55 = _mm256_cmpeq_epi32(name_vector, hash_vector_55);
    const auto hash_compare_56 = _mm256_cmpeq_epi32(name_vector, hash_vector_56);
    const auto hash_compare_57 = _mm256_cmpeq_epi32(name_vector, hash_vector_57);
    const auto hash_compare_58 = _mm256_cmpeq_epi32(name_vector, hash_vector_58);
    const auto hash_compare_59 = _mm256_cmpeq_epi32(name_vector, hash_vector_59);
    const auto hash_compare_60 = _mm256_cmpeq_epi32(name_vector, hash_vector_60);
    const auto hash_compare_61 = _mm256_cmpeq_epi32(name_vector, hash_vector_61);
    const auto hash_compare_62 = _mm256_cmpeq_epi32(name_vector, hash_vector_62);
    const auto hash_compare_63 = _mm256_cmpeq_epi32(name_vector, hash_vector_63);
    const auto hash_compare_64 = _mm256_cmpeq_epi32(name_vector, hash_vector_64);

    const auto mask_1  = _mm256_movemask_ps((__m256)hash_compare_1);
    const auto mask_2  = _mm256_movemask_ps((__m256)hash_compare_2);
    const auto mask_3  = _mm256_movemask_ps((__m256)hash_compare_3);
    const auto mask_4  = _mm256_movemask_ps((__m256)hash_compare_4);
    const auto mask_5  = _mm256_movemask_ps((__m256)hash_compare_5);
    const auto mask_6  = _mm256_movemask_ps((__m256)hash_compare_6);
    const auto mask_7  = _mm256_movemask_ps((__m256)hash_compare_7);
    const auto mask_8  = _mm256_movemask_ps((__m256)hash_compare_8);
    const auto mask_9  = _mm256_movemask_ps((__m256)hash_compare_9);
    const auto mask_10 = _mm256_movemask_ps((__m256)hash_compare_10);
    const auto mask_11 = _mm256_movemask_ps((__m256)hash_compare_11);
    const auto mask_12 = _mm256_movemask_ps((__m256)hash_compare_12);
    const auto mask_13 = _mm256_movemask_ps((__m256)hash_compare_13);
    const auto mask_14 = _mm256_movemask_ps((__m256)hash_compare_14);
    const auto mask_15 = _mm256_movemask_ps((__m256)hash_compare_15);
    const auto mask_16 = _mm256_movemask_ps((__m256)hash_compare_16);
    const auto mask_17 = _mm256_movemask_ps((__m256)hash_compare_17);
    const auto mask_18 = _mm256_movemask_ps((__m256)hash_compare_18);
    const auto mask_19 = _mm256_movemask_ps((__m256)hash_compare_19);
    const auto mask_20 = _mm256_movemask_ps((__m256)hash_compare_20);
    const auto mask_21 = _mm256_movemask_ps((__m256)hash_compare_21);
    const auto mask_22 = _mm256_movemask_ps((__m256)hash_compare_22);
    const auto mask_23 = _mm256_movemask_ps((__m256)hash_compare_23);
    const auto mask_24 = _mm256_movemask_ps((__m256)hash_compare_24);
    const auto mask_25 = _mm256_movemask_ps((__m256)hash_compare_25);
    const auto mask_26 = _mm256_movemask_ps((__m256)hash_compare_26);
    const auto mask_27 = _mm256_movemask_ps((__m256)hash_compare_27);
    const auto mask_28 = _mm256_movemask_ps((__m256)hash_compare_28);
    const auto mask_29 = _mm256_movemask_ps((__m256)hash_compare_29);
    const auto mask_30 = _mm256_movemask_ps((__m256)hash_compare_30);
    const auto mask_31 = _mm256_movemask_ps((__m256)hash_compare_31);
    const auto mask_32 = _mm256_movemask_ps((__m256)hash_compare_32);
    const auto mask_33 = _mm256_movemask_ps((__m256)hash_compare_33);
    const auto mask_34 = _mm256_movemask_ps((__m256)hash_compare_34);
    const auto mask_35 = _mm256_movemask_ps((__m256)hash_compare_35);
    const auto mask_36 = _mm256_movemask_ps((__m256)hash_compare_36);
    const auto mask_37 = _mm256_movemask_ps((__m256)hash_compare_37);
    const auto mask_38 = _mm256_movemask_ps((__m256)hash_compare_38);
    const auto mask_39 = _mm256_movemask_ps((__m256)hash_compare_39);
    const auto mask_40 = _mm256_movemask_ps((__m256)hash_compare_40);
    const auto mask_41 = _mm256_movemask_ps((__m256)hash_compare_41);
    const auto mask_42 = _mm256_movemask_ps((__m256)hash_compare_42);
    const auto mask_43 = _mm256_movemask_ps((__m256)hash_compare_43);
    const auto mask_44 = _mm256_movemask_ps((__m256)hash_compare_44);
    const auto mask_45 = _mm256_movemask_ps((__m256)hash_compare_45);
    const auto mask_46 = _mm256_movemask_ps((__m256)hash_compare_46);
    const auto mask_47 = _mm256_movemask_ps((__m256)hash_compare_47);
    const auto mask_48 = _mm256_movemask_ps((__m256)hash_compare_48);
    const auto mask_49 = _mm256_movemask_ps((__m256)hash_compare_49);
    const auto mask_50 = _mm256_movemask_ps((__m256)hash_compare_50);
    const auto mask_51 = _mm256_movemask_ps((__m256)hash_compare_51);
    const auto mask_52 = _mm256_movemask_ps((__m256)hash_compare_52);
    const auto mask_53 = _mm256_movemask_ps((__m256)hash_compare_53);
    const auto mask_54 = _mm256_movemask_ps((__m256)hash_compare_54);
    const auto mask_55 = _mm256_movemask_ps((__m256)hash_compare_55);
    const auto mask_56 = _mm256_movemask_ps((__m256)hash_compare_56);
    const auto mask_57 = _mm256_movemask_ps((__m256)hash_compare_57);
    const auto mask_58 = _mm256_movemask_ps((__m256)hash_compare_58);
    const auto mask_59 = _mm256_movemask_ps((__m256)hash_compare_59);
    const auto mask_60 = _mm256_movemask_ps((__m256)hash_compare_60);
    const auto mask_61 = _mm256_movemask_ps((__m256)hash_compare_61);
    const auto mask_62 = _mm256_movemask_ps((__m256)hash_compare_62);
    const auto mask_63 = _mm256_movemask_ps((__m256)hash_compare_63);
    const auto mask_64 = _mm256_movemask_ps((__m256)hash_compare_64);

    if (mask_1 != 0)
        return result[__builtin_clz(mask_1) + (0 * 8 - 24)];
    if (mask_2 != 0)
        return result[__builtin_clz(mask_2) + (1 * 8 - 24)];
    if (mask_3 != 0)
        return result[__builtin_clz(mask_3) + (2 * 8 - 24)];
    if (mask_4 != 0)
        return result[__builtin_clz(mask_4) + (3 * 8 - 24)];
    if (mask_5 != 0)
        return result[__builtin_clz(mask_5) + (4 * 8 - 24)];
    if (mask_6 != 0)
        return result[__builtin_clz(mask_6) + (5 * 8 - 24)];
    if (mask_7 != 0)
        return result[__builtin_clz(mask_7) + (6 * 8 - 24)];
    if (mask_8 != 0)
        return result[__builtin_clz(mask_8) + (7 * 8 - 24)];
    if (mask_9 != 0)
        return result[__builtin_clz(mask_9) + (8 * 8 - 24)];
    if (mask_10 != 0)
        return result[__builtin_clz(mask_10) + (9 * 8 - 24)];
    if (mask_11 != 0)
        return result[__builtin_clz(mask_11) + (10 * 8 - 24)];
    if (mask_12 != 0)
        return result[__builtin_clz(mask_12) + (11 * 8 - 24)];
    if (mask_13 != 0)
        return result[__builtin_clz(mask_13) + (12 * 8 - 24)];
    if (mask_14 != 0)
        return result[__builtin_clz(mask_14) + (13 * 8 - 24)];
    if (mask_15 != 0)
        return result[__builtin_clz(mask_15) + (14 * 8 - 24)];
    if (mask_16 != 0)
        return result[__builtin_clz(mask_16) + (15 * 8 - 24)];
    if (mask_17 != 0)
        return result[__builtin_clz(mask_17) + (16 * 8 - 24)];
    if (mask_18 != 0)
        return result[__builtin_clz(mask_18) + (17 * 8 - 24)];
    if (mask_19 != 0)
        return result[__builtin_clz(mask_19) + (18 * 8 - 24)];
    if (mask_20 != 0)
        return result[__builtin_clz(mask_20) + (19 * 8 - 24)];
    if (mask_21 != 0)
        return result[__builtin_clz(mask_21) + (20 * 8 - 24)];
    if (mask_22 != 0)
        return result[__builtin_clz(mask_22) + (21 * 8 - 24)];
    if (mask_23 != 0)
        return result[__builtin_clz(mask_23) + (22 * 8 - 24)];
    if (mask_24 != 0)
        return result[__builtin_clz(mask_24) + (23 * 8 - 24)];
    if (mask_25 != 0)
        return result[__builtin_clz(mask_25) + (24 * 8 - 24)];
    if (mask_26 != 0)
        return result[__builtin_clz(mask_26) + (25 * 8 - 24)];
    if (mask_27 != 0)
        return result[__builtin_clz(mask_27) + (26 * 8 - 24)];
    if (mask_28 != 0)
        return result[__builtin_clz(mask_28) + (27 * 8 - 24)];
    if (mask_29 != 0)
        return result[__builtin_clz(mask_29) + (28 * 8 - 24)];
    if (mask_30 != 0)
        return result[__builtin_clz(mask_30) + (29 * 8 - 24)];
    if (mask_31 != 0)
        return result[__builtin_clz(mask_31) + (30 * 8 - 24)];
    if (mask_32 != 0)
        return result[__builtin_clz(mask_32) + (31 * 8 - 24)];
    if (mask_33 != 0)
        return result[__builtin_clz(mask_33) + (32 * 8 - 24)];
    if (mask_34 != 0)
        return result[__builtin_clz(mask_34) + (33 * 8 - 24)];
    if (mask_35 != 0)
        return result[__builtin_clz(mask_35) + (34 * 8 - 24)];
    if (mask_36 != 0)
        return result[__builtin_clz(mask_36) + (35 * 8 - 24)];
    if (mask_37 != 0)
        return result[__builtin_clz(mask_37) + (36 * 8 - 24)];
    if (mask_38 != 0)
        return result[__builtin_clz(mask_38) + (37 * 8 - 24)];
    if (mask_39 != 0)
        return result[__builtin_clz(mask_39) + (38 * 8 - 24)];
    if (mask_40 != 0)
        return result[__builtin_clz(mask_40) + (39 * 8 - 24)];
    if (mask_41 != 0)
        return result[__builtin_clz(mask_41) + (40 * 8 - 24)];
    if (mask_42 != 0)
        return result[__builtin_clz(mask_42) + (41 * 8 - 24)];
    if (mask_43 != 0)
        return result[__builtin_clz(mask_43) + (42 * 8 - 24)];
    if (mask_44 != 0)
        return result[__builtin_clz(mask_44) + (43 * 8 - 24)];
    if (mask_45 != 0)
        return result[__builtin_clz(mask_45) + (44 * 8 - 24)];
    if (mask_46 != 0)
        return result[__builtin_clz(mask_46) + (45 * 8 - 24)];
    if (mask_47 != 0)
        return result[__builtin_clz(mask_47) + (46 * 8 - 24)];
    if (mask_48 != 0)
        return result[__builtin_clz(mask_48) + (47 * 8 - 24)];
    if (mask_49 != 0)
        return result[__builtin_clz(mask_49) + (48 * 8 - 24)];
    if (mask_50 != 0)
        return result[__builtin_clz(mask_50) + (49 * 8 - 24)];
    if (mask_51 != 0)
        return result[__builtin_clz(mask_51) + (50 * 8 - 24)];
    if (mask_52 != 0)
        return result[__builtin_clz(mask_52) + (51 * 8 - 24)];
    if (mask_53 != 0)
        return result[__builtin_clz(mask_53) + (52 * 8 - 24)];
    if (mask_54 != 0)
        return result[__builtin_clz(mask_54) + (53 * 8 - 24)];
    if (mask_55 != 0)
        return result[__builtin_clz(mask_55) + (54 * 8 - 24)];
    if (mask_56 != 0)
        return result[__builtin_clz(mask_56) + (55 * 8 - 24)];
    if (mask_57 != 0)
        return result[__builtin_clz(mask_57) + (56 * 8 - 24)];
    if (mask_58 != 0)
        return result[__builtin_clz(mask_58) + (57 * 8 - 24)];
    if (mask_59 != 0)
        return result[__builtin_clz(mask_59) + (58 * 8 - 24)];
    if (mask_60 != 0)
        return result[__builtin_clz(mask_60) + (59 * 8 - 24)];
    if (mask_61 != 0)
        return result[__builtin_clz(mask_61) + (60 * 8 - 24)];
    if (mask_62 != 0)
        return result[__builtin_clz(mask_62) + (61 * 8 - 24)];
    if (mask_63 != 0)
        return result[__builtin_clz(mask_63) + (62 * 8 - 24)];
    if (mask_64 != 0)
        return result[__builtin_clz(mask_64) + (63 * 8 - 24)];

    return nullptr;
}

static const __m256i organized[] = {
  _mm256_set_epi32(hashes[0], hashes[1], hashes[2], hashes[3], hashes[4], hashes[5], hashes[6], hashes[7]),
  _mm256_set_epi32(hashes[8], hashes[9], hashes[10], hashes[11], hashes[12], hashes[13], hashes[14], hashes[15]),
  _mm256_set_epi32(hashes[16], hashes[17], hashes[18], hashes[19], hashes[20], hashes[21], hashes[22], hashes[23]),
  _mm256_set_epi32(hashes[24], hashes[25], hashes[26], hashes[27], hashes[28], hashes[29], hashes[30], hashes[31]),
  _mm256_set_epi32(hashes[32], hashes[33], hashes[34], hashes[35], hashes[36], hashes[37], hashes[38], hashes[39]),
  _mm256_set_epi32(hashes[40], hashes[41], hashes[42], hashes[43], hashes[44], hashes[45], hashes[46], hashes[47]),
  _mm256_set_epi32(hashes[48], hashes[49], hashes[50], hashes[51], hashes[52], hashes[53], hashes[54], hashes[55]),
  _mm256_set_epi32(hashes[56], hashes[57], hashes[58], hashes[59], hashes[60], hashes[61], hashes[62], hashes[63]),
  _mm256_set_epi32(hashes[64], hashes[65], hashes[66], hashes[67], hashes[68], hashes[69], hashes[70], hashes[71]),
  _mm256_set_epi32(hashes[72], hashes[73], hashes[74], hashes[75], hashes[76], hashes[77], hashes[78], hashes[79]),
  _mm256_set_epi32(hashes[80], hashes[81], hashes[82], hashes[83], hashes[84], hashes[85], hashes[86], hashes[87]),
  _mm256_set_epi32(hashes[88], hashes[89], hashes[90], hashes[91], hashes[92], hashes[93], hashes[94], hashes[95]),
  _mm256_set_epi32(hashes[96], hashes[97], hashes[98], hashes[99], hashes[100], hashes[101], hashes[102], hashes[103]),
  _mm256_set_epi32(hashes[104], hashes[105], hashes[106], hashes[107], hashes[108], hashes[109], hashes[110], hashes[111]),
  _mm256_set_epi32(hashes[112], hashes[113], hashes[114], hashes[115], hashes[116], hashes[117], hashes[118], hashes[119]),
  _mm256_set_epi32(hashes[120], hashes[121], hashes[122], hashes[123], hashes[124], hashes[125], hashes[126], hashes[127]),
  _mm256_set_epi32(hashes[128], hashes[129], hashes[130], hashes[131], hashes[132], hashes[133], hashes[134], hashes[135]),
  _mm256_set_epi32(hashes[136], hashes[137], hashes[138], hashes[139], hashes[140], hashes[141], hashes[142], hashes[143]),
  _mm256_set_epi32(hashes[144], hashes[145], hashes[146], hashes[147], hashes[148], hashes[149], hashes[150], hashes[151]),
  _mm256_set_epi32(hashes[152], hashes[153], hashes[154], hashes[155], hashes[156], hashes[157], hashes[158], hashes[159]),
  _mm256_set_epi32(hashes[160], hashes[161], hashes[162], hashes[163], hashes[164], hashes[165], hashes[166], hashes[167]),
  _mm256_set_epi32(hashes[168], hashes[169], hashes[170], hashes[171], hashes[172], hashes[173], hashes[174], hashes[175]),
  _mm256_set_epi32(hashes[176], hashes[177], hashes[178], hashes[179], hashes[180], hashes[181], hashes[182], hashes[183]),
  _mm256_set_epi32(hashes[184], hashes[185], hashes[186], hashes[187], hashes[188], hashes[189], hashes[190], hashes[191]),
  _mm256_set_epi32(hashes[192], hashes[193], hashes[194], hashes[195], hashes[196], hashes[197], hashes[198], hashes[199]),
  _mm256_set_epi32(hashes[200], hashes[201], hashes[202], hashes[203], hashes[204], hashes[205], hashes[206], hashes[207]),
  _mm256_set_epi32(hashes[208], hashes[209], hashes[210], hashes[211], hashes[212], hashes[213], hashes[214], hashes[215]),
  _mm256_set_epi32(hashes[216], hashes[217], hashes[218], hashes[219], hashes[220], hashes[221], hashes[222], hashes[223]),
  _mm256_set_epi32(hashes[224], hashes[225], hashes[226], hashes[227], hashes[228], hashes[229], hashes[230], hashes[231]),
  _mm256_set_epi32(hashes[232], hashes[233], hashes[234], hashes[235], hashes[236], hashes[237], hashes[238], hashes[239]),
  _mm256_set_epi32(hashes[240], hashes[241], hashes[242], hashes[243], hashes[244], hashes[245], hashes[246], hashes[247]),
  _mm256_set_epi32(hashes[248], hashes[249], hashes[250], hashes[251], hashes[252], hashes[253], hashes[254], hashes[255]),
  _mm256_set_epi32(hashes[256], hashes[257], hashes[258], hashes[259], hashes[260], hashes[261], hashes[262], hashes[263]),
  _mm256_set_epi32(hashes[264], hashes[265], hashes[266], hashes[267], hashes[268], hashes[269], hashes[270], hashes[271]),
  _mm256_set_epi32(hashes[272], hashes[273], hashes[274], hashes[275], hashes[276], hashes[277], hashes[278], hashes[279]),
  _mm256_set_epi32(hashes[280], hashes[281], hashes[282], hashes[283], hashes[284], hashes[285], hashes[286], hashes[287]),
  _mm256_set_epi32(hashes[288], hashes[289], hashes[290], hashes[291], hashes[292], hashes[293], hashes[294], hashes[295]),
  _mm256_set_epi32(hashes[296], hashes[297], hashes[298], hashes[299], hashes[300], hashes[301], hashes[302], hashes[303]),
  _mm256_set_epi32(hashes[304], hashes[305], hashes[306], hashes[307], hashes[308], hashes[309], hashes[310], hashes[311]),
  _mm256_set_epi32(hashes[312], hashes[313], hashes[314], hashes[315], hashes[316], hashes[317], hashes[318], hashes[319]),
  _mm256_set_epi32(hashes[320], hashes[321], hashes[322], hashes[323], hashes[324], hashes[325], hashes[326], hashes[327]),
  _mm256_set_epi32(hashes[328], hashes[329], hashes[330], hashes[331], hashes[332], hashes[333], hashes[334], hashes[335]),
  _mm256_set_epi32(hashes[336], hashes[337], hashes[338], hashes[339], hashes[340], hashes[341], hashes[342], hashes[343]),
  _mm256_set_epi32(hashes[344], hashes[345], hashes[346], hashes[347], hashes[348], hashes[349], hashes[350], hashes[351]),
  _mm256_set_epi32(hashes[352], hashes[353], hashes[354], hashes[355], hashes[356], hashes[357], hashes[358], hashes[359]),
  _mm256_set_epi32(hashes[360], hashes[361], hashes[362], hashes[363], hashes[364], hashes[365], hashes[366], hashes[367]),
  _mm256_set_epi32(hashes[368], hashes[369], hashes[370], hashes[371], hashes[372], hashes[373], hashes[374], hashes[375]),
  _mm256_set_epi32(hashes[376], hashes[377], hashes[378], hashes[379], hashes[380], hashes[381], hashes[382], hashes[383]),
  _mm256_set_epi32(hashes[384], hashes[385], hashes[386], hashes[387], hashes[388], hashes[389], hashes[390], hashes[391]),
  _mm256_set_epi32(hashes[392], hashes[393], hashes[394], hashes[395], hashes[396], hashes[397], hashes[398], hashes[399]),
  _mm256_set_epi32(hashes[400], hashes[401], hashes[402], hashes[403], hashes[404], hashes[405], hashes[406], hashes[407]),
  _mm256_set_epi32(hashes[408], hashes[409], hashes[410], hashes[411], hashes[412], hashes[413], hashes[414], hashes[415]),
  _mm256_set_epi32(hashes[416], hashes[417], hashes[418], hashes[419], hashes[420], hashes[421], hashes[422], hashes[423]),
  _mm256_set_epi32(hashes[424], hashes[425], hashes[426], hashes[427], hashes[428], hashes[429], hashes[430], hashes[431]),
  _mm256_set_epi32(hashes[432], hashes[433], hashes[434], hashes[435], hashes[436], hashes[437], hashes[438], hashes[439]),
  _mm256_set_epi32(hashes[440], hashes[441], hashes[442], hashes[443], hashes[444], hashes[445], hashes[446], hashes[447]),
  _mm256_set_epi32(hashes[448], hashes[449], hashes[450], hashes[451], hashes[452], hashes[453], hashes[454], hashes[455]),
  _mm256_set_epi32(hashes[456], hashes[457], hashes[458], hashes[459], hashes[460], hashes[461], hashes[462], hashes[463]),
  _mm256_set_epi32(hashes[464], hashes[465], hashes[466], hashes[467], hashes[468], hashes[469], hashes[470], hashes[471]),
  _mm256_set_epi32(hashes[472], hashes[473], hashes[474], hashes[475], hashes[476], hashes[477], hashes[478], hashes[479]),
  _mm256_set_epi32(hashes[480], hashes[481], hashes[482], hashes[483], hashes[484], hashes[485], hashes[486], hashes[487]),
  _mm256_set_epi32(hashes[488], hashes[489], hashes[490], hashes[491], hashes[492], hashes[493], hashes[494], hashes[495]),
  _mm256_set_epi32(hashes[496], hashes[497], hashes[498], hashes[499], hashes[500], hashes[501], hashes[502], hashes[503]),
  _mm256_set_epi32(hashes[504], hashes[505], hashes[506], hashes[507], hashes[508], hashes[509], hashes[510], hashes[511]),
};

void* GetProcAddressSIMDCombined(const char* name) {
    const auto name_hash   = MurmurHash2(name, strlen(name), 0);
    const auto name_vector = _mm256_set1_epi32(name_hash);

    for (auto index = 0; index < 64; index++) {
        const auto compare = _mm256_cmpeq_epi32(name_vector, organized[index]);
        const auto mask = _mm256_movemask_ps((__m256)compare);

        if (mask != 0) {
            return result[__builtin_clz(mask) + (index * 8 - 24)];
        }
    }

    return nullptr;
}

void* GetProcAddressSIMDCombinedStraight(uint32_t name_hash) {
    const auto name_vector = _mm256_set1_epi32(name_hash);

    for (auto index = 0; index < 64; index++) {
        const auto compare = _mm256_cmpeq_epi32(name_vector, organized[index]);
        const auto mask = _mm256_movemask_ps((__m256)compare);

        if (mask != 0) {
            return result[__builtin_clz(mask) + (index * 8 - 24)];
        }
    }

    return nullptr;
}

//#include <iostream>
//#include <bitset>

void* GetProcAddressSIMDTryFit(uint32_t name_hash) {
    const auto name_vector = _mm256_set1_epi32(name_hash);

    for (auto index = 0; index < 16; index++) {
        const auto compare_1 = _mm256_cmpeq_epi32(name_vector, organized[4 * index + 0]);
        const auto compare_2 = _mm256_cmpeq_epi32(name_vector, organized[4 * index + 1]);
        const auto compare_3 = _mm256_cmpeq_epi32(name_vector, organized[4 * index + 2]);
        const auto compare_4 = _mm256_cmpeq_epi32(name_vector, organized[4 * index + 3]);

        const auto mask_1 = _mm256_movemask_ps((__m256)compare_1);
        const auto mask_2 = _mm256_movemask_ps((__m256)compare_2);
        const auto mask_3 = _mm256_movemask_ps((__m256)compare_3);
        const auto mask_4 = _mm256_movemask_ps((__m256)compare_4);

        const auto final_mask = (mask_1 << 24) | (mask_2 << 16) | (mask_3 << 8) | mask_4;

        //std::cout << "0b" << std::bitset<32>(final_mask) << std::endl;

        if (final_mask != 0) {
            const auto result_offset = index * 32;
            const auto result_position = result_offset + __builtin_clz(final_mask);
            return result[result_position];
        }
    }

    return nullptr;
}

typedef void (*ProcCallback)(const char* name);

static void BM_Simple(benchmark::State& state) {
    for (auto _ : state) {
        auto callback = (ProcCallback)GetProcAddressSimple("vkCallback");
        callback("hello");
    }
}

BENCHMARK(BM_Simple);

static void BM_SIMD(benchmark::State& state) {
    for (auto _ : state) {
        auto callback = (ProcCallback)GetProcAddressSIMD("vkCallback");
        callback("hello");
    }
}

BENCHMARK(BM_SIMD);

static void BM_SIMDCombined(benchmark::State& state) {
    for (auto _ : state) {
        auto callback = (ProcCallback)GetProcAddressSIMDCombined("vkCallback");
        callback("hello");
    }
}

BENCHMARK(BM_SIMDCombined);

static void BM_SIMDStraight(benchmark::State& state) {
    const auto hash = MurmurHash2("vkCallback", strlen("vkCallback"), 0);

    for (auto _ : state) {
        auto callback = (ProcCallback)GetProcAddressSIMDStraight(hash);
        callback("hello");
    }
}

BENCHMARK(BM_SIMDStraight);

static void BM_SIMDCombinedStraight(benchmark::State& state) {
    const auto hash = MurmurHash2("vkCallback", strlen("vkCallback"), 0);

    for (auto _ : state) {
        auto callback = (ProcCallback)GetProcAddressSIMDCombinedStraight(hash);
        callback("hello");
    }
}

BENCHMARK(BM_SIMDCombinedStraight);

static void BM_SIMDTryFit(benchmark::State& state) {
    const auto hash = MurmurHash2("vkCallback", strlen("vkCallback"), 0);

    for (auto _ : state) {
        auto callback = (ProcCallback)GetProcAddressSIMDTryFit(hash);
        callback("hello");
    }
}

BENCHMARK(BM_SIMDTryFit);

BENCHMARK_MAIN();
