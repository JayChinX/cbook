
#include <array>
#include <cstdlib>
#include <iostream>
#include <ostream>

int main(int argc, char **argv)
{
    int a[] = {1, 2, 3, 4};
    std::array<int, 5> arrays = {1, 2, 3, 4, 5};

    // 正向迭代
    for (auto it = arrays.begin(); it != arrays.end(); ++it) {
        std::cout << ' ' << *it;
    }
    std::cout << std::endl;
    // 反向迭代
    for (auto rit = arrays.rbegin(); rit < arrays.rend(); ++rit) {
        std::cout << ' ' << *rit;
    }
    std::cout << std::endl;
    // 常量迭代器
    for (auto it = arrays.cbegin(); it != arrays.cend(); ++it) {
        std::cout << ' ' << *it;
    }
    std::cout << std::endl;

    // 元素填充
    std::array<int, 10> arr;
    arr.fill(0);
    for (int it : arr) {
        std::cout << ' ' << it;
    }
    std::cout << std::endl;

    std::array<int, 5> arr1;
    arr1.fill(-1);
    // 两个 array 交换
    arr1.swap(arrays);

    for (int it : arr1) {
        std::cout << ' ' << it;
    }
    std::cout << std::endl;
    for (int it : arrays) {
        std::cout << ' ' << it;
    }
    std::cout << std::endl;

    printf("%d ", arr1.at(2));
    printf("%d ", arr1[3]);

    system("pause");
    return 0;
}
