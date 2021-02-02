#include <string.h>
#include <iostream>

typedef enum VkStructureType {
    VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO        = 1,
    VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO = 2,
    VK_STRUCTURE_TYPE_DEBUG                       = 3,
} VkStructureType;

typedef uint64_t VkInstance;

struct VkInstanceCreateInfo;

typedef void (*PFN_vkVoidFunction)(void);
typedef void (*PFN_vkDebugCallback)(const char* message);
typedef PFN_vkVoidFunction (*PFN_vkGetProcedureAddress)(VkInstance instance, const char* pName);
typedef void (*PFN_vkCreateInstance)(VkInstanceCreateInfo* create, VkInstance* instance);
typedef void (*PFN_vkDestroyInstance)(VkInstance instance);
typedef void (*PFN_vkCmdDraw)(VkInstance instance);

struct VkStructure {
    VkStructureType type;
    const void*     next;
};

struct VkDebugInformation {
    VkStructureType type;
    const void*     next;

    PFN_vkDebugCallback Callback;
};

struct VkLayerInstanceLink {
    struct VkLayerInstanceLink* next;

    PFN_vkGetProcedureAddress NextGetProcedureAddress;
};

struct VkLayerInstanceCreateInfo {
    VkStructureType      type;
    const void*          next;
    VkLayerInstanceLink* layer_information;
};

typedef struct VkInstanceCreateInfo {
    VkStructureType type;
    const void*     next;
} VkInstanceCreateInfo;

struct VkLayerDispatchTable {
    PFN_vkGetProcedureAddress GetProcedureAddress;
    PFN_vkCreateInstance      CreateInstance;
    PFN_vkDestroyInstance     DestroyInstance;
    PFN_vkCmdDraw             Draw;
};

struct VkLayerObjectWrapper {
    uint64_t             object;
    VkLayerDispatchTable dispatch;
    void*                user;
};

const void* GetStructure(const void* first, VkStructureType structure_type) {
    auto structure = (VkStructure*)first;

    while (structure != nullptr && structure->type != structure_type) {
        structure = (VkStructure*)structure->next;
    }

    return structure;
}

void SampleICD_CreateInstance(VkInstanceCreateInfo* create, VkInstance* instance) {
    auto debug = (VkDebugInformation*)GetStructure(create->next, VK_STRUCTURE_TYPE_DEBUG);

    auto wrapper = new VkLayerObjectWrapper{};
    wrapper->user = (void*)debug->Callback;

    *instance = (VkInstance)wrapper;
}

void SampleICD_DestroyInstance(VkInstance instance) {
    auto wrapper = (VkLayerObjectWrapper*)instance;
    delete wrapper;
}

void SampleICD_CmdDraw(VkInstance instance) {
    auto wrapper = (VkLayerObjectWrapper*)instance;
    auto callback = (PFN_vkDebugCallback)wrapper->user;

    callback("ICD - Draw");
}

PFN_vkVoidFunction SampleICD_GetProcedureAddress(VkInstance instance, const char* pName) {
    if (!strcmp(pName, "vkCreateInstance")) {
        return (PFN_vkVoidFunction)&SampleICD_CreateInstance;
    }

    if (!strcmp(pName, "vkDestroyInstance")) {
        return (PFN_vkVoidFunction)&SampleICD_DestroyInstance;
    }

    if (!strcmp(pName, "vkCmdDraw")) {
        return (PFN_vkVoidFunction)&SampleICD_CmdDraw;
    }

    return nullptr;
}

void SampleLayer1_CmdDraw(VkInstance instance) {
    std::cout << "Layer 1 - Draw (Pre)" << std::endl;

    auto wrap = (VkLayerObjectWrapper*)instance;
    wrap->dispatch.Draw(wrap->object);

    std::cout << "Layer 1 - Draw (Post)" << std::endl;
}

void SampleLayer1_CreateInstance(VkInstanceCreateInfo* create, VkInstance* instance) {
    auto layerCreateInfo       = (VkLayerInstanceCreateInfo*)GetStructure(create->next, VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO);
    auto get_procedure_address = layerCreateInfo->layer_information->NextGetProcedureAddress;

    layerCreateInfo->layer_information = layerCreateInfo->layer_information->next;

    auto create_instance_callback = (PFN_vkCreateInstance)get_procedure_address(0, "vkCreateInstance");

    auto inner_instance = VkInstance {};
    create_instance_callback(create, &inner_instance);

    auto wrap                          = new VkLayerObjectWrapper {};
    wrap->object                       = inner_instance;
    wrap->dispatch.GetProcedureAddress = get_procedure_address;
    wrap->dispatch.DestroyInstance     = (PFN_vkDestroyInstance)get_procedure_address(inner_instance, "vkDestroyInstance");
    wrap->dispatch.Draw                = (PFN_vkCmdDraw)get_procedure_address(inner_instance, "vkCmdDraw");

    *instance = (VkInstance)wrap;
}

void SampleLayer1_DestroyInstance(VkInstance instance) {
    auto wrap = (VkLayerObjectWrapper*)instance;
    wrap->dispatch.DestroyInstance(wrap->object);
    delete wrap;
}

PFN_vkVoidFunction SampleLayer1_GetProcedureAddress(VkInstance instance, const char* pName) {
    if (!strcmp(pName, "vkCreateInstance")) {
        return (PFN_vkVoidFunction)&SampleLayer1_CreateInstance;
    }

    if (!strcmp(pName, "vkDestroyInstance")) {
        return (PFN_vkVoidFunction)&SampleLayer1_DestroyInstance;
    }

    if (!strcmp(pName, "vkCmdDraw")) {
        return (PFN_vkVoidFunction)&SampleLayer1_CmdDraw;
    }

    auto wrap = (VkLayerObjectWrapper*)instance;
    return wrap->dispatch.GetProcedureAddress(wrap->object, pName);
}

void SampleLayer2_CmdDraw(VkInstance instance) {
    std::cout << "Layer 2 - Draw (Pre)" << std::endl;

    auto wrap = (VkLayerObjectWrapper*)instance;
    wrap->dispatch.Draw(wrap->object);

    std::cout << "Layer 2 - Draw (Post)" << std::endl;
}

void SampleLayer2_CreateInstance(VkInstanceCreateInfo* create, VkInstance* instance) {
    auto layerCreateInfo       = (VkLayerInstanceCreateInfo*)GetStructure(create->next, VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO);
    auto get_procedure_address = layerCreateInfo->layer_information->NextGetProcedureAddress;

    layerCreateInfo->layer_information = layerCreateInfo->layer_information->next;

    auto create_instance_callback = (PFN_vkCreateInstance)get_procedure_address(0, "vkCreateInstance");

    auto inner_instance = VkInstance {};
    create_instance_callback(create, &inner_instance);

    auto wrap                          = new VkLayerObjectWrapper {};
    wrap->object                       = inner_instance;
    wrap->dispatch.GetProcedureAddress = get_procedure_address;
    wrap->dispatch.DestroyInstance     = (PFN_vkDestroyInstance)get_procedure_address(inner_instance, "vkDestroyInstance");
    wrap->dispatch.Draw                = (PFN_vkCmdDraw)get_procedure_address(inner_instance, "vkCmdDraw");

    *instance = (VkInstance)wrap;
}

void SampleLayer2_DestroyInstance(VkInstance instance) {
    auto wrap = (VkLayerObjectWrapper*)instance;
    wrap->dispatch.DestroyInstance(wrap->object);
    delete wrap;
}

PFN_vkVoidFunction SampleLayer2_GetProcedureAddress(VkInstance instance, const char* pName) {
    if (!strcmp(pName, "vkCreateInstance")) {
        return (PFN_vkVoidFunction)&SampleLayer2_CreateInstance;
    }

    if (!strcmp(pName, "vkDestroyInstance")) {
        return (PFN_vkVoidFunction)&SampleLayer2_DestroyInstance;
    }

    if (!strcmp(pName, "vkCmdDraw")) {
        return (PFN_vkVoidFunction)&SampleLayer2_CmdDraw;
    }

    auto wrap = (VkLayerObjectWrapper*)instance;
    return wrap->dispatch.GetProcedureAddress(wrap->object, pName);
}

void vkCmdDraw(VkInstance instance) {
    auto wrap = (VkLayerObjectWrapper*)instance;
    wrap->dispatch.Draw(wrap->object);
}

void DebugCallback(const char* message) {
    std::cout << message << std::endl;
}

void vkCreateInstance(VkInstance* instance) {
    auto layer_icd                    = VkLayerInstanceLink {};
    layer_icd.next                    = nullptr;
    layer_icd.NextGetProcedureAddress = nullptr;

    auto layer_1                    = VkLayerInstanceLink {};
    layer_1.next                    = &layer_icd;
    layer_1.NextGetProcedureAddress = (PFN_vkGetProcedureAddress)&SampleICD_GetProcedureAddress;

    auto layer_2                    = VkLayerInstanceLink {};
    layer_2.next                    = &layer_1;
    layer_2.NextGetProcedureAddress = (PFN_vkGetProcedureAddress)&SampleLayer1_GetProcedureAddress;

    auto layers              = VkLayerInstanceCreateInfo {};
    layers.type              = VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO;
    layers.next              = nullptr;
    layers.layer_information = &layer_2;
    // layers.layer_information = &layer_icd;

    auto debug     = VkDebugInformation {};
    debug.type     = VK_STRUCTURE_TYPE_DEBUG;
    debug.next     = &layers;
    debug.Callback = (PFN_vkDebugCallback)&DebugCallback;

    auto create_instance_information = VkInstanceCreateInfo {};
    create_instance_information.type = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_instance_information.next = &debug;

    auto get_procedure_address = (PFN_vkGetProcedureAddress)&SampleLayer2_GetProcedureAddress;
    // auto get_procedure_address = (PFN_vkGetProcedureAddress)&SampleICD_GetProcedureAddress;
    auto create_instance       = (PFN_vkCreateInstance)get_procedure_address(0, "vkCreateInstance");

    auto inner_handle = VkInstance {};
    create_instance(&create_instance_information, &inner_handle);

    auto wrap                          = new VkLayerObjectWrapper {};
    wrap->object                       = inner_handle;
    wrap->dispatch.GetProcedureAddress = get_procedure_address;
    wrap->dispatch.DestroyInstance     = (PFN_vkDestroyInstance)get_procedure_address(inner_handle, "vkDestroyInstance");
    wrap->dispatch.Draw                = (PFN_vkCmdDraw)get_procedure_address(inner_handle, "vkCmdDraw");

    *instance = (VkInstance)wrap;
}

void vkDestroyInstance(VkInstance instance) {
    auto wrap = (VkLayerObjectWrapper*)instance;
    wrap->dispatch.DestroyInstance(wrap->object);
    delete wrap;
}

int main() {
    auto instance = VkInstance {};

    vkCreateInstance(&instance);
    vkCmdDraw(instance);
    vkDestroyInstance(instance);

    return 0;
}
