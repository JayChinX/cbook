
#include "colleague.h"
#include "mediator.h"

Colleague::Colleague(Mediator *mediator) : mediator(mediator) {
    this->mediator->add(this);
}

Mediator *Colleague::getMediator() {
    return mediator;
}

void Colleague::setMediator(Mediator *const mediator) {
    this->mediator = mediator;
}