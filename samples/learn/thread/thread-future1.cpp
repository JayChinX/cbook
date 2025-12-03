
#include <functional>
#include <iostream>
#include <future>

class Number {
  private:
    int num;

  public:
    Number() { num = 1; }
    explicit Number(int a) : num(a) {}
    int getNum() { return this->num; }
    void setNum(int num) { this->num = num; }
};

class Worker {
  public:
    int test(Number &number) {
        int num = number.getNum();
        std::cout << "This num is " << num
                  << ". threadId = " << std::this_thread::get_id() << std::endl;
        number.setNum(++num);
        return num;
    }
};
int main() {
    Number *number = new Number(1);
    Worker *work = new Worker();

    std::future<int> fu0 = std::async(&Worker::test, work, std::ref(*number));

    // lambda 表达式
    std::future<void> fu = std::async([&] {
        std::cout << "This async is running"
                  << ". threadId = " << std::this_thread::get_id() << std::endl;
    });
    std::cout << "Future0 get value = " << fu0.get() << std::endl;
    fu.wait();

    delete work;
    delete number;

    return 0;
}