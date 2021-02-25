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

static bool VideoVulkan_Create(SDL_Window* window, size_t position_x, size_t position_y, size_t size_x, size_t size_y);
static void VideoVulkan_Destroy(SDL_Window* window);
static void VideoVulkan_BeginFrame(void);
static void VideoVulkan_EndFrame(void);

video_export_t* VideoVulkan_Exports(common_export_t* common) {
    common_exports = common;

    video_exports.Create     = VideoVulkan_Create;
    video_exports.Destroy    = VideoVulkan_Destroy;
    video_exports.BeginFrame = VideoVulkan_BeginFrame;
    video_exports.EndFrame   = VideoVulkan_EndFrame;

    return &video_exports;
}

static bool VideoVulkan_Create(SDL_Window* window, size_t position_x, size_t position_y, size_t size_x, size_t size_y) {
    common_exports->log->Print(PRINT_LEVEL_INFORMATION, "Starting Vulkan renderer.\n");

    VkResult vulkan_result = volkInitialize();
    if (vulkan_result != VK_SUCCESS) {
        common_exports->log->Print(PRINT_LEVEL_WARNING, "Failed to initialize the Volk library.");

        return false;
    }

    main_window = window;

    vulkan_enable_debugging_variable          = common_exports->variable->Register("vid_vk_debugging", "1", 0);
    vulkan_debug_trace_variable               = common_exports->variable->Register("vid_vk_debug_trace", "1", 0);
    vulkan_debug_information_variable         = common_exports->variable->Register("vid_vk_debug_information", "1", 0);
    vulkan_debug_warning_variable             = common_exports->variable->Register("vid_vk_debug_warning", "1", 0);
    vulkan_debug_performance_warning_variable = common_exports->variable->Register("vid_vk_debug_performace", "1", 0);

    if (VideoVulkan_CreateExtensions() == false) {
        return false;
    }

    if (VideoVulkan_CreateLayers() == false) {
        return false;
    }

    if (VideoVulkan_CreateUseExtensions() == false) {
        return false;
    }

    if (VideoVulkan_CreateUseLayers() == false) {
        return false;
    }

    if (VideoVulkan_CreateInstance() == false) {
        return false;
    }

    if (VideoVulkan_CreateDebugCallback() == false) {
        return false;
    }

    if (VideoVulkan_CreatePhysicalDeviceBuffers() == false) {
        return false;
    }

    if (VideoVulkan_CreatePhysicalDevice() == false) {
        return false;
    }

    if (VideoVulkan_CreateLogicalDevice() == false) {
        return false;
    }

    return true;
}

static void VideoVulkan_Destroy(SDL_Window* window) {
    common_exports->log->Print(PRINT_LEVEL_INFORMATION, "Destroying Vulkan renderer.\n");

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

static void VideoVulkan_BeginFrame(void) {
}

static void VideoVulkan_EndFrame(void) {
}
