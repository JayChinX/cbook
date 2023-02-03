// 对象适配器方式

#include <iostream>
#include <ostream>
class ThreeOutlet {
  public:
    void ThreeOutletCharge() {
        std::cout << "开始三插座充电......" << std::endl;
    }
};

class AbstractTwoOutlet {
  public:
    virtual void TwoOutletCharge() = 0;
};

class TwoOutlet : public AbstractTwoOutlet {
  public:
    void TwoOutletCharge() override {
        std::cout << "开始二插座充电......" << std::endl;
    }
};

// 对象适配器
class OutletAdapter : public AbstractTwoOutlet {
  public:
    OutletAdapter(ThreeOutlet *pout) : pout(pout) {}

    void TwoOutletCharge() override {
        Convertor();
        pout->ThreeOutletCharge();
    }

    void Convertor() {
        std::cout << "三插头转换为二插头后:" << std::endl;
        TwoOutlet *t = new TwoOutlet;
        t->TwoOutletCharge();
    }

    ThreeOutlet *pout;
};

int main() {
    ThreeOutlet *pThree = new ThreeOutlet;
    AbstractTwoOutlet *pTwo = new OutletAdapter(pThree);
    pTwo->TwoOutletCharge();
    return 0;
}