
#include "colleague.h"
#include "mediator.h"
#include <vector>
class ConcreteMediator : public Mediator {
  public:
    void add(Colleague *colleague) override {
        colleague_list.push_back(colleague);
    }
    void send(std::string message, Colleague *colleague) override {
        for (auto value : colleague_list) {
            if (colleague != value) { value->notify(message); }
        }
    }

  private:
    std::vector<Colleague *> colleague_list;
};