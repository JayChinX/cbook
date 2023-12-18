

#include <iostream>
void printX() {}

// 特化
template <typename T, typename... Types>
void printX(const T &firstArg, const Types &...args)
{
    std::cout << firstArg << std::endl;
    printX(args...);
}

int main(int argc, char **argv)
{
    printX(1.0, "a", "b", 'c', 'd', 1);
    system("pause");
    return 0;
}
