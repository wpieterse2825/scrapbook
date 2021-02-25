#include <setjmp.h>

#include <SDL2/SDL.h>

#include "common/com_public.h"
#include "common/com_local.h"

#include "server/sv_public.h"

#include "client/cl_public.h"

static jmp_buf error_capture           = {};
static bool    error_occured           = false;
static char    error_buffer[16 * 1024] = {0};
static bool    quit_requested          = false;

static int64_t variable_common_developer = -1;
static int64_t variable_common_dedicated = -1;

static void Common_PumpEvents();

void Common_Error(const char* message, ...) {
    va_list argument_list = {};

    error_occured = true;

    va_start(argument_list, message);
    vsprintf(error_buffer, message, argument_list);
    va_end(argument_list);

    longjmp(error_capture, -1);
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

void Common_Start() {
    Variable_Start();
    Command_Start();

    ConsoleBuffer_Start();

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

    ConsoleBuffer_Stop();

    Command_Stop();
    Variable_Stop();
}

bool Common_Frame() {
    if (setjmp(error_capture)) {
        Common_Stop();

        ConsoleSystem_Show();
    }

    Common_PumpEvents();

    ConsoleSystem_Frame();

    Variable_Frame();
    Command_Frame();

    ConsoleBuffer_Frame();

    Server_Frame();
    Client_Frame();

    return quit_requested;
}

void Common_Quit() {
    quit_requested = true;
}

static void Common_PumpEvents() {
    SDL_Event sdl_event = {};

    while (SDL_PollEvent(&sdl_event) == true) {
        if (sdl_event.type == SDL_QUIT) {
            Common_Quit();
        } else if (sdl_event.type == SDL_KEYUP) {
            if (sdl_event.key.keysym.sym == SDLK_ESCAPE) {
                Common_Quit();
            } else if (sdl_event.key.keysym.sym == SDLK_q) {
                ConsoleBuffer_AddLine("list_variables");
            } else if (sdl_event.key.keysym.sym == SDLK_w) {
                ConsoleBuffer_AddLine("list_commands");
            } else if (sdl_event.key.keysym.sym == SDLK_e) {
                Common_Error("Testing errors.");
            } else if (sdl_event.key.keysym.sym == SDLK_a) {
                Common_Log(LOG_LEVEL_DEVELOPER, "Developer message\n");
            } else if (sdl_event.key.keysym.sym == SDLK_s) {
                Variable_SetInteger(variable_common_developer, 1);
            } else if (sdl_event.key.keysym.sym == SDLK_d) {
                Variable_SetInteger(variable_common_developer, 0);
            } else if (sdl_event.key.keysym.sym == SDLK_z) {
                ConsoleBuffer_AddLine("vid_restart");
            } else if (sdl_event.key.keysym.sym == SDLK_x) {
                ConsoleSystem_Show();
            } else if (sdl_event.key.keysym.sym == SDLK_c) {
                ConsoleSystem_Hide();
            }
        }
    }
}
