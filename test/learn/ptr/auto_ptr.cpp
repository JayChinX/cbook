
#include <iostream>
#include <memory>
#include <ostream>
int main(int argc, char **argv)
{
    std::shared_ptr<int> c_ptr = std::make_shared<int>(1);
    std::cout << "c: " << *c_ptr.get() << std::endl;

    std::shared_ptr<int> e_ptr(new int(10));
    std::shared_ptr<int> f_ptr = e_ptr;
    std::cout << "e: " << *e_ptr.get() << std::endl;
    std::cout << "f: " << *f_ptr.get() << std::endl;

    int a = 123;
    std::unique_ptr<int> u_ptr(new int(13));
    std::cout << "a: " << *u_ptr.get() << std::endl;

    system("pause");
    return 0;
}
