
#include <atomic>
#include <iostream>
#include <future>
#include <ostream>
#include <thread>

std::atomic<int> a{0};

void test(void) {
    for (int i = 0; i < 100000; ++i) { ++a; }
}
int main() {
    std::thread thd{test};
    std::thread thd1{test};

    thd.join();
    thd1.join();

    std::cout << "a = " << a << std::endl;

    return 0;
}