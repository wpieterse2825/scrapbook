#include <SDL2/SDL.h>

#include "common/com_shared.h"
#include "common/com_public.h"

#include "video_common/vid_public.h"

#include "video_opengl/gl_public.h"
#include "video_opengl/gl_local.h"

common_export_t* opengl_common_export = NULL;
SDL_Window*      opengl_main_window    = NULL;

static bool VideoOpenGL_Create(SDL_Window* window, size_t position_x, size_t position_y, size_t size_x, size_t size_y);
static void VideoOpenGL_Destroy(SDL_Window* window);
static void VideoOpenGL_BeginFrame(void);
static void VideoOpenGL_EndFrame(void);

static video_export_t video_exports = {
  .Create     = VideoOpenGL_Create,
  .Destroy    = VideoOpenGL_Destroy,
  .BeginFrame = VideoOpenGL_BeginFrame,
  .EndFrame   = VideoOpenGL_EndFrame,
};

video_export_t* VideoOpenGL_GetExports(common_export_t* common) {
    opengl_common_export = common;

    return &video_exports;
}

static bool VideoOpenGL_Create(SDL_Window* window, size_t position_x, size_t position_y, size_t size_x, size_t size_y) {
    opengl_common_export->log->Print(PRINT_LEVEL_INFORMATION, "Starting OpenGL renderer.\n");

    opengl_main_window = window;

    return true;
}

static void VideoOpenGL_Destroy(SDL_Window* window) {
    opengl_common_export->log->Print(PRINT_LEVEL_INFORMATION, "Destroying OpenGL renderer.\n");

    opengl_main_window    = NULL;
    opengl_common_export = NULL;
}

static void VideoOpenGL_BeginFrame(void) {
}

static void VideoOpenGL_EndFrame(void) {
}
