
#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
class Iterator {
  public:
    Iterator(){};
    virtual ~Iterator(){};
    virtual std::string First() = 0;
    virtual std::string Next() = 0;
    virtual std::string CurrentItem() = 0;
    virtual bool IsDone() = 0;
};

class Aggregate {
  public:
    virtual int Count() = 0;
    virtual void Push(const std::string &strValue) = 0;
    virtual std::string Pop(const int index) = 0;
    virtual Iterator *CreateIterator() = 0;
};

class ConcreteIterator : public Iterator {
  public:
    ConcreteIterator(Aggregate *aggregate)
        : appregate(aggregate), current(0), Iterator(){};

    std::string First() override { return appregate->Pop(0); }

    std::string Next() override {
        std::string strRet;
        current++;
        if (current < appregate->Count()) { strRet = appregate->Pop(current); }
        return strRet;
    }

    std::string CurrentItem() override { return appregate->Pop(current); }

    bool IsDone() override {
        return current >= appregate->Count() ? true : false;
    }

  private:
    Aggregate *appregate;
    int current;
};

class ConcreteAggregate : public Aggregate {
  public:
    ConcreteAggregate() : pIt(nullptr) { items.clear(); }
    ~ConcreteAggregate() {
        if (nullptr != pIt) {
            delete pIt;
            pIt = nullptr;
        }
    }

    Iterator *CreateIterator() override {
        if (nullptr == pIt) { pIt = new ConcreteIterator(this); }
        return pIt;
    }

    int Count() override { return items.size(); }

    void Push(const std::string &strValue) override {
        items.push_back(strValue);
    }

    std::string Pop(const int index) override {
        std::string strRet;
        if (index < Count()) { strRet = items.at(index); }
        return strRet;
    }

  private:
    std::vector<std::string> items;
    Iterator *pIt;
};

int main(int argc, char **argv) {
    ConcreteAggregate *p = nullptr;
    p = new ConcreteAggregate;

    if (nullptr != p) {
        p->Push("Hello");
        p->Push("World");
        p->Push("CPP");
    }
    Iterator *iter = nullptr;
    iter = p->CreateIterator();
    if (nullptr != iter) {
        std::string strItem = iter->First();
        while (!iter->IsDone()) {
            std::cout << iter->CurrentItem() << " is ok." << std::endl;
            iter->Next();
        }
    }

    system("pause");
    return 0;
}
