#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

#include "../external/volk/volk.h"

#include "common/com_shared.h"
#include "common/com_public.h"

#include "video_common/vid_public.h"

#include "video_vulkan/vk_public.h"
#include "video_vulkan/vk_local.h"

common_export_t* vulkan_common_export                      = NULL;
SDL_Window*      vulkan_main_window                        = NULL;
int64_t          vulkan_enable_debugging_variable          = -1;
int64_t          vulkan_debug_trace_variable               = -1;
int64_t          vulkan_debug_information_variable         = -1;
int64_t          vulkan_debug_warning_variable             = -1;
int64_t          vulkan_debug_performance_warning_variable = -1;

static bool VideoVulkan_Create(SDL_Window* window, size_t position_x, size_t position_y, size_t size_x, size_t size_y);
static void VideoVulkan_Destroy(SDL_Window* window);
static void VideoVulkan_BeginFrame(void);
static void VideoVulkan_EndFrame(void);

static video_export_t video_exports = {
  .Create     = VideoVulkan_Create,
  .Destroy    = VideoVulkan_Destroy,
  .BeginFrame = VideoVulkan_BeginFrame,
  .EndFrame   = VideoVulkan_EndFrame,
};

video_export_t* VideoVulkan_GetExports(common_export_t* common) {
    vulkan_common_export = common;

    return &video_exports;
}

static bool VideoVulkan_Create(SDL_Window* window, size_t position_x, size_t position_y, size_t size_x, size_t size_y) {
    vulkan_common_export->log->Print(PRINT_LEVEL_INFORMATION, "Starting Vulkan renderer.\n");

    VkResult vulkan_result = volkInitialize();
    if (vulkan_result != VK_SUCCESS) {
        vulkan_common_export->log->Print(PRINT_LEVEL_WARNING, "Failed to initialize the Volk library.");

        return false;
    }

    vulkan_main_window = window;

    vulkan_enable_debugging_variable =
      vulkan_common_export->variable->Register("vid_vk_debugging", "1", VARIABLE_FLAG_RENDERER | VARIABLE_FLAG_CHEAT);
    vulkan_debug_trace_variable =
      vulkan_common_export->variable->Register("vid_vk_debug_trace", "1", VARIABLE_FLAG_RENDERER | VARIABLE_FLAG_CHEAT);
    vulkan_debug_information_variable =
      vulkan_common_export->variable->Register("vid_vk_debug_information", "1", VARIABLE_FLAG_RENDERER | VARIABLE_FLAG_CHEAT);
    vulkan_debug_warning_variable =
      vulkan_common_export->variable->Register("vid_vk_debug_warning", "1", VARIABLE_FLAG_RENDERER | VARIABLE_FLAG_CHEAT);
    vulkan_debug_performance_warning_variable =
      vulkan_common_export->variable->Register("vid_vk_debug_performace", "1", VARIABLE_FLAG_RENDERER | VARIABLE_FLAG_CHEAT);

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
    vulkan_common_export->log->Print(PRINT_LEVEL_INFORMATION, "Destroying Vulkan renderer.\n");

    VideoVulkan_DestroyLogicalDevice();
    VideoVulkan_DestroyPhysicalDevice();
    VideoVulkan_DestroyPhysicalDeviceBuffers();
    VideoVulkan_DestroyDebugCallback();
    VideoVulkan_DestroyInstance();
    VideoVulkan_DestroyUseLayers();
    VideoVulkan_DestroyUseExtensions();
    VideoVulkan_DestroyLayers();
    VideoVulkan_DestroyExtensions();

    vulkan_common_export->variable->Unregister(vulkan_debug_performance_warning_variable);
    vulkan_common_export->variable->Unregister(vulkan_debug_warning_variable);
    vulkan_common_export->variable->Unregister(vulkan_debug_information_variable);
    vulkan_common_export->variable->Unregister(vulkan_debug_trace_variable);
    vulkan_common_export->variable->Unregister(vulkan_enable_debugging_variable);

    vulkan_debug_performance_warning_variable = -1;
    vulkan_debug_warning_variable             = -1;
    vulkan_debug_information_variable         = -1;
    vulkan_debug_trace_variable               = -1;
    vulkan_enable_debugging_variable          = -1;

    vulkan_main_window   = NULL;
    vulkan_common_export = NULL;
}

static void VideoVulkan_BeginFrame(void) {
}

static void VideoVulkan_EndFrame(void) {
}
