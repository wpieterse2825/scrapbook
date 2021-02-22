set(SOURCE_RANDOMS_SIMD
    main.cpp
)

add_executable(randoms_simd
    ${SOURCE_RANDOMS_SIMD}
)

target_compile_options(randoms_simd
    PRIVATE "-mavx2"
)
