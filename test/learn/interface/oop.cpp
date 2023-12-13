
#include <cstdlib>
#include <iostream>
class Base {
    virtual void vfunc(float) {}
};

class Derived : Base {
public:
    void vfunc(float) override;
};

void Derived::vfunc(float i)
{
    std::cout << "i = " << i << std::endl;
}

int main(int argc, char **argv)
{
    Derived d;
    d.vfunc(0.1);

    return 0;
}
