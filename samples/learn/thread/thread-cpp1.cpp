
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
        mutex.lock();  // 加锁，对临界代码多公共资源的存取进行保护
        int num = number.getNum();
        std::cout << "This num is " << num << ". threadId = " << std::this_thread::get_id() << std::endl;
        number.setNum(++num);
        mutex.unlock();
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