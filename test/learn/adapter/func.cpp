
#include <iostream>
#include <ostream>
#include <vector>

class func {
public:
    int operator()(const int &a, const int &b)
    {
        printf("%d ", a + b);
        return a + b;
    }
};

int main(int argc, char **argv)
{
    std::vector<int> args = {1, 2, 3, 4};
    for (auto &item : args) {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    args.push_back(5);
    args.push_back(6);

    for (auto &item : args) {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    args.pop_back();

    // while 迭代器
    auto iter = args.begin();
    while (iter != args.end()) {
        std::cout << *iter << " ";
        iter++;
    }
    std::cout << std::endl;

    // 反向迭代
    auto riter = args.rbegin();
    while (riter != args.rend()) {
        std::cout << *riter << " ";
        riter++;
    }

    std::cout << std::endl;

    std::for_each(args.begin(), args.end(), std::bind(func(), std::placeholders::_1, 2));

    std::cout << std::endl;

    for (auto it = args.begin(); it != args.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    // 小于4的数量
    int i = std::count_if(args.begin(), args.end(), std::bind2nd(std::less<int>(), 4));
    std::cout << i;
    std::cout << std::endl;
    int j = std::count_if(args.begin(), args.end(), std::not1(std::bind2nd(std::less<int>(), 4)));
    std::cout << j;

    std::cout << std::endl;

    // 输入迭代器
    // std::copy(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), std::inserter(args, args.end()));

    // 输出迭代器
    std::copy(args.begin(), args.end(), std::ostream_iterator<int>(std::cout, " "));
    // std::cout << std::endl;
    return 0;
}
