#include <SDL2/SDL.h>

#include "common/com_public.h"

#include "video_common/vid_public.h"

static bool          video_restart = false;
static SDL_Window*   main_window   = NULL;
static SDL_Renderer* main_renderer = NULL;

static int64_t command_video_restart = -1;

static int64_t variable_video_screen_position_x = -1;
static int64_t variable_video_screen_position_y = -1;
static int64_t variable_video_screen_size_x     = -1;
static int64_t variable_video_screen_size_y     = -1;

static void Video_Restart();
static void Video_CreateWindow();
static void Video_DestroyWindow();
static void Video_Command_Restart(command_arguments_t argument);

void Video_Start() {
    command_video_restart = Command_Register("vid_restart", Video_Command_Restart);

    variable_video_screen_position_x = Variable_Register("vid_pos_x", "120", 0);
    variable_video_screen_position_y = Variable_Register("vid_pos_y", "120", 0);
    variable_video_screen_size_x     = Variable_Register("vid_size_x", "1280", 0);
    variable_video_screen_size_y     = Variable_Register("vid_size_y", "720", 0);

    Variable_ClearModified(variable_video_screen_position_x);
    Variable_ClearModified(variable_video_screen_position_y);
    Variable_ClearModified(variable_video_screen_size_x);
    Variable_ClearModified(variable_video_screen_size_y);

    Video_CreateWindow();
}

void Video_Stop() {
    Video_DestroyWindow();

    Variable_Unregister(variable_video_screen_size_y);
    variable_video_screen_size_y = -1;

    Variable_Unregister(variable_video_screen_size_x);
    variable_video_screen_size_x = -1;

    Variable_Unregister(variable_video_screen_position_y);
    variable_video_screen_position_y = -1;

    Variable_Unregister(variable_video_screen_position_x);
    variable_video_screen_position_x = -1;

    Command_Unregister(command_video_restart);
    command_video_restart = -1;
}

void Video_Frame() {
    bool is_variables_modified = false;

    Video_Restart();

    is_variables_modified |= Variable_IsModified(variable_video_screen_position_x);
    is_variables_modified |= Variable_IsModified(variable_video_screen_position_y);
    is_variables_modified |= Variable_IsModified(variable_video_screen_size_x);
    is_variables_modified |= Variable_IsModified(variable_video_screen_size_y);

    if (is_variables_modified == true) {
        Common_Log(LOG_LEVEL_INFORMATION, "Video setting changes will be applied after vid_restart.\n");

        Variable_ClearModified(variable_video_screen_position_x);
        Variable_ClearModified(variable_video_screen_position_y);
        Variable_ClearModified(variable_video_screen_size_x);
        Variable_ClearModified(variable_video_screen_size_y);
    }

    SDL_RenderClear(main_renderer);
    SDL_RenderPresent(main_renderer);
}

static void Video_Restart() {
    if (video_restart == true) {
        Video_DestroyWindow();
        Video_CreateWindow();

        video_restart = false;
    }
}

static void Video_CreateWindow() {
    int64_t position_x = Variable_GetInteger(variable_video_screen_position_x);
    int64_t position_y = Variable_GetInteger(variable_video_screen_position_y);
    int64_t size_x     = Variable_GetInteger(variable_video_screen_size_x);
    int64_t size_y     = Variable_GetInteger(variable_video_screen_size_y);

    main_window = SDL_CreateWindow("Bob", position_x, position_y, size_x, size_y, 0);
    if (main_window == NULL) {
        Common_Error("Failed to create SDL window : %s.", SDL_GetError());
    }

    main_renderer = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_SOFTWARE);
    if (main_renderer == NULL) {
        Common_Error("Failed to create SDL software renderer : %s.", SDL_GetError());
    }
}

static void Video_DestroyWindow() {
    if (main_renderer != NULL) {
        SDL_DestroyRenderer(main_renderer);
        main_renderer = NULL;
    }

    if (main_window != NULL) {
        SDL_DestroyWindow(main_window);
        main_window = NULL;
    }
}

static void Video_Command_Restart(command_arguments_t argument) {
    video_restart = true;
}
