#include <memory>
#include <string>
#include <vector>
#include <iostream>

class Message {
  public:
    std::vector<std::string> parts;

    void Print() {
        for (const auto& part : parts) {
            std::cout << part << std::endl;
        }
    }
};

class MessageBuilder {
  public:
    virtual ~MessageBuilder() {
    }

    virtual void Reset() = 0;

    virtual MessageBuilder& AddPartA() = 0;
    virtual MessageBuilder& AddPartB() = 0;
    virtual MessageBuilder& AddPartC() = 0;

    virtual std::unique_ptr<Message> Build() = 0;
};

class MessageBuilderImpl : public MessageBuilder {
  private:
    std::unique_ptr<Message> _message;

  public:
    MessageBuilderImpl()
      : _message {nullptr} {
        Reset();
    }

    virtual void Reset() {
        _message = std::unique_ptr<Message> {new Message {}};
    }

    virtual MessageBuilder& AddPartA() {
        _message->parts.emplace_back("Part A");
        return *this;
    }

    virtual MessageBuilder& AddPartB() {
        _message->parts.emplace_back("Part B");
        return *this;
    }

    virtual MessageBuilder& AddPartC() {
        _message->parts.emplace_back("Part C");
        return *this;
    }

    virtual std::unique_ptr<Message> Build() {
        auto result = std::move(_message);

        Reset();
        return result;
    }
};

class MessageDirector {
  private:
    MessageBuilder* _builder;

  public:
    MessageDirector(MessageBuilder* builder)
      : _builder {builder} {
    }

    void BuildMinimumViableProduct() {
        _builder->AddPartA();
        _builder->AddPartB();
        _builder->AddPartC();
    }

    void BuildOtherProduct() {
        _builder->AddPartC();
    }
};

int main() {
    auto builder  = MessageBuilderImpl {};
    auto director = MessageDirector {&builder};

    std::cout << "==================================================" << std::endl;
    director.BuildMinimumViableProduct();
    auto message = builder.Build();
    message->Print();
    std::cout << "==================================================" << std::endl;

    std::cout << std::endl;

    std::cout << "==================================================" << std::endl;
    director.BuildOtherProduct();
    message = builder.Build();
    message->Print();
    std::cout << "==================================================" << std::endl;

    return 0;
}
