#include <cstdlib>
#include <iostream>
#include <ostream>

int main(int argc, char **argv) {
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

    auto b = [] {
    };

    system("pause");
    return 0;
}
