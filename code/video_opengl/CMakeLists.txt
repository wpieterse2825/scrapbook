set(FOLKLORE_VIDEO_OPENGL_SOURCES
    gl_foundation.c
    gl_local.h
    gl_main.c
    gl_public.h
)

add_library(folklore_video_opengl STATIC ${FOLKLORE_VIDEO_OPENGL_SOURCES})
add_library(Folklore::Video::OpenGL ALIAS folklore_video_opengl)
