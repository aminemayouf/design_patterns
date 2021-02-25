#include <iostream>
#include <string>
#include <vector>

class ComponentA;
class ComponentB;

class Visitor {
    public:
    virtual void Visit(const ComponentA *element) const = 0;
    virtual void Visit(const ComponentB *element) const = 0;
};

class Component {
    public:
    virtual ~Component() {}
    virtual void Accept(Visitor *visitor) const = 0;

};


class ComponentA : public Component {
    public:
    void Accept(Visitor* visitor) const override {
        visitor->Visit(this);
    }
    float Price() const {
        return 10;
    }
};

class ComponentB : public Component {
    public:
    void Accept(Visitor* visitor) const override {
        visitor->Visit(this);
    }
    float Price() const {
        return 20;
    }
};

class Visitor1 : public Visitor {
    public:
    void Visit(const ComponentA *element) const override {
        std::cout << "Visitor1 - Component A: " << element->Price() * 0.2 << std::endl;
    }
    void Visit(const ComponentB *element) const override {
        std::cout << "Visitor1 - Component B: " << element->Price() * 0.2 << std::endl;
    }
};

class Visitor2 : public Visitor {
    public:
    void Visit(const ComponentA *element) const override {
        std::cout << "Visitor2 - Component A: " << element->Price() * 0.5 << std::endl;
    }
    void Visit(const ComponentB *element) const override {
        std::cout << "Visitor2 - Componenet B: " << element->Price() * 0.5 << std::endl;
    }
};

int main() {

    std::vector<std::unique_ptr<Component>> components;
    components.push_back(std::move(std::make_unique<ComponentA>()));
    components.push_back(std::move(std::make_unique<ComponentB>()));
    
    Visitor1 v1;
    Visitor2 v2;

    for (const auto& component : components) {
        component->Accept(&v1);
        component->Accept(&v2);
    }

    return 0;
}