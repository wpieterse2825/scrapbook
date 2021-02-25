#include <SDL2/SDL.h>

#include "common/com_public.h"
#include "common/com_local.h"

static SDL_Window*   console_window   = NULL;
static SDL_Renderer* console_renderer = NULL;
static const char*   error_message    = NULL;

void ConsoleSystem_Start() {
    console_window = SDL_CreateWindow("Bob", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_HIDDEN);
    if (console_window == NULL) {
        Common_Error("Failed to create SDL window : %s.", SDL_GetError());
    }

    console_renderer = SDL_CreateRenderer(console_window, -1, SDL_RENDERER_SOFTWARE);
    if (console_renderer == NULL) {
        Common_Error("Failed to create SDL software renderer : %s.", SDL_GetError());
    }
}

void ConsoleSystem_Stop() {
    if (console_renderer != NULL) {
        SDL_DestroyRenderer(console_renderer);
        console_renderer = NULL;
    }

    if (console_window != NULL) {
        SDL_DestroyWindow(console_window);
        console_window = NULL;
    }
}

void ConsoleSystem_Frame() {
}

void ConsoleSystem_SetError(const char* error_message) {
    error_message = error_message;
}

void ConsoleSystem_Print(const char* message) {
    printf("%s", message);
}

void ConsoleSystem_Show() {
    if (console_window != NULL) {
        SDL_ShowWindow(console_window);
    }
}

void ConsoleSystem_Hide() {
    if (console_window != NULL) {
        SDL_HideWindow(console_window);
    }
}
