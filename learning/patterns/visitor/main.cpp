#include <string>
#include <vector>
#include <iostream>

class VirtualBase {
  public:
    virtual ~VirtualBase() {
    }
};

class ComponentA;
class ComponentASub;
class ComponentB;
class ComponentBSub;

class Visitor : public VirtualBase {
  public:
    virtual void Visit(ComponentA* component)    = 0;
    virtual void Visit(ComponentASub* component) = 0;
    virtual void Visit(ComponentB* component)    = 0;
    virtual void Visit(ComponentBSub* component) = 0;
};

class Component : public VirtualBase {
  public:
    virtual void Accept(Visitor* visitor) = 0;
};

class ComponentA final : public Component {
  private:
    std::vector<Component*> _subs;

  public:
    const char* Name() {
        return "Component A";
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

class ComponentASub final : public Component {
  public:
    const char* Name() {
        return "Component A - Sub";
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
  private:
    void PrintName(const char* name) {
        std::cout << " - " << name << std::endl;
    }

  public:
    void Visit(ComponentA* component) override {
        PrintName(component->Name());
    }

    void Visit(ComponentASub* component) override {
        PrintName(component->Name());
    }

    void Visit(ComponentB* component) override {
        PrintName(component->Name());
    }

    void Visit(ComponentBSub* component) override {
        PrintName(component->Name());
    }
};

Component* CreateA() {
    auto result = new ComponentA {};

    auto sub_1 = new ComponentASub {};
    result->AddComponent(sub_1);

    auto sub_2 = new ComponentASub {};
    result->AddComponent(sub_2);

    return result;
}

Component* CreateB() {
    auto result = new ComponentB {};

    auto sub_1 = new ComponentBSub {};
    result->AddComponent(sub_1);

    auto sub_2 = new ComponentBSub {};
    result->AddComponent(sub_2);

    return result;
}

int main() {
    auto visitor = new VisitorImpl {};

    std::cout << "==================================================" << std::endl;
    std::cout << "Visitor (Part A):" << std::endl;
    auto component_a = CreateA();
    component_a->Accept(visitor);
    std::cout << "==================================================" << std::endl;

    std::cout << std::endl;

    std::cout << "==================================================" << std::endl;
    std::cout << "Visitor (Part B):" << std::endl;
    auto component_b = CreateB();
    component_b->Accept(visitor);
    std::cout << "==================================================" << std::endl;

    return 0;
}
