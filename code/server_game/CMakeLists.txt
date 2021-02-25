set(FOLKLORE_SERVER_GAME_SOURCES
    sg_local.h
    sg_main.c
)

add_library(folklore_server_game STATIC ${FOLKLORE_SERVER_GAME_SOURCES})
add_library(Folklore::Server::Game ALIAS folklore_server_game)

# target_link_libraries(folklore_server_game)
