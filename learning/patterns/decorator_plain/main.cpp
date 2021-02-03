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
typedef PFN_vkVoidFunction (*PFN_vkGetProcedureAddress)(VkInstance instance, const char* procedure_name);
typedef void (*PFN_vkCreateInstance)(VkInstanceCreateInfo* create, VkInstance* instance);
typedef void (*PFN_vkDestroyInstance)(VkInstance instance);
typedef void (*PFN_vkCmdDraw)(VkInstance instance);

struct VkStructure {
    VkStructureType type;
    void*           next;
};

struct VkDebugInformation {
    VkStructureType type;
    void*           next;

    PFN_vkDebugCallback callback;
};

struct VkLayerInstanceLink {
    struct VkLayerInstanceLink* next;

    PFN_vkGetProcedureAddress next_get_procedure_address;
};

struct VkLayerInstanceCreateInfo {
    VkStructureType      type;
    void*                next;
    VkLayerInstanceLink* layer_information;
};

struct VkInstanceCreateInfo {
    VkStructureType type;
    void*           next;
};

struct VkLayerDispatchTable {
    PFN_vkGetProcedureAddress get_procedure_address;
    PFN_vkCreateInstance      create_instance;
    PFN_vkDestroyInstance     destroy_instance;
    PFN_vkCmdDraw             draw;
};

struct VkLayerObjectWrapper {
    uint64_t             object;
    VkLayerDispatchTable dispatch;
    void*                user;
};

void* GetStructure(void* first, VkStructureType structure_type) {
    auto structure = static_cast<VkStructure*>(first);

    while (structure != nullptr && structure->type != structure_type) {
        structure = static_cast<VkStructure*>(structure->next);
    }

    return structure;
}

void SampleICD_CreateInstance(VkInstanceCreateInfo* create, VkInstance* instance) {
    auto debug = static_cast<VkDebugInformation*>(GetStructure(create->next, VK_STRUCTURE_TYPE_DEBUG));

    auto wrapper  = new VkLayerObjectWrapper {};
    wrapper->user = reinterpret_cast<void*>(debug->callback);

    *instance = reinterpret_cast<VkInstance>(wrapper);
}

void SampleICD_DestroyInstance(VkInstance instance) {
    auto wrapper = reinterpret_cast<VkLayerObjectWrapper*>(instance);
    delete wrapper;
}

void SampleICD_CmdDraw(VkInstance instance) {
    auto wrapper  = reinterpret_cast<VkLayerObjectWrapper*>(instance);
    auto callback = reinterpret_cast<PFN_vkDebugCallback>(wrapper->user);

    callback(" - ICD - Draw");
}

PFN_vkVoidFunction SampleICD_GetProcedureAddress(VkInstance instance, const char* procedure_name) {
    if (!strcmp(procedure_name, "vkCreateInstance")) {
        return reinterpret_cast<PFN_vkVoidFunction>(&SampleICD_CreateInstance);
    }

    if (!strcmp(procedure_name, "vkDestroyInstance")) {
        return reinterpret_cast<PFN_vkVoidFunction>(&SampleICD_DestroyInstance);
    }

    if (!strcmp(procedure_name, "vkCmdDraw")) {
        return reinterpret_cast<PFN_vkVoidFunction>(&SampleICD_CmdDraw);
    }

    return nullptr;
}

void SampleLayer1_CmdDraw(VkInstance instance) {
    std::cout << " - Layer 1 - Pre-Draw" << std::endl;

    auto wrap = reinterpret_cast<VkLayerObjectWrapper*>(instance);
    wrap->dispatch.draw(wrap->object);

    std::cout << " - Layer 1 - Post-Draw" << std::endl;
}

void SampleLayer1_CreateInstance(VkInstanceCreateInfo* create, VkInstance* instance) {
    auto layerCreateInfo       = static_cast<VkLayerInstanceCreateInfo*>(GetStructure(create->next, VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO));
    auto get_procedure_address = layerCreateInfo->layer_information->next_get_procedure_address;

    layerCreateInfo->layer_information = layerCreateInfo->layer_information->next;

    auto create_instance_callback = reinterpret_cast<PFN_vkCreateInstance>(get_procedure_address(0, "vkCreateInstance"));

    auto inner_instance = VkInstance {};
    create_instance_callback(create, &inner_instance);

    auto wrap                            = new VkLayerObjectWrapper {};
    wrap->object                         = inner_instance;
    wrap->dispatch.get_procedure_address = get_procedure_address;
    wrap->dispatch.destroy_instance      = reinterpret_cast<PFN_vkDestroyInstance>(get_procedure_address(inner_instance, "vkDestroyInstance"));
    wrap->dispatch.draw                  = reinterpret_cast<PFN_vkCmdDraw>(get_procedure_address(inner_instance, "vkCmdDraw"));

    *instance = reinterpret_cast<VkInstance>(wrap);
}

void SampleLayer1_DestroyInstance(VkInstance instance) {
    auto wrap = reinterpret_cast<VkLayerObjectWrapper*>(instance);
    wrap->dispatch.destroy_instance(wrap->object);
    delete wrap;
}

PFN_vkVoidFunction SampleLayer1_GetProcedureAddress(VkInstance instance, const char* procedure_name) {
    if (!strcmp(procedure_name, "vkCreateInstance")) {
        return reinterpret_cast<PFN_vkVoidFunction>(&SampleLayer1_CreateInstance);
    }

    if (!strcmp(procedure_name, "vkDestroyInstance")) {
        return reinterpret_cast<PFN_vkVoidFunction>(&SampleLayer1_DestroyInstance);
    }

    if (!strcmp(procedure_name, "vkCmdDraw")) {
        return reinterpret_cast<PFN_vkVoidFunction>(&SampleLayer1_CmdDraw);
    }

    auto wrap = reinterpret_cast<VkLayerObjectWrapper*>(instance);
    return wrap->dispatch.get_procedure_address(wrap->object, procedure_name);
}

void SampleLayer2_CmdDraw(VkInstance instance) {
    std::cout << " - Layer 2 - Pre-Draw" << std::endl;

    auto wrap = reinterpret_cast<VkLayerObjectWrapper*>(instance);
    wrap->dispatch.draw(wrap->object);

    std::cout << " - Layer 2 - Post-Draw" << std::endl;
}

void SampleLayer2_CreateInstance(VkInstanceCreateInfo* create, VkInstance* instance) {
    auto layerCreateInfo       = reinterpret_cast<VkLayerInstanceCreateInfo*>(GetStructure(create->next, VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO));
    auto get_procedure_address = layerCreateInfo->layer_information->next_get_procedure_address;

    layerCreateInfo->layer_information = layerCreateInfo->layer_information->next;

    auto create_instance_callback = reinterpret_cast<PFN_vkCreateInstance>(get_procedure_address(0, "vkCreateInstance"));

    auto inner_instance = VkInstance {};
    create_instance_callback(create, &inner_instance);

    auto wrap                            = new VkLayerObjectWrapper {};
    wrap->object                         = inner_instance;
    wrap->dispatch.get_procedure_address = get_procedure_address;
    wrap->dispatch.destroy_instance      = reinterpret_cast<PFN_vkDestroyInstance>(get_procedure_address(inner_instance, "vkDestroyInstance"));
    wrap->dispatch.draw                  = reinterpret_cast<PFN_vkCmdDraw>(get_procedure_address(inner_instance, "vkCmdDraw"));

    *instance = reinterpret_cast<VkInstance>(wrap);
}

void SampleLayer2_DestroyInstance(VkInstance instance) {
    auto wrap = reinterpret_cast<VkLayerObjectWrapper*>(instance);
    wrap->dispatch.destroy_instance(wrap->object);
    delete wrap;
}

PFN_vkVoidFunction SampleLayer2_GetProcedureAddress(VkInstance instance, const char* procedure_name) {
    if (!strcmp(procedure_name, "vkCreateInstance")) {
        return reinterpret_cast<PFN_vkVoidFunction>(&SampleLayer2_CreateInstance);
    }

    if (!strcmp(procedure_name, "vkDestroyInstance")) {
        return reinterpret_cast<PFN_vkVoidFunction>(&SampleLayer2_DestroyInstance);
    }

    if (!strcmp(procedure_name, "vkCmdDraw")) {
        return reinterpret_cast<PFN_vkVoidFunction>(&SampleLayer2_CmdDraw);
    }

    auto wrap = reinterpret_cast<VkLayerObjectWrapper*>(instance);
    return wrap->dispatch.get_procedure_address(wrap->object, procedure_name);
}

void vkCmdDraw(VkInstance instance) {
    auto wrap = reinterpret_cast<VkLayerObjectWrapper*>(instance);
    wrap->dispatch.draw(wrap->object);
}

void DebugCallback(const char* message) {
    std::cout << message << std::endl;
}

void vkCreateInstance(VkInstance* instance) {
    auto layer_icd                       = VkLayerInstanceLink {};
    layer_icd.next                       = nullptr;
    layer_icd.next_get_procedure_address = nullptr;

    auto layer_1                       = VkLayerInstanceLink {};
    layer_1.next                       = &layer_icd;
    layer_1.next_get_procedure_address = reinterpret_cast<PFN_vkGetProcedureAddress>(&SampleICD_GetProcedureAddress);

    auto layer_2                       = VkLayerInstanceLink {};
    layer_2.next                       = &layer_1;
    layer_2.next_get_procedure_address = reinterpret_cast<PFN_vkGetProcedureAddress>(&SampleLayer1_GetProcedureAddress);

    auto layers              = VkLayerInstanceCreateInfo {};
    layers.type              = VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO;
    layers.next              = nullptr;
    layers.layer_information = &layer_2;
    // layers.layer_information = &layer_icd;

    auto debug     = VkDebugInformation {};
    debug.type     = VK_STRUCTURE_TYPE_DEBUG;
    debug.next     = &layers;
    debug.callback = reinterpret_cast<PFN_vkDebugCallback>(&DebugCallback);

    auto create_instance_information = VkInstanceCreateInfo {};
    create_instance_information.type = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_instance_information.next = &debug;

    auto get_procedure_address = reinterpret_cast<PFN_vkGetProcedureAddress>(&SampleLayer2_GetProcedureAddress);
    // auto get_procedure_address = (PFN_vkGetProcedureAddress)&SampleICD_GetProcedureAddress;
    auto create_instance = reinterpret_cast<PFN_vkCreateInstance>(get_procedure_address(0, "vkCreateInstance"));

    auto inner_handle = VkInstance {};
    create_instance(&create_instance_information, &inner_handle);

    auto wrap                            = new VkLayerObjectWrapper {};
    wrap->object                         = inner_handle;
    wrap->dispatch.get_procedure_address = get_procedure_address;
    wrap->dispatch.destroy_instance      = reinterpret_cast<PFN_vkDestroyInstance>(get_procedure_address(inner_handle, "vkDestroyInstance"));
    wrap->dispatch.draw                  = reinterpret_cast<PFN_vkCmdDraw>(get_procedure_address(inner_handle, "vkCmdDraw"));

    *instance = (VkInstance)wrap;
}

void vkDestroyInstance(VkInstance instance) {
    auto wrap = reinterpret_cast<VkLayerObjectWrapper*>(instance);
    wrap->dispatch.destroy_instance(wrap->object);
    delete wrap;
}

int main() {
    std::cout << "==================================================" << std::endl;
    std::cout << "Decorator (Plain):" << std::endl;

    auto instance = VkInstance {};
    vkCreateInstance(&instance);
    vkCmdDraw(instance);
    vkDestroyInstance(instance);

    std::cout << "==================================================" << std::endl;

    return 0;
}
