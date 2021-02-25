#include <iostream>

class Product {
    public:
    virtual ~Product() {}
    virtual std::string Operation() const = 0;
};

class ProductA : public Product {
    public:
    std::string Operation() const override {
        return "Result of the product A";
    }
};

class ProductB : public Product {
    public:
    std::string Operation() const override {
        return "Result of the product B";
    }
};

class Creator {
    public:
    virtual ~Creator() {}
    virtual Product* FactoryMethod() const = 0;

    std::string SomeOperation() const {
        Product* product = this->FactoryMethod();
        std::string result = "Creator: " + product->Operation();
        delete product;
        return result;
    }
};

class Creator1 : public Creator {
    public:
    Product* FactoryMethod() const override {
        return new ProductA();
    }
};

class Creator2 : public Creator {
    public:
    Product* FactoryMethod() const override {
        return new ProductB();
    }
};

int main () {

    Creator* creator = new Creator1();
    std::cout << creator->SomeOperation() << std::endl;
    delete creator;
    creator = new Creator2();
    std::cout << creator->SomeOperation() << std::endl;
    delete creator;

    return 0;
}