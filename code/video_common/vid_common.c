#include <SDL2/SDL.h>

#include "video_common/vid_public.h"

SDL_Window*   main_window   = NULL;
SDL_Renderer* main_renderer = NULL;

void Video_Start() {
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0) {
        System_Error("Failed to initialize the SDL video subsystem : %s.", SDL_GetError());
    }

    main_window = SDL_CreateWindow("Bob", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    if (main_window == NULL) {
        System_Error("Failed to create SDL window : %s.", SDL_GetError());
    }

    main_renderer = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_SOFTWARE);
    if (main_renderer == NULL) {
        System_Error("Failed to create SDL software renderer : %s.", SDL_GetError());
    }
}

void Video_Stop() {
    if (main_renderer != NULL) {
        SDL_DestroyRenderer(main_renderer);
        main_renderer = NULL;
    }

    if (main_window != NULL) {
        SDL_DestroyWindow(main_window);
        main_window = NULL;
    }

    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

void Video_Frame() {
    SDL_RenderClear(main_renderer);
    SDL_RenderPresent(main_renderer);
}
