
#include <iostream>
#include <list>
#include <ostream>

// 抽象观察者
class AbstractHero {
  public:
    virtual void Update() = 0;
};

class HeroA : public AbstractHero {
  public:
    HeroA() { std::cout << "英雄A正在撸BOSS" << std::endl; }

    void Update() override {
        std::cout << "英雄A停止撸BOSS，待机状态" << std::endl;
    }
};

class HeroB : public AbstractHero {
  public:
    HeroB() { std::cout << "英雄B正在撸BOSS" << std::endl; }

    void Update() override {
        std::cout << "英雄B停止撸BOSS，待机状态" << std::endl;
    }
};

class HeroC : public AbstractHero {
  public:
    HeroC() { std::cout << "英雄C正在撸BOSS" << std::endl; }

    void Update() override {
        std::cout << "英雄C停止撸BOSS，待机状态" << std::endl;
    }
};

// 抽象观察目标
class AbstractBoss {
  public:
    virtual void addHero(AbstractHero *hero) = 0;
    virtual void deleteHero(AbstractHero *hero) = 0;
    virtual void notify() = 0;
};

class BossA : public AbstractBoss {
  public:
    void addHero(AbstractHero *hero) override { p_hero_list.push_back(hero); }
    void deleteHero(AbstractHero *hero) override { p_hero_list.remove(hero); }
    void notify() override {
        for (auto &it : p_hero_list) { it->Update(); }
    }

  private:
    std::list<AbstractHero *> p_hero_list;
};

int main() {
    AbstractHero *heroA = new HeroA;
    AbstractHero *heroB = new HeroB;
    AbstractHero *heroC = new HeroC;

    AbstractBoss *bossA = new BossA;
    bossA->addHero(heroA);
    bossA->addHero(heroB);
    bossA->addHero(heroC);

    std::cout << "heroC阵亡" << std::endl;
    bossA->deleteHero(heroC);

    std::cout << "Boss死了，通知其他英雄停止攻击......" << std::endl;
    bossA->notify();
}