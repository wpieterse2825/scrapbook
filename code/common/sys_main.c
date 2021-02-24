#include <stdarg.h>
#include <stdio.h>

#include <SDL2/SDL.h>

#include "common/com_public.h"

#include "server/sv_public.h"
#include "client/cl_public.h"

void System_Error(const char* message, ...) {
    char    formatted_message[16 * 1024] = {0};
    va_list argument_list                = {};

    System_Stop();

    va_start(argument_list, message);
    vsprintf(formatted_message, message, argument_list);
    va_end(argument_list);

    printf("ERROR : %s\n", formatted_message);
    exit(1);
}

void System_Start() {
    Server_Start();
    Client_Start();
}

void System_Stop() {
    Client_Stop();
    Server_Stop();

    SDL_Quit();
}

void System_PumpEvents() {
    SDL_Event sdl_event = {};

    while (SDL_PollEvent(&sdl_event) == true) {
        if (sdl_event.type == SDL_QUIT) {
            System_Error("Quit.");
        } else if (sdl_event.type == SDL_KEYUP) {
            if (sdl_event.key.keysym.sym == SDLK_ESCAPE) {
                System_Error("Quit.");
            }
        }
    }
}

void System_Frame() {
    System_PumpEvents();

    Server_Frame();
    Client_Frame();
}
