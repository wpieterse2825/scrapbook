extern common_export_t* vulkan_common_export;
extern SDL_Window*      vulkan_main_window;
extern int64_t          vulkan_enable_debugging_variable;
extern int64_t          vulkan_debug_trace_variable;
extern int64_t          vulkan_debug_information_variable;
extern int64_t          vulkan_debug_warning_variable;
extern int64_t          vulkan_debug_performance_warning_variable;

bool VideoVulkan_CreateExtensions(void);
bool VideoVulkan_CreateLayers(void);
bool VideoVulkan_CreateUseExtensions(void);
bool VideoVulkan_CreateUseLayers(void);
bool VideoVulkan_CreateInstance(void);
bool VideoVulkan_CreateDebugCallback(void);
bool VideoVulkan_CreatePhysicalDeviceBuffers(void);
bool VideoVulkan_CreatePhysicalDevice(void);
bool VideoVulkan_CreateLogicalDevice(void);
bool VideoVulkan_DestroyLogicalDevice(void);
bool VideoVulkan_DestroyPhysicalDevice(void);
bool VideoVulkan_DestroyPhysicalDeviceBuffers(void);
bool VideoVulkan_DestroyDebugCallback(void);
bool VideoVulkan_DestroyInstance(void);
bool VideoVulkan_DestroyUseLayers(void);
bool VideoVulkan_DestroyUseExtensions(void);
bool VideoVulkan_DestroyLayers(void);
bool VideoVulkan_DestroyExtensions(void);
