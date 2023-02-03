// 组合实体模式

#include <algorithm>
#include <iostream>
#include <list>
#include <ostream>
class Component {
  public:
    Component() = default;
    virtual ~Component() {};
    virtual void Operation() = 0;
    virtual void Add(Component *pChild){};
    virtual void Remove(Component *pChild){};
    virtual Component *GetChild(int index) { return nullptr; };
};

class Leaf : public Component {
  public:
    Leaf() = default;
    ~Leaf() override = default;
    void Operation() override {
        std::cout << "Operation by leaf" << std::endl;
    };
};

class Composite : public Component {
  public:
    Composite() = default;
    ~Composite() override {
        std::list<Component *>::iterator iter1, iter2, temp;
        for (iter1 = m_listOfComponent.begin(), iter2 = m_listOfComponent.end();
             iter1 != iter2;) {
            temp = iter1;
            ++iter1;
            delete (*temp);
        }
    };
    void Operation() override {
        std::cout << "Operation by Composite" << std::endl;
        std::list<Component *>::iterator iter1, iter2;
        for (iter1 = m_listOfComponent.begin(), iter2 = m_listOfComponent.end();
             iter1 != iter2; ++iter1) {
            (*iter1)->Operation();
        }
    }
    void Add(Component *pChild) override {
        m_listOfComponent.push_back(pChild);
    }
    void Remove(Component *pChild) override {
        std::list<Component *>::iterator iter;
        iter = std::find(
            m_listOfComponent.begin(), m_listOfComponent.end(), pChild);
        if (m_listOfComponent.end() != iter) { m_listOfComponent.erase(iter); }
    }

    Component *GetChild(int index) override {
        if (index <= 0 || index > m_listOfComponent.size()) { return nullptr; }
        std::list<Component *>::iterator iter1, iter2;
        int i;
        for (i = 1, iter1 = m_listOfComponent.begin(),
            iter2 = m_listOfComponent.end();
             iter1 != iter2; ++iter1, ++i) {
            if (i == index) { break; }
        }
        return *iter1;
    }

  private:
    std::list<Component *> m_listOfComponent;
};

int main() {
    Leaf *pLeaf1 = new Leaf;
    Leaf *pLeaf2 = new Leaf;
    Composite *pCom = new Composite;
    pCom->Add(pLeaf1);
    pCom->Add(pLeaf2);
    pCom->Operation();
    pCom->GetChild(2)->Operation();
    return 0;
}
