#include <algorithm>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <ostream>
int main(int argc, char **argv) {
    std::deque<int> q;                         // 空队列
    std::deque<int> s(4, 100);                 // 4个100
    std::deque<int> iters(s.begin(), s.end()); // 迭代构造拷贝
    std::deque<int> c(iters);                  // 拷贝构造

    int myints[] = {1, 2, 3, 4};
    std::deque<int> fifth(
        myints, myints + sizeof(myints) / sizeof(int)); // 迭代构造拷贝 arrays

    for (std::deque<int>::iterator it = fifth.begin(); it != fifth.end();
         ++it) {
        std::cout << ' ' << *it << std::endl;
    }

    fifth.push_back(10);

    std::for_each(fifth.begin(), fifth.end(), [&](const int &index) {
        std::cout << index << ",";
        if (&index == &fifth.back()) { std::cout << std::endl; }
    });

    fifth.pop_back();

    fifth.push_back(5);
    fifth.push_front(0);

    for (std::deque<int>::iterator it = fifth.begin(); it != fifth.end();
         ++it) {
        std::cout << *it << ",";
    }

    // system("pause");
    return 0;
}
