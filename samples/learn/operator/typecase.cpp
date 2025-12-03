
#include <iostream>
#include <ostream>
class Circle {
  public:
    Circle(double x1, double y1, double r1) {
        this->x = x1;
        this->y = y1;
        this->r = r1;
    }
    operator int() { return int(r); }
    operator double() { return 2 * 3.14 * r; }
    operator float() { return (float)3.14 * r * r; }

  private:
    double x, y, r;
};

int main(int argc, char **argv) {
    Circle c(2.3, 4.2, 2.5);

    int r = c; // 调用operator int()，将Circle类型转换成int

    double l = c; //调用operator double()，转换成double

    double len = (double)c;

    std::cout << "r: " << r << ", l: " << l << ", len: " << len << std::endl;

    system("pause");
    return 0;
}
