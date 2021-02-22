set(SOURCE_LIBRARIES_SOFTWARE_RASTERIZER
    main.cpp
)

add_executable(libraries_software_rasterizer
    ${SOURCE_LIBRARIES_SOFTWARE_RASTERIZER}
)

target_include_directories(libraries_software_rasterizer
    PRIVATE ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(libraries_software_rasterizer
    ${SDL2_LIBRARIES}
)
