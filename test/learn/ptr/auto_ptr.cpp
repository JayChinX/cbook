
#include <iostream>
#include <memory>
#include <ostream>
int main(int argc, char **argv)
{
    std::shared_ptr<int> c_ptr = std::make_shared<int>(1);
    std::cout << "c: " << *c_ptr.get() << std::endl;

    int a = 123;
    // std::unique_ptr<int> u_ptr = a;

    system("pause");
    return 0;
}
