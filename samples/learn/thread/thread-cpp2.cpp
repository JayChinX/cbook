
#include <functional>
#include <iostream>
#include <mutex>
#include <ostream>
#include <thread>

class Number {
private:
    int num;

public:
    Number()
    {
        num = 1;
    }
    explicit Number(int a) : num(a) {}
    int getNum()
    {
        return this->num;
    }
    void setNum(int num)
    {
        this->num = num;
    }
};

std::mutex mutex;  // 实例化mutex

class Worker {
public:
    void test(Number &number)
    {
        // RALL
        // 用此语句替换了m.lock()；lock_guard传入一个参数时，该参数为互斥量，此时调用了lock_guard的构造函数，申请锁定mutex
        std::lock_guard<std::mutex> g1(mutex);
        int num = number.getNum();
        std::cout << "This num is " << num << ". threadId = " << std::this_thread::get_id() << std::endl;
        number.setNum(++num);
        // mutex.unlock(); // 此时不需要写mutex.unlock(),g1出了作用域被释放，自动调用析构函数，于是mutex被解锁
    }
};
int main()
{
    Number *number = new Number(1);
    Worker *work = new Worker();

    std::thread thd {&Worker::test, work, std::ref(*number)};
    std::thread thd1 {&Worker::test, work, std::ref(*number)};
    std::thread thd2 {&Worker::test, work, std::ref(*number)};
    std::thread thd3 {&Worker::test, work, std::ref(*number)};

    thd.join();
    thd1.join();
    thd2.join();
    thd3.join();

    delete number;
    delete work;

    return 0;
}