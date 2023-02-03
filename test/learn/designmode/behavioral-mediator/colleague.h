#ifndef __COLLEAGUE_H__
#define __COLLEAGUE_H__

#include <string>
class Mediator;

class Colleague {
  public:
    Colleague(Mediator *mediator);
    ~Colleague();
    Mediator *getMediator();
    void setMediator(Mediator *const mediator);
    virtual void notify(std::string message) = 0;

  private:
    Mediator *mediator;
};
#endif // __COLLEAGUE_H__