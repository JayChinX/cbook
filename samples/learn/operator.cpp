

#include <iostream>
#include <ostream>
#include <string>
#include <stdint.h>

class Fr {
    // friend void operator+(Fr &f, uint16_t age);

private:
    std::string name;
    uint16_t age;

public:
    Fr(std::string name, uint16_t age) : name(name), age(age) {}

    void show()
    {
        std::cout << "姓名：" << name << ", 年龄：" << age << std::endl;
    }

    uint16_t operator+(uint16_t age)
    {
        this->age = this->age + age;
        return this->age;
    }
};

int main()
{
    Fr f("赵乐乐", 18);
    Fr c = {"", 10};  // 初始化列表
    f + 10;
    f.show();
}