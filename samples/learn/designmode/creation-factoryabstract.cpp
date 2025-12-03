
// 创建型模式-抽象工厂模式
// 定义：定义一个创建产品对象的工厂接口，将实际的创建工作推迟到子类当中

// 核心工厂类不在负责产品的创建，这样核心工厂类成为一个抽象工厂的角色，仅负责具体工厂子类必须实现的接口。
// 这样进一步抽象化的好处是使得工厂方法模式可以使系统不在修改具体工厂角色的情况下引进新的产品。

// 抽象工厂角色：工厂方法的核心，任何工厂类都必须实现这个接口
// 具体工厂角色：具体工厂是抽象工厂的一个实现，负责实例化产品对象
// 抽象角色... 具体产品角色...

//工厂模式与简单工厂模式在结构上的不同不是很明显，工厂方法类的核心是一个抽象工厂类，而简单工厂模式把核心放在一个具体的类上。

// 工厂方法模式之所以有一个别名叫多态型工厂模式是因为具体工厂类都是共同的接口或者有共同的抽象父类。

// 当系统扩展需要添加新的产品对象时，仅仅需要添加一个具体对象以及一个具体工厂对象，原有工厂对象不需要进行任何修改，也不需要修改客户端，很好的符合了
// -
// 开放封闭-原则。而简单工厂模式再添加新产品对象后不得不修改工厂方法，扩展性不好。工厂模式退化后可演变成简单工厂模式。

// 开放－封闭，通过添加代码的方式，不是通过修改代码的方式完成功能的增强

// 特点 :不需要修改源代码就可以实现新工能的添加

#include <cstddef>
#include <iostream>
#include <ostream>
class Fruit {
  public:
    virtual void getFruit(void) const = 0;
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

class AbstractFactory {
  public:
    virtual Fruit *createProduct(void) const = 0;

    virtual ~AbstractFactory() = default;
};

class BananaFactory : public AbstractFactory {
  public:
    Fruit *createProduct() const override { return new Banana; }
};

class AppleFactory : public AbstractFactory {
  public:
    Fruit *createProduct() const override { return new Apple; }
};

/**
 */

class Peer : public Fruit {
  public:
    void getFruit() const override { std::cout << "I'm peer." << std::endl; }
};

class PeerFactory : public AbstractFactory {
  public:
    Fruit *createProduct() const override { return new Peer; }
};

int main(int argc, char *const argv[]) {
    AbstractFactory *f = NULL;
    Fruit *fruit = NULL;

    f = new BananaFactory;
    fruit = f->createProduct();
    fruit->getFruit();
    delete f;
    delete fruit;

    f = new AppleFactory;
    fruit = f->createProduct();
    fruit->getFruit();
    delete f;
    delete fruit;

    // 扩展
    std::cout<< "Extern product peer."<< std::endl;
    f = new PeerFactory;
    fruit = f->createProduct();
    fruit->getFruit();
    delete f;
    delete fruit;

    std::cout<< "Simple factory test."<< std::endl;


    return 0;
}