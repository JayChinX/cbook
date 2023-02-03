#include <iostream>
#include <ostream>
#include <string>
#include <vector>

//建造者模式实现步骤

// 1.提供抽象建造者类: 为创建产品各个部分，统一抽象接口

// 2.提供具体建造者类：具体实现抽象建造者各个部件的接口

// 3.提供多个具体产品类:具体的创建产品的各个部分

// 4.提供一个指挥类：负责安排和调度复杂对象的各个建造过程

// 抽象产品
// 电脑组装：显示器、鼠标、键盘、主机
class AbstractProduct {
  public:
    virtual void
    setDisplayer(const std::string &displayer) = 0; // = 0 表示纯虚构函数
    virtual void setMouse(const std::string &mouse) = 0;
    virtual void setKeyBoard(const std::string &keyBoard) = 0;
    virtual void setHost(const std::string &host) = 0;
    virtual void show() = 0;
};

// 具体产品
// 台式机组装
class Computer : public AbstractProduct {
    void setDisplayer(const std::string &displayer) override {
        std::cout << "正在安装: " << displayer << std::endl;
        m_list.push_back(displayer);
    }

    void setMouse(const std::string &mouse) override {
        std::cout << "正在安装: " << mouse << std::endl;
        m_list.push_back(mouse);
    }

    void setKeyBoard(const std::string &keyBoard) override {
        std::cout << "正在安装: " << keyBoard << std::endl;
        std::cout << keyBoard << "没有库存" << std::endl;
        std::string tKeyBoard = "罗技键盘";
        std::cout << "用 " << tKeyBoard << " 替代" << std::endl;
        m_list.push_back(tKeyBoard);
    }

    void setHost(const std::string &host) override {
        std::cout << "正在安装: " << host << std::endl;
        m_list.push_back(host);
    }

    void show() override {
        std::cout << "电脑组装结果: " << std::endl;
        for (auto t : m_list) { std::cout << t << std::endl; }
    }

  private:
    // 配置表
    std::vector<std::string> m_list;
};

// 抽象建造者
class AbstractBuilder {
  public:
    AbstractBuilder(AbstractProduct *product) : product(product) {}

    virtual void buildDisplayer(const std::string &displayer) = 0;
    virtual void buildMouse(const std::string &mouse) = 0;
    virtual void buildKeyBoard(const std::string &keyBoard) = 0;
    virtual void buildHost(const std::string &host) = 0;

    AbstractProduct *getProduct() { return product; }

  protected:
    AbstractProduct *product;
};

// 具体建造者
// 技术员
class ConcreteComputerBuilder : public AbstractBuilder {
  public:
    ConcreteComputerBuilder() : AbstractBuilder(new Computer) {}
    void buildDisplayer(const std::string &displayer) override {
        product->setDisplayer(displayer);
    }

    void buildMouse(const std::string &mouse) override {
        product->setMouse(mouse);
    }

    void buildKeyBoard(const std::string &keyBoard) override {
        product->setKeyBoard(keyBoard);
    }

    void buildHost(const std::string &host) override { product->setHost(host); }
};

// 电脑部件
struct ComputerComponent {
    std::string displayer;
    std::string mouse;
    std::string keyBoard;
    std::string host;
};

class Director {
  public:
    Director(AbstractBuilder *pBuilder) : pBuilder(pBuilder) {}

    AbstractProduct *createProduct(const ComputerComponent &component) {
        pBuilder->buildDisplayer(component.displayer);
        pBuilder->buildMouse(component.mouse);
        pBuilder->buildKeyBoard(component.keyBoard);
        pBuilder->buildHost(component.host);

        return pBuilder->getProduct();
    }

  private:
    AbstractBuilder *pBuilder;
};

int main() {
    auto *pD = new Director(new ConcreteComputerBuilder);
    AbstractProduct *computer = pD->createProduct(
        {"三星显示器", "牧马人鼠标", "雷蛇键盘", "外星人主机"});
    computer->show();
    return 0;
}