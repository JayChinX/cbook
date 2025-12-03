
// 遍历算法
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <ostream>
#include <vector>
int main(int argc, char **argv)
{
    std::vector<int> vc {1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 12};

    std::vector<int> vc1 {1, 2, 3, 14, 5, 6, 7, 8, 9, 10, 11};

    // 遍历
    std::for_each(vc.begin(), vc.end(), [&](int &item) { printf("%d ", item); });

    // 遍历 比较两个序列，返回第一个不匹配的元素，pair
    auto m = std::mismatch(vc.begin(), vc.end(), vc1.begin());
    printf("first: %d, second: %d \n", *m.first, *m.second);

    // 遍历 比较两个序列，返回第一个不匹配的元素，pair，比较方法自定义，返回不符合的
    auto m1 =
        std::mismatch(vc.begin(), vc.end(), vc1.begin(), [&](int &first, int &second) { return first <= second; });
    printf("first: %d, second: %d \n", *m1.first, *m1.second);

    std::vector<int> vc2(vc1);

    // 遍历 比较两个序列，是否相等
    bool eq = std::equal(vc1.begin(), vc1.end(), vc2.begin());

    printf("vc1 == vc2 %d \n", eq);

    bool eq1 = std::equal(vc.begin(), vc.end(), vc2.begin());

    printf("vc == vc2 %d \n", eq1);

    // 遍历 比较两个序列，比较方法自定义
    bool eq2 = std::equal(vc.begin(), vc.end(), vc2.begin(), [&](int &first, int &second) { return first < second; });

    printf("vc == vc2 %d \n", eq2);

    std::fill(vc.begin(), vc.end(), 1);

    std::for_each(vc.begin(), vc.end(), [&](int &item) { printf("%d ", item); });

    std::cout << std::endl;
    std::generate(vc.begin(), vc.end(), [&]() -> int { return 2; });
    std::for_each(vc.begin(), vc.end(), [&](int &item) { printf("%d ", item); });
    std::cout << std::endl;

    // 输入迭代器
    std::vector<int> vc3(vc2.size());
    std::copy(vc2.begin(), vc2.end(), vc3.begin());

    std::for_each(vc3.begin(), vc3.end(), [&](int &item) { printf("%d ", item); });
    std::cout << std::endl;

    std::vector<int> vc4(4);
    std::copy_n(vc2.begin(), 4, vc4.begin());

    std::for_each(vc4.begin(), vc4.end(), [&](int &item) { printf("%d ", item); });
    std::cout << std::endl;

    std::vector<int> vc5(vc2.size());
    std::move(vc2.begin(), vc2.end(), vc5.begin());

    std::cout << "vc2:" << std::endl;

    std::for_each(vc2.begin(), vc2.end(), [&](int &item) { printf("%d ", item); });
    std::cout << std::endl;
    std::cout << "vc5:" << std::endl;
    std::for_each(vc5.begin(), vc5.end(), [&](int &item) { printf("%d ", item); });
    std::cout << std::endl;

    std::vector<int> vector {1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 12};

    std::vector<int> vector1 {11, 12, 13, 14, 15, 16, 17, 18, 19, 10, 11};

    std::iter_swap(vector.begin(), vector1.begin());

    std::cout << "vector:" << std::endl;
    std::for_each(vector.begin(), vector.end(), [&](int &item) { printf("%d ", item); });
    std::cout << std::endl;
    std::cout << "vector1:" << std::endl;
    std::for_each(vector1.begin(), vector1.end(), [&](int &item) { printf("%d ", item); });
    std::cout << std::endl;

    std::swap_ranges(vector.begin(), vector.end(), vector1.begin());

    std::cout << "vector:" << std::endl;
    std::for_each(vector.begin(), vector.end(), [&](int &item) { printf("%d ", item); });
    std::cout << std::endl;
    std::cout << "vector1:" << std::endl;
    std::for_each(vector1.begin(), vector1.end(), [&](int &item) { printf("%d ", item); });
    std::cout << std::endl;

    auto ter = std::find(vector1.begin(), vector1.end(), 0);

    if (ter != vector1.end()) {
        printf("find ele: %d \n", *ter);
    } else {
        printf("ele not find\n");
    }

    system("pause");
    return 0;
}
