
#include <cstring>
#include <iostream>
#include <ostream>
struct Person {
    double salary; // 工资
    char *name;    // 姓名
};

class SalaryManager {
  public:
    SalaryManager(int max = 0) : max(max), n(0), employ(new Person[max]) {}
    ~SalaryManager() { delete[] employ; }

    // 返回引用特性是可以直接放在左值，直接使用
    double &operator[](char *name) {
        // 重载 [] 返回应用
        Person *p;
        for (p = employ; p < employ + n; ++p) {
            // 如果存在返回
            if (strcmp(p->name, name) == 0) { return p->salary; }
        }
        // 不存在
        p = employ + n++;
        p->name = new char[strlen(name) + 1];
        strcpy(p->name, name);
        p->salary = 0;
        return p->salary;
    }

    void display() {
        for (int i = 0; i < n; ++i) {
            std::cout << employ[i].name << "  " << employ[i].salary
                      << std::endl;
        }
    }

  private:
    Person *employ; // 存放职工信息的数组
    int max;        // 数组的下标上界
    int n;          // 人数
};

int main(int argc, char **argv) {
    SalaryManager s(3);
    s["张三"] = 2188.88;
    s["李四"] = 1234.88;
    s["王五"] = 3200.88;

    std::cout << "张三\t" << s["张三"] << std::endl;
    std::cout << "李四\t" << s["李四"] << std::endl;
    std::cout << "王五\t" << s["王五"] << std::endl;

    std::cout << "-------下为display的输出--------\n\n";
    s.display();

    system("pause");
    return 0;
}
