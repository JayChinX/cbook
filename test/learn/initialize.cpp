

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

    std::string getName()
    {
        return this->name;
    }

    uint16_t operator+(uint16_t age)
    {
        this->age = this->age + age;
        return this->age;
    }

    uint16_t operator()()
    {
        return this->age;
    }
};

struct Man {
    Fr fr;
    int age;
};

int main()
{
    Fr f("赵乐乐", 18);
    f + 10;
    f.show();

    Fr c = {"赵乐乐", 10};  // 初始化列表
    Man man = {f, f()};
    std::cout << "man fr: name" << man.fr.getName() << ", age" << man.age << std::endl;
}