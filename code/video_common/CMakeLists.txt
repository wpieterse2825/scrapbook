set(FOLKLORE_VIDEO_COMMON_SOURCES
    vid_common.c
    vid_public.h
)

add_library(folklore_video_common STATIC ${FOLKLORE_VIDEO_COMMON_SOURCES})
add_library(Folklore::Video::Common ALIAS folklore_video_common)

target_link_libraries(folklore_video_common
    ${SDL2_LIBRARIES}

    Folklore::Common
)
