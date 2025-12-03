
#include <iostream>
#include <list>
class Man;
class Woman;

class Action {
  public:
    virtual void getManResult(Man *man) = 0;
    virtual void getWomanResult(Woman *woman) = 0;
};

class Success : public Action {
  public:
    void getManResult(Man *man) override {
        std::cout << "男人给的评价该歌手很成功" << std::endl;
    }
    void getWomanResult(Woman *woman) override {
        std::cout << "女人给的评价该歌手很成功" << std::endl;
    }
};
class Fail : public Action {
  public:
    void getManResult(Man *man) override {
        std::cout << "男人给的评价该歌手是失败" << std::endl;
    }
    void getWomanResult(Woman *woman) override {
        std::cout << "女人给的评价该歌手是失败" << std::endl;
    }
};

class Person {
  public:
    virtual void accept(Action *action) = 0;
};

class Man : public Person {
  public:
    void accept(Action *action) override { action->getManResult(this); }
};

class Woman : public Person {
  public:
    void accept(Action *action) override { action->getWomanResult(this); }
};

class ObjectStructure {
  public:
    void attach(Person *p) { persons.push_back(p); }
    void detach(Person *p) { persons.remove(p); }
    void display(Action *action) {
        for (auto person : persons) { person->accept(action); }
    }

  private:
    std::list<Person *> persons;
};

int main() {
    Man man;
    Woman woman;
    ObjectStructure objectStructure;
    objectStructure.attach(&man);
    objectStructure.attach(&woman);

    Success *success = new Success;

    objectStructure.display(success);

    std::cout << "=======================" << std::endl;

    Fail *fail = new Fail;
    objectStructure.display(fail);
    return 0;
}