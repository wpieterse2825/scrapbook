set(FOLKLORE_SERVER_SOURCES
    sv_local.h
    sv_main.c
    sv_public.h
)

add_library(folklore_server STATIC ${FOLKLORE_SERVER_SOURCES})
add_library(Folklore::Server ALIAS folklore_server)

# target_link_libraries(folklore_server)
