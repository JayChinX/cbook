// variadic template(c++11) 数量不定的模板参数

#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>
#include <tuple>
#include <vector>

// 参数个数  参数个数逐一递减
// 参数类型  参数类型逐一递减

// 3. 终止函数
template<typename T>
void _hash(size_t &seed, const T &val) {
    std::cout << "hash over " << val << std::endl;
}

// 2. 展开函数，把参数分为一个普通函数和一个参数包，调用一次，参数包大小就减一
template<typename T, typename... Args>
void _hash(size_t &seed, const T &val, const Args &...args) {
    std::cout << "parameter " << val << std::endl;
    // 递归调用自己
    _hash(seed, args...); // 如果不加 T 参数，递归成死循环
}

// 1. 泛化
template<typename... Args>
size_t _hash(const Args &...args) {
    std::cout << "hash start " << std::endl;
    size_t seed = 0;
    // 递归调用自己
    _hash(seed, args...);
    return seed;
}

template<typename... Args>
class A {
  private:
    int size = 0;

  public:
    A() {
        size = sizeof...(Args);
        std::cout << size << std::endl;
    }
};

int main(int argc, char **argv) {
    size_t f = 10;
    _hash("asdas", 2, 3, 4);
    A<int, std::string, std::vector<int>> a;

    // tuple 就是利用这个特性的变长参数模板
    std::tuple<int, std::string> t = std::make_tuple(1, "hha");
    int firstArg = std::get<0>(t);
    std::string secondArg = std::get<1>(t);

    std::cout << firstArg << " " << secondArg << std::endl;

    system("pause");
    return 0;
}
