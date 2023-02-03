// 装饰器模式
//装饰器模式:对类的功能进行扩展（代替继承）。可以动态的给类增加功能

#include <iostream>
#include <ostream>
#include <string>
class AbstractComponent {
    public:
    virtual void show() = 0;
    std::string pstr;
};

class Girl : public AbstractComponent {
    public:
    Girl() {
        this->pstr = "漂亮的女孩";
    }
    void show() override {
        std::cout << pstr << std::endl;
    }
};

class AbstractDecorate : public AbstractComponent {
    public:
    void show() override  = 0;

    protected:
    AbstractComponent* pbase;
};

// 超短裙装饰
class MiniSkirt : public AbstractDecorate {
    public:
    MiniSkirt(AbstractComponent* pbase) {
        this->pbase = pbase;
    }
    void show() override {
        this->pstr = pbase->pstr + " 穿超短裙";
        std::cout << pstr << std::endl;
    }
};

// 穿黑丝
class BlackSilk : public AbstractDecorate {
    public:
    BlackSilk(AbstractComponent* pbase) {
        this->pbase = pbase;
    }
    void show() override {
        this->pstr = pbase->pstr + " 穿黑丝";
        std::cout << pstr << std::endl;
    }
};

int main() {
    AbstractComponent* pg = new Girl;
    pg->show();

    pg = new MiniSkirt(pg);
    pg->show();

    pg = new BlackSilk(pg);
    pg->show();
    
    return 0;
}