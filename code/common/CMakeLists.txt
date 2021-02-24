set(FOLKLORE_COMMON_SOURCES
    allocator.c
    allocator.h
    array.h
    atomic.h
    bheap.c
    bheap.h
    bitarray.h
    CMakeLists.txt
    cmdline.c
    cmdline.h
    com_main.c
    com_public.h
    config.h
    fiber.c
    fiber.h
    fiber_jump.S
    fiber_make.S
    fiber_ontop.S
    getopt.h
    getopt.c
    handle.c
    handle.h
    hash.c
    hash.h
    io.c
    io.h
    jobs.c
    jobs.h
    lin-alloc.c
    lin-alloc.h
    linear-buffer.h
    lockless.c
    lockless.h
    macros.h
    math.c
    math-easing.h
    math.h
    math-scalar.h
    math-types.h
    math-vec.h
    os.c
    os.h
    platform.h
    pool.h
    ringbuffer.c
    ringbuffer.h
    rng.c
    rng.h
    _simd.h
    simd.h
    sokol_time.h
    stb_printf.h
    string.c
    string.h
    strpool.h
    sx.c
    sx.h
    threads.c
    threads.h
    timer.c
    timer.h
    vmem.c
    vmem.h
    xxhash.c
    xxhash.h
)

set_source_files_properties(${FOLKLORE_COMMON_SYSTEM_SOURCES} PROPERTIES COMPILE_DEFINITIONS BOOST_CONTEXT_EXPORT=)

set(FOLKLORE_COMMON_SYSTEM_SOURCES
    sys_main.c
)

add_library(folklore_common STATIC ${FOLKLORE_COMMON_SOURCES})
add_library(Folklore::Common ALIAS folklore_common)

target_link_libraries(folklore_common
    ${CMAKE_DL_LIBS}
    Threads::Threads
)

add_library(folklore_common_system STATIC ${FOLKLORE_COMMON_SYSTEM_SOURCES})
add_library(Folklore::Common::System ALIAS folklore_common_system)

target_link_libraries(folklore_common_system
    Folklore::Common
    Folklore::Server
    Folklore::Client
)
