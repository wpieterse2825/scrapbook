#include <SDL2/SDL.h>

#include "common/com_shared.h"
#include "common/com_public.h"
#include "common/com_local.h"

static bool          is_window_shown  = false;
static SDL_Window*   console_window   = NULL;
static SDL_Renderer* console_renderer = NULL;
static const char*   error_message    = NULL;

static void ConsoleSystem_Destroy();

void ConsoleSystem_Start() {
    Common_Print(PRINT_LEVEL_INFORMATION, "Creating system console window.\n");

    // Ensure we shutdown SDL correctly.
    atexit(ConsoleSystem_Destroy);

    console_window = SDL_CreateWindow(GAME_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_HIDDEN);
    if (console_window == NULL) {
        Common_Error("Failed to create SDL window : %s.", SDL_GetError());
    }

    Common_Print(PRINT_LEVEL_INFORMATION, "Creating system console renderer.\n");

    console_renderer = SDL_CreateRenderer(console_window, -1, SDL_RENDERER_SOFTWARE);
    if (console_renderer == NULL) {
        Common_Error("Failed to create SDL software renderer : %s.", SDL_GetError());
    }
}

void ConsoleSystem_Stop() {
    // The window and the renderer are destroyed in the ConsoleSyste_Destroy call, which is executed at program exit. Doing it here will
    // cause issues when an error is thrown, as this function is called via Common_Stop, which is executed in the error path.
}

void ConsoleSystem_Frame() {
    if (is_window_shown == true) {
        SDL_SetRenderDrawColor(console_renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(console_renderer);

        SDL_RenderPresent(console_renderer);
    }
}

void ConsoleSystem_Error(const char* error_message) {
    if (console_window == NULL) {
        Common_Print(PRINT_LEVEL_ERROR, "Error before system console could be created, quitting.\n");

        exit(1);
    }

    if (console_renderer == NULL) {
        Common_Print(PRINT_LEVEL_ERROR, "Error before system console could be created, quitting.\n");

        exit(1);
    }

    ConsoleSystem_Show();

    error_message = error_message;
}

void ConsoleSystem_Print(const char* message) {
    printf("%s", message);
}

void ConsoleSystem_Show() {
    if (console_window != NULL) {
        SDL_ShowWindow(console_window);
    }

    is_window_shown = true;
}

void ConsoleSystem_Hide() {
    is_window_shown = false;

    if (console_window != NULL) {
        SDL_HideWindow(console_window);
    }
}

static void ConsoleSystem_Destroy() {
    if (console_renderer != NULL) {
        Common_Print(PRINT_LEVEL_INFORMATION, "Destroying system console renderer.\n");

        SDL_DestroyRenderer(console_renderer);
        console_renderer = NULL;
    }

    if (console_window != NULL) {
        Common_Print(PRINT_LEVEL_INFORMATION, "Destroying system console window.\n");

        SDL_DestroyWindow(console_window);
        console_window = NULL;
    }

    SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
    SDL_Quit();
}
