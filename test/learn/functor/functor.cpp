
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
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

class AverageValue {
  public:
    AverageValue() : sum(0), num(0) {}

    void operator()(int elem) {
        sum += elem;
        num++;
    }

    double value() {
        // return sum * 1.0 / num;
        return static_cast<double>(sum * 1.0 / num);
    }

  private:
    int num;
    int sum;
};

int main(int argc, char **argv) {
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
    system("pause");
    return 0;
}
