set(FOLKLORE_CLIENT_SOURCES
    cl_local.h
    cl_main.c
    cl_public.h
)

add_library(folklore_client STATIC ${FOLKLORE_CLIENT_SOURCES})
add_library(Folklore::Client ALIAS folklore_client)

target_link_libraries(folklore_client
    Folklore::Common
    Folklore::Video::Vulkan
    Folklore::Client::Game
)
