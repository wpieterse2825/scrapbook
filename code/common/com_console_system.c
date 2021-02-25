#include <SDL2/SDL.h>

#include "common/com_public.h"
#include "common/com_local.h"

static SDL_Window*   console_system_window   = NULL;
static SDL_Renderer* console_system_renderer = NULL;

void ConsoleSystem_Start() {
    console_system_window = SDL_CreateWindow("Bob", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_HIDDEN);
    if (console_system_window == NULL) {
        Common_Error("Failed to create SDL window : %s.", SDL_GetError());
    }

    console_system_renderer = SDL_CreateRenderer(console_system_window, -1, SDL_RENDERER_SOFTWARE);
    if (console_system_renderer == NULL) {
        Common_Error("Failed to create SDL software renderer : %s.", SDL_GetError());
    }
}

void ConsoleSystem_Stop() {
    if (console_system_renderer != NULL) {
        SDL_DestroyRenderer(console_system_renderer);
        console_system_renderer = NULL;
    }

    if (console_system_window != NULL) {
        SDL_DestroyWindow(console_system_window);
        console_system_window = NULL;
    }
}

void ConsoleSystem_Frame() {
}

void ConsoleSystem_Show() {
    if (console_system_window != NULL) {
        SDL_ShowWindow(console_system_window);
    }
}

void ConsoleSystem_Hide() {
    if (console_system_window != NULL) {
        SDL_HideWindow(console_system_window);
    }
}
