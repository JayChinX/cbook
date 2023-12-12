
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

template <typename T>
using Vec = std::vector<T, std::allocator<T>>;

int main(int argc, char **argv)
{
    MyValueType value("开始");
    std::vector<MyValueType> a {value};

    test_container<MyValueType, Vec>(a);
    system("pause");
    return 0;
}
