#include <cstring>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>
#include "books.h"
#include "book.h"

#define MAX 1000

using namespace std;  // 使用 std的作用域

// 书库类型结构体 in stack //结构体类型定义语法
using Cir = struct Circulation {
    /* data */
    Book data;
    struct Circulation *next;
};
using PCir = Cir *;  // 结构体变量 Circulation类型的 变量 cir, Cir类型的指针变量 strCir,

// 创建书库
void creatCir(PCir &L, int n)
{
    // 开辟内存 sizeof 计算一个指定类型的大小
    L = (PCir)malloc(sizeof(Cir));  // 返回指针，指向一段可用内存的起始地址
    L->next = nullptr;              // 初始化 next 为NULL
    PCir p, q;                      // 尾节点指针q  尾节点的下一个指针 p
    q = L;                          // 链表节点初始化完成

    // 格式输出
    // IO操作符 cout << 向屏幕输出
    cout << "请你依次输入图书编号，图书名，图书作者，图书出版社，价格" << endl;

    for (int i = 0; i < n; i++) {
        // 返回指针
        Cir cir;   // 生成一个新的节点
        p = &cir;  // 关联尾节点
        // IO 操作符 cin 抽取操作符(从屏幕输入抽取)
        cout << "请输入图书编号: " << ends;
        cin >> p->data.id;

        cout << "请输入图书名: " << ends;
        cin >> p->data.name;

        cout << "请输入图书作者: " << ends;
        cin >> p->data.author;

        cout << "请输入图书出版社: " << ends;
        cin >> p->data.press;

        cout << "请输入图书价格: " << ends;
        cin >> p->data.price;

        //
        p->next = nullptr;
        q->next = p;  // 与链表关联
        q = p;        // 尾节点移动
    }

    // 写入文件
    ofstream ofs;
    ofs.open("text.txt", ios::app);  // 写入权限
    // 链表
    PCir s;
    s = L->next;
    while (s) {
        ofs << s->data.id << " " << s->data.name << " " << s->data.author << " " << s->data.press << " "
            << s->data.price << " " << endl;
        s = s->next;
    }
    ofs.close();
}

// 显示录入的信息
void display(PCir &L)
{
    ifstream ifs;
    ifs.open("text.txt", ios::in);
    char buf[10000] = {0};
    int i = 0;
    cout << "下面是你录入的信息:" << endl;
    while (ifs >> buf) {
        if (i % 5 == 0) {
            cout << endl;
        }
        cout << buf << " ";
        i++;
    }
    ifs.close();
}

// 查找id
void findById(char *arr)
{
    char id[100];
    strcpy(id, arr);  // copy id 信息
    ifstream ifs;
    ifs.open("text.txt", ios::in);
    char buf[1000] = {0};
    int i = 0;
    while (ifs >> buf) {
        // 函数strcmp的功能是比较两个字符串的大小。也就是把字符串str1和str2从首字符开始逐个字符的进行比较，直到某个字符不相同或者其中一个字符串比较完毕才停止比较
        // n == 0 表示相等
        int n = strcmp(id, buf);
        if (n == 0) {
            cout << "查找到图书信息:" << endl;
            cout << buf << " " << ends;
            i++;
            continue;
        }
        if (i >= 5) {
            cout << endl;
            return;
        }
        if (i < 5 && i >= 1) {
            cout << buf << " " << ends;
            i++;
        }
    }
    if (i == 0) {
        cout << "编号不存在！！！" << endl;
    }

    ifs.close();
}

void findByName(char *arr)
{
    char a[100];
    strcpy(a, arr);
    ifstream ifs;
    ifs.open("text.txt", ios::in);
    char buf[10000] = {0};
    int i = 0;
    Book *pbook = new Book();
    while (ifs >> buf) {
        if (i % 5 == 0) {
            pbook->id = buf;
        } else if (i % 5 == 1) {
            pbook->name = buf;
        } else if (i % 5 == 2) {
            pbook->author = buf;
        } else if (i % 5 == 3) {
            pbook->press = buf;
        } else if (i % 5 == 4) {
            pbook->price = buf;
        }
        if (i % 5 == 4) {
            int n = strcmp(a, pbook->name.data());
            if (n == 0) {
                i = 0;
                cout << "查找到图书信息:" << endl;
                cout << pbook->id << " " << pbook->name << " " << pbook->author << " " << pbook->press << " "
                     << pbook->price << " " << endl;
                break;
            }
            free(pbook);
            pbook = new Book();
        }
        i++;
    }
    if (i != 0) {
        cout << "图书不存在！！！" << endl;
    }
    ifs.close();
}

void deleteById(char *arr)
{
    char a[100];
    strcpy(a, arr);

    ifstream ifs;
    ifs.open("text.txt", ios::in);

    ofstream ofs;
    ofs.open("temp.txt", ios::app | ios::trunc);

    char buf[10000] = {0};
    int i = 0;
    bool deleted = false;
    Book *pbook = new Book();
    while (ifs >> buf) {
        if (i % 5 == 0) {
            pbook->id = buf;
        } else if (i % 5 == 1) {
            pbook->name = buf;
        } else if (i % 5 == 2) {
            pbook->author = buf;
        } else if (i % 5 == 3) {
            pbook->press = buf;
        } else if (i % 5 == 4) {
            pbook->price = buf;
        }
        if (i % 5 == 4) {
            int n = strcmp(a, pbook->id.data());
            if (n == 0) {
                deleted = true;
            } else {
                // 不相等，输出到临时文件
                ofs << pbook->id << " " << pbook->name << " " << pbook->author << " " << pbook->press << " "
                    << pbook->price << " " << endl;
            }
            free(pbook);
            pbook = new Book();
        }
        i++;
    }
    ifs.close();
    ofs.close();
    remove("text.txt");
    rename("temp.txt", "text.txt");

    cout << (deleted ? "删除成功" : "图书不存在！！！") << endl;
}

// 插入
void insert(PCir &L, char *arr, Book *book)
{
    PCir p, q, s;
}

// 修改
void modify(PCir &L, char *arr, Book *book) {}

void menu()
{
    cout << "*****************************" << endl;
    cout << "******欢迎光临图书管理系统******" << endl;
    cout << "******  1. 输入1  退出程序  ******" << endl;
    cout << "******  2. 输入2  录入信息  ******" << endl;
    cout << "******  3. 输入3  陈列信息  ******" << endl;
    cout << "******  4. 输入4  按编号查找 ******" << endl;
    cout << "******  5. 输入5  按书名查找 ******" << endl;
    cout << "******  6. 输入6  删除     ******" << endl;
    cout << "******  7. 输入7  插入     ******" << endl;
    cout << "******  8. 输入8  修改     ******" << endl;
    cout << "*****************************" << endl;
}

void start()
{
    menu();
    int x = 0;
    while (cin >> x) {
        if (x == 1) {
            break;
        }

        switch (x) {
            case 2: {  // 录入信息
                int n = 0;
                PCir L;
                cout << "开始录入信息，请输入你要录入几本书的信息:" << endl;
                cin >> n;
                creatCir(L, n);
                cout << "录入完毕!" << endl;
                break;
            }
            case 3: {
                // 陈列信息
                PCir L;
                display(L);
                break;
            }
            case 4: {  // 依据 id 查找信息
                char id[100];
                cout << "请输入你要查找的图书编号:" << endl;
                cin >> id;
                findById(id);
                break;
            }
            case 5:
                // 依据 name 查找信息
                char name[100];
                cout << "请输入你要查找的图书名:" << endl;
                cin >> name;
                findByName(name);
                break;
            case 6: {  // 删除信息
                char id[100];
                cout << "请输入您要删除图书的编号:" << endl;
                cin >> id;
                deleteById(id);
                break;
            }
            case 7: {  // 插入信息
                char id[100];
                Book book;
                PCir L;
                cout << "请输入您要进行插入地方图书的编号以及插入的图书编号，图书名，图"
                        "书作者，图书出版社，价格"
                     << endl;
                cin >> id >> book.id >> book.name >> book.author >> book.press >> book.price;
                insert(L, id, &book);
                break;
            }
            case 8: {  // 修改信息
                char id[100];
                Book book;
                PCir L;
                cout << "请输入您要进行修改的用户的编号以及您需要修改的信息" << endl;
                cin >> book.id >> book.name >> book.author >> book.press >> book.price;
                modify(L, id, &book);
            } break;
            default:
                cout << "你的输入有误，请重新输入" << endl;
        }
    }

    return;
}
