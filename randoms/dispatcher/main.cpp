#include <stdint.h>
#include <string.h>

#include <iostream>

#define VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO          0
#define VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO   1
#define VK_STRUCTURE_TYPE_LOADER_LAYER                  2
#define VK_STRUCTURE_TYPE_LAYER_INSTANCE_DISPATCH_TABLE 3

using VkResult   = int64_t;
using VkInstance = size_t;

struct VkStructure;
struct VkInstanceCreateInfo;
struct VkLoaderInstanceCreateInfo;
struct VkLayerInstanceDispatchTable;

typedef void* (*PFN_GetInstanceProcAddress)(VkInstance instance, const char* procedure_name);
typedef VkResult (*PFN_CreateInstance)(VkInstanceCreateInfo* create_info, VkInstance* out_instace);
typedef void (*PFN_DestroyInstance)(VkInstance instance);
typedef void (*PFN_Draw)(VkInstance instance);

struct VkStructure {
    uint64_t structure_type;
    void*    next_structure;
};

struct VkLoaderLayer {
    uint64_t structure_type;
    void*    next_structure;

    VkLoaderLayer*             next_layer;
    PFN_GetInstanceProcAddress next_gipa;
};

struct VkLoaderInstanceCreateInfo {
    uint64_t structure_type;
    void*    next_structure;

    VkLoaderLayer* layers;
};

struct VkInstanceCreateInfo {
    uint64_t structure_type;
    void*    next_structure;
};

struct VkLayerInstanceDispatchTable {
    PFN_GetInstanceProcAddress GetInstanceProcAddress;
    PFN_CreateInstance         CreateInstance;
    PFN_DestroyInstance        DestroyInstance;
    PFN_Draw                   Draw;
};

struct VkICDInstance {
    VkLayerInstanceDispatchTable dispatcher_block;

    const char* name;
};

void PopulateDispatcherTable(VkLayerInstanceDispatchTable* dispatch_table, VkInstance instance, PFN_GetInstanceProcAddress gipa) {
    dispatch_table->GetInstanceProcAddress = (PFN_GetInstanceProcAddress)gipa(instance, "VkGetInstanceProcAddress");
    dispatch_table->CreateInstance         = (PFN_CreateInstance)gipa(instance, "VkCreateInstance");
    dispatch_table->DestroyInstance        = (PFN_DestroyInstance)gipa(instance, "VkDestroyInstance");
    dispatch_table->Draw                   = (PFN_Draw)gipa(instance, "VkDraw");
}

VkResult VkCreateInstanceICD(VkInstanceCreateInfo* create_info, VkInstance* out_instance) {
    VkICDInstance* our_instance = (VkICDInstance*)malloc(sizeof(VkICDInstance));

    our_instance->name = "Super Fantastic ICD";

    *out_instance = (VkInstance)our_instance;

    return 0;
}

void VkDestroyInstanceICD(VkInstance instance) {
    VkICDInstance* our_instance = (VkICDInstance*)instance;

    free(our_instance);
}

void VkDrawICD(VkInstance instance) {
    VkICDInstance* our_instance = (VkICDInstance*)instance;

    std::cout << "Draw - ICD - " << our_instance->name << std::endl;
}

void* VkGetInstanceProcAddressICD(VkInstance instance, const char* name) {
    if (!strcmp(name, "VkGetInstanceProcAddress")) {
        return (void*)&VkGetInstanceProcAddressICD;
    }

    if (!strcmp(name, "VkCreateInstance")) {
        return (void*)&VkCreateInstanceICD;
    }

    if (!strcmp(name, "VkDestroyInstance")) {
        return (void*)&VkDestroyInstanceICD;
    }

    if (!strcmp(name, "VkDraw")) {
        return (void*)&VkDrawICD;
    }

    return nullptr;
}

struct VkLayerInstance {
    VkLayerInstanceDispatchTable dispatcher_block;

    const char* layer_name;

    VkInstance                   inner_instance;
    VkLayerInstanceDispatchTable inner_dispatcher;
};

VkResult VkCreateInstanceLayer_1(VkInstanceCreateInfo* create_info, VkInstance* out_instance) {
    VkStructure*                next_structure       = (VkStructure*)create_info->next_structure;
    VkLoaderInstanceCreateInfo* instance_create_info = nullptr;

    while (next_structure != nullptr) {
        if (next_structure->structure_type == VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO) {
            instance_create_info = (VkLoaderInstanceCreateInfo*)next_structure;

            break;
        }

        next_structure = (VkStructure*)next_structure->next_structure;
    }

    PFN_GetInstanceProcAddress next_gipa = instance_create_info->layers->next_gipa;
    instance_create_info->layers         = instance_create_info->layers->next_layer;

    PFN_CreateInstance next_ci = (PFN_CreateInstance)next_gipa(0, "VkCreateInstance");

    VkInstance next_instance = 0;
    VkResult   next_result   = next_ci(create_info, &next_instance);

    VkLayerInstance* our_instance = (VkLayerInstance*)malloc(sizeof(VkLayerInstance));
    *out_instance                 = (VkInstance)our_instance;

    our_instance->layer_name = "Debug Layer";

    our_instance->inner_instance = next_instance;

    PopulateDispatcherTable(&our_instance->inner_dispatcher, next_instance, next_gipa);

    return 0;
}

void VkDestroyInstanceLayer_1(VkInstance instance) {
    VkLayerInstance* our_instance = (VkLayerInstance*)instance;

    our_instance->inner_dispatcher.DestroyInstance(our_instance->inner_instance);

    free(our_instance);
}

void VkDrawLayer_1(VkInstance instance) {
    VkLayerInstance* our_instance = (VkLayerInstance*)instance;

    std::cout << "Draw - Layer 1 - " << our_instance->layer_name << " - Pre" << std::endl;

    our_instance->inner_dispatcher.Draw(our_instance->inner_instance);

    std::cout << "Draw - Layer 1 - " << our_instance->layer_name << " - Post" << std::endl;
}

void* VkGetInstanceProcAddressLayer_1(VkInstance instance, const char* name) {
    if (!strcmp(name, "VkGetInstanceProcAddress")) {
        return (void*)&VkGetInstanceProcAddressLayer_1;
    }

    if (!strcmp(name, "VkCreateInstance")) {
        return (void*)&VkCreateInstanceLayer_1;
    }

    if (!strcmp(name, "VkDestroyInstance")) {
        return (void*)&VkDestroyInstanceLayer_1;
    }

    if (!strcmp(name, "VkDraw")) {
        return (void*)&VkDrawLayer_1;
    }

    VkLayerInstance* our_instance = (VkLayerInstance*)instance;

    return our_instance->inner_dispatcher.GetInstanceProcAddress(our_instance->inner_instance, name);
}

VkResult VkCreateInstanceLayer_2(VkInstanceCreateInfo* create_info, VkInstance* out_instance) {
    VkStructure*                next_structure       = (VkStructure*)create_info->next_structure;
    VkLoaderInstanceCreateInfo* instance_create_info = nullptr;

    while (next_structure != nullptr) {
        if (next_structure->structure_type == VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO) {
            instance_create_info = (VkLoaderInstanceCreateInfo*)next_structure;

            break;
        }

        next_structure = (VkStructure*)next_structure->next_structure;
    }

    PFN_GetInstanceProcAddress next_gipa = instance_create_info->layers->next_gipa;
    instance_create_info->layers         = instance_create_info->layers->next_layer;

    PFN_CreateInstance next_ci = (PFN_CreateInstance)next_gipa(0, "VkCreateInstance");

    VkInstance next_instance = 0;
    VkResult   next_result   = next_ci(create_info, &next_instance);

    VkLayerInstance* our_instance = (VkLayerInstance*)malloc(sizeof(VkLayerInstance));
    *out_instance                 = (VkInstance)our_instance;

    our_instance->layer_name = "Validation Layer";

    our_instance->inner_instance = next_instance;

    PopulateDispatcherTable(&our_instance->inner_dispatcher, next_instance, next_gipa);

    return 0;
}

void VkDestroyInstanceLayer_2(VkInstance instance) {
    VkLayerInstance* our_instance = (VkLayerInstance*)instance;

    our_instance->inner_dispatcher.DestroyInstance(our_instance->inner_instance);

    free(our_instance);
}

void VkDrawLayer_2(VkInstance instance) {
    VkLayerInstance* our_instance = (VkLayerInstance*)instance;

    std::cout << "Draw - Layer 2 - " << our_instance->layer_name << " - Pre" << std::endl;

    our_instance->inner_dispatcher.Draw(our_instance->inner_instance);

    std::cout << "Draw - Layer 2 - " << our_instance->layer_name << " - Post" << std::endl;
}

void* VkGetInstanceProcAddressLayer_2(VkInstance instance, const char* name) {
    if (!strcmp(name, "VkGetInstanceProcAddress")) {
        return (void*)&VkGetInstanceProcAddressLayer_2;
    }

    if (!strcmp(name, "VkCreateInstance")) {
        return (void*)&VkCreateInstanceLayer_2;
    }

    if (!strcmp(name, "VkDestroyInstance")) {
        return (void*)&VkDestroyInstanceLayer_2;
    }

    if (!strcmp(name, "VkDraw")) {
        return (void*)&VkDrawLayer_2;
    }

    VkLayerInstance* our_instance = (VkLayerInstance*)instance;

    return our_instance->inner_dispatcher.GetInstanceProcAddress(our_instance->inner_instance, name);
}

VkResult VkCreateInstance(VkInstanceCreateInfo* create_info, VkInstance* out_instance) {
    VkLoaderLayer              layer_layer_1        = {};
    VkLoaderLayer              layer_layer_2        = {};
    VkLoaderInstanceCreateInfo instance_create_info = {};

    layer_layer_1.structure_type = VK_STRUCTURE_TYPE_LOADER_LAYER;
    layer_layer_1.next_layer     = nullptr;
    layer_layer_1.next_gipa      = VkGetInstanceProcAddressICD;

    layer_layer_2.structure_type = VK_STRUCTURE_TYPE_LOADER_LAYER;
    layer_layer_2.next_layer     = &layer_layer_1;
    layer_layer_2.next_gipa      = VkGetInstanceProcAddressLayer_1;

    instance_create_info.structure_type = VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO;
    instance_create_info.layers         = &layer_layer_2;

    create_info->next_structure = &instance_create_info;

    PFN_GetInstanceProcAddress gipa            = (PFN_GetInstanceProcAddress)&VkGetInstanceProcAddressLayer_2;
    PFN_CreateInstance         create_instance = (PFN_CreateInstance)gipa(0, "VkCreateInstance");

    create_instance(create_info, out_instance);

    VkLayerInstanceDispatchTable* dispatch_table = (VkLayerInstanceDispatchTable*)*out_instance;

    PopulateDispatcherTable(dispatch_table, *out_instance, gipa);

    return 0;
}

void VkDestroyInstance(VkInstance instance) {
    VkLayerInstanceDispatchTable* dispatch_table = (VkLayerInstanceDispatchTable*)instance;

    dispatch_table->DestroyInstance(instance);
}

void* VkGetInstanceProcAddress(VkInstance instance, const char* name) {
    VkLayerInstanceDispatchTable* dispatch_table = (VkLayerInstanceDispatchTable*)instance;

    return dispatch_table->GetInstanceProcAddress(instance, name);
}

void VkDraw(VkInstance instance) {
    VkLayerInstanceDispatchTable* dispatch_table = (VkLayerInstanceDispatchTable*)instance;

    dispatch_table->Draw(instance);
}

int main() {
    VkInstanceCreateInfo instance_create_info = {};
    VkInstance           out_instance         = 0;

    instance_create_info.structure_type = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

    VkCreateInstance(&instance_create_info, &out_instance);
    VkDraw(out_instance);
    VkDestroyInstance(out_instance);

    return 0;
}
