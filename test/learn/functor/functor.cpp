
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <ostream>
#include <set>

#define MACRO_FUNC()       \
    {                      \
        printf("Hello\n"); \
        printf("World\n"); \
    }

#define MAC_FUNC(args)               \
    {                                \
        printf("hello hello hello"); \
        printf("hello");             \
    }

#define p()                \
    do {                   \
        printf("Hello\n"); \
        printf("World\n"); \
    } while (0)

#define macro(x) \
    do {         \
        x += 2;  \
        x += 1;  \
    } while (0)

class AverageValue {
public:
    AverageValue() = default;

    void operator()(int elem)
    {
        sum += elem;
        num++;
    }

    double value()
    {
        // return sum * 1.0 / num;
        return static_cast<double>(sum * 1.0 / num);
    }

private:
    int num = 0;
    int sum = 0;
};

int main(int argc, char **argv)
{
    std::set<int> sets;
    sets.insert(1);
    sets.insert(2);
    sets.insert(3);
    sets.insert(4);
    sets.insert(5);

    sets.insert(6);

    AverageValue a = std::for_each(sets.begin(), sets.end(), AverageValue());
    std::cout << "value: " << a.value() << std::endl;

    MACRO_FUNC();
    p();
    int c = 1;
    macro(c);

    std::cout << c << std::endl;

    system("pause");
    return 0;
}
