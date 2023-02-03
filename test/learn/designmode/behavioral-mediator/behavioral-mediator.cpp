
#include "colleague.h"
#include "concrete_mediator.h"
#include "concrete_colleague.h"

#include <cstdlib>

int main(int argc, char **argv) {
    Mediator *mediator = new ConcreteMediator;
    ConcreteColleagueA *colleague = new ConcreteColleagueA(mediator);
    ConcreteColleagueB *colleagueB = new ConcreteColleagueB(mediator);

    colleague->send("早上好！");
    colleagueB->send("早安！");
    system("pause");
    return 0;
}
