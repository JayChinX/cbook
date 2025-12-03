
#include <iostream>
#include <ostream>
#include <string>
class Monkey {
  public:
    Monkey() {}

    virtual ~Monkey() {}
    virtual Monkey *Clone() = 0;
    virtual void Play() = 0;
};

class SunWuKong : public Monkey {
  public:
    SunWuKong(std::string name) : m_name(name) {}
    ~SunWuKong() {}

    // 实现深拷贝的关键
    SunWuKong(const SunWuKong &other) {
        // 将成员都拷贝一份
        m_name = other.m_name;
    }

    Monkey *Clone() override { return new SunWuKong(*this); }

    void Play() override { std::cout << m_name << ":金箍棒" << std::endl; }

  private:
    std::string m_name;
};

int main() {
    Monkey *monkey = new SunWuKong("齐天大圣孙悟空");

    Monkey *m1 = monkey->Clone();
    Monkey *m2 = m1->Clone();

    m1->Play();
    m2->Play();

    delete monkey;
    delete m1;
    delete m2;
    return 0;
}