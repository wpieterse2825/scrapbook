set(FOLKLORE_COMMON_SOURCES
    com_main.c
    com_public.h
    sys_main.c
)

set_source_files_properties(${FOLKLORE_COMMON_SYSTEM_SOURCES} PROPERTIES COMPILE_DEFINITIONS BOOST_CONTEXT_EXPORT=)

set(FOLKLORE_COMMON_SYSTEM_SOURCES
    sys_main.c
)

add_library(folklore_common STATIC ${FOLKLORE_COMMON_SOURCES})
add_library(Folklore::Common ALIAS folklore_common)

target_link_libraries(folklore_common
    ${CMAKE_DL_LIBS}
    Threads::Threads
)

add_library(folklore_common_system STATIC ${FOLKLORE_COMMON_SYSTEM_SOURCES})
add_library(Folklore::Common::System ALIAS folklore_common_system)

target_link_libraries(folklore_common_system
    Folklore::Common
    Folklore::Server
    Folklore::Client
)
