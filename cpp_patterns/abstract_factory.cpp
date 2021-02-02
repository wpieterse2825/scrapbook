#include <memory>
#include <string>
#include <iostream>

#include "shared.hpp"

namespace wynand_pieterse::scrapbook::cpp_patterns::abstract_factory {
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

    namespace victorian {
        class VictorianProductA final : public ProductA {
          public:
            std::string Name() override {
                return "Victorian - A";
            }
        };

        class VictorianProductB final : public ProductB {
          public:
            std::string Name() override {
                return "Victorian - B";
            }
        };

        class VictorianFactory final : public AbstractFactory {
          public:
            std::unique_ptr<ProductA> CreateProductA() override {
                return std::unique_ptr<ProductA> {new VictorianProductA {}};
            }

            std::unique_ptr<ProductB> CreateProductB() override {
                return std::unique_ptr<ProductB> {new VictorianProductB {}};
            }
        };
    } // namespace victorian

    namespace modern {
        class ModernProductA final : public ProductA {
          public:
            std::string Name() override {
                return "Modern - A";
            }
        };

        class ModernProductB final : public ProductB {
          public:
            std::string Name() override {
                return "Modern - B";
            }
        };

        class ModernFactory final : public AbstractFactory {
          public:
            std::unique_ptr<ProductA> CreateProductA() override {
                return std::unique_ptr<ProductA> {new ModernProductA {}};
            }

            std::unique_ptr<ProductB> CreateProductB() override {
                return std::unique_ptr<ProductB> {new ModernProductB {}};
            }
        };
    } // namespace modern
} // namespace wynand_pieterse::scrapbook::cpp_patterns::abstract_factory

int main() {
    using wynand_pieterse::scrapbook::cpp_patterns::abstract_factory::AbstractFactory;
    using wynand_pieterse::scrapbook::cpp_patterns::abstract_factory::victorian::VictorianFactory;

    auto factory = std::unique_ptr<AbstractFactory> {new VictorianFactory {}};

    auto product_a = factory->CreateProductA();
    auto product_b = factory->CreateProductB();

    std::cout << product_a->Name() << std::endl;
    std::cout << product_b->Name() << std::endl;

    return 0;
}
