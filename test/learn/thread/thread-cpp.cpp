
#include <iostream>
#include <thread>

void fun(int tid)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "Launched by thread " << tid << ", id = " << std::this_thread::get_id() << std::endl;
}
int main()
{
    std::thread t[5];  // 线程数组
    for (int i = 0; i < 5; ++i) {
        t[i] = std::thread(fun, i);
    }

    for (int i = 0; i < 5; ++i) {
        t[i].join();
        std::cout << "Main: completed thread id: " << i << std::endl;
    }

    std::thread t1(fun, 10);

    t1.join();

    return 0;
}