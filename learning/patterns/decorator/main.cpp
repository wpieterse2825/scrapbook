#include <stdint.h>
#include <iostream>

using VkInstance = size_t;
using VkDevice   = size_t;

constexpr void* PointerIncrement(void* pointer, size_t number_of_bytes) {
    return static_cast<uint8_t*>(pointer) + number_of_bytes;
}

class VirtualBase {
  public:
    ~VirtualBase() {
    }
};

class Device : public VirtualBase {
  public:
};

class Instance : public VirtualBase {
  public:
    virtual void Destroy() = 0;

    virtual size_t GetDeviceSize()                             = 0;
    virtual void   CreateDevice(void* buffer, Device** device) = 0;
};

class InstanceDecorator : public Instance {
  private:
    Instance* _next;

  protected:
    InstanceDecorator(Instance* next)
      : _next {next} {
    }

  public:
    virtual void Destroy() override {
        _next->Destroy();
    }

    virtual size_t GetDeviceSize() override {
        return _next->GetDeviceSize();
    }

    virtual void CreateDevice(void* buffer, Device** device) override {
        std::cout << " - InstanceDecorator::CreateDevice" << std::endl;
        _next->CreateDevice(buffer, device);
    }
};

class TestDevice final : public Device {
  public:
};

class TestInstance final : public Instance {
  public:
    static size_t GetSize() {
        return sizeof(TestInstance);
    }

    virtual void Destroy() override {
        this->~TestInstance();
    }

    virtual size_t GetDeviceSize() override {
        return sizeof(TestDevice);
    }

    virtual void CreateDevice(void* buffer, Device** device) override {
        std::cout << " - TestInstance::CreateDevice" << std::endl;
        *device = new (buffer) TestDevice {};
    }
};

class TestInstanceDecorator_1 final : public InstanceDecorator {
  public:
    TestInstanceDecorator_1(Instance* next)
      : InstanceDecorator {next} {
    }

    static size_t GetSize() {
        return sizeof(TestInstanceDecorator_1);
    }

    virtual void Destroy() override {
        InstanceDecorator::Destroy();

        this->~TestInstanceDecorator_1();
    }

    virtual void CreateDevice(void* buffer, Device** device) override {
        std::cout << " - TestInstanceDecorator_1::CreateDevice" << std::endl;
        InstanceDecorator::CreateDevice(buffer, device);
    }
};

class TestInstanceDecorator_2 final : public InstanceDecorator {
  public:
    TestInstanceDecorator_2(Instance* next)
      : InstanceDecorator {next} {
    }

    static size_t GetSize() {
        return sizeof(TestInstanceDecorator_2);
    }

    virtual void Destroy() override {
        InstanceDecorator::Destroy();

        this->~TestInstanceDecorator_2();
    }

    virtual void CreateDevice(void* buffer, Device** device) override {
        std::cout << " - TestInstanceDecorator_2::CreateDevice" << std::endl;
        InstanceDecorator::CreateDevice(buffer, device);
    }
};

class TestInstanceDecorator_3 final : public InstanceDecorator {
  public:
    TestInstanceDecorator_3(Instance* next)
      : InstanceDecorator {next} {
    }

    static size_t GetSize() {
        return sizeof(TestInstanceDecorator_3);
    }

    virtual void Destroy() override {
        InstanceDecorator::Destroy();

        this->~TestInstanceDecorator_3();
    }

    virtual void CreateDevice(void* buffer, Device** device) override {
        std::cout << " - TestInstanceDecorator_3::CreateDevice" << std::endl;
        InstanceDecorator::CreateDevice(buffer, device);
    }
};

class AbstractFactory : public VirtualBase {
  public:
    virtual size_t GetInstanceSize()                                 = 0;
    virtual void   CreateInstance(void* buffer, Instance** instance) = 0;

    virtual size_t GetInstanceExtensionSize(uint32_t extension_id)                                                   = 0;
    virtual void   CreateInstanceExtension(uint32_t extension_id, void* buffer, Instance* next, Instance** instance) = 0;
};

class TestAbstractFactory final : public AbstractFactory {
  public:
    virtual size_t GetInstanceSize() override {
        return sizeof(TestInstance);
    }

    virtual void CreateInstance(void* buffer, Instance** instance) override {
        *instance = new (buffer) TestInstance {};
    }

    virtual size_t GetInstanceExtensionSize(uint32_t extension_id) override {
        if (extension_id == 0) {
            return sizeof(TestInstanceDecorator_1);
        }

        if (extension_id == 1) {
            return sizeof(TestInstanceDecorator_2);
        }

        if (extension_id == 2) {
            return sizeof(TestInstanceDecorator_3);
        }

        return (size_t)-1;
    }

    virtual void CreateInstanceExtension(uint32_t extension_id, void* buffer, Instance* next, Instance** instance) override {
        if (extension_id == 0) {
            *instance = new (buffer) TestInstanceDecorator_1 {next};
            return;
        }

        if (extension_id == 1) {
            *instance = new (buffer) TestInstanceDecorator_2 {next};
            return;
        }

        if (extension_id == 2) {
            *instance = new (buffer) TestInstanceDecorator_3 {next};
            return;
        }
    }
};

void vkCreateInstance(VkInstance* instance) {
    AbstractFactory* factory = new TestAbstractFactory {};

    size_t  main_size            = 0;
    int32_t extension_count      = 0;
    size_t  extension_sizes[16]  = {0};
    size_t  extension_size_total = 0;

    main_size = factory->GetInstanceSize();
    for (uint32_t index = 0; index < 16; index++) {
        size_t extension_size = factory->GetInstanceExtensionSize(index);
        if (extension_size == (size_t)-1) {
            break;
        }

        extension_sizes[extension_count] = extension_size;
        extension_size_total += extension_size;
        extension_count++;
    }

    size_t buffer_size = main_size + extension_size_total;
    void*  buffer      = malloc(buffer_size);

    void*     main_instance_buffer = PointerIncrement(buffer, extension_size_total);
    Instance* main_instance        = nullptr;

    factory->CreateInstance(main_instance_buffer, &main_instance);

    Instance* current_instance = main_instance;
    for (int32_t index = 0; index < extension_count; index++) {
        extension_size_total -= extension_sizes[index];
        void* instance_buffer = PointerIncrement(buffer, extension_size_total);

        factory->CreateInstanceExtension(index, instance_buffer, current_instance, &current_instance);
    }

    *instance = (VkInstance)current_instance;
}

void vkDestroyInstance(VkInstance instance) {
    Instance* main_instance = (Instance*)instance;

    main_instance->Destroy();
    free(main_instance);
}

void vkCreateDevice(VkInstance instance, VkDevice* device) {
    Instance* main_instance = (Instance*)instance;

    size_t  main_device_size   = main_instance->GetDeviceSize();
    void*   main_device_buffer = malloc(main_device_size);
    Device* main_device        = nullptr;
    main_instance->CreateDevice(main_device_buffer, &main_device);

    *device = (VkDevice)main_device;
}

int main() {
    VkInstance instance;
    VkDevice   device;

    std::cout << "==================================================" << std::endl;
    std::cout << "Decorator:" << std::endl;

    vkCreateInstance(&instance);
    vkCreateDevice(instance, &device);

    std::cout << "==================================================" << std::endl;

    return 0;
}
