#include <iostream>
#include <vector>

class Product1 {
    public:
    std::vector<std::string> m_parts;
    void PrintParts() const {
        std::cout << "Product parts: ";
        for (size_t i = 0; i < m_parts.size(); ++i) {
            if (m_parts[i] == m_parts.back()) {
                std::cout << m_parts[i];
            }
            else {
                std::cout << m_parts[i] << ", ";
            }
        }
        std::cout << "\n\n";
    }
};

class Builder {
    public:
    virtual ~Builder() {}
    virtual void ProducePartA() const = 0;
    virtual void ProducePartB() const = 0;
    virtual void ProducePartC() const = 0;
};

class Builder1 : public Builder {
    private:
    Product1* product;

    public:
    Builder1() {
        this->Reset();
    }

    ~Builder1() {
        delete product;
    }

    void Reset() {
        this->product = new Product1();
    }

    void ProducePartA() const override {
        this->product->m_parts.push_back("PartA1");
    }

    void ProducePartB() const override {
        this->product->m_parts.push_back("PartB1");
    }

    void ProducePartC() const override {
        this->product->m_parts.push_back("PartC1");
    }

    Product1* GetProduct() {
        Product1* result = this->product;
        this->Reset();
        return result;
    }
};

class Director {
    private:
    Builder* builder;

    public:
    void SetBuilder(Builder* builder) {
        this->builder = builder;
    }

    void BuildMinimalViableProduct() {
        this->builder->ProducePartA();
    }

    void BuildFeaturedProduct() {
        this->builder->ProducePartA();
        this->builder->ProducePartB();
        this->builder->ProducePartC();
    }
};

int main() {

    Director* director = new Director();
    Builder1* builder = new Builder1();

    director->SetBuilder(builder);
    director->BuildFeaturedProduct();

    Product1* product = builder->GetProduct();
    product->PrintParts();

    delete product;
    delete director;
    delete builder;

    return 0;
}