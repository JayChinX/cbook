
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

double test(Number &number) {
    int num = number.getNum();
    std::cout << "This num is " << num
              << ". threadId = " << std::this_thread::get_id() << std::endl;
    number.setNum(++num);
    return number.getNum();
}
int main() {
    Number *number = new Number(1);

    std::future<double> fu = std::async(test, std::ref(*number));
    std::cout << "Future get value = " << fu.get() << std::endl;

    delete number;

    return 0;
}