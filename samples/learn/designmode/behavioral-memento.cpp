
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

class Memento {
  public:
    // explicit 避免隐式转换
    explicit Memento(const std::string &state) : state(state) {}
    std::string getState() const { return state; }

  private:
    std::string state;
};

class Originator {
  public:
    std::string getState() const { return state; }
    void setState(const std::string &state) { this->state = state; }

    Memento saveStateMemento() { return Memento(state); }
    void getStateFormMemento(Memento memento) { state = memento.getState(); }

  private:
    std::string state;
};

class Caretaker {
  public:
    void add(Memento memento) { memento_list.push_back(memento); }

    Memento get(int index) { return memento_list.at(index); }

  private:
    std::vector<Memento> memento_list;
};

int main() {
    // 当前状态
    Originator originator;
    // 状态保存-备忘录
    Caretaker caretaker;
    // TODO

    //
    originator.setState("状态1，攻击力100");
    std::cout << "当前的状态：" << originator.getState() << std::endl;
    // 保存当前状态
    caretaker.add(originator.saveStateMemento());

    // 受到debuff，攻击力下降
    std::cout << "受到debuff，攻击力下降" << std::endl;
    originator.setState("状态2，攻击力为80");
    // 保存状态
    caretaker.add(originator.saveStateMemento());

    std::cout << "当前的状态：" << originator.getState() << std::endl;
    std::cout << "debuff时间结束，回到状态1" << std::endl;

    originator.getStateFormMemento(caretaker.get(0));
    std::cout << "恢复到状态1后的状态：" << originator.getState() << std::endl;
    return 0;
}
