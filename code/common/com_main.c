#include <SDL2/SDL.h>

#include "common/com_public.h"
#include "common/com_local.h"

#include "server/sv_public.h"

#include "client/cl_public.h"

int64_t variable_common_developer = -1;
int64_t variable_common_dedicated = -1;

static void Common_PumpEvents();

void Common_Start() {
    Variable_Start();
    Command_Start();

    Console_Start();

    variable_common_developer = Variable_Register("com_developer", "0", 0);
    variable_common_dedicated = Variable_Register("com_dedicated", "0", 0);

    Server_Start();
    Client_Start();
}

void Common_Stop() {
    Client_Stop();
    Server_Stop();

    Variable_Unregister(variable_common_dedicated);
    variable_common_dedicated = -1;

    Variable_Unregister(variable_common_developer);
    variable_common_developer = -1;

    Console_Stop();

    Command_Stop();
    Variable_Stop();

    SDL_Quit();
}

void Common_Frame() {
    Common_PumpEvents();

    Variable_Frame();
    Command_Frame();

    Console_Frame();

    Server_Frame();
    Client_Frame();
}

void Common_Error(const char* message, ...) {
    char    formatted_message[16 * 1024] = {0};
    va_list argument_list                = {};

    Common_Stop();

    va_start(argument_list, message);
    vsprintf(formatted_message, message, argument_list);
    va_end(argument_list);

    printf("ERROR : %s\n", formatted_message);
    exit(1);
}

void Common_Log(uint8_t log_level, const char* message, ...) {
    char    formatted_message[16 * 1024] = {0};
    va_list argument_list                = {};

    if (log_level == LOG_LEVEL_DEVELOPER) {
        int64_t is_developer = Variable_GetInteger(variable_common_developer);

        if (is_developer != 1) {
            return;
        }
    }

    va_start(argument_list, message);
    vsprintf(formatted_message, message, argument_list);
    va_end(argument_list);

    printf("%s", formatted_message);
}

static void Common_PumpEvents() {
    SDL_Event sdl_event = {};

    while (SDL_PollEvent(&sdl_event) == true) {
        if (sdl_event.type == SDL_QUIT) {
            Common_Error("Quit.");
        } else if (sdl_event.type == SDL_KEYUP) {
            if (sdl_event.key.keysym.sym == SDLK_ESCAPE) {
                Common_Error("Quit.");
            } else if (sdl_event.key.keysym.sym == SDLK_q) {
                Console_AddLine("list_variables hello world");
            } else if (sdl_event.key.keysym.sym == SDLK_w) {
                Console_AddLine("list_commands");
            } else if (sdl_event.key.keysym.sym == SDLK_a) {
                Variable_SetInteger(variable_common_developer, 1);
            } else if (sdl_event.key.keysym.sym == SDLK_s) {
                Variable_SetInteger(variable_common_developer, 0);
            } else if (sdl_event.key.keysym.sym == SDLK_d) {
                Common_Log(LOG_LEVEL_DEVELOPER, "Developer message\n");
            }
        }
    }
}
