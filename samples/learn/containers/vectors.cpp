

#include <algorithm>
#include <iostream>
#include <ostream>
#include <vector>

int main(int argc, char **argv)
{
    // 列表初始化
    std::vector<double> a {1, 2, 3, 4, 5, 6, 7, 8, 9};
    // 获取大小
    std::cout << "a size = " << a.size() << std::endl;

    // 构造函数
    std::vector<double> values(20, 1.0);
    // at 访问
    std::cout << "values index 4 = " << values.at(4) << std::endl;

    // 尾插
    a.push_back(10);
    std::cout << "a size = " << a.size() << std::endl;

    // 插入
    values.insert(values.begin(), 2.0);
    std::cout << "values index 0 = " << values.at(0) << std::endl;

    // for_each 遍历 lambda
    std::for_each(values.begin(), values.end(), [=](const double index) { std::cout << index << ", "; });

    std::cout << " -> values" << std::endl;

    std::for_each(a.begin(), a.end(), [](const double &index) { std::cout << index << ", "; });

    std::cout << " -> a" << std::endl;

    // 输出迭代器
    std::copy(values.begin(), values.end(), std::ostream_iterator<double>(std::cout, ", "));

    return 0;
}
