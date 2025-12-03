
#include <chrono>
#include <iostream>
#include <future>
#include <ostream>

int main() {
    std::promise<void> ready_promise, t1_ready_promise, t2_ready_promise;
    std::shared_future<void> ready_future(ready_promise.get_future());

    std::chrono::time_point<std::chrono::high_resolution_clock> start;

    auto fun = [&,
                ready_future]() -> std::chrono::duration<double, std::milli> {
        t1_ready_promise.set_value();
        ready_future.wait();
        return std::chrono::high_resolution_clock::now() - start;
    };

    auto fun1 = [&,
                 ready_future]() -> std::chrono::duration<double, std::milli> {
        t2_ready_promise.set_value();
        ready_future.wait();
        return std::chrono::high_resolution_clock::now() - start;
    };

    auto result = std::async(std::launch::async, fun);

    auto result1 = std::async(std::launch::async, fun1);

    t1_ready_promise.get_future().wait();
    t2_ready_promise.get_future().wait();

    start = std::chrono::high_resolution_clock::now();

    ready_promise.set_value();

    std::cout << "Thread 1 received the signal " << result.get().count()
              << " ms after start. "
              << "Thread2 received the signal " << result1.get().count()
              << " ms after start." << std::endl;

    return 0;
}