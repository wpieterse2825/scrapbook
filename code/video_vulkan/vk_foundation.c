#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

#define VOLK_IMPLEMENTATION
#include "../external/volk/volk.h"

#include "common/com_shared.h"
#include "common/com_public.h"

#include "video_common/vid_public.h"

#include "video_vulkan/vk_public.h"
#include "video_vulkan/vk_local.h"

static uint32_t                    vulkan_extension_count                         = 0;
static const char**                vulkan_extensions                              = NULL;
static uint32_t                    vulkan_use_extension_count                     = 0;
static const char**                vulkan_use_extensions                          = NULL;
static uint32_t                    vulkan_layer_count                             = 0;
static VkLayerProperties*          vulkan_layers                                  = NULL;
static uint32_t                    vulkan_use_layer_count                         = 0;
static const char**                vulkan_use_layers                              = NULL;
static VkInstance                  vulkan_instance                                = NULL;
static bool                        can_use_debugging                              = false;
static VkDebugReportCallbackEXT    vulkan_debug_callback                          = NULL;
static uint32_t                    vulkan_physical_device_count                   = 0;
static VkPhysicalDevice*           vulkan_physical_devices                        = NULL;
static VkPhysicalDeviceProperties* vulkan_physical_device_properties              = NULL;
static uint32_t*                   vulkan_physical_device_queue_properties_counts = NULL;
static VkQueueFamilyProperties**   vulkan_physical_device_queue_properties        = NULL;
static uint32_t                    vulkan_physical_device_transfer_queue          = -1;
static uint32_t                    vulkan_physical_device_compute_queue           = -1;
static uint32_t                    vulkan_physical_device_graphics_queue          = -1;
static uint32_t                    vulkan_physical_device_index                   = -1;
static VkPhysicalDevice            vulkan_physical_device                         = NULL;
static VkDevice                    vulkan_logical_device                          = NULL;

static VKAPI_ATTR VkBool32 VKAPI_CALL VideoVulkan_DebugCallback(VkDebugReportFlagsEXT      flags,
                                                                VkDebugReportObjectTypeEXT object_type,
                                                                uint64_t                   object,
                                                                size_t                     location,
                                                                int32_t                    code,
                                                                const char*                layer_prefix,
                                                                const char*                message,
                                                                void*                      user_data);

bool VideoVulkan_CreateExtensions(void) {
    if (SDL_Vulkan_GetInstanceExtensions(main_window, &vulkan_extension_count, NULL) == 0) {
        common_exports->log->Print(PRINT_LEVEL_WARNING, "Failed to query Vulkan for extension count: %s\n", SDL_GetError());

        return false;
    }

    size_t allocation_count = sizeof(const char*) * vulkan_extension_count;
    vulkan_extensions       = (const char**)common_exports->memory_system->Allocate(allocation_count, MEMORY_TAG_RENDERER);
    if (vulkan_extensions == NULL) {
        common_exports->log->Print(PRINT_LEVEL_WARNING, "Failed to allocate memory to store Vulkan extension information.");

        return false;
    }

    if (SDL_Vulkan_GetInstanceExtensions(main_window, &vulkan_extension_count, vulkan_extensions) == 0) {
        common_exports->log->Print(PRINT_LEVEL_WARNING, "Failed to query Vulkan for extension information: %s\n", SDL_GetError());

        return false;
    }

    if (vulkan_extension_count == 0) {
        common_exports->log->Print(PRINT_LEVEL_INFORMATION, "No registered Vulkan extensions.\n");
    } else {
        common_exports->log->Print(PRINT_LEVEL_INFORMATION, "Vulkan extensions (%ld):\n", vulkan_extension_count);

        for (int32_t extension_index = 0; extension_index < vulkan_extension_count; extension_index++) {
            const char* current_extension = vulkan_extensions[extension_index];

            common_exports->log->Print(PRINT_LEVEL_INFORMATION, " - %s\n", current_extension);
        }
    }

    return true;
}

bool VideoVulkan_CreateLayers(void) {
    VkResult vulkan_result = VK_SUCCESS;

    vulkan_result = vkEnumerateInstanceLayerProperties(&vulkan_layer_count, NULL);
    if (vulkan_result != VK_SUCCESS) {
        common_exports->log->Print(PRINT_LEVEL_WARNING, "Failed to query Vulkan for layer count.");

        return false;
    }

    size_t allocation_count = sizeof(VkLayerProperties) * vulkan_layer_count;
    vulkan_layers           = (VkLayerProperties*)common_exports->memory_system->Allocate(allocation_count, MEMORY_TAG_RENDERER);
    if (vulkan_layers == NULL) {
        common_exports->log->Print(PRINT_LEVEL_WARNING, "Failed to allocate memory to store Vulkan layer information.");

        return false;
    }

    vulkan_result = vkEnumerateInstanceLayerProperties(&vulkan_layer_count, vulkan_layers);
    if (vulkan_result != VK_SUCCESS) {
        common_exports->log->Print(PRINT_LEVEL_WARNING, "Failed to query Vulkan for layer information.");

        return false;
    }

    if (vulkan_layer_count == 0) {
        common_exports->log->Print(PRINT_LEVEL_INFORMATION, "No registered Vulkan layers.\n");
    } else {
        common_exports->log->Print(PRINT_LEVEL_INFORMATION, "Vulkan layers (%ld):\n", vulkan_layer_count);

        for (int32_t layer_index = 0; layer_index < vulkan_layer_count; layer_index++) {
            VkLayerProperties* current_layer = &vulkan_layers[layer_index];

            common_exports->log->Print(PRINT_LEVEL_INFORMATION,
                                     " - %s (%ld - %ld) - %s\n",
                                     current_layer->layerName,
                                     current_layer->specVersion,
                                     current_layer->implementationVersion,
                                     current_layer->description);
        }
    }

    return true;
}

bool VideoVulkan_CreateUseExtensions(void) {
    size_t allocation_count = sizeof(const char*) * ((vulkan_extension_count + 1) * 2);

    vulkan_use_extensions = (const char**)common_exports->memory_system->Allocate(allocation_count, MEMORY_TAG_RENDERER);
    if (vulkan_use_extensions == NULL) {
        common_exports->log->Print(PRINT_LEVEL_WARNING, "Failed to allocate memory for the enable Vulkan extensions array.");

        return false;
    }

    common_exports->log->Print(PRINT_LEVEL_INFORMATION, "Using the following Vulkan extension:\n");

    // For now, use all available extensions.
    for (uint32_t current_extension = 0; current_extension < vulkan_extension_count; current_extension++) {
        const char* extension_name = vulkan_extensions[current_extension];

        common_exports->log->Print(PRINT_LEVEL_INFORMATION, " - %s\n", extension_name);

        vulkan_use_extensions[current_extension] = vulkan_extensions[current_extension];
    }

    // Same as above, use all available extensions.
    vulkan_use_extension_count = vulkan_extension_count;

    common_exports->log->Print(PRINT_LEVEL_INFORMATION, "Enabled %ld Vulkan extensions.\n", vulkan_use_extension_count);

    return true;
}

bool VideoVulkan_CreateUseLayers(void) {
    size_t allocation_count = sizeof(const char*) * ((vulkan_layer_count + 1) * 2);

    vulkan_use_layers = (const char**)common_exports->memory_system->Allocate(allocation_count, MEMORY_TAG_RENDERER);
    if (vulkan_use_layers == NULL) {
        common_exports->log->Print(PRINT_LEVEL_WARNING, "Failed to allocate memory for the enable Vulkan layers array.");

        return false;
    }

    int64_t debug_enable = common_exports->variable->GetInteger(vulkan_enable_debugging_variable);

    for (uint32_t layer_index = 0; layer_index < vulkan_layer_count; layer_index++) {
        VkLayerProperties* current_layer      = &vulkan_layers[layer_index];
        const char*        current_layer_name = current_layer->layerName;

        if (debug_enable == 1) {
            if (common_exports->string->Compare("VK_LAYER_KHRONOS_validation", current_layer_name)) {
                vulkan_use_layers[vulkan_use_layer_count] = current_layer_name;
                vulkan_use_layer_count++;

                // Need to also apply to the extension array.
                // TODO(wpieterse): Fix this mess.
                vulkan_use_extensions[vulkan_use_extension_count] = VK_EXT_DEBUG_REPORT_EXTENSION_NAME;
                vulkan_use_extension_count++;

                can_use_debugging = true;
            }
        }

        if (common_exports->string->Compare("VK_LAYER_MESA_device_select", current_layer_name)) {
            vulkan_use_layers[vulkan_use_layer_count] = current_layer_name;
            vulkan_use_layer_count++;
        }

        if (common_exports->string->Compare("VK_LAYER_MESA_overlay", current_layer_name)) {
            vulkan_use_layers[vulkan_use_layer_count] = current_layer_name;
            vulkan_use_layer_count++;
        }

        if (common_exports->string->Compare("VK_LAYER_NV_optimus", current_layer_name)) {
            vulkan_use_layers[vulkan_use_layer_count] = current_layer_name;
            vulkan_use_layer_count++;
        }

        if (common_exports->string->Compare("VK_LAYER_RENDERDOC_Capture", current_layer_name)) {
            vulkan_use_layers[vulkan_use_layer_count] = current_layer_name;
            vulkan_use_layer_count++;
        }
    }

    if (debug_enable == 1) {
        if (can_use_debugging == false) {
            common_exports->log->Print(PRINT_LEVEL_WARNING, "Requested to use Vulkan debug layer, but the layer could not be found.\n");
        }
    }

    common_exports->log->Print(PRINT_LEVEL_INFORMATION, "Using the following Vulkan layers:\n");

    for (int32_t layer_index = 0; layer_index < vulkan_use_layer_count; layer_index++) {
        const char* current_layer_name = vulkan_use_layers[layer_index];

        common_exports->log->Print(PRINT_LEVEL_INFORMATION, " - %s\n", current_layer_name);
    }

    common_exports->log->Print(PRINT_LEVEL_INFORMATION, "Enabled %ld Vulkan layers.\n", vulkan_use_layer_count);

    return true;
}

bool VideoVulkan_CreateInstance(void) {
    uint32_t vulkan_api_version = 0;

    vkEnumerateInstanceVersion(&vulkan_api_version);

    uint32_t vulkan_version_major = VK_VERSION_MAJOR(vulkan_api_version);
    uint32_t vulkan_version_minor = VK_VERSION_MINOR(vulkan_api_version);
    uint32_t vulkan_version_patch = VK_VERSION_PATCH(vulkan_api_version);

    common_exports->log->Print(PRINT_LEVEL_INFORMATION,
                             "Creating Vulkan instance, using API version %ld.%ld.%ld.\n",
                             vulkan_version_major,
                             vulkan_version_minor,
                             vulkan_version_patch);

    VkApplicationInfo application_information  = {};
    application_information.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    application_information.pNext              = NULL;
    application_information.apiVersion         = vulkan_api_version;
    application_information.pApplicationName   = GAME_NAME;
    application_information.applicationVersion = GAME_VERSION;
    application_information.pEngineName        = ENGINE_NAME;
    application_information.engineVersion      = ENGINE_VERSION;

    VkInstanceCreateInfo instance_information    = {};
    instance_information.sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instance_information.pNext                   = NULL;
    instance_information.flags                   = 0;
    instance_information.pApplicationInfo        = &application_information;
    instance_information.enabledExtensionCount   = vulkan_use_extension_count;
    instance_information.ppEnabledExtensionNames = vulkan_use_extensions;
    instance_information.enabledLayerCount       = vulkan_use_layer_count;
    instance_information.ppEnabledLayerNames     = vulkan_use_layers;

    // TODO(wpieterse): Get Vulkan to use our allocators.
    VkResult vulkan_result = vkCreateInstance(&instance_information, NULL, &vulkan_instance);
    if (vulkan_result != VK_SUCCESS) {
        if (vulkan_result == VK_ERROR_INCOMPATIBLE_DRIVER) {
            common_exports->log->Print(PRINT_LEVEL_WARNING, "Failed to find a suitable Vulkan driver.");

            return false;
        } else {
            common_exports->log->Print(PRINT_LEVEL_WARNING, "Failed to create the Vulkan instance object.");

            return false;
        }
    }

    volkLoadInstanceOnly(vulkan_instance);

    return true;
}

bool VideoVulkan_CreateDebugCallback(void) {
    if (can_use_debugging == true) {
        int64_t debug_enable          = common_exports->variable->GetInteger(vulkan_enable_debugging_variable);
        int64_t debug_use_trace       = common_exports->variable->GetInteger(vulkan_debug_trace_variable);
        int64_t debug_use_information = common_exports->variable->GetInteger(vulkan_debug_information_variable);
        int64_t debug_use_warning     = common_exports->variable->GetInteger(vulkan_debug_warning_variable);
        int64_t debug_use_performance = common_exports->variable->GetInteger(vulkan_debug_performance_warning_variable);

        if (debug_enable == 1) {
            VkDebugReportFlagsEXT debug_enable_flags = 0;

            common_exports->log->Print(PRINT_LEVEL_INFORMATION, "Enabling Vulkan debug layer with the following bits:\n");
            if (debug_use_trace == 1) {
                debug_enable_flags |= VK_DEBUG_REPORT_DEBUG_BIT_EXT;

                common_exports->log->Print(PRINT_LEVEL_INFORMATION, " - Trace\n");
            }

            if (debug_use_information == 1) {
                debug_enable_flags |= VK_DEBUG_REPORT_INFORMATION_BIT_EXT;

                common_exports->log->Print(PRINT_LEVEL_INFORMATION, " - Information\n");
            }

            if (debug_use_warning == 1) {
                debug_enable_flags |= VK_DEBUG_REPORT_WARNING_BIT_EXT;

                common_exports->log->Print(PRINT_LEVEL_INFORMATION, " - Warning\n");
            }

            if (debug_use_performance == 1) {
                debug_enable_flags |= VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT;

                common_exports->log->Print(PRINT_LEVEL_INFORMATION, " - Performace\n");
            }

            // Always enable error logging when using the debug interface.
            debug_enable_flags |= VK_DEBUG_REPORT_ERROR_BIT_EXT;

            common_exports->log->Print(PRINT_LEVEL_INFORMATION, " - Error\n");

            VkDebugReportCallbackCreateInfoEXT debug_information = {};
            debug_information.sType                              = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
            debug_information.flags                              = debug_enable_flags;
            debug_information.pfnCallback                        = VideoVulkan_DebugCallback;

            // TODO(wpieterse): Get Vulkan to use our allocators.
            VkResult vulkan_result = vkCreateDebugReportCallbackEXT(vulkan_instance, &debug_information, NULL, &vulkan_debug_callback);
            if (vulkan_result != VK_SUCCESS) {
                common_exports->log->Print(PRINT_LEVEL_WARNING, "Failed to enable debug logging for Vulkan.\n");
            }
        }
    }

    return true;
}

bool VideoVulkan_CreatePhysicalDeviceBuffers(void) {
    vkEnumeratePhysicalDevices(vulkan_instance, &vulkan_physical_device_count, NULL);
    if (vulkan_physical_device_count == 0) {
        common_exports->log->Print(PRINT_LEVEL_WARNING, "Failed to find any Vulkan devices.");

        return false;
    }

    vulkan_physical_devices = (VkPhysicalDevice*)common_exports->memory_system->Allocate(
      sizeof(VkPhysicalDevice) * vulkan_physical_device_count, MEMORY_TAG_RENDERER);
    if (vulkan_physical_devices == NULL) {
        common_exports->log->Print(PRINT_LEVEL_WARNING, "Failed to allocate memory to store the physical Vulkan devices.");

        return false;
    }

    vulkan_physical_device_properties = (VkPhysicalDeviceProperties*)common_exports->memory_system->Allocate(
      sizeof(VkPhysicalDeviceProperties) * vulkan_physical_device_count, MEMORY_TAG_RENDERER);
    if (vulkan_physical_device_properties == NULL) {
        common_exports->log->Print(PRINT_LEVEL_WARNING, "Failed to allocate memory to store the physical Vulkan devices properties.");

        return false;
    }

    vulkan_physical_device_queue_properties_counts =
      (uint32_t*)common_exports->memory_system->Allocate(sizeof(uint32_t) * vulkan_physical_device_count, MEMORY_TAG_RENDERER);
    if (vulkan_physical_device_queue_properties_counts == NULL) {
        common_exports->log->Print(PRINT_LEVEL_WARNING,
                                 "Failed to allocate memory to store the physical Vulkan devices queue property counts.");

        return false;
    }

    vulkan_physical_device_queue_properties = (VkQueueFamilyProperties**)common_exports->memory_system->Allocate(
      sizeof(VkQueueFamilyProperties*) * vulkan_physical_device_count, MEMORY_TAG_RENDERER);
    if (vulkan_physical_device_queue_properties == NULL) {
        common_exports->log->Print(PRINT_LEVEL_WARNING, "Failed to allocate memory to store the physical Vulkan devices queue properties.");

        return false;
    }

    vkEnumeratePhysicalDevices(vulkan_instance, &vulkan_physical_device_count, vulkan_physical_devices);

    for (size_t device_index = 0; device_index < vulkan_physical_device_count; device_index++) {
        VkPhysicalDevice            current_physical_device            = vulkan_physical_devices[device_index];
        VkPhysicalDeviceProperties* current_physical_device_properties = &vulkan_physical_device_properties[device_index];

        vkGetPhysicalDeviceProperties(current_physical_device, current_physical_device_properties);

        vkGetPhysicalDeviceQueueFamilyProperties(
          current_physical_device, &vulkan_physical_device_queue_properties_counts[device_index], NULL);

        vulkan_physical_device_queue_properties[device_index] = (VkQueueFamilyProperties*)common_exports->memory_system->Allocate(
          sizeof(VkQueueFamilyProperties) * vulkan_physical_device_queue_properties_counts[device_index], MEMORY_TAG_RENDERER);
        if (vulkan_physical_device_queue_properties[device_index] == NULL) {
            common_exports->log->Print(PRINT_LEVEL_WARNING, "Failed to allocate memory to store the physical Vulkan devices queue properties.");

            return false;
        }

        vkGetPhysicalDeviceQueueFamilyProperties(current_physical_device,
                                                 &vulkan_physical_device_queue_properties_counts[device_index],
                                                 vulkan_physical_device_queue_properties[device_index]);
    }

    common_exports->log->Print(PRINT_LEVEL_INFORMATION, "Vulkan devices (%ld):\n", vulkan_physical_device_count);
    for (size_t device_index = 0; device_index < vulkan_physical_device_count; device_index++) {
        VkPhysicalDeviceProperties* current_physical_device_properties = &vulkan_physical_device_properties[device_index];

        common_exports->log->Print(PRINT_LEVEL_INFORMATION, " - %s\n", current_physical_device_properties->deviceName);

        switch (current_physical_device_properties->vendorID) {
            case 0x8086:
                common_exports->log->Print(PRINT_LEVEL_INFORMATION, "   - Vendor         : Intel\n");
                break;
            case 0x10DE:
                common_exports->log->Print(PRINT_LEVEL_INFORMATION, "   - Vendor         : nVidia\n");
                break;
            case 0x1002:
                common_exports->log->Print(PRINT_LEVEL_INFORMATION, "   - Vendor         : AMD\n");
                break;
            default:
                common_exports->log->Print(
                  PRINT_LEVEL_INFORMATION, "   - Vendor         : Unknown (%ld)\n", current_physical_device_properties->vendorID);
                break;
        }

        common_exports->log->Print(PRINT_LEVEL_INFORMATION, "   - Device  ID     : %ld\n", current_physical_device_properties->deviceID);
        common_exports->log->Print(PRINT_LEVEL_INFORMATION, "   - Driver Version : %ld\n", current_physical_device_properties->driverVersion);

        uint32_t vulkan_version       = current_physical_device_properties->apiVersion;
        uint32_t vulkan_version_major = VK_VERSION_MAJOR(vulkan_version);
        uint32_t vulkan_version_minor = VK_VERSION_MINOR(vulkan_version);
        uint32_t vulkan_version_patch = VK_VERSION_PATCH(vulkan_version);

        common_exports->log->Print(
          PRINT_LEVEL_INFORMATION, "   - Vulkan Version : %ld.%ld.%ld\n", vulkan_version_major, vulkan_version_minor, vulkan_version_patch);

        switch (current_physical_device_properties->deviceType) {
            case VK_PHYSICAL_DEVICE_TYPE_OTHER:
                common_exports->log->Print(PRINT_LEVEL_INFORMATION, "   - Vulkan Type    : Other\n");
                break;
            case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
                common_exports->log->Print(PRINT_LEVEL_INFORMATION, "   - Vulkan Type    : Integrated GPU\n");
                break;
            case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
                common_exports->log->Print(PRINT_LEVEL_INFORMATION, "   - Vulkan Type    : Discrete GPU\n");
                break;
            case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
                common_exports->log->Print(PRINT_LEVEL_INFORMATION, "   - Vulkan Type    : Virtual GPU\n");
                break;
            case VK_PHYSICAL_DEVICE_TYPE_CPU:
                common_exports->log->Print(PRINT_LEVEL_INFORMATION, "   - Vulkan Type    : CPU\n");
                break;
            default:
                common_exports->log->Print(PRINT_LEVEL_INFORMATION, "   - Vulkan Type    : Unknown\n");
                break;
        }
    }

    return true;
}

bool VideoVulkan_CreatePhysicalDevice(void) {
    for (uint32_t device_index = 0; device_index < vulkan_physical_device_count; device_index++) {
        uint32_t device_queue_count = vulkan_physical_device_queue_properties_counts[device_index];

        for (uint32_t queue_index = 0; queue_index < device_queue_count; queue_index++) {
            VkQueueFamilyProperties* current_queue_properties = &vulkan_physical_device_queue_properties[device_index][queue_index];

            if (current_queue_properties->queueCount == 0) {
                Common_Print(PRINT_LEVEL_WARNING, "Vulkan device %ld queue %ld has zero queues!\n", device_index, queue_index);

                continue;
            }

            // TODO(wpieterse): Find a better way to select a device here. Also, implement a way for common variables to select a device
            // so that the user can have some preferences.
            bool queue_supports_transfer = current_queue_properties->queueFlags & VK_QUEUE_TRANSFER_BIT;
            bool queue_supports_compute  = current_queue_properties->queueFlags & VK_QUEUE_COMPUTE_BIT;
            bool queue_supports_graphics = current_queue_properties->queueFlags & VK_QUEUE_GRAPHICS_BIT;

            if (queue_supports_transfer == true) {
                vulkan_physical_device_transfer_queue = queue_index;
            }

            if (queue_supports_compute == true) {
                vulkan_physical_device_compute_queue = queue_index;
            }

            if (queue_supports_graphics == true) {
                vulkan_physical_device_graphics_queue = queue_index;
            }

            vulkan_physical_device_index = device_index;
            vulkan_physical_device       = vulkan_physical_devices[device_index];
            break;
        }
    }

    if (vulkan_physical_device_transfer_queue == -1) {
        common_exports->log->Print(PRINT_LEVEL_WARNING, "Failed to find a Vulkan transfer queue.");

        return false;
    } else {
        common_exports->log->Print(PRINT_LEVEL_INFORMATION,
                                 "Using queue %ld on device %ld for transfer.\n",
                                 vulkan_physical_device_transfer_queue,
                                 vulkan_physical_device_index);
    }

    if (vulkan_physical_device_compute_queue == -1) {
        common_exports->log->Print(PRINT_LEVEL_WARNING, "Failed to find a Vulkan compute queue.");

        return false;
    } else {
        common_exports->log->Print(PRINT_LEVEL_INFORMATION,
                                 "Using queue %ld on device %ld for compute.\n",
                                 vulkan_physical_device_compute_queue,
                                 vulkan_physical_device_index);
    }

    if (vulkan_physical_device_graphics_queue == -1) {
        common_exports->log->Print(PRINT_LEVEL_WARNING, "Failed to find a Vulkan graphics queue.");

        return false;
    } else {
        common_exports->log->Print(PRINT_LEVEL_INFORMATION,
                                 "Using queue %ld on device %ld for graphics.\n",
                                 vulkan_physical_device_graphics_queue,
                                 vulkan_physical_device_index);
    }

    return true;
}

bool VideoVulkan_CreateLogicalDevice(void) {
    return true;
}

bool VideoVulkan_DestroyLogicalDevice(void) {
}

bool VideoVulkan_DestroyPhysicalDevice(void) {
    vulkan_physical_device_index = -1;

    if (vulkan_physical_device != NULL) {
        vulkan_physical_device = NULL;
    }

    vulkan_physical_device_graphics_queue = -1;
    vulkan_physical_device_compute_queue  = -1;
    vulkan_physical_device_transfer_queue = -1;
}

bool VideoVulkan_DestroyPhysicalDeviceBuffers(void) {
    if (vulkan_physical_device_queue_properties != NULL) {
        for (uint32_t device_index = 0; device_index < vulkan_physical_device_count; device_index++) {
            common_exports->memory_system->Free(vulkan_physical_device_queue_properties[device_index]);

            vulkan_physical_device_queue_properties[device_index] = NULL;
        }

        common_exports->memory_system->Free(vulkan_physical_device_queue_properties);

        vulkan_physical_device_queue_properties = NULL;
    }

    if (vulkan_physical_device_queue_properties_counts != NULL) {
        common_exports->memory_system->Free(vulkan_physical_device_queue_properties_counts);

        vulkan_physical_device_queue_properties_counts = NULL;
    }

    if (vulkan_physical_device_properties != NULL) {
        common_exports->memory_system->Free(vulkan_physical_device_properties);

        vulkan_physical_device_properties = NULL;
    }

    if (vulkan_physical_devices != NULL) {
        common_exports->memory_system->Free(vulkan_physical_devices);

        vulkan_physical_devices = NULL;
    }

    vulkan_physical_device_count = 0;
}

bool VideoVulkan_DestroyDebugCallback(void) {
    if (vulkan_debug_callback != NULL) {
        // TODO(wpieterse): Get Vulkan to use our allocators.
        vkDestroyDebugReportCallbackEXT(vulkan_instance, vulkan_debug_callback, NULL);

        vulkan_debug_callback = NULL;
    }

    can_use_debugging = false;
}

bool VideoVulkan_DestroyInstance(void) {
    if (vulkan_instance != NULL) {
        // TODO(wpieterse): Get Vulkan to use our allocators.
        vkDestroyInstance(vulkan_instance, NULL);

        vulkan_instance = NULL;
    }
}

bool VideoVulkan_DestroyUseLayers(void) {
    if (vulkan_use_layers != NULL) {
        common_exports->memory_system->Free(vulkan_use_layers);
        vulkan_use_layers = NULL;
    }

    vulkan_use_layer_count = 0;
}

bool VideoVulkan_DestroyUseExtensions(void) {
    if (vulkan_use_extensions != NULL) {
        common_exports->memory_system->Free(vulkan_use_extensions);
        vulkan_use_extensions = NULL;
    }

    vulkan_use_extension_count = 0;
}

bool VideoVulkan_DestroyLayers(void) {
    if (vulkan_layers != NULL) {
        common_exports->memory_system->Free(vulkan_layers);
        vulkan_layers = NULL;
    }

    vulkan_layer_count = 0;
}

bool VideoVulkan_DestroyExtensions(void) {
    if (vulkan_extensions != NULL) {
        common_exports->memory_system->Free(vulkan_extensions);
        vulkan_extensions = NULL;
    }

    vulkan_extension_count = 0;
}

static VKAPI_ATTR VkBool32 VKAPI_CALL VideoVulkan_DebugCallback(VkDebugReportFlagsEXT      flags,
                                                                VkDebugReportObjectTypeEXT object_type,
                                                                uint64_t                   object,
                                                                size_t                     location,
                                                                int32_t                    code,
                                                                const char*                layer_prefix,
                                                                const char*                message,
                                                                void*                      user_data) {
    char message_buffer[LARGE_STRING_MAXIMUM] = {0};

    common_exports->string->Print(message_buffer,
                                  LARGE_STRING_MAXIMUM,
                                  "%s - %s - Location: %ld - Object Type: %ld - Object ID : %ld - Code : %ld.\n",
                                  layer_prefix,
                                  message,
                                  location,
                                  object_type,
                                  object,
                                  code);

    if (flags & VK_DEBUG_REPORT_DEBUG_BIT_EXT) {
        common_exports->log->Print(PRINT_LEVEL_DEVELOPER, message_buffer);
    } else if (flags & VK_DEBUG_REPORT_INFORMATION_BIT_EXT) {
        common_exports->log->Print(PRINT_LEVEL_INFORMATION, message_buffer);
    } else if (flags & VK_DEBUG_REPORT_WARNING_BIT_EXT) {
        common_exports->log->Print(PRINT_LEVEL_WARNING, message_buffer);
    } else if (flags & VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT) {
        common_exports->log->Print(PRINT_LEVEL_WARNING, message_buffer);
    } else if (flags & VK_DEBUG_REPORT_ERROR_BIT_EXT) {
        common_exports->log->Print(PRINT_LEVEL_ERROR, message_buffer);
    }

    return VK_FALSE;
}
