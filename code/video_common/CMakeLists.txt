set(FOLKLORE_VIDEO_COMMON_SOURCES
    vid_common.c
    vid_local.h
    vid_public.h
)

add_library(folklore_video_common STATIC ${FOLKLORE_VIDEO_COMMON_SOURCES})
add_library(Folklore::Video::Common ALIAS folklore_video_common)
