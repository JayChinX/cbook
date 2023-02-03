
// 模板模式

// 做饮料模版
#include <iostream>
#include <ostream>
class DrinkTemplate {
  public:
    //煮水
    virtual void BoiledWater() = 0;
    // 冲泡
    virtual void Brew() = 0;
    // 倒入瓶中
    virtual void PourInCup() = 0;
    // 加辅料
    virtual void AddSomething() = 0;

    // 模板方法
    void Make() {
        BoiledWater();
        Brew();
        PourInCup();
        AddSomething();
    }
};

// 咖啡
class Coffee : public DrinkTemplate {
    void BoiledWater() override { std::cout << "煮山泉水" << std::endl; }

    void Brew() override { std::cout << "冲泡咖啡" << std::endl; }

    void PourInCup() override { std::cout << "咖啡倒入杯中" << std::endl; }

    void AddSomething() override { std::cout << "加糖，加牛奶" << std::endl; }
};

// 茶
class Tea : public DrinkTemplate {
    void BoiledWater() override { std::cout << "煮自来水" << std::endl; }

    void Brew() override { std::cout << "冲泡铁观音" << std::endl; }

    void PourInCup() override { std::cout << "咖啡倒入杯中" << std::endl; }

    void AddSomething() override { std::cout << "加糖，加大蒜" << std::endl; }
};

int main() {
    Tea *tea = new Tea;
    tea->Make();

    Coffee* coffee = new Coffee;
    coffee->Make();
    return 0;
}