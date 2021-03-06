#include <SDL2/SDL.h>

#include "common/com_shared.h"
#include "common/com_public.h"

#include "video_common/vid_public.h"

#include "video_opengl/gl_public.h"
#include "video_vulkan/vk_public.h"

static bool            video_restart                    = false;
static SDL_Window*     main_window                      = NULL;
static const char*     current_renderer                 = NULL;
static int64_t         position_x                       = -1;
static int64_t         position_y                       = -1;
static int64_t         size_x                           = -1;
static int64_t         size_y                           = -1;
static video_export_t* video_exports                    = NULL;
static int64_t         video_restart_command            = -1;
static int64_t         video_screen_position_x_variable = -1;
static int64_t         video_screen_position_y_variable = -1;
static int64_t         video_screen_size_x_variable     = -1;
static int64_t         video_screen_size_y_variable     = -1;
static int64_t         video_renderer_variable          = -1;

static void Video_Create(void);
static void Video_Destroy(void);
static void Video_CheckModifiedVariables(void);
static void Video_ProcessRestart(void);
static void Video_Command_Restart(command_arguments_t argument);

void Video_Start(void) {
    video_restart_command = Command_Register("vid_restart", Video_Command_Restart, COMMAND_FLAG_PRODUCTION | COMMAND_FLAG_RENDERER);

    video_screen_position_x_variable =
      Variable_Register("vid_pos_x", "120", VARIABLE_FLAG_PRODUCTION | VARIABLE_FLAG_RENDERER | VARIABLE_FLAG_ARCHIVE);
    video_screen_position_y_variable =
      Variable_Register("vid_pos_y", "120", VARIABLE_FLAG_PRODUCTION | VARIABLE_FLAG_RENDERER | VARIABLE_FLAG_ARCHIVE);
    video_screen_size_x_variable =
      Variable_Register("vid_size_x", "1280", VARIABLE_FLAG_PRODUCTION | VARIABLE_FLAG_RENDERER | VARIABLE_FLAG_ARCHIVE);
    video_screen_size_y_variable =
      Variable_Register("vid_size_y", "720", VARIABLE_FLAG_PRODUCTION | VARIABLE_FLAG_RENDERER | VARIABLE_FLAG_ARCHIVE);
    video_renderer_variable =
      Variable_Register("vid_renderer", "vulkan", VARIABLE_FLAG_PRODUCTION | VARIABLE_FLAG_RENDERER | VARIABLE_FLAG_ARCHIVE);

    Variable_ClearModified(video_screen_position_x_variable);
    Variable_ClearModified(video_screen_position_y_variable);
    Variable_ClearModified(video_screen_size_x_variable);
    Variable_ClearModified(video_screen_size_y_variable);

    Video_Create();
}

void Video_Stop(void) {
    Video_Destroy();

    Variable_Unregister(video_renderer_variable);
    Variable_Unregister(video_screen_size_y_variable);
    Variable_Unregister(video_screen_size_x_variable);
    Variable_Unregister(video_screen_position_y_variable);
    Variable_Unregister(video_screen_position_x_variable);

    Command_Unregister(video_restart_command);

    video_renderer_variable          = -1;
    video_screen_size_y_variable     = -1;
    video_screen_size_x_variable     = -1;
    video_screen_position_y_variable = -1;
    video_screen_position_x_variable = -1;
    video_restart_command            = -1;
}

void Video_BeginFrame(void) {
    Video_CheckModifiedVariables();
    Video_ProcessRestart();

    if (video_exports != NULL) {
        video_exports->BeginFrame();
    }
}

void Video_EndFrame(void) {
    if (video_exports != NULL) {
        video_exports->EndFrame();
    }
}

// TODO(wpieterse): Find a better way of dealing with this.
static void Video_Create(void) {
    bool             still_trying     = true;
    Uint32           window_flags     = SDL_WINDOW_SHOWN;
    common_export_t* common_exports   = Common_Exports();
    bool             created_renderer = false;

    while (still_trying == true) {
        position_x       = Variable_GetInteger(video_screen_position_x_variable);
        position_y       = Variable_GetInteger(video_screen_position_y_variable);
        size_x           = Variable_GetInteger(video_screen_size_x_variable);
        size_y           = Variable_GetInteger(video_screen_size_y_variable);
        current_renderer = Variable_GetString(video_renderer_variable);

        Common_Print(PRINT_LEVEL_INFORMATION,
                     "Creating main window located at (%ld, %ld) with a size of (%ld, %ld).\n",
                     position_x,
                     position_y,
                     size_x,
                     size_y);

        if (String_Compare(current_renderer, "vulkan", COMMAND_LINE_MAXIMUM)) {
            window_flags |= SDL_WINDOW_VULKAN;

            video_exports = VideoVulkan_GetExports(common_exports);
        } else if (String_Compare(current_renderer, "opengl", COMMAND_LINE_MAXIMUM)) {
            window_flags |= SDL_WINDOW_OPENGL;

            video_exports = VideoOpenGL_GetExports(common_exports);
        } else {
            Common_Error("Unknown renderer '%s'.", current_renderer);
        }

        main_window = SDL_CreateWindow(GAME_NAME, position_x, position_y, size_x, size_y, window_flags);
        if (main_window == NULL) {
            Common_Error("Failed to create SDL window : %s.", SDL_GetError());
        }

        created_renderer = video_exports->Create(main_window, position_x, position_y, size_x, size_y);
        if (created_renderer == false) {
            video_exports->Destroy(main_window);

            Common_Print(PRINT_LEVEL_INFORMATION, "Destroying the main window.\n");

            SDL_DestroyWindow(main_window);
            main_window = NULL;

            if (String_Compare(current_renderer, "vulkan", COMMAND_LINE_MAXIMUM)) {
                Common_Print(PRINT_LEVEL_INFORMATION, "Trying the OpenGL renderer next.\n");

                Variable_SetString(video_renderer_variable, "opengl");
            } else if (String_Compare(current_renderer, "opengl", COMMAND_LINE_MAXIMUM)) {
                Common_Error("Failed to create a suitable rendering engine.");
            }
        } else {
            still_trying = false;
        }
    }
}

static void Video_Destroy(void) {
    if (video_exports != NULL) {
        video_exports->Destroy(main_window);

        video_exports = NULL;
    }

    if (main_window != NULL) {
        Common_Print(PRINT_LEVEL_INFORMATION, "Destroying the main window.\n");

        SDL_DestroyWindow(main_window);
        main_window = NULL;
    }

    position_x       = -1;
    position_y       = -1;
    size_x           = -1;
    size_y           = -1;
    current_renderer = NULL;
}

static void Video_CheckModifiedVariables(void) {
    bool is_variables_modified = false;

    is_variables_modified |= Variable_IsModified(video_screen_position_x_variable);
    is_variables_modified |= Variable_IsModified(video_screen_position_y_variable);
    is_variables_modified |= Variable_IsModified(video_screen_size_x_variable);
    is_variables_modified |= Variable_IsModified(video_screen_size_y_variable);

    if (is_variables_modified == true) {
        Common_Print(PRINT_LEVEL_INFORMATION, "Video setting changes will be applied after vid_restart.\n");

        Variable_ClearModified(video_screen_position_x_variable);
        Variable_ClearModified(video_screen_position_y_variable);
        Variable_ClearModified(video_screen_size_x_variable);
        Variable_ClearModified(video_screen_size_y_variable);
    }
}

static void Video_ProcessRestart(void) {
    if (video_restart == true) {
        Video_Destroy();
        Video_Create();

        video_restart = false;
    }
}

static void Video_Command_Restart(command_arguments_t argument) {
    Common_Print(PRINT_LEVEL_INFORMATION, "Restarting the video subsystem.\n");

    video_restart = true;
}
