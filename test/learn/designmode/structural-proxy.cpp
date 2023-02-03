// 代理模式

#include <iostream>
#include <ostream>
class AbstractSubject {
  public:
    virtual void BuyTicket() = 0;
    virtual void end() { std::cout << "购票成功" << std::endl; }

    void start() {
        std::cout << "购票开始" << std::endl;
    }
};

class User : public AbstractSubject {
  public:
    void BuyTicket() override {
        std::cout << "用户购票" << std::endl;
        end();
    }
};

class Ctrip : public AbstractSubject {
  public:
    Ctrip(AbstractSubject *pBase) : pbase(pBase) {}
    void BuyTicket() override {
        start();
        std::cout << "携程购票" << std::endl;
        this->pbase->BuyTicket();
    }
    void end() override {
        std::cout << "携程购票成功" << std::endl;
        this->AbstractSubject::end();
    }

    void start() {
        std::cout << "携程购票开始" << std::endl;
    }

  private:
    AbstractSubject *pbase;
};

int main() {
    AbstractSubject *pbase = new User;
    pbase->BuyTicket();

    Ctrip *proxy = new Ctrip(pbase);
    proxy->BuyTicket();
    return 0;
}