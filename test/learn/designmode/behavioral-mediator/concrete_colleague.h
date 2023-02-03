#include "colleague.h"
#include "mediator.h"
#include <iostream>
#include <string>
class ConcreteColleagueA : public Colleague {
  public:
    ConcreteColleagueA(Mediator *mediator) : Colleague(mediator) {}
    ~ConcreteColleagueA() = default;

    void send(std::string message) { getMediator()->send(message, this); }
    void notify(std::string message) override {
        std::cout << "同事1收到消息：" << message << std::endl;
    }
};

class ConcreteColleagueB : public Colleague {
  public:
    ConcreteColleagueB(Mediator *mediator) : Colleague(mediator) {}
    ~ConcreteColleagueB() = default;

    void send(std::string message) { getMediator()->send(message, this); }
    void notify(std::string message) override {
        std::cout << "同事2收到消息：" << message << std::endl;
    }
};