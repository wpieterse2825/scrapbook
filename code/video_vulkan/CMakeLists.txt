set(FOLKLORE_VIDEO_VULKAN_SOURCES
    vk_local.h
    vk_main.c
)

add_library(folklore_video_vulkan STATIC ${FOLKLORE_VIDEO_VULKAN_SOURCES})
add_library(Folklore::Video::Vulkan ALIAS folklore_video_vulkan)

target_link_libraries(folklore_video_vulkan
    Folklore::Video::Common
)
