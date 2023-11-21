#include <cstdlib>
#include <iostream>
#include <ostream>

int main(int argc, char **argv)
{
    // lambda 函数表达式
    int i = 1;
    int j = 4;
    //  [] 捕获列表，用来捕获局部变量
    //  (int &i) 参数列表
    //  -> int 返回类型，-> void 可省略
    //
    auto f = [&](const int &n) -> int {
        // 函数体
        std::cout << "n = " << n << std::endl;
        std::cout << "i = " << i << std::endl;
        std::cout << "j = " << j << std::endl;
        return 3;
    };

    int c = f(2);

    std::cout << "c = " << c << std::endl;

    auto b = [] {};  // 忽略参数列表和返回值

    auto d = [&/*捕获列表*/](const int &n /*参数*/) mutable -> int /*返回值*/ {
        std::cout << "d = " << n << std::endl;
        return 0;
    };

    d(1);

    int res[] = {0, 1, 2, 3, 4};

    for (auto &i : res) {
        std::cout << "i = " << i << std::endl;
    }

    system("pause");
    return 0;
}
