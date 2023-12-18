
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <utility>
#include <vector>

template <typename T, template <typename> class Container>
void test_container(Container<T> container)
{
    srand(time(NULL));
    for (auto &item : container) {
        std::cout << item;
    }
    for (int i = 0; i < 100; i++) {
        container.insert(container.end(), T(i));
        std::cout << *(container.end() - 1);
    }
}

class MyValueType {
public:
    MyValueType()
    {
        this->name = "default";
    }
    MyValueType(std::string name)
    {
        this->name = std::move(name);
    }
    MyValueType(int i)
    {
        this->name = std::to_string(i);
    }
    friend std::ostream &operator<<(std::ostream &os, const MyValueType &p);  // 声明operator<<为友元函数
private:
    std::string name;
};

std::ostream &operator<<(std::ostream &out, const MyValueType &p)
{
    out << p.name + " ";
    return out;
}

// template template parameter
template <typename T, template <class> class Container>
class XCls {
public:
    XCls()
    {
        for (auto &item : container) {
            std::cout << item;
        }
        for (int i = 0; i < 100; i++) {
            container.insert(container.end(), T(i));
            std::cout << *(container.end() - 1);
        }
    }

private:
    Container<T> container;
};

class B {
public:
    int b;
};
class C : private B {
public:
    using B::b;
    C()
    {
        this->b = 1;
    }
};

// alias template
template <typename T>
using Vec = std::vector<T, std::allocator<T>>;

void test(int i, int j) {}

int main(int argc, char **argv)
{
    MyValueType value("开始");
    std::vector<MyValueType> a {value};

    test_container<MyValueType, Vec>(a);
    XCls<MyValueType, Vec> c;

    using func = void (*)(int, int);
    func fn = test;
    fn(1, 2);

    C c1;
    c1.b;

    system("pause");
    return 0;
}
