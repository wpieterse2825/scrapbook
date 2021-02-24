set(FOLKLORE_CLIENT_GAME_SOURCES
    cg_local.h
    cg_main.c
)

add_library(folklore_client_game STATIC ${FOLKLORE_CLIENT_GAME_SOURCES})
add_library(Folklore::Client::Game ALIAS folklore_client_game)

target_link_libraries(folklore_client_game
    Folklore::Common
)
