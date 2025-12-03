
#include <iostream>
#include <ostream>
#include "thread_pool/ThreadPool.h"
int main(int argc, char **argv)
{
    ThreadPool tp(5);
    auto f = tp.submit(
        [&](int i) {
            std::cout << "thread id:" << std::this_thread::get_id() << ", i: " << i << std::endl;
            return i;
        },
        1);

    auto f1 = tp.submit(
        [&](int i) {
            std::cout << "thread id:" << std::this_thread::get_id() << ", i: " << i << std::endl;
            return i;
        },
        2);

    auto f2 = tp.submit(
        [&](int i) {
            std::cout << "thread id:" << std::this_thread::get_id() << ", i: " << i << std::endl;
            return i;
        },
        3);

    auto f3 = tp.submit(
        [&](int i) {
            std::cout << "thread id:" << std::this_thread::get_id() << ", i: " << i << std::endl;
            return i;
        },
        4);

    tp.init();

    auto fr = f.get();
    auto f1r = f1.get();
    auto f2r = f2.get();
    auto f3r = f3.get();
    std::cout << "f: " << fr << ", f1: " << f1r << ", f2: " << f2r << ", f3: " << f3r << std::endl;
    // f.get();
    // f1.get();
    // f2.get();
    // f3.get();
    tp.shutdown();

    std::packaged_task<std::string(std::string)> task([&](std::string name) -> std::string { return name; });
    auto result = task.get_future();
    // task("");
    std::thread th(std::move(task), "arg");  // 执行函数

    std::cout << "result: " << result.get() << std::endl;
    th.join();  // 回收资源
    system("pause");
    return 0;
}
