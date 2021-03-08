set(SOURCE_RANDOMS_DEVICE
    main.cpp
)

add_executable(randoms_device
    ${SOURCE_RANDOMS_DEVICE}
)

target_link_libraries(randoms_device
    ${CMAKE_THREAD_LIBS_INIT}
)
