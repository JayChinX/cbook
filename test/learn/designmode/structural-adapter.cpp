// 类适配器方式

#include <iostream>
#include <ostream>
class Target {
    public:
    Target(){};
    virtual ~Target(){};
    virtual void Request() {
        std::cout << "Target: Request" << std::endl;
    }
};

class Adaptee {
    public:
    Adaptee(){};
    ~Adaptee(){};
    void SpecificRequest() {
        std::cout << "Adaptee::SpecificRequest" << std::endl;
    }
};

class Adapter: public Target {
    public:
    Adapter(Adaptee* ade): ade(ade) {};
    ~Adapter(){};
    void Request() override {
        ade->SpecificRequest();
    }

    private:
    Adaptee* ade;
};

int main() {
    Adaptee* ade = new Adaptee;
    Target* adt = new Adapter(ade);
    adt->Request();
    return 0;
}