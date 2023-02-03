
// 策略模式
// 抽象武器
#include <iostream>
#include <ostream>
class WeaponStrategy {
  public:
    virtual void UseWeapon() = 0;
};

// 匕首
class Knife : public WeaponStrategy {
  public:
    void UseWeapon() override { std::cout << "使用匕首" << std::endl; }
};

class AK47 : public WeaponStrategy {
  public:
    void UseWeapon() override { std::cout << "使用AK47" << std::endl; }
};

// 策略使用对象
class Character {
  public:
    WeaponStrategy *pWeapon;
    void setWeapon(WeaponStrategy *pWeapon) { this->pWeapon = pWeapon; }

    void ThrowWeapon() { this->pWeapon->UseWeapon(); }
};

int main() {
    Character *c = new Character;
    WeaponStrategy* knife = new Knife;
    WeaponStrategy* ak47 = new AK47;

    c->setWeapon(knife);
    c->ThrowWeapon();

    c->setWeapon(ak47);
    c->ThrowWeapon();
    return 0;
}