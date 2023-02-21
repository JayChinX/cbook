
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <ios>
#include <iostream>
#include <ostream>
#include <vector>
class Person {
  public:
    Person() {}
    Person(char *n, char *pid, int Age, char *Addr) {
        strcpy(name, n);
        strcpy(id, pid);
        age = Age;
        strcpy(addr, Addr);
    }
    void display() {
        std::cout << name << "\t" << id << "\t" << age << "\t" << addr
                  << std::endl;
    }
    char name[20];
    char id[18];
    int age;
    char addr[20];
};

int main(int argc, char **argv) {
    char ch;

    // 输出到文件，写操作
    std::ofstream out("./person.txt", std::ios::out | std::ios::app);

    char name[20], id[18], addr[20];
    int age;

    std::cout << "------输入个人档案------" << std::endl << std::endl;
    do {
        std::cout << "姓名：";
        std::cin >> name;
        std::cout << "身份证号：";
        std::cin >> id;
        std::cout << "年龄：";
        std::cin >> age;
        std::cout << "地址：";
        std::cin >> addr;

        Person per(name, id, age, addr);
        // 获取 per 的内存空间 / 空间大小
        // out.write((char *)&per, sizeof(per));

        out << per.name << ' ' << per.id << ' ' << per.age << ' ' << per.addr
            << std::endl;

        std::cout << "Enter another Person(y/n)?";
        std::cin >> ch;
    } while (ch == 'y');

    out.close();

    // 输入到屏幕，读
    std::ifstream in("./person.txt", std::ios::in);

    // Person s;
    // in.read((char *)&s, sizeof(s));

    // std::vector<Person> v;
    // std::vector<Person>::iterator iter;

    char buf[10000] = {0};

    int i = 0;
    while (in >> buf) {
        // v.push_back(s);
        // in.read((char *)&s, sizeof(s));
        std::cout << buf << ' ';
        i++;
        if (i % 4 == 0) { std::cout << std::endl; }
    }

    std::cout << "\n-----------从文件中读出的数据" << std::endl;
    // iter = v.begin();

    // for (iter = v.begin(); iter != v.end(); ++iter) { iter->display(); }

    system("pause");
    return 0;
}
