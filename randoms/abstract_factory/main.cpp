#include <memory>
#include <string>
#include <iostream>

class VirtualBase {
  public:
    virtual ~VirtualBase() {
    }
};

class ProductA : public VirtualBase {
  public:
    virtual std::string Name() = 0;
};

class ProductB : public VirtualBase {
  public:
    virtual std::string Name() = 0;
};

class AbstractFactory : public VirtualBase {
  public:
    virtual std::unique_ptr<ProductA> CreateProductA() = 0;
    virtual std::unique_ptr<ProductB> CreateProductB() = 0;
};

class VictorianProductA final : public ProductA {
  public:
    virtual std::string Name() override {
        return "Victorian - A";
    }
};

class VictorianProductB final : public ProductB {
  public:
    virtual std::string Name() override {
        return "Victorian - B";
    }
};

class VictorianFactory final : public AbstractFactory {
  public:
    virtual std::unique_ptr<ProductA> CreateProductA() override {
        return std::unique_ptr<ProductA> {new VictorianProductA {}};
    }

    virtual std::unique_ptr<ProductB> CreateProductB() override {
        return std::unique_ptr<ProductB> {new VictorianProductB {}};
    }
};

class ModernProductA final : public ProductA {
  public:
    virtual std::string Name() override {
        return "Modern - A";
    }
};

class ModernProductB final : public ProductB {
  public:
    virtual std::string Name() override {
        return "Modern - B";
    }
};

class ModernFactory final : public AbstractFactory {
  public:
    virtual std::unique_ptr<ProductA> CreateProductA() override {
        return std::unique_ptr<ProductA> {new ModernProductA {}};
    }

    virtual std::unique_ptr<ProductB> CreateProductB() override {
        return std::unique_ptr<ProductB> {new ModernProductB {}};
    }
};

void CreateAndPrintVectorProducts(std::unique_ptr<AbstractFactory> factory) {
    auto product_a = factory->CreateProductA();
    std::cout << " - " << product_a->Name() << std::endl;

    auto product_b = factory->CreateProductB();
    std::cout << " - " << product_b->Name() << std::endl;
}

int main() {
    std::cout << "==================================================" << std::endl;
    std::cout << "Abstract Factory (Victorian):" << std::endl;
    auto factory_victorian = std::unique_ptr<AbstractFactory> {new VictorianFactory {}};
    CreateAndPrintVectorProducts(std::move(factory_victorian));
    std::cout << "==================================================" << std::endl;

    std::cout << std::endl;

    std::cout << "==================================================" << std::endl;
    std::cout << "Abstract Factory (Modern):" << std::endl;
    auto factory_modern = std::unique_ptr<AbstractFactory> {new ModernFactory {}};
    CreateAndPrintVectorProducts(std::move(factory_modern));
    std::cout << "==================================================" << std::endl;

    return 0;
}
