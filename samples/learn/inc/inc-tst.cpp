
#include <iostream>
#include "template_state.h"

class MyState : public State<int> {
public:
    MyState() {};
};

int main(int argc, char **argv)
{
    MyState state;
    state.setIdentify(1);
    std::cout << "Identify: " << state.getIdentify() << std::endl;
    return 0;
}
