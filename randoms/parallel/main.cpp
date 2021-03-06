#include <iostream>

#if defined(__cplusplus)
#define EXTERN_C extern "C"
#else
#define EXTERN_C
#endif

typedef uint64_t FResult;

typedef struct PGUID {
    uint64_t low;
    uint64_t high;
} FGUID;

#define DEFINE_GUID(guid_name) EXTERN_C const FGUID guid_name

#define DECLARE_GUID(guid_name, low, high) EXTERN_C const FGUID guid_name = {low, high}

// #define _USE_C_INTERFACE 1

#define INTERFACE_METHOD_CALL_TYPE

#if defined(__cplusplus) && !defined(_USE_C_INTERFACE)

#define INTERFACE_METHOD_CUSTOM(method_name, result_type, ...) virtual result_type INTERFACE_METHOD_CALL_TYPE method_name(__VA_ARGS__) = 0
#define INTERFACE_METHOD(method_name, ...)                     virtual FResult INTERFACE_METHOD_CALL_TYPE method_name(__VA_ARGS__) = 0

#define DECLARE_BASE_INTERFACE(interface_name)                        struct interface_name
#define DECLARE_INTERFACE(this_interface_name, parent_interface_name) struct this_interface_name : public parent_interface_name

#else

#define INTERFACE_METHOD_CUSTOM(method_name, result_type, ...)                                                                             \
    result_type(INTERFACE_METHOD_CALL_TYPE* method_name)(CURRENT_INTERFACE * this_interface, ##__VA_ARGS__)

#define INTERFACE_METHOD(method_name, ...)                                                                                                 \
    FResult(INTERFACE_METHOD_CALL_TYPE* method_name)(CURRENT_INTERFACE * this_interface, ##__VA_ARGS__)

#define THIS_INTERFACE_BARE CURRENT_INTERFACE* this_interface
#define THIS_INTERFACE      CURRENT_INTERFACE *this_interface,

#define DECLARE_BASE_INTERFACE(interface_name)                                                                                             \
    typedef struct interface_name##Pre {                                                                                                   \
        const struct interface_name##Methods* methods;                                                                                     \
    } interface_name;                                                                                                                      \
    struct interface_name##Methods

#define DECLARE_INTERFACE(this_interface_name, parent_interface_name) DECLARE_BASE_INTERFACE(interface_name)

#endif

DECLARE_GUID(IID_IUnknown, 0, 0);

DECLARE_GUID(ICD_ObjectName, 0, 0);

#undef CURRENT_INTERFACE
#define CURRENT_INTERFACE IUnknown
DECLARE_BASE_INTERFACE(IUnknown) {
    INTERFACE_METHOD_CUSTOM(IncrementReference, int64_t);
    INTERFACE_METHOD_CUSTOM(DecrementReference, int64_t);

    INTERFACE_METHOD(QueryInterface, FGUID interface_id, void** interface_pointer);

    INTERFACE_METHOD(SetCustomData, FGUID data_id, size_t data_size, const void* data_pointer);
    INTERFACE_METHOD(GetCustomData, FGUID data_id, size_t data_size, void* data_pointer);

    INTERFACE_METHOD(SetName, const char* object_name);
};

#if defined(__cplusplus) && !defined(_USE_C_INTERFACE)
#define IUnknown_IncrementReference(this_interface) (this_interface)->IncrementReference()
#define IUnknown_DecrementReference(this_interface) (this_interface)->DecrementReference()
#define IUnknown_QueryInterface(this_interface, interface_id, interface_pointer)                                                           \
    (this_interface)->QueryInterface(interface_id, interface_pointer)
#define IUnknown_SetCustomData(this_interface, data_id, data_size, data_pointer)                                                           \
    (this_interface)->SetCustomData(data_id, data_size, data_pointer)
#define IUnknown_GetCustomData(this_interface, data_id, data_size, data_pointer)                                                           \
    (this_interface)->GetCustomData(data_id, data_size, data_pointer)
#define IUnknown_SetName(this_interface, object_name) (this_interface)->SetName(object_name)
#else
#define IUnknown_IncrementReference(this_interface) (this_interface)->methods->IncrementReference(this_interface)
#define IUnknown_DecrementReference(this_interface) (this_interface)->methods->DecrementReference(this_interface)
#define IUnknown_QueryInterface(this_interface, interface_id, interface_pointer)                                                           \
    (this_interface)->methods->QueryInterface(this_interface, interface_id, interface_pointer)
#define IUnknown_SetCustomData(this_interface, data_id, data_size, data_pointer)                                                           \
    (this_interface)->methods->SetCustomData(this_interface, data_id, data_size, data_pointer)
#define IUnknown_GetCustomData(this_interface, data_id, data_size, data_pointer)                                                           \
    (this_interface)->methods->GetCustomData(this_interface, data_id, data_size, data_pointer)
#define IUnknown_SetName(this_interface, object_name) (this_interface)->methods->SetName(this_interface, object_name)
#endif

DECLARE_GUID(IID_IPhysicalGraphicsDevice, 0, 0);
DECLARE_GUID(IID_IPhysicalGraphicsDeviceChild, 0, 0);
DECLARE_GUID(IID_IPhysicalGraphicsDeviceOutput, 0, 0);
DECLARE_GUID(IID_ILogicalGraphicsDevice, 0, 0);
DECLARE_GUID(IID_ILogicalGraphicsDeviceChild, 0, 0);
DECLARE_GUID(IID_ILogicalGraphicsDeviceCommandQueue, 0, 0);
DECLARE_GUID(IID_ILogicalGraphicsDeviceDataCommandQueue, 0, 0);
DECLARE_GUID(IID_ILogicalGraphicsDeviceGraphicsCommandQueue, 0, 0);
DECLARE_GUID(IID_ILogicalGraphicsDeviceComputeCommandQueue, 0, 0);
DECLARE_GUID(IID_ILogicalGraphicsDeviceCommandAllocator, 0, 0);
DECLARE_GUID(IID_ILogicalGraphicsDeviceDataCommandAllocator, 0, 0);
DECLARE_GUID(IID_ILogicalGraphicsDeviceGraphicsCommandAllocator, 0, 0);
DECLARE_GUID(IID_ILogicalGraphicsDeviceComputeCommandAllocator, 0, 0);
DECLARE_GUID(IID_ILogicalGraphicsDeviceCommandList, 0, 0);
DECLARE_GUID(IID_ILogicalGraphicsDeviceDataCommandList, 0, 0);
DECLARE_GUID(IID_ILogicalGraphicsDeviceGraphicsCommandList, 0, 0);
DECLARE_GUID(IID_ILogicalGraphicsDeviceComputeCommandList, 0, 0);

struct IPhysicalGraphicsDevice;
struct IPhysicalGraphicsDeviceChild;
struct IPhysicalGraphicsDeviceOutput;
struct ILogicalGraphicsDevice;
struct ILogicalGraphicsDeviceChild;
struct ILogicalGraphicsDeviceCommandQueue;
struct ILogicalGraphicsDeviceDataCommandQueue;
struct ILogicalGraphicsDeviceGraphicsCommandQueue;
struct ILogicalGraphicsDeviceComputeCommandQueue;
struct ILogicalGraphicsDeviceCommandAllocator;
struct ILogicalGraphicsDeviceDataCommandAllocator;
struct ILogicalGraphicsDeviceGraphicsCommandAllocator;
struct ILogicalGraphicsDeviceComputeCommandAllocator;
struct ILogicalGraphicsDeviceCommandList;
struct ILogicalGraphicsDeviceDataCommandList;
struct ILogicalGraphicsDeviceGraphicsCommandList;
struct ILogicalGraphicsDeviceComputeCommandList;

#undef CURRENT_INTERFACE
#define CURRENT_INTERFACE IPhysicalGraphicsDevice
DECLARE_INTERFACE(IPhysicalGraphicsDevice, IUnknown) {
    INTERFACE_METHOD_CUSTOM(IncrementReference, int64_t);
    INTERFACE_METHOD_CUSTOM(DecrementReference, int64_t);

    INTERFACE_METHOD(QueryInterface, FGUID interface_id, void** interface_pointer);

    INTERFACE_METHOD(SetCustomData, FGUID data_id, size_t data_size, const void* data_pointer);
    INTERFACE_METHOD(GetCustomData, FGUID data_id, size_t data_size, void* data_pointer);

    INTERFACE_METHOD(SetName, const char* object_name);
};

#undef CURRENT_INTERFACE
#define CURRENT_INTERFACE IPhysicalGraphicsDeviceChild
DECLARE_INTERFACE(IPhysicalGraphicsDeviceChild, IUnknown) {
    INTERFACE_METHOD_CUSTOM(IncrementReference, int64_t);
    INTERFACE_METHOD_CUSTOM(DecrementReference, int64_t);

    INTERFACE_METHOD(QueryInterface, FGUID interface_id, void** interface_pointer);

    INTERFACE_METHOD(SetCustomData, FGUID data_id, size_t data_size, const void* data_pointer);
    INTERFACE_METHOD(GetCustomData, FGUID data_id, size_t data_size, void* data_pointer);

    INTERFACE_METHOD(SetName, const char* object_name);

    INTERFACE_METHOD(GetDevice, IPhysicalGraphicsDevice * *device_pointer);
};

#undef CURRENT_INTERFACE
#define CURRENT_INTERFACE IPhysicalGraphicsDeviceOutput
DECLARE_INTERFACE(IPhysicalGraphicsDeviceOutput, IPhysicalGraphicsDeviceChild) {
    INTERFACE_METHOD_CUSTOM(IncrementReference, int64_t);
    INTERFACE_METHOD_CUSTOM(DecrementReference, int64_t);

    INTERFACE_METHOD(QueryInterface, FGUID interface_id, void** interface_pointer);

    INTERFACE_METHOD(SetCustomData, FGUID data_id, size_t data_size, const void* data_pointer);
    INTERFACE_METHOD(GetCustomData, FGUID data_id, size_t data_size, void* data_pointer);

    INTERFACE_METHOD(SetName, const char* object_name);

    INTERFACE_METHOD(GetDevice, IPhysicalGraphicsDevice * *device_pointer);
};

#undef CURRENT_INTERFACE
#define CURRENT_INTERFACE ILogicalGraphicsDevice
DECLARE_INTERFACE(ILogicalGraphicsDevice, IUnknown) {
    INTERFACE_METHOD_CUSTOM(IncrementReference, int64_t);
    INTERFACE_METHOD_CUSTOM(DecrementReference, int64_t);

    INTERFACE_METHOD(QueryInterface, FGUID interface_id, void** interface_pointer);

    INTERFACE_METHOD(SetCustomData, FGUID data_id, size_t data_size, const void* data_pointer);
    INTERFACE_METHOD(GetCustomData, FGUID data_id, size_t data_size, void* data_pointer);

    INTERFACE_METHOD(SetName, const char* object_name);

    INTERFACE_METHOD(CreateDataCommandList, ILogicalGraphicsDeviceDataCommandList * *command_list_pointer);
    INTERFACE_METHOD(CreateGraphicsCommandList, ILogicalGraphicsDeviceGraphicsCommandList * *command_list_pointer);
    INTERFACE_METHOD(CreateComputeCommandList, ILogicalGraphicsDeviceComputeCommandList * *command_list_pointer);
};

#undef CURRENT_INTERFACE
#define CURRENT_INTERFACE ILogicalGraphicsDeviceChild
DECLARE_INTERFACE(ILogicalGraphicsDeviceChild, IUnknown) {
    INTERFACE_METHOD_CUSTOM(IncrementReference, int64_t);
    INTERFACE_METHOD_CUSTOM(DecrementReference, int64_t);

    INTERFACE_METHOD(QueryInterface, FGUID interface_id, void** interface_pointer);

    INTERFACE_METHOD(SetCustomData, FGUID data_id, size_t data_size, const void* data_pointer);
    INTERFACE_METHOD(GetCustomData, FGUID data_id, size_t data_size, void* data_pointer);

    INTERFACE_METHOD(SetName, const char* object_name);

    INTERFACE_METHOD(GetDevice, ILogicalGraphicsDevice * *device_pointer);
};

#undef CURRENT_INTERFACE
#define CURRENT_INTERFACE ILogicalGraphicsDeviceCommandQueue
DECLARE_INTERFACE(ILogicalGraphicsDeviceCommandQueue, ILogicalGraphicsDeviceChild) {
    INTERFACE_METHOD_CUSTOM(IncrementReference, int64_t);
    INTERFACE_METHOD_CUSTOM(DecrementReference, int64_t);

    INTERFACE_METHOD(QueryInterface, FGUID interface_id, void** interface_pointer);

    INTERFACE_METHOD(SetCustomData, FGUID data_id, size_t data_size, const void* data_pointer);
    INTERFACE_METHOD(GetCustomData, FGUID data_id, size_t data_size, void* data_pointer);

    INTERFACE_METHOD(SetName, const char* object_name);

    INTERFACE_METHOD(GetDevice, ILogicalGraphicsDevice * *device_pointer);
};

#undef CURRENT_INTERFACE
#define CURRENT_INTERFACE ILogicalGraphicsDeviceDataCommandQueue
DECLARE_INTERFACE(ILogicalGraphicsDeviceDataCommandQueue, ILogicalGraphicsDeviceCommandQueue) {
    INTERFACE_METHOD_CUSTOM(IncrementReference, int64_t);
    INTERFACE_METHOD_CUSTOM(DecrementReference, int64_t);

    INTERFACE_METHOD(QueryInterface, FGUID interface_id, void** interface_pointer);

    INTERFACE_METHOD(SetCustomData, FGUID data_id, size_t data_size, const void* data_pointer);
    INTERFACE_METHOD(GetCustomData, FGUID data_id, size_t data_size, void* data_pointer);

    INTERFACE_METHOD(SetName, const char* object_name);

    INTERFACE_METHOD(GetDevice, ILogicalGraphicsDevice * *device_pointer);
};

#undef CURRENT_INTERFACE
#define CURRENT_INTERFACE ILogicalGraphicsDeviceGraphicsCommandQueue
DECLARE_INTERFACE(ILogicalGraphicsDeviceGraphicsCommandQueue, ILogicalGraphicsDeviceCommandQueue) {
    INTERFACE_METHOD_CUSTOM(IncrementReference, int64_t);
    INTERFACE_METHOD_CUSTOM(DecrementReference, int64_t);

    INTERFACE_METHOD(QueryInterface, FGUID interface_id, void** interface_pointer);

    INTERFACE_METHOD(SetCustomData, FGUID data_id, size_t data_size, const void* data_pointer);
    INTERFACE_METHOD(GetCustomData, FGUID data_id, size_t data_size, void* data_pointer);

    INTERFACE_METHOD(SetName, const char* object_name);

    INTERFACE_METHOD(GetDevice, ILogicalGraphicsDevice * *device_pointer);
};

#undef CURRENT_INTERFACE
#define CURRENT_INTERFACE ILogicalGraphicsDeviceComputeCommandQueue
DECLARE_INTERFACE(ILogicalGraphicsDeviceComputeCommandQueue, ILogicalGraphicsDeviceCommandQueue) {
    INTERFACE_METHOD_CUSTOM(IncrementReference, int64_t);
    INTERFACE_METHOD_CUSTOM(DecrementReference, int64_t);

    INTERFACE_METHOD(QueryInterface, FGUID interface_id, void** interface_pointer);

    INTERFACE_METHOD(SetCustomData, FGUID data_id, size_t data_size, const void* data_pointer);
    INTERFACE_METHOD(GetCustomData, FGUID data_id, size_t data_size, void* data_pointer);

    INTERFACE_METHOD(SetName, const char* object_name);

    INTERFACE_METHOD(GetDevice, ILogicalGraphicsDevice * *device_pointer);
};

#undef CURRENT_INTERFACE
#define CURRENT_INTERFACE ILogicalGraphicsDeviceCommandAllocator
DECLARE_INTERFACE(ILogicalGraphicsDeviceCommandAllocator, ILogicalGraphicsDeviceChild) {
    INTERFACE_METHOD_CUSTOM(IncrementReference, int64_t);
    INTERFACE_METHOD_CUSTOM(DecrementReference, int64_t);

    INTERFACE_METHOD(QueryInterface, FGUID interface_id, void** interface_pointer);

    INTERFACE_METHOD(SetCustomData, FGUID data_id, size_t data_size, const void* data_pointer);
    INTERFACE_METHOD(GetCustomData, FGUID data_id, size_t data_size, void* data_pointer);

    INTERFACE_METHOD(SetName, const char* object_name);

    INTERFACE_METHOD(GetDevice, ILogicalGraphicsDevice * *device_pointer);
};

#undef CURRENT_INTERFACE
#define CURRENT_INTERFACE ILogicalGraphicsDeviceDataCommandAllocator
DECLARE_INTERFACE(ILogicalGraphicsDeviceDataCommandAllocator, ILogicalGraphicsDeviceCommandAllocator) {
    INTERFACE_METHOD_CUSTOM(IncrementReference, int64_t);
    INTERFACE_METHOD_CUSTOM(DecrementReference, int64_t);

    INTERFACE_METHOD(QueryInterface, FGUID interface_id, void** interface_pointer);

    INTERFACE_METHOD(SetCustomData, FGUID data_id, size_t data_size, const void* data_pointer);
    INTERFACE_METHOD(GetCustomData, FGUID data_id, size_t data_size, void* data_pointer);

    INTERFACE_METHOD(SetName, const char* object_name);

    INTERFACE_METHOD(GetDevice, ILogicalGraphicsDevice * *device_pointer);
};

#undef CURRENT_INTERFACE
#define CURRENT_INTERFACE ILogicalGraphicsDeviceGraphicsCommandAllocator
DECLARE_INTERFACE(ILogicalGraphicsDeviceGraphicsCommandAllocator, ILogicalGraphicsDeviceCommandAllocator) {
    INTERFACE_METHOD_CUSTOM(IncrementReference, int64_t);
    INTERFACE_METHOD_CUSTOM(DecrementReference, int64_t);

    INTERFACE_METHOD(QueryInterface, FGUID interface_id, void** interface_pointer);

    INTERFACE_METHOD(SetCustomData, FGUID data_id, size_t data_size, const void* data_pointer);
    INTERFACE_METHOD(GetCustomData, FGUID data_id, size_t data_size, void* data_pointer);

    INTERFACE_METHOD(SetName, const char* object_name);

    INTERFACE_METHOD(GetDevice, ILogicalGraphicsDevice * *device_pointer);
};

#undef CURRENT_INTERFACE
#define CURRENT_INTERFACE ILogicalGraphicsDeviceComputeCommandAllocator
DECLARE_INTERFACE(ILogicalGraphicsDeviceComputeCommandAllocator, ILogicalGraphicsDeviceCommandAllocator) {
    INTERFACE_METHOD_CUSTOM(IncrementReference, int64_t);
    INTERFACE_METHOD_CUSTOM(DecrementReference, int64_t);

    INTERFACE_METHOD(QueryInterface, FGUID interface_id, void** interface_pointer);

    INTERFACE_METHOD(SetCustomData, FGUID data_id, size_t data_size, const void* data_pointer);
    INTERFACE_METHOD(GetCustomData, FGUID data_id, size_t data_size, void* data_pointer);

    INTERFACE_METHOD(SetName, const char* object_name);

    INTERFACE_METHOD(GetDevice, ILogicalGraphicsDevice * *device_pointer);
};

#undef CURRENT_INTERFACE
#define CURRENT_INTERFACE ILogicalGraphicsDeviceCommandList
DECLARE_INTERFACE(ILogicalGraphicsDeviceCommandList, ILogicalGraphicsDeviceChild) {
    INTERFACE_METHOD_CUSTOM(IncrementReference, int64_t);
    INTERFACE_METHOD_CUSTOM(DecrementReference, int64_t);

    INTERFACE_METHOD(QueryInterface, FGUID interface_id, void** interface_pointer);

    INTERFACE_METHOD(SetCustomData, FGUID data_id, size_t data_size, const void* data_pointer);
    INTERFACE_METHOD(GetCustomData, FGUID data_id, size_t data_size, void* data_pointer);

    INTERFACE_METHOD(SetName, const char* object_name);

    INTERFACE_METHOD(GetDevice, ILogicalGraphicsDevice * *device_pointer);
};

#undef CURRENT_INTERFACE
#define CURRENT_INTERFACE ILogicalGraphicsDeviceDataCommandList
DECLARE_INTERFACE(ILogicalGraphicsDeviceDataCommandList, ILogicalGraphicsDeviceCommandList) {
    INTERFACE_METHOD_CUSTOM(IncrementReference, int64_t);
    INTERFACE_METHOD_CUSTOM(DecrementReference, int64_t);

    INTERFACE_METHOD(QueryInterface, FGUID interface_id, void** interface_pointer);

    INTERFACE_METHOD(SetCustomData, FGUID data_id, size_t data_size, const void* data_pointer);
    INTERFACE_METHOD(GetCustomData, FGUID data_id, size_t data_size, void* data_pointer);

    INTERFACE_METHOD(SetName, const char* object_name);

    INTERFACE_METHOD(GetDevice, ILogicalGraphicsDevice * *device_pointer);
};

#undef CURRENT_INTERFACE
#define CURRENT_INTERFACE ILogicalGraphicsDeviceGraphicsCommandList
DECLARE_INTERFACE(ILogicalGraphicsDeviceGraphicsCommandList, ILogicalGraphicsDeviceCommandList) {
    INTERFACE_METHOD_CUSTOM(IncrementReference, int64_t);
    INTERFACE_METHOD_CUSTOM(DecrementReference, int64_t);

    INTERFACE_METHOD(QueryInterface, FGUID interface_id, void** interface_pointer);

    INTERFACE_METHOD(SetCustomData, FGUID data_id, size_t data_size, const void* data_pointer);
    INTERFACE_METHOD(GetCustomData, FGUID data_id, size_t data_size, void* data_pointer);

    INTERFACE_METHOD(SetName, const char* object_name);

    INTERFACE_METHOD(GetDevice, ILogicalGraphicsDevice * *device_pointer);
};

#undef CURRENT_INTERFACE
#define CURRENT_INTERFACE ILogicalGraphicsDeviceComputeCommandList
DECLARE_INTERFACE(ILogicalGraphicsDeviceComputeCommandList, ILogicalGraphicsDeviceCommandList) {
    INTERFACE_METHOD_CUSTOM(IncrementReference, int64_t);
    INTERFACE_METHOD_CUSTOM(DecrementReference, int64_t);

    INTERFACE_METHOD(QueryInterface, FGUID interface_id, void** interface_pointer);

    INTERFACE_METHOD(SetCustomData, FGUID data_id, size_t data_size, const void* data_pointer);
    INTERFACE_METHOD(GetCustomData, FGUID data_id, size_t data_size, void* data_pointer);

    INTERFACE_METHOD(SetName, const char* object_name);

    INTERFACE_METHOD(GetDevice, ILogicalGraphicsDevice * *device_pointer);
};

int main() {
    return 0;
}
