#ifndef __MEDIATOR_H__
#define __MEDIATOR_H__

#include "colleague.h"
class Mediator {
  public:
    virtual void send(std::string message, Colleague *colleague) = 0;
    virtual void add(Colleague *colleague) = 0;
};
#endif // __MEDIATOR_H__