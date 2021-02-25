set(FOLKLORE_VIDEO_VULKAN_SOURCES
    vk_foundation.c
    vk_local.h
    vk_main.c
    vk_public.h
)

add_library(folklore_video_vulkan STATIC ${FOLKLORE_VIDEO_VULKAN_SOURCES})
add_library(Folklore::Video::Vulkan ALIAS folklore_video_vulkan)
