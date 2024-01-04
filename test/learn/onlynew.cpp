
#include <iostream>
class HeapOnly {
public:
    // 2. 提供一个获取对象的接口，并且该接口必须设置为静态成员函数
    static HeapOnly *CreateObj()
    {
        return new HeapOnly();
    }

    int getNum()
    {
        this->i += 1;
        return this->i;
    }
    ~HeapOnly()
    {
        std::cout << "heap only free" << std::endl;
        this->i = -1;
    }

private:
    int i = -1;
    // 1. 将构造函数设置为私有
    HeapOnly() : i(0) {}
    // 3. 将拷贝构造函数设置为私有，并且只声明不实现
    // C++98
    // HeapOnly(const HeapOnly &);
    // C++11
    HeapOnly(const HeapOnly &) = delete;
};

class Heap {
public:
    Heap() : i(0) {}
    int getNum()
    {
        this->i += 1;
        return this->i;
    }
    ~Heap()
    {
        std::cout << "heap free" << std::endl;
        this->i = -1;
    }

private:
    int i = -1;
};

int main(int argc, char **argv)
{
    HeapOnly *ho = HeapOnly::CreateObj();
    delete ho;

    if (ho != nullptr) {
        std::cout << "ho's i: " << ho->getNum() << std::endl;
    }

    ho = nullptr;

    if (ho == nullptr) {
        std::cout << "ho is null" << std::endl;
    }

    Heap *heap = new Heap();
    delete heap;

    if (heap != nullptr) {
        std::cout << "heap's i: " << heap->getNum() << std::endl;
    }

    heap = nullptr;

    if (heap == nullptr) {
        std::cout << "heap is null" << std::endl;
    }

    return 0;
}
