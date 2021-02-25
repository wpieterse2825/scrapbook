set(FOLKLORE_COMMON_SOURCES
    com_command.c
    com_console_buffer.c
    com_console_system.c
    com_local.h
    com_main.c
    com_public.h
    com_utilities.c
    com_variable.c
)

add_library(folklore_common STATIC ${FOLKLORE_COMMON_SOURCES})
add_library(Folklore::Common ALIAS folklore_common)
