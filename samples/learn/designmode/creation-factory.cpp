
// 创建型模式-简单工厂模式（静态工厂方法模式）
// 定义：通过专门定义一个类来负责创建其他类的实例，被创建的实例通常具有共同的父类。

// 工厂角色：简单工厂模式的核心，负责实现创建所有实例的内部逻辑。工厂可以被外界直接调用，创建所需的产品对象。
// 抽象角色：简单工厂模式所创建的所有对象的父类，负责描述所有实例所共有的公共接口。
// 具体产品角色：简单工厂模式所创建的具体实例对象

// 简单工厂模式的优缺点
// 在简单工厂模式中，工厂类是整个魔偶是的关键所在。它包含必要的判断逻辑，能够根据外界给定的信息，决定究竟应该创建哪个具体类的对象。用户在使用的时候，可以直接根据工厂类去创建所需的实例，而无需了解这些对象是如何创建以及如何组织的。有利于整个软件体系结构的优化。
// 不难发现，简单工厂模式的有点也体现在工厂类上，由于工厂类集中了所有实例创建的逻辑，所以高内聚方面做的不好，
// 另外，当系统中的具体产品类不断增多时，可能出现要求工厂也要做响应的修改，扩展性不好

// 抽象类
#include <iostream>
#include <string>
class Fruit {
  public:
    // 抽象方法
    virtual void getFruit(void) const = 0;
    // 析构函数动态绑定
    virtual ~Fruit() = default;
};

class Banana : public Fruit {
  public:
    void getFruit() const override { std::cout << "I'm banana." << std::endl; }
};

class Apple : public Fruit {
  public:
    void getFruit() const override { std::cout << "I'm apple." << std::endl; }
};

class Factory final{
  public:
    Fruit *createFruit(std::string &pstr) {
        if (0 == pstr.compare("banana")) {
            return new Banana;
        } else if (0 == pstr.compare("apple")) {
            return new Apple;
        } else {
            std::cout << "Factory not support." << std::endl;
        }
        return NULL;
    }
};

int main(int argc, char const *argv[]) {
    Factory *f = new Factory;
    Fruit *fruit = NULL;
    std::string bananastr("banana");
    std::string applestr("apple");

    fruit = f->createFruit(bananastr);
    if (NULL != fruit) {
        fruit->getFruit();
        delete fruit;
    }

    fruit = f->createFruit(applestr);
    if (NULL != fruit) {
        fruit->getFruit();
        delete fruit;
    }

    delete f;
    std::cout << "Simple factory test." << std::endl;
    return 0;
}