
#include <atomic>
#include <chrono>
#include <iostream>
#include <future>
#include <iterator>
#include <map>
#include <ostream>
#include <thread>

std::atomic<bool> b_end{false};

void test(void) {
    std::cout << "thread start" << std::endl;
    std::chrono::microseconds dur{1000};
    while (!b_end) {
        std::cout << "Thread id " << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(dur);
    }
    std::cout << "thread begin" << std::endl;
}
int main() {
    std::cout << "main start" << std::endl;
    std::thread thd{test};

    std::this_thread::sleep_for(std::chrono::microseconds(50000));
    b_end = true;
    thd.join();
    std::cout << "main end" << std::endl;


    return 0;
}