
#include <iostream>
#include <utility>
class BoyInterface {
public:
    BoyInterface(std::string name) : name(std::move(name)) {}
    virtual void eat() const = 0;
    virtual void wash() const
    {
        std::cout << "boy wash" << std::endl;
    }
    virtual void sleep() const
    {
        std::cout << "boy sleep" << std::endl;
    }

protected:
    std::string name;
};

class YoungBoy : private BoyInterface {
public:
    using BoyInterface::name;
    YoungBoy(std::string name) : BoyInterface(std::move(name)) {}
    void eat() const override
    {
        std::cout << "young boy " << this->name << " eat" << std::endl;
    }

    void wash() const override
    {
        std::cout << "young boy wash" << std::endl;
    }

    void sleep() const override
    {
        std::cout << "young boy sleep" << std::endl;
        this->BoyInterface::sleep();
    }
};

int main(int argc, char **argv)
{
    YoungBoy boy("xiao ming");
    boy.eat();
    boy.wash();
    boy.sleep();
    std::cout << "boy name is " << boy.name;

    system("pause");
    return 0;
}
