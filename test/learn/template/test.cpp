

// 函数模版
#include <cstring>
#include <iostream>
#include <ostream>
template<typename T>
T compareMax(T t1, T t2) {
    return t1 > t2 ? t1 : t2;
}

// 特化
template<>
const char *compareMax<const char *>(const char *s1, const char *s2) {
    std::cout << "[for debug]"
              << " call compareMax template" << std::endl;
    return strcmp(s1, s2) >= 0 ? s1 : s2;
}

int main(int argc, char **argv) {
    std::cout << compareMax(1, 2) << std::endl;
    std::cout << compareMax("asda", "qwer") << std::endl;

    system("pause");
    return 0;
}
