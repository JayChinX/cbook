// 条件锁

#include <iostream>
#include <mutex>
#include <thread>
int main(int argc, char **argv)
{
    // 两个线程交替打印 100 内的奇偶数
    int n = 100;

    std::mutex mtx;
    std::condition_variable cv;  // 条件变量

    bool flag = true;  // true 打印奇数 ， false 打印偶数

    // 奇数
    std::thread t1([&] {
        int i = 1;
        while (i <= 100) {
            std::unique_lock<std::mutex> ul(mtx);  // 加锁

            // 当 pred 为 false 时阻塞等待唤醒。 当唤醒后先判断 pred 条件是否满足，不满足则继续阻塞等待
            cv.wait(ul, [&flag]() -> bool { return flag; });

            std::cout << std::this_thread::get_id() << ":" << i << std::endl;
            i += 2;
            flag = false;     // 打印偶数
            cv.notify_one();  // 唤醒条件变量下等待的一个线程
        }
    });

    // 偶数
    std::thread t2([&] {
        int j = 2;
        while (j <= 100) {
            std::unique_lock<std::mutex> ul(mtx);
            // 当 pred 为 false 时阻塞等待唤醒。 当唤醒后先判断 pred 条件是否满足，不满足则继续阻塞等待
            cv.wait(ul, [&flag]() -> bool { return !flag; });
            std::cout << std::this_thread::get_id() << ":" << j << std::endl;
            j += 2;
            flag = true;      // 打印奇数
            cv.notify_one();  // 唤醒条件变量
        }
    });

    t1.join();
    t2.join();

    system("pause");
    return 0;
}
