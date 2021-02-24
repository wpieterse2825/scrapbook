set(SOURCE_RANDOMS_SOFTWARE_RASTERIZER
    main.cpp
)

add_executable(randoms_software_rasterizer
    ${SOURCE_RANDOMS_SOFTWARE_RASTERIZER}
)

target_include_directories(randoms_software_rasterizer
    PRIVATE ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(randoms_software_rasterizer
    ${SDL2_LIBRARIES}
)
