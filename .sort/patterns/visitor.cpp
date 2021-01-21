#include <string>
#include <vector>
#include <iostream>

class VirtualBase {
  public:
    virtual ~VirtualBase() {
    }
};

class ComponentA;
class ComponentB;
class ComponentBSub;

class Visitor : public VirtualBase {
  public:
    virtual void Visit(ComponentA* component)    = 0;
    virtual void Visit(ComponentB* component)    = 0;
    virtual void Visit(ComponentBSub* component) = 0;
};

class Component : public VirtualBase {
  public:
    virtual void Accept(Visitor* visitor) = 0;
};

class ComponentA final : public Component {
  public:
    const char* Name() {
        return "Component A";
    }

    void Accept(Visitor* visitor) override {
        visitor->Visit(this);
    };
};

class ComponentB final : public Component {
  private:
    std::vector<Component*> _subs;

  public:
    const char* Name() {
        return "Component B";
    }

    void AddComponent(Component* component) {
        _subs.push_back(component);
    }

    void Accept(Visitor* visitor) override {
        visitor->Visit(this);

        for (auto item : _subs) {
            item->Accept(visitor);
        }
    };
};

class ComponentBSub final : public Component {
  public:
    const char* Name() {
        return "Component B - Sub";
    }

    void Accept(Visitor* visitor) override {
        visitor->Visit(this);
    };
};

class VisitorImpl final : public Visitor {
  public:
    void Visit(ComponentA* component) override {
        std::cout << component->Name() << std::endl;
    }

    void Visit(ComponentB* component) override {
        std::cout << component->Name() << std::endl;
    }

    void Visit(ComponentBSub* component) override {
        std::cout << component->Name() << std::endl;
    }
};

Component* CreateA() {
    return new ComponentA {};
}

Component* CreateB() {
    auto result = new ComponentB {};
    auto sub_1  = new ComponentBSub {};
    auto sub_2  = new ComponentBSub {};

    result->AddComponent(sub_1);
    result->AddComponent(sub_2);

    return result;
}

int main() {
    auto component_a = CreateA();
    auto component_b = CreateB();
    auto visitor     = new VisitorImpl {};

    component_b->Accept(visitor);
    component_a->Accept(visitor);

    return 0;
}
