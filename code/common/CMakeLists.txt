set(FOLKLORE_COMMON_SOURCES
    com_main.c
    com_public.h
)

set(FOLKLORE_COMMON_SYSTEM_SOURCES
    sys_main.c
)

add_library(folklore_common STATIC ${FOLKLORE_COMMON_SOURCES})
add_library(Folklore::Common ALIAS folklore_common)

add_library(folklore_common_system STATIC ${FOLKLORE_COMMON_SYSTEM_SOURCES})
add_library(Folklore::Common::System ALIAS folklore_common_system)

target_link_libraries(folklore_common_system
    Folklore::Common
    Folklore::Server
    Folklore::Client
)
