
#include <iostream>
#include <ostream>
class Context {
  public:
    Context(int num) : m_num(num) {}

    void setNum(int num) { this->m_num = num; }
    int getNum() { return m_num; }

    void setRes(int res) { this->m_res = res; }
    int getRes() { return m_res; }

  private:
    int m_num;
    int m_res;
};

class Expression {
  public:
    virtual void interpreter(Context *context) = 0;
};

class PlusExpression : public Expression {
  public:
    void interpreter(Context *context) override {
        int num = context->getNum();
        ++num;
        context->setNum(num);
        context->setRes(num);
    }
};

class MinusExpression : public Expression {
  public:
    void interpreter(Context *context) override {
        int num = context->getNum();
        --num;
        context->setNum(num);
        context->setRes(num);
    }
};

int main(int argc, char **argv) {
    Context *pCxt = new Context(10);
    Expression *pExp = new PlusExpression();

    pExp->interpreter(pCxt);
    std::cout << "PlusExpression: " << pCxt->getRes() << std::endl;

    Expression *pExp1 = new MinusExpression();
    pExp1->interpreter(pCxt);
    std::cout << "MinusExpression: " << pCxt->getRes() << std::endl;

    delete pCxt;
    delete pExp;
    delete pExp1;

    system("pause");
    return 0;
}
