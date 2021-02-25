include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(common)
add_subdirectory(server_game)
add_subdirectory(server)
add_subdirectory(video_common)
add_subdirectory(video_vulkan)
add_subdirectory(client_game)
add_subdirectory(client)

set(FOLKLORE_SOURCES
    folklore.c
)

add_executable(folklore
    ${FOLKLORE_SOURCES}
)

target_link_libraries(folklore
    Folklore::Common
    Folklore::Server
    Folklore::Client
)
