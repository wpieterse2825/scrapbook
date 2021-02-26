include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(FOLKLORE_FOUNDATION_SOURCES
    foundation/parser.cpp
    foundation/parser.hpp
)

set(FOLKLORE_FRAMEWORK_SOURCES
    framework/common.cpp
    framework/common.hpp
    framework/console_command.cpp
    framework/console_command.hpp
    framework/console_variable.cpp
    framework/console_variable.hpp
    framework/console.cpp
    framework/console.hpp
)

set(FOLKLORE_SERVER_SOURCES
    server/server.cpp
    server/server.hpp
)

set(FOLKLORE_CLIENT_SOURCES
    client/client.cpp
    client/client.hpp
)

set(FOLKLORE_VIDEO_SOURCES
    video/video.cpp
    video/video.hpp
)

set(FOLKLORE_AUDIO_SOURCES
    audio/audio.cpp
    audio/audio.hpp
)

set(FOLKLORE_SOURCES
    folklore.cpp
)

add_executable(folklore
    ${FOLKLORE_FOUNDATION_SOURCES}
    ${FOLKLORE_FRAMEWORK_SOURCES}
    ${FOLKLORE_SERVER_SOURCES}
    ${FOLKLORE_CLIENT_SOURCES}
    ${FOLKLORE_VIDEO_SOURCES}
    ${FOLKLORE_AUDIO_SOURCES}
    ${FOLKLORE_SOURCES}
)

target_include_directories(folklore
    PRIVATE ${SDL2_INCLUDE_DIR}
    PRIVATE ${Vulkan_INCLUDE_DIR}
)

target_link_libraries(folklore
    ${SDL2_LIBRARIES}
    ${Vulkan_LIBRARIES}
    volk_headers
)
