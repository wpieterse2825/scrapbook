#include <atomic>
#include <iostream>

#if defined(__cplusplus)
#define EXPORT_C_INTERFACE extern "C"
#else
#define EXPORT_C_INTERFACE
#endif

typedef uint64_t FResult;

#define RESULT_SUCCESS               0
#define RESULT_NO_SUCH_INTERFACE     1
#define RESULT_INVALID_PARAMETER     2
#define RESULT_UNSUPPORTED_STRUCTURE 3
#define RESULT_UNIMPLEMENTED         4
#define RESULT_NO_PARENT             5
#define RESULT_UNKNOWN_CHILD         6

#define DECLARE_GUID_TYPE(identifier)                                                                                                      \
    typedef struct identifier##Pre {                                                                                                       \
        uint64_t low;                                                                                                                      \
        uint64_t high;                                                                                                                     \
    } identifier

#define GUID_DEFINITION(guid_type, guid_name) EXPORT_C_INTERFACE const guid_type guid_name

#define GUID_DECLARATION(guid_type, guid_name, low_value, high_value) EXPORT_C_INTERFACE const guid_type guid_name = {low_value, high_value}

DECLARE_GUID_TYPE(FInterfaceID);

#define INTERFACE_ID_DEFINITION(interface_id_name) GUID_DEFINITION(FInterfaceID, interface_id_name)

#define INTERFACE_ID_DECLARATION(interface_id_name, low_value, high_value)                                                                 \
    GUID_DECLARATION(FInterfaceID, interface_id_name, low_value, high_value)

DECLARE_GUID_TYPE(FCustomDataID);

#define CUSTOM_DATA_ID_DEFINITION(blob_id_name) GUID_DEFINITION(FCustomDataID, blob_id_name)

#define CUSTOM_DATA_ID_DECLARATION(blob_id_name, low_value, high_value) GUID_DECLARATION(FCustomDataID, blob_id_name, low_value, high_value)

// #define _USE_C_INTERFACE 1

#define INTERFACE_METHOD_CALL_TYPE

#if defined(__cplusplus) && !defined(_USE_C_INTERFACE)

#define DECLARE_INTERFACE_METHOD(method_name, ...) virtual FResult INTERFACE_METHOD_CALL_TYPE method_name(__VA_ARGS__) = 0

#define DECLARE_BASE_INTERFACE(this_interface_name) struct this_interface_name

#define DECLARE_INTERFACE(this_interface_name, parent_interface_name) struct this_interface_name : public parent_interface_name

#else

#define DECLARE_INTERFACE_METHOD(method_name, ...)                                                                                         \
    FResult(INTERFACE_METHOD_CALL_TYPE* method_name)(CURRENT_INTERFACE * this_interface, ##__VA_ARGS__)

#define DECLARE_BASE_INTERFACE(this_interface_name)                                                                                        \
    typedef struct this_interface_name##Pre {                                                                                              \
        const struct this_interface_name##Methods* methods;                                                                                \
    } this_interface_name;                                                                                                                 \
    struct this_interface_name##Methods

#define DECLARE_INTERFACE(this_interface_name, parent_interface_name) DECLARE_BASE_INTERFACE(interface_name)

#endif

INTERFACE_ID_DECLARATION(IID_IBase, 0, 0);

CUSTOM_DATA_ID_DECLARATION(CDID_Name, 0, 0);

struct IBase;

typedef enum COM_STRUCTURE_TYPE_PRE
{
    COM_STRUCTURE_TYPE_ENUMERATION_FIRST = 0,
    COM_STRUCTURE_TYPE_INCREMENT_REFERENCE_PARAMETERS,
    COM_STRUCTURE_TYPE_DECREMENT_REFERENCE_PARAMETERS,
    COM_STRUCTURE_TYPE_QUERY_INTERFACE_PARAMETERS,
    COM_STRUCTURE_TYPE_GET_PARENT_PARAMETERS,
    COM_STRUCTURE_TYPE_GET_CHILD_COUNT_PARAMETERS,
    COM_STRUCTURE_TYPE_GET_CHILD_PARAMETERS,
    COM_STRUCTURE_TYPE_SET_CUSTOM_DATA_PARAMETERS,
    COM_STRUCTURE_TYPE_GET_CUSTOM_DATA_PARAMETERS,
    COM_STRUCTURE_TYPE_SET_NAME_PARAMETERS,
    COM_STRUCTURE_TYPE_ENUMERATION_LAST,
    COM_STRUCTURE_TYPE_ENUMERATION_MAX = UINT32_MAX,
} COM_STRUCTURE_TYPE;

typedef struct COM_INCREMENT_REFERENCE_PARAMETERS_PRE {
    uint32_t structure_type;
    void*    next_structure;

    int64_t current_reference_count;

#if defined(__cplusplus) && !defined(_USE_C_INTERFACE)
    COM_INCREMENT_REFERENCE_PARAMETERS_PRE()
      : structure_type(COM_STRUCTURE_TYPE_INCREMENT_REFERENCE_PARAMETERS)
      , next_structure {nullptr}
      , current_reference_count {0} {
    }
#endif
} COM_INCREMENT_REFERENCE_PARAMETERS;

typedef struct COM_DECREMENT_REFERENCE_PARAMETERS_PRE {
    uint32_t structure_type;
    void*    next_structure;

    int64_t current_reference_count;

#if defined(__cplusplus) && !defined(_USE_C_INTERFACE)
    COM_DECREMENT_REFERENCE_PARAMETERS_PRE()
      : structure_type(COM_STRUCTURE_TYPE_DECREMENT_REFERENCE_PARAMETERS)
      , next_structure {nullptr}
      , current_reference_count {0} {
    }
#endif
} COM_DECREMENT_REFERENCE_PARAMETERS;

typedef struct COM_QUERY_INTERFACE_PARAMETERS_PRE {
    uint32_t structure_type;
    void*    next_structure;

    FInterfaceID interface_id;
    IBase*       interface_pointer;

#if defined(__cplusplus) && !defined(_USE_C_INTERFACE)
    COM_QUERY_INTERFACE_PARAMETERS_PRE()
      : structure_type(COM_STRUCTURE_TYPE_QUERY_INTERFACE_PARAMETERS)
      , next_structure {nullptr}
      , interface_id {}
      , interface_pointer {nullptr} {
    }
#endif
} COM_QUERY_INTERFACE_PARAMETERS;

typedef struct COM_GET_PARENT_PARAMETERS_PRE {
    uint32_t structure_type;
    void*    next_structure;

    FInterfaceID interface_id;
    IBase*       interface_pointer;

#if defined(__cplusplus) && !defined(_USE_C_INTERFACE)
    COM_GET_PARENT_PARAMETERS_PRE()
      : structure_type(COM_STRUCTURE_TYPE_GET_PARENT_PARAMETERS)
      , next_structure {nullptr}
      , interface_id {}
      , interface_pointer {nullptr} {
    }
#endif
} COM_GET_PARENT_PARAMETERS;

typedef struct COM_GET_CHILD_COUNT_PARAMETERS_PRE {
    uint32_t structure_type;
    void*    next_structure;

    int64_t child_count;

#if defined(__cplusplus) && !defined(_USE_C_INTERFACE)
    COM_GET_CHILD_COUNT_PARAMETERS_PRE()
      : structure_type(COM_STRUCTURE_TYPE_GET_CHILD_COUNT_PARAMETERS)
      , next_structure {nullptr}
      , child_count {0} {
    }
#endif
} COM_GET_CHILD_COUNT_PARAMETERS;

typedef struct COM_GET_CHILD_PARAMETERS_PRE {
    uint32_t structure_type;
    void*    next_structure;

    int64_t      index;
    FInterfaceID interface_id;
    IBase*       interface_pointer;

#if defined(__cplusplus) && !defined(_USE_C_INTERFACE)
    COM_GET_CHILD_PARAMETERS_PRE()
      : structure_type(COM_STRUCTURE_TYPE_GET_CHILD_PARAMETERS)
      , next_structure {nullptr}
      , index {-1}
      , interface_id {}
      , interface_pointer {nullptr} {
    }
#endif
} COM_GET_CHILD_PARAMETERS;

typedef struct COM_SET_CUSTOM_DATA_PARAMETERS_PRE {
    uint32_t structure_type;
    void*    next_structure;

    FCustomDataID data_id;
    size_t        data_size;
    void*         data_buffer;

#if defined(__cplusplus) && !defined(_USE_C_INTERFACE)
    COM_SET_CUSTOM_DATA_PARAMETERS_PRE()
      : structure_type(COM_STRUCTURE_TYPE_SET_CUSTOM_DATA_PARAMETERS)
      , next_structure {nullptr}
      , data_id {}
      , data_size {0}
      , data_buffer {nullptr} {
    }
#endif
} COM_SET_CUSTOM_DATA_PARAMETERS;

typedef struct COM_GET_CUSTOM_DATA_PARAMETERS_PRE {
    uint32_t structure_type;
    void*    next_structure;

    FCustomDataID data_id;
    size_t        data_size;
    void*         data_buffer;

#if defined(__cplusplus) && !defined(_USE_C_INTERFACE)
    COM_GET_CUSTOM_DATA_PARAMETERS_PRE()
      : structure_type(COM_STRUCTURE_TYPE_GET_CUSTOM_DATA_PARAMETERS)
      , next_structure {nullptr}
      , data_id {}
      , data_size {0}
      , data_buffer {nullptr} {
    }
#endif
} COM_GET_CUSTOM_DATA_PARAMETERS;

typedef struct COM_SET_NAME_PARAMETERS_PRE {
    uint32_t structure_type;
    void*    next_structure;

    const char* name;

#if defined(__cplusplus) && !defined(_USE_C_INTERFACE)
    COM_SET_NAME_PARAMETERS_PRE()
      : structure_type(COM_STRUCTURE_TYPE_SET_NAME_PARAMETERS)
      , next_structure {nullptr}
      , name {nullptr} {
    }
#endif
} COM_SET_NAME_PARAMETERS;

#undef CURRENT_INTERFACE
#define CURRENT_INTERFACE IBase
DECLARE_BASE_INTERFACE(IBase) {
    DECLARE_INTERFACE_METHOD(IncrementReference, COM_INCREMENT_REFERENCE_PARAMETERS * parameters);
    DECLARE_INTERFACE_METHOD(DecrementReference, COM_DECREMENT_REFERENCE_PARAMETERS * parameters);

    DECLARE_INTERFACE_METHOD(QueryInterface, COM_QUERY_INTERFACE_PARAMETERS * parameters);

    DECLARE_INTERFACE_METHOD(GetParent, COM_GET_PARENT_PARAMETERS * parameters);
    DECLARE_INTERFACE_METHOD(GetChildCount, COM_GET_CHILD_COUNT_PARAMETERS * parameters);
    DECLARE_INTERFACE_METHOD(GetChild, COM_GET_CHILD_PARAMETERS * parameters);

    DECLARE_INTERFACE_METHOD(SetCustomData, COM_SET_CUSTOM_DATA_PARAMETERS * parameters);
    DECLARE_INTERFACE_METHOD(GetCustomData, COM_GET_CUSTOM_DATA_PARAMETERS * parameters);

    DECLARE_INTERFACE_METHOD(SetName, COM_SET_NAME_PARAMETERS * parameters);
};

#if defined(__cplusplus) && !defined(_USE_C_INTERFACE)
#define IBase_IncrementReference(this_interface, parameters) (this_interface)->IncrementReference((parameters))
#define IBase_DecrementReference(this_interface, parameters) (this_interface)->DecrementReference((parameters))
#define IBase_QueryInterface(this_interface, parameters)     (this_interface)->QueryInterface((parameters))
#define IBase_GetParent(this_interface, parameters)          (this_interface)->GetParent((parameters))
#define IBase_GetChildCount(this_interface, parameters)      (this_interface)->GetChildCount((parameters))
#define IBase_GetChild(this_interface, parameters)           (this_interface)->GetChild((parameters))
#define IBase_SetCustomData(this_interface, parameters)      (this_interface)->SetCustomData((parameters))
#define IBase_GetCustomData(this_interface, parameters)      (this_interface)->GetCustomData((parameters))
#define IBase_SetName(this_interface, parameters)            (this_interface)->SetName((parameters))
#else
#define IBase_IncrementReference(this_interface, parameters) (this_interface)->methods->IncrementReference((this_interface), (parameters))
#define IBase_DecrementReference(this_interface, parameters) (this_interface)->methods->DecrementReference((this_interface), (parameters))
#define IBase_QueryInterface(this_interface, parameters)     (this_interface)->methods->QueryInterface((this_interface), (parameters))
#define IBase_GetParent(this_interface, parameters)          (this_interface)->methods->GetParent((this_interface), (parameters))
#define IBase_GetChildCount(this_interface, parameters)      (this_interface)->methods->GetChildCount((this_interface), (parameters))
#define IBase_GetChild(this_interface, parameters)           (this_interface)->methods->GetChild((this_interface), (parameters))
#define IBase_SetCustomData(this_interface, parameters)      (this_interface)->methods->SetCustomData((this_interface), (parameters))
#define IBase_GetCustomData(this_interface, parameters)      (this_interface)->methods->GetCustomData((this_interface), (parameters))
#define IBase_SetName(this_interface, parameters)            (this_interface)->methods->SetName((this_interface), (parameters))
#endif

class FVirtualBase {
  public:
    virtual ~FVirtualBase();
};

FVirtualBase::~FVirtualBase() {
}

inline bool IsEqual(const FInterfaceID& lhs, const FInterfaceID& rhs) {
    if (lhs.low != rhs.low) {
        return false;
    }

    if (lhs.high != rhs.high) {
        return false;
    }

    return true;
}

class FBase
  : public FVirtualBase
  , public IBase {
  public:
    FBase(FBase* parent);
    virtual ~FBase();

    virtual FResult IncrementReference(COM_INCREMENT_REFERENCE_PARAMETERS* parameters) override;
    virtual FResult DecrementReference(COM_DECREMENT_REFERENCE_PARAMETERS* parameters) override;

    virtual FResult QueryInterface(COM_QUERY_INTERFACE_PARAMETERS* parameters) override;

    virtual FResult GetParent(COM_GET_PARENT_PARAMETERS* parameters) override;
    virtual FResult GetChildCount(COM_GET_CHILD_COUNT_PARAMETERS* parameters) override;
    virtual FResult GetChild(COM_GET_CHILD_PARAMETERS* parameters) override;

    virtual FResult SetCustomData(COM_SET_CUSTOM_DATA_PARAMETERS* parameters) override;
    virtual FResult GetCustomData(COM_GET_CUSTOM_DATA_PARAMETERS* parameters) override;

    virtual FResult SetName(COM_SET_NAME_PARAMETERS* parameters) override;

  protected:
    virtual FResult DestructObject();

    virtual void NotifyChildDestruction(FBase* child);

  private:
    std::atomic<int64_t> _reference_count;

    FBase* _parent;

    // TODO(wpieterse): Move this over to use a container.
    int64_t _child_count;
    FBase*  _children[256];
};

FBase::FBase(FBase* parent)
  : _reference_count {0}
  , _parent {parent}
  , _child_count {0}
  , _children {nullptr} {
}

FBase::~FBase() {
}

FResult FBase::IncrementReference(COM_INCREMENT_REFERENCE_PARAMETERS* parameters) {
    if (parameters == nullptr) {
        return RESULT_INVALID_PARAMETER;
    }

    if (parameters->structure_type != COM_STRUCTURE_TYPE_INCREMENT_REFERENCE_PARAMETERS) {
        return RESULT_UNSUPPORTED_STRUCTURE;
    }

    parameters->current_reference_count = ++_reference_count;

    return RESULT_SUCCESS;
}

FResult FBase::DecrementReference(COM_DECREMENT_REFERENCE_PARAMETERS* parameters) {
    if (parameters == nullptr) {
        return RESULT_INVALID_PARAMETER;
    }

    if (parameters->structure_type != COM_STRUCTURE_TYPE_DECREMENT_REFERENCE_PARAMETERS) {
        return RESULT_UNSUPPORTED_STRUCTURE;
    }

    parameters->current_reference_count = --_reference_count;
    if (parameters->current_reference_count == 0) {
        return DestructObject();
    }

    return RESULT_SUCCESS;
}

FResult FBase::QueryInterface(COM_QUERY_INTERFACE_PARAMETERS* parameters) {
    IBase*                             interface_pointer = nullptr;
    COM_INCREMENT_REFERENCE_PARAMETERS increment_parameters {};

    if (parameters == nullptr) {
        return RESULT_INVALID_PARAMETER;
    }

    if (parameters->structure_type != COM_STRUCTURE_TYPE_QUERY_INTERFACE_PARAMETERS) {
        return RESULT_UNSUPPORTED_STRUCTURE;
    }

    parameters->interface_pointer = nullptr;
    if (IsEqual(parameters->interface_id, IID_IBase)) {
        interface_pointer = this;

        auto increment_result = interface_pointer->IncrementReference(&increment_parameters);
        if (increment_result == RESULT_SUCCESS) {
            parameters->interface_pointer = interface_pointer;
        }

        return increment_result;
    }

    return RESULT_NO_SUCH_INTERFACE;
}

FResult FBase::GetParent(COM_GET_PARENT_PARAMETERS* parameters) {
    FResult                        query_result = RESULT_SUCCESS;
    COM_QUERY_INTERFACE_PARAMETERS query_interface_parameters {};

    if (parameters == nullptr) {
        return RESULT_INVALID_PARAMETER;
    }

    if (parameters->structure_type != COM_STRUCTURE_TYPE_GET_PARENT_PARAMETERS) {
        return RESULT_UNSUPPORTED_STRUCTURE;
    }

    parameters->interface_pointer = nullptr;
    if (_parent == nullptr) {
        return RESULT_NO_PARENT;
    }

    query_interface_parameters.interface_id = parameters->interface_id;

    query_result = _parent->QueryInterface(&query_interface_parameters);
    if (query_result == RESULT_SUCCESS) {
        parameters->interface_pointer = query_interface_parameters.interface_pointer;
    }

    return query_result;
}

FResult FBase::GetChildCount(COM_GET_CHILD_COUNT_PARAMETERS* parameters) {
    if (parameters == nullptr) {
        return RESULT_INVALID_PARAMETER;
    }

    if (parameters->structure_type != COM_STRUCTURE_TYPE_GET_CHILD_COUNT_PARAMETERS) {
        return RESULT_UNSUPPORTED_STRUCTURE;
    }

    // TODO(wpieterse): Move this over to use a container.
    parameters->child_count = _child_count;

    return RESULT_SUCCESS;
}

FResult FBase::GetChild(COM_GET_CHILD_PARAMETERS* parameters) {
    FBase*                         child_pointer = nullptr;
    FResult                        query_result  = RESULT_SUCCESS;
    COM_QUERY_INTERFACE_PARAMETERS query_interface_parameters {};

    if (parameters == nullptr) {
        return RESULT_INVALID_PARAMETER;
    }

    if (parameters->structure_type != COM_STRUCTURE_TYPE_GET_CHILD_PARAMETERS) {
        return RESULT_UNSUPPORTED_STRUCTURE;
    }

    parameters->interface_pointer = nullptr;

    // TODO(wpieterse): Move this over to use a container.
    if (parameters->index < 0) {
        return RESULT_INVALID_PARAMETER;
    }

    if (parameters->index >= 256) {
        return RESULT_INVALID_PARAMETER;
    }

    child_pointer = _children[parameters->index];
    if (child_pointer == nullptr) {
        return RESULT_UNKNOWN_CHILD;
    }

    query_interface_parameters.interface_id = parameters->interface_id;

    query_result = child_pointer->QueryInterface(&query_interface_parameters);
    if (query_result == RESULT_SUCCESS) {
        parameters->interface_pointer = query_interface_parameters.interface_pointer;
    }

    return query_result;
}

FResult FBase::SetCustomData(COM_SET_CUSTOM_DATA_PARAMETERS* parameters) {
    if (parameters == nullptr) {
        return RESULT_INVALID_PARAMETER;
    }

    if (parameters->structure_type != COM_STRUCTURE_TYPE_SET_CUSTOM_DATA_PARAMETERS) {
        return RESULT_UNSUPPORTED_STRUCTURE;
    }

    return RESULT_UNIMPLEMENTED;
}

FResult FBase::GetCustomData(COM_GET_CUSTOM_DATA_PARAMETERS* parameters) {
    if (parameters == nullptr) {
        return RESULT_INVALID_PARAMETER;
    }

    if (parameters->structure_type != COM_STRUCTURE_TYPE_GET_CUSTOM_DATA_PARAMETERS) {
        return RESULT_UNSUPPORTED_STRUCTURE;
    }

    parameters->data_size   = 0;
    parameters->data_buffer = nullptr;

    return RESULT_UNIMPLEMENTED;
}

FResult FBase::SetName(COM_SET_NAME_PARAMETERS* parameters) {
    if (parameters == nullptr) {
        return RESULT_INVALID_PARAMETER;
    }

    if (parameters->structure_type != COM_STRUCTURE_TYPE_SET_NAME_PARAMETERS) {
        return RESULT_UNSUPPORTED_STRUCTURE;
    }

    return RESULT_UNIMPLEMENTED;
}

FResult FBase::DestructObject() {
    if (_parent != nullptr) {
        _parent->NotifyChildDestruction(this);
    }

    // TODO(wpieterse): Move this over to use a container.
    for (int64_t child_index = 0; child_index < 256; child_index++) {
        FBase* current_child = _children[child_index];
        if (current_child != nullptr) {
            current_child->DestructObject();
        }
    }

    delete this;

    return RESULT_SUCCESS;
}

void FBase::NotifyChildDestruction(FBase* child) {
}

INTERFACE_ID_DECLARATION(IID_IPhysicalGraphicsDevice, 0, 0);
INTERFACE_ID_DECLARATION(IID_IPhysicalGraphicsDeviceChild, 0, 0);
INTERFACE_ID_DECLARATION(IID_IPhysicalGraphicsDeviceOutput, 0, 0);

struct IPhysicalGraphicsDevice;
struct IPhysicalGraphicsDeviceChild;
struct IPhysicalGraphicsDeviceOutput;

typedef enum GRAPHICS_STRUCTURE_TYPE_PRE
{
    GRAPHICS_STRUCTURE_TYPE_ENUMERATION_FIRST = 0,
    GRAPHICS_STRUCTURE_TYPE_GET_DEVICE_PARAMETERS,
    GRAPHICS_STRUCTURE_TYPE_ENUMERATION_LAST,
    GRAPHICS_STRUCTURE_TYPE_ENUMERATION_MAX = UINT32_MAX,
} GRAPHICS_STRUCTURE_TYPE;

typedef struct GRAPHICS_GET_DEVICE_PARAMETERS_PRE {
    uint32_t    structure_type;
    const void* next_structure;

    FInterfaceID interface_id;
    IBase*       interface_pointer;

#if defined(__cplusplus) && !defined(_USE_C_INTERFACE)
    GRAPHICS_GET_DEVICE_PARAMETERS_PRE()
      : structure_type(GRAPHICS_STRUCTURE_TYPE_GET_DEVICE_PARAMETERS)
      , next_structure {nullptr}
      , interface_id {}
      , interface_pointer {nullptr} {
    }
#endif
} GRAPHICS_GET_DEVICE_PARAMETERS;

#undef CURRENT_INTERFACE
#define CURRENT_INTERFACE IPhysicalGraphicsDevice
DECLARE_INTERFACE(IPhysicalGraphicsDevice, IBase) {
    DECLARE_INTERFACE_METHOD(IncrementReference, COM_INCREMENT_REFERENCE_PARAMETERS * parameters);
    DECLARE_INTERFACE_METHOD(DecrementReference, COM_DECREMENT_REFERENCE_PARAMETERS * parameters);

    DECLARE_INTERFACE_METHOD(QueryInterface, COM_QUERY_INTERFACE_PARAMETERS * parameters);

    DECLARE_INTERFACE_METHOD(GetParent, COM_GET_PARENT_PARAMETERS * parameters);
    DECLARE_INTERFACE_METHOD(GetChildCount, COM_GET_CHILD_COUNT_PARAMETERS * parameters);
    DECLARE_INTERFACE_METHOD(GetChild, COM_GET_CHILD_PARAMETERS * parameters);

    DECLARE_INTERFACE_METHOD(SetCustomData, COM_SET_CUSTOM_DATA_PARAMETERS * parameters);
    DECLARE_INTERFACE_METHOD(GetCustomData, COM_GET_CUSTOM_DATA_PARAMETERS * parameters);

    DECLARE_INTERFACE_METHOD(SetName, COM_SET_NAME_PARAMETERS * parameters);
};

#undef CURRENT_INTERFACE
#define CURRENT_INTERFACE IPhysicalGraphicsDeviceOutput
DECLARE_INTERFACE(IPhysicalGraphicsDeviceOutput, IBase) {
    DECLARE_INTERFACE_METHOD(IncrementReference, COM_INCREMENT_REFERENCE_PARAMETERS * parameters);
    DECLARE_INTERFACE_METHOD(DecrementReference, COM_DECREMENT_REFERENCE_PARAMETERS * parameters);

    DECLARE_INTERFACE_METHOD(QueryInterface, COM_QUERY_INTERFACE_PARAMETERS * parameters);

    DECLARE_INTERFACE_METHOD(GetParent, COM_GET_PARENT_PARAMETERS * parameters);
    DECLARE_INTERFACE_METHOD(GetChildCount, COM_GET_CHILD_COUNT_PARAMETERS * parameters);
    DECLARE_INTERFACE_METHOD(GetChild, COM_GET_CHILD_PARAMETERS * parameters);

    DECLARE_INTERFACE_METHOD(SetCustomData, COM_SET_CUSTOM_DATA_PARAMETERS * parameters);
    DECLARE_INTERFACE_METHOD(GetCustomData, COM_GET_CUSTOM_DATA_PARAMETERS * parameters);

    DECLARE_INTERFACE_METHOD(SetName, COM_SET_NAME_PARAMETERS * parameters);
};

class FPhysicalGraphicsDevice
  : public FBase
  , public IPhysicalGraphicsDevice {
    using FSuper = FBase;

  public:
    FPhysicalGraphicsDevice();
    virtual ~FPhysicalGraphicsDevice();

    virtual FResult IncrementReference(COM_INCREMENT_REFERENCE_PARAMETERS* parameters) override;
    virtual FResult DecrementReference(COM_DECREMENT_REFERENCE_PARAMETERS* parameters) override;

    virtual FResult QueryInterface(COM_QUERY_INTERFACE_PARAMETERS* parameters) override;

    virtual FResult GetParent(COM_GET_PARENT_PARAMETERS* parameters) override;
    virtual FResult GetChildCount(COM_GET_CHILD_COUNT_PARAMETERS* parameters) override;
    virtual FResult GetChild(COM_GET_CHILD_PARAMETERS* parameters) override;

    virtual FResult SetCustomData(COM_SET_CUSTOM_DATA_PARAMETERS* parameters) override;
    virtual FResult GetCustomData(COM_GET_CUSTOM_DATA_PARAMETERS* parameters) override;

    virtual FResult SetName(COM_SET_NAME_PARAMETERS* parameters) override;
};

FPhysicalGraphicsDevice::FPhysicalGraphicsDevice()
  : FBase {nullptr} {
}

FPhysicalGraphicsDevice::~FPhysicalGraphicsDevice() {
}

FResult FPhysicalGraphicsDevice::IncrementReference(COM_INCREMENT_REFERENCE_PARAMETERS* parameters) {
    return FSuper::IncrementReference(parameters);
}

FResult FPhysicalGraphicsDevice::DecrementReference(COM_DECREMENT_REFERENCE_PARAMETERS* parameters) {
    return FSuper::DecrementReference(parameters);
}

FResult FPhysicalGraphicsDevice::QueryInterface(COM_QUERY_INTERFACE_PARAMETERS* parameters) {
    IPhysicalGraphicsDevice*           interface_pointer = nullptr;
    COM_INCREMENT_REFERENCE_PARAMETERS increment_parameters {};

    if (parameters == nullptr) {
        return RESULT_INVALID_PARAMETER;
    }

    if (parameters->structure_type != COM_STRUCTURE_TYPE_QUERY_INTERFACE_PARAMETERS) {
        return RESULT_UNSUPPORTED_STRUCTURE;
    }

    parameters->interface_pointer = nullptr;
    if (IsEqual(parameters->interface_id, IID_IPhysicalGraphicsDevice)) {
        interface_pointer = this;

        auto increment_result = interface_pointer->IncrementReference(&increment_parameters);
        if (increment_result == RESULT_SUCCESS) {
            parameters->interface_pointer = interface_pointer;
        }

        return increment_result;
    }

    return FSuper::QueryInterface(parameters);
}

FResult FPhysicalGraphicsDevice::GetParent(COM_GET_PARENT_PARAMETERS* parameters) {
    return FSuper::GetParent(parameters);
}

FResult FPhysicalGraphicsDevice::GetChildCount(COM_GET_CHILD_COUNT_PARAMETERS* parameters) {
    return FSuper::GetChildCount(parameters);
}

FResult FPhysicalGraphicsDevice::GetChild(COM_GET_CHILD_PARAMETERS* parameters) {
    return FSuper::GetChild(parameters);
}

FResult FPhysicalGraphicsDevice::SetCustomData(COM_SET_CUSTOM_DATA_PARAMETERS* parameters) {
    return FSuper::SetCustomData(parameters);
}

FResult FPhysicalGraphicsDevice::GetCustomData(COM_GET_CUSTOM_DATA_PARAMETERS* parameters) {
    return FSuper::GetCustomData(parameters);
}

FResult FPhysicalGraphicsDevice::SetName(COM_SET_NAME_PARAMETERS* parameters) {
    return FSuper::SetName(parameters);
}

class FPhysicalGraphicsDeviceOutput
  : public FBase
  , public IPhysicalGraphicsDeviceOutput {
    using FSuper = FBase;

  public:
    FPhysicalGraphicsDeviceOutput(FPhysicalGraphicsDevice* parent);
    virtual ~FPhysicalGraphicsDeviceOutput();

    virtual FResult IncrementReference(COM_INCREMENT_REFERENCE_PARAMETERS* parameters) override;
    virtual FResult DecrementReference(COM_DECREMENT_REFERENCE_PARAMETERS* parameters) override;

    virtual FResult QueryInterface(COM_QUERY_INTERFACE_PARAMETERS* parameters) override;

    virtual FResult GetParent(COM_GET_PARENT_PARAMETERS* parameters) override;
    virtual FResult GetChildCount(COM_GET_CHILD_COUNT_PARAMETERS* parameters) override;
    virtual FResult GetChild(COM_GET_CHILD_PARAMETERS* parameters) override;

    virtual FResult SetCustomData(COM_SET_CUSTOM_DATA_PARAMETERS* parameters) override;
    virtual FResult GetCustomData(COM_GET_CUSTOM_DATA_PARAMETERS* parameters) override;

    virtual FResult SetName(COM_SET_NAME_PARAMETERS* parameters) override;
};

FPhysicalGraphicsDeviceOutput::FPhysicalGraphicsDeviceOutput(FPhysicalGraphicsDevice* parent)
  : FBase {parent} {
}

FPhysicalGraphicsDeviceOutput::~FPhysicalGraphicsDeviceOutput() {
}

FResult FPhysicalGraphicsDeviceOutput::IncrementReference(COM_INCREMENT_REFERENCE_PARAMETERS* parameters) {
    return FSuper::IncrementReference(parameters);
}

FResult FPhysicalGraphicsDeviceOutput::DecrementReference(COM_DECREMENT_REFERENCE_PARAMETERS* parameters) {
    return FSuper::DecrementReference(parameters);
}

FResult FPhysicalGraphicsDeviceOutput::QueryInterface(COM_QUERY_INTERFACE_PARAMETERS* parameters) {
    IPhysicalGraphicsDeviceOutput*     interface_pointer = nullptr;
    COM_INCREMENT_REFERENCE_PARAMETERS increment_parameters {};

    if (parameters == nullptr) {
        return RESULT_INVALID_PARAMETER;
    }

    if (parameters->structure_type != COM_STRUCTURE_TYPE_QUERY_INTERFACE_PARAMETERS) {
        return RESULT_UNSUPPORTED_STRUCTURE;
    }

    parameters->interface_pointer = nullptr;
    if (IsEqual(parameters->interface_id, IID_IPhysicalGraphicsDeviceOutput)) {
        interface_pointer = this;

        auto increment_result = interface_pointer->IncrementReference(&increment_parameters);
        if (increment_result == RESULT_SUCCESS) {
            parameters->interface_pointer = interface_pointer;
        }

        return increment_result;
    }

    return FSuper::QueryInterface(parameters);
}

FResult FPhysicalGraphicsDeviceOutput::GetParent(COM_GET_PARENT_PARAMETERS* parameters) {
    return FSuper::GetParent(parameters);
}

FResult FPhysicalGraphicsDeviceOutput::GetChildCount(COM_GET_CHILD_COUNT_PARAMETERS* parameters) {
    return FSuper::GetChildCount(parameters);
}

FResult FPhysicalGraphicsDeviceOutput::GetChild(COM_GET_CHILD_PARAMETERS* parameters) {
    return FSuper::GetChild(parameters);
}

FResult FPhysicalGraphicsDeviceOutput::SetCustomData(COM_SET_CUSTOM_DATA_PARAMETERS* parameters) {
    return FSuper::SetCustomData(parameters);
}

FResult FPhysicalGraphicsDeviceOutput::GetCustomData(COM_GET_CUSTOM_DATA_PARAMETERS* parameters) {
    return FSuper::GetCustomData(parameters);
}

FResult FPhysicalGraphicsDeviceOutput::SetName(COM_SET_NAME_PARAMETERS* parameters) {
    return FSuper::SetName(parameters);
}

int main() {
    auto base_increment = COM_INCREMENT_REFERENCE_PARAMETERS {};
    auto base_decrement = COM_DECREMENT_REFERENCE_PARAMETERS {};
    auto base_test      = new FPhysicalGraphicsDevice {};

    IBase_IncrementReference(base_test, &base_increment);
    std::cout << base_increment.current_reference_count << std::endl;

    IBase_IncrementReference(base_test, &base_increment);
    std::cout << base_increment.current_reference_count << std::endl;

    IBase_DecrementReference(base_test, &base_decrement);
    std::cout << base_decrement.current_reference_count << std::endl;

    IBase_DecrementReference(base_test, &base_decrement);
    std::cout << base_decrement.current_reference_count << std::endl;

    return 0;
}
