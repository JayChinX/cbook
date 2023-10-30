
#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <list>
#include <ostream>
int main(int argc, char **argv) {
    std::list<int> values;

    // 每个元素的值都为相应类型的默认值（int类型的默认值为 0）。
    std::list<int> a(10);

    //创建一个包含 n 个元素的 list 容器，并为每个元素指定初始值
    std::list<int> b(10, 5);

    //拷贝函数创建
    std::list<int> c(values);

    // 过拷贝其他类型容器（或者普通数组）中指定区域内的元素，可以创建新的 list
    // 容器
    //拷贝普通数组，创建list容器
    int l[] = {1, 2, 3, 4, 5};
    std::list<int> d(l, l + 5);
    //拷贝其它类型的容器，创建 list 容器
    std::array<int, 5> arr = {11, 12, 13, 14, 15};
    std::list<int> e(arr.begin() + 2, arr.end()); //拷贝arr容器中的{13,14,15}
    std::for_each(e.begin(), e.end(), [&](const int &i) {
        std::cout << i << (&i == &e.back() ? "" : ",");
        if (&i == &e.back()) { std::cout << std::endl; }
    });
    system("pause");
    return 0;
}
