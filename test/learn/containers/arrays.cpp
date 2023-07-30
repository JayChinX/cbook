
#include <array>
#include <cstdlib>
#include <iostream>
#include <ostream>

int main(int argc, char **argv) {
    int a[] = {1, 2, 3, 4};
    std::array<int, 5> arrays = {1, 2, 3, 4, 5};
    // 正向迭代
    for (auto it = arrays.begin(); it != arrays.end(); ++it) {
        std::cout << ' ' << *it << std::endl;
    }
    // 反向迭代
    for (auto rit = arrays.rbegin(); rit < arrays.rend(); ++rit) {
        std::cout << ' ' << *rit << std::endl;
    }

    system("pause");
    return 0;
}
