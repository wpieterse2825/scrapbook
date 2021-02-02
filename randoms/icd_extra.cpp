#include <iostream>

constexpr void* PointerIncrement(void* pointer, size_t number_of_bytes) {
    return (static_cast<uint8_t*>(pointer) + number_of_bytes);
}

class VirtualBase {
  public:
    virtual ~VirtualBase() {
    }
};

class Device;

class Instance : public VirtualBase {
  public:
    virtual size_t GetDeviceSize() = 0;

    virtual void CreateDevice(void* buffer, Device** device) = 0;
};

class Device : public VirtualBase {
  public:
    virtual void Destroy() = 0;
};

class InstanceDecorator : public Instance {
  private:
    Instance* _previous;
    Instance* _next;

  protected:
    InstanceDecorator(Instance* previous, Instance* next)
      : _previous {previous}
      , _next {next} {
    }

  public:
    virtual size_t GetDeviceSize() override {
        return _next->GetDeviceSize();
    }

    virtual void CreateDevice(void* buffer, Device** device) override {
        std::cout << "InstanceDecorator::CreateDevice" << std::endl;
        _next->CreateDevice(buffer, device);
    }
};

class DeviceDecorator : public Device {
  private:
    Device* _previous;
    Device* _next;

  protected:
    DeviceDecorator(Device* previous, Device* next)
      : _previous {previous}
      , _next {next} {
    }

  public:
    virtual void Destroy() override {
        std::cout << "DeviceDecorator::Destroy" << std::endl;
        _next->Destroy();
    }
};

class TestDevice final : public Device {
  private:
    uint32_t _value;

  public:
    TestDevice()
      : _value {0xFFFFFFFF} {
    }

    virtual void Destroy() override {
        std::cout << "TestDevice::Destroy - " << _value << std::endl;

        this->~TestDevice();
    }
};

class TestInstance final : public Instance {
  public:
    virtual size_t GetDeviceSize() override {
        return sizeof(TestDevice);
    }

    virtual void CreateDevice(void* buffer, Device** device) override {
        std::cout << "TestInstance::CreateDevice" << std::endl;
        *device = new (buffer) TestDevice {};
    }
};

class TestDeviceDecorator_1 final : public DeviceDecorator {
  private:
    uint32_t _value;

  public:
    TestDeviceDecorator_1(Device* next)
      : DeviceDecorator {nullptr, next}
      , _value {0xFFFFFFFF} {
    }

    virtual void Destroy() override {
        std::cout << "TestDeviceDecorator_1::Destroy - " << _value << std::endl;

        DeviceDecorator::Destroy();

        this->~TestDeviceDecorator_1();
    }
};

class TestDeviceDecorator_2 final : public DeviceDecorator {
  private:
    uint32_t _value;

  public:
    TestDeviceDecorator_2(Device* next)
      : DeviceDecorator {nullptr, next}
      , _value {0xFFFFFFFF} {
    }

    virtual void Destroy() override {
        std::cout << "TestDeviceDecorator_2::Destroy - " << _value << std::endl;

        DeviceDecorator::Destroy();

        this->~TestDeviceDecorator_2();
    }
};

class TestInstanceDecorator final : public InstanceDecorator {
  public:
    TestInstanceDecorator(Instance* next)
      : InstanceDecorator {nullptr, next} {
    }

    virtual size_t GetDeviceSize() override {
        return sizeof(TestDeviceDecorator_1) + sizeof(TestDeviceDecorator_2) + InstanceDecorator::GetDeviceSize();
    }

    virtual void CreateDevice(void* buffer, Device** device) override {
        std::cout << "TestInstanceDecorator::CreateDevice" << std::endl;

        auto decorator_2_address = PointerIncrement(buffer, 0);
        auto decorator_1_address = PointerIncrement(decorator_2_address, sizeof(TestDeviceDecorator_2));
        auto instance_address    = PointerIncrement(decorator_1_address, sizeof(TestDeviceDecorator_1));

        InstanceDecorator::CreateDevice(instance_address, device);

        *device = new (decorator_1_address) TestDeviceDecorator_1 {*device};
        *device = new (decorator_2_address) TestDeviceDecorator_2 {*device};
    }
};

int main() {
    Instance* instance           = new TestInstance {};
    Instance* instance_decorator = new TestInstanceDecorator {instance};

    size_t  device_size   = instance_decorator->GetDeviceSize();
    void*   device_buffer = malloc(device_size);
    Device* device        = nullptr;

    instance_decorator->CreateDevice(device_buffer, &device);

    device->Destroy();

    free(device_buffer);

    std::cout << instance_decorator->GetDeviceSize() << std::endl;

    return 0;
}
