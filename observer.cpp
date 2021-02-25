#include <iostream>
#include <string>
#include <list>

class IObserver {
    public:
    virtual ~IObserver() {};
    virtual void Update(const std::string &message) = 0;
};

class IObservable {
    public:
    virtual ~IObservable() {};
    virtual void Add(IObserver* observer) = 0;
    virtual void Remove(IObserver* observer) = 0;
    virtual void Notify(const std::string& message) = 0;
};

class Observable : public IObservable {
    public:
    void Add(IObserver* observer) override {
        m_observers.push_back(observer);
    }

    void Remove(IObserver* observer) override {
        m_observers.remove(observer);
    }

    void Notify(const std::string& message) override {
        for (auto it = m_observers.begin(); it != m_observers.end(); ++it) {
            (*it)->Update(message);
        }
    }

    private:
    std::list<IObserver*> m_observers;
};

class Observer : public IObserver {

    void Update(const std::string& message) override {
        std::cout << message << std::endl;
    }
};

int main() {

    Observable observable;
    Observer observer1;
    Observer observer2;
    observable.Add(&observer1);
    observable.Add(&observer2);

    observable.Notify("hello world!");

    observable.Remove(&observer1);
    
    observable.Notify("hello world!");

    return 0;
}
