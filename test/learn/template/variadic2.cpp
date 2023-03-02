

#include <bitset>
#include <iostream>
#include <ostream>
#include <string>
#include <tuple>

template<int IDX, int MAX, typename... Args>
struct print_tuple {
    static void print(std::ostream &os, const std::tuple<Args...> &t) {
        os << std::get<IDX>(t) << (IDX + 1 == MAX ? "" : ",");
        print_tuple<IDX + 1, MAX, Args...>::print(os, t);
    }
};

// 特化结束操作
template<int MAX, typename... Args>
struct print_tuple<MAX, MAX, Args...> {
    static void print(std::ostream &os, const std::tuple<Args...> &t) {}
};

template<typename... Args>
std::ostream &operator<<(std::ostream &os, const std::tuple<Args...> &t) {
    os << "[";
    print_tuple<0, sizeof...(Args), Args...>::print(os, t);
    return os << "]";
}

int main(int argc, char **argv) {
    std::cout << std::make_tuple(
        7.5, std::string("hello"), std::bitset<16>(377), 47)
              << std::endl;

    system("pause");
    return 0;
}
