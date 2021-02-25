#include <setjmp.h>

#include <SDL2/SDL.h>

#include "common/com_shared.h"
#include "common/com_public.h"
#include "common/com_local.h"

#include "server/sv_public.h"

#include "client/cl_public.h"

static jmp_buf error_capture                      = {};
static bool    error_occured                      = false;
static char    error_buffer[LARGE_STRING_MAXIMUM] = {0};
static bool    quit_requested                     = false;
static int64_t developer_variable                 = -1;
static int64_t dedicated_variable                 = -1;

static common_export_log_t exports_log = {
  .Error = Common_Error,
  .Print = Common_Print,
};

static common_export_memory_system_t exports_memory_system = {
  .Allocate = Memory_SystemAllocate,
  .Free     = Memory_SystemFree,
};

static common_export_string_t exports_string = {
  .Allocate    = String_Allocate,
  .Free        = String_Free,
  .Length      = String_Length,
  .Compare     = String_Compare,
  .Copy        = String_Copy,
  .Clone       = String_Clone,
  .Print       = String_Print,
  .ToInteger   = String_ToInteger,
  .FromInteger = String_FromInteger,
};

static common_export_console_buffer_t exports_console_buffer = {
  .AddText = ConsoleBuffer_AddText,
  .AddLine = ConsoleBuffer_AddLine,
};

static common_export_variable_t exports_variable = {
  .Register          = Variable_Register,
  .Unregister        = Variable_Unregister,
  .Reset             = Variable_Reset,
  .GetString         = Variable_GetString,
  .SetString         = Variable_SetString,
  .GetInteger        = Variable_GetInteger,
  .SetInteger        = Variable_SetInteger,
  .IsModified        = Variable_IsModified,
  .ModificationCount = Variable_ModificationCount,
  .ClearModified     = Variable_ClearModified,
};

static common_export_command_t exports_command = {
  .Register   = Command_Register,
  .Unregister = Command_Unregister,
};

static common_export_t common_exports = {
  .log            = &exports_log,
  .memory_system  = &exports_memory_system,
  .string         = &exports_string,
  .console_buffer = &exports_console_buffer,
  .variable       = &exports_variable,
  .command        = &exports_command,
};

static void Common_PumpEvents();

void Common_Start() {
    if (setjmp(error_capture)) {
        Common_Stop();

        ConsoleSystem_Error(error_buffer);

        return;
    }

    ConsoleBuffer_Start();
    ConsoleSystem_Start();
    ConsoleGame_Start();

    Variable_Start();
    Command_Start();

    developer_variable = Variable_Register("com_developer", "0", VARIABLE_FLAG_SYSTEM | VARIABLE_FLAG_CHEAT);
    dedicated_variable = Variable_Register("com_dedicated", "0", VARIABLE_FLAG_PRODUCTION | VARIABLE_FLAG_NETWORK);

    Server_Start();
    Client_Start();
}

void Common_Stop() {
    Client_Stop();
    Server_Stop();

    Variable_Unregister(dedicated_variable);
    Variable_Unregister(developer_variable);

    dedicated_variable = -1;
    developer_variable = -1;

    Command_Stop();
    Variable_Stop();

    ConsoleGame_Stop();
    ConsoleSystem_Stop();
    ConsoleBuffer_Stop();
}

void Common_Frame() {
    if (setjmp(error_capture)) {
        Common_Stop();

        ConsoleSystem_Error(error_buffer);
    }

    Common_PumpEvents();

    ConsoleBuffer_Frame();
    ConsoleSystem_Frame();
    ConsoleGame_Frame();

    Variable_Frame();
    Command_Frame();

    Server_Frame();
    Client_Frame();
}

void Common_Quit() {
    quit_requested = true;
}

bool Common_IsQuitting() {
    return quit_requested;
}

void Common_Error(const char* message, ...) {
    va_list argument_list = {};

    if (error_occured == true) {
        ConsoleSystem_Print("FATAL: Recursive error. Quitting.\n");

        exit(1);
    }

    error_occured = true;

    va_start(argument_list, message);
    vsprintf(error_buffer, message, argument_list);
    va_end(argument_list);

    Common_Print(PRINT_LEVEL_ERROR, "ERROR: %s\n", error_buffer);

    longjmp(error_capture, -1);
}

void Common_Print(uint8_t log_level, const char* message, ...) {
    char    formatted_message[16 * 1024] = {0};
    va_list argument_list                = {};

    if (log_level == PRINT_LEVEL_DEVELOPER) {
        int64_t is_developer = Variable_GetInteger(developer_variable);

        if (is_developer != 1) {
            return;
        }
    }

    va_start(argument_list, message);
    vsprintf(formatted_message, message, argument_list);
    va_end(argument_list);

    ConsoleSystem_Print(formatted_message);
    ConsoleGame_Print(formatted_message);
}

common_export_t* Common_Exports() {
    return &common_exports;
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
                Common_Print(PRINT_LEVEL_DEVELOPER, "Developer message\n");
            } else if (sdl_event.key.keysym.sym == SDLK_s) {
                Variable_SetInteger(developer_variable, 1);
            } else if (sdl_event.key.keysym.sym == SDLK_d) {
                Variable_SetInteger(developer_variable, 0);
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
