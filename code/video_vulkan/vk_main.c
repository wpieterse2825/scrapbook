#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

#include "../external/volk/volk.h"

#include "common/com_shared.h"
#include "common/com_public.h"

#include "video_common/vid_public.h"

#include "video_vulkan/vk_public.h"
#include "video_vulkan/vk_local.h"

common_export_t* common_exports                            = NULL;
SDL_Window*      main_window                               = NULL;
int64_t          vulkan_enable_debugging_variable          = -1;
int64_t          vulkan_debug_trace_variable               = -1;
int64_t          vulkan_debug_information_variable         = -1;
int64_t          vulkan_debug_warning_variable             = -1;
int64_t          vulkan_debug_performance_warning_variable = -1;

static video_export_t video_exports = {};

static void VideoVulkan_Create(SDL_Window* window, size_t position_x, size_t position_y, size_t size_x, size_t size_y);
static void VideoVulkan_Destroy(SDL_Window* window);
static void VideoVulkan_BeginFrame();
static void VideoVulkan_EndFrame();

video_export_t* VideoVulkan_Exports(common_export_t* common) {
    common_exports = common;

    video_exports.Create     = VideoVulkan_Create;
    video_exports.Destroy    = VideoVulkan_Destroy;
    video_exports.BeginFrame = VideoVulkan_BeginFrame;
    video_exports.EndFrame   = VideoVulkan_EndFrame;

    return &video_exports;
}

static void VideoVulkan_Create(SDL_Window* window, size_t position_x, size_t position_y, size_t size_x, size_t size_y) {
    common_exports->log->Log(LOG_LEVEL_INFORMATION, "Starting Vulkan renderer.\n");

    VkResult vulkan_result = volkInitialize();
    if (vulkan_result != VK_SUCCESS) {
        Common_Error("Failed to initialize the Volk library.");
    }

    main_window = window;

    vulkan_enable_debugging_variable          = common_exports->variable->Register("vid_vk_debugging", "1", 0);
    vulkan_debug_trace_variable               = common_exports->variable->Register("vid_vk_debug_trace", "1", 0);
    vulkan_debug_information_variable         = common_exports->variable->Register("vid_vk_debug_information", "1", 0);
    vulkan_debug_warning_variable             = common_exports->variable->Register("vid_vk_debug_warning", "1", 0);
    vulkan_debug_performance_warning_variable = common_exports->variable->Register("vid_vk_debug_performace", "1", 0);

    VideoVulkan_CreateExtensions();
    VideoVulkan_CreateLayers();
    VideoVulkan_CreateUseExtensions();
    VideoVulkan_CreateUseLayers();
    VideoVulkan_CreateInstance();
    VideoVulkan_CreateDebugCallback();
    VideoVulkan_CreatePhysicalDeviceBuffers();
    VideoVulkan_CreatePhysicalDevice();
    VideoVulkan_CreateLogicalDevice();
}

static void VideoVulkan_Destroy(SDL_Window* window) {
    common_exports->log->Log(LOG_LEVEL_INFORMATION, "Destroying Vulkan renderer.\n");

    VideoVulkan_DestroyLogicalDevice();
    VideoVulkan_DestroyPhysicalDevice();
    VideoVulkan_DestroyPhysicalDeviceBuffers();
    VideoVulkan_DestroyDebugCallback();
    VideoVulkan_DestroyInstance();
    VideoVulkan_DestroyUseLayers();
    VideoVulkan_DestroyUseExtensions();
    VideoVulkan_DestroyLayers();
    VideoVulkan_DestroyExtensions();

    common_exports->variable->Unregister(vulkan_debug_performance_warning_variable);
    common_exports->variable->Unregister(vulkan_debug_warning_variable);
    common_exports->variable->Unregister(vulkan_debug_information_variable);
    common_exports->variable->Unregister(vulkan_debug_trace_variable);
    common_exports->variable->Unregister(vulkan_enable_debugging_variable);

    vulkan_debug_performance_warning_variable = -1;
    vulkan_debug_warning_variable             = -1;
    vulkan_debug_information_variable         = -1;
    vulkan_debug_trace_variable               = -1;
    vulkan_enable_debugging_variable          = -1;

    main_window    = NULL;
    common_exports = NULL;
}

static void VideoVulkan_BeginFrame() {
}

static void VideoVulkan_EndFrame() {
}
