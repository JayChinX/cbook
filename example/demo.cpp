#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#define Max 1000
using namespace std;
class admin
{
public:
    char name[100];
    char num[100];
    char tel[100];
    char name1[100];
    char adress[100];
};
typedef struct londe
{
    admin data;
    struct londe *next;
} londe, *strlonde;
void londecreat(strlonde &L, int n)
{
    L = (strlonde)malloc(sizeof(londe));
    L->next = NULL;
    strlonde p, q;
    q = L;
    int i = 0;
    cout << "请您依次输入图书编号，图书名，图书作者，图书出版社，价格" << endl;
    for (i = 0; i < n; i++)
    {
        p = (strlonde)malloc(sizeof(londe));
        cin >> p->data.name;
        cin >> p->data.num;
        cin >> p->data.tel;
        cin >> p->data.name1;
        cin >> p->data.adress;
        p->next = NULL;
        q->next = p;
        q = p;
    }
    ofstream ofs;
    ofs.open("text.txt", ios::out);
    strlonde S;
    S = L->next;
    while (S)
    {
        ofs << S->data.name << " " << S->data.num << " " << S->data.tel << " " << S->data.name1 << " " << S->data.adress << " " << endl;
        S = S->next;
    }
    ofs.close();
}
void display(strlonde &L)
{
    ifstream ifs;
    ifs.open("text.txt", ios::in);
    char buf[10000] = {0};
    int i = 0;
    cout << "下面是您录入的信息" << endl;
    while (ifs >> buf)
    {
        if (i % 5 == 0)
        {
            cout << endl;
        }
        cout << buf << " ";
        i++;
    }
    ifs.close();
}
void findname(char *arr)
{
    char a[100];
    strcpy(a, arr);
    ifstream ifs;
    ifs.open("text.txt", ios::in);
    char buf[1000] = {0};
    int i = 0;
    while (ifs >> buf)
    {
        int n = strcmp(a, buf);
        if (n == 0)
        {
            cout << buf << " ";
            i++;
            continue;
        }
        if (i > 5)
        {
            return;
        }
        if (i <= 5 && i >= 1)
        {
            cout << buf << " ";
            i++;
        }
    }
    ifs.close();
}
void findnum(char *arr)
{
    char a[100];
    strcpy(a, arr);
    ifstream ifs;
    ifs.open("text.txt", ios::in);
    char buf[10000] = {0};
    int i = 0;
    while (ifs >> buf)
    {
        if (i == 3)
        {
            cout << buf << " ";
            return;
        }
        if (i == 2)
        {
            cout << buf << " ";
            i++;
        }
        if (i == 1)
        {
            cout << buf << " ";
            i++;
        }
        int n = strcmp(a, buf);
        if (n == 0)
        {
            cout << buf << " ";
            i++;
        }
    }
    ifs.close();
}
void delete1(strlonde &L, char *arr)
{
    char a[100], b[100];
    int i = 0, j = 0, count = 0;
    strcpy(a, arr);
    while (*arr != '\0')
    {
        count++;
        arr++;
    }
    strlonde p, q, r;
    q = L;
    p = L->next;
    while (p != NULL)
    {
        strcpy(b, p->data.name);
        i = 0, j = 0;
        while (a[i] == b[j] && a[i] != '\0' && b[j] != '\0')
        {
            i++;
            j++;
        }
        if (i == count)
        {
            r = p;
            while (q)
            {
                while (q->next == r)
                {
                    q->next = q->next->next;
                    free(r);
                    cout << "删除图书信息成功！" << endl;
                    ofstream ofs;
                    ofs.open("text.txt", ios::out);
                    strlonde S;
                    S = L->next;
                    while (S)
                    {
                        ofs << S->data.name << " " << S->data.num << " " << S->data.tel << " " << S->data.name1 << " " << S->data.adress << " " << endl;
                        S = S->next;
                    }
                    ofs.close();
                    return;
                }
                q = q->next;
            }
        }
        p = p->next;
    }
}
void insert(strlonde &L, char *arr, char *arr2, char *arr3, char *arr4, char *arr5, char *arr6)
{
    strlonde p, q, s;

    char a[100], b[100];
    int count = 0, i = 0, j = 0;
    s = (strlonde)malloc(sizeof(londe));
    strcpy(s->data.name, arr3);
    strcpy(s->data.num, arr2);
    strcpy(s->data.tel, arr4);
    strcpy(s->data.name1, arr5);
    strcpy(s->data.adress, arr6);
    strcpy(a, arr);
    while (*arr != '\0')
    {
        count++;
        arr++;
    }
    q = L;
    p = L->next;
    while (p != NULL)
    {
        strcpy(b, p->data.name);
        i = 0, j = 0;
        while (a[i] == b[j] && a[i] != '\0' && b[j] != '\0')
        {
            i++;
            j++;
        }
        if (i == count)
        {
            while (q)
            {
                while (q->next == p)
                {
                    q->next = s;
                    s->next = p;
                    cout << "插入成功" << endl;
                    ofstream ofs;
                    ofs.open("text.txt", ios::out);
                    strlonde S;
                    S = L->next;
                    while (S)
                    {
                        ofs << S->data.name << " " << S->data.num << " " << S->data.tel << " " << S->data.name1 << " " << S->data.adress << " " << endl;
                        S = S->next;
                    }
                    ofs.close();
                    return;
                }
                q = q->next;
            }
        }
        p = p->next;
    }
}
void modify(strlonde &L, char *arr, char *arr1, char *arr2, char *arr3, char *arr4, char *arr5)
{
    char a[100], b[100];
    strcpy(a, arr);
    strlonde p;
    int count = 0, i = 0, j = 0;
    while (*arr != '\0')
    {
        count++;
        arr++;
    }
    p = L->next;
    while (p)
    {
        strcpy(b, p->data.name);
        i = 0, j = 0;
        while (a[i] == b[j] && a[i] != '\0' && b[j] != '\0')
        {
            i++;
            j++;
        }
        if (i == count)
        {
            strcpy(p->data.num, arr1);
            strcpy(p->data.name, arr2);
            strcpy(p->data.tel, arr3);
            strcpy(p->data.name1, arr4);
            strcpy(p->data.adress, arr5);
            cout << "修改成功" << endl;
            ofstream ofs;
            ofs.open("text.txt", ios::out);
            strlonde S;
            S = L->next;
            while (S)
            {
                ofs << S->data.name << " " << S->data.num << " " << S->data.tel << " " << S->data.name1 << " " << S->data.adress << " " << endl;
                S = S->next;
            }
            ofs.close();
            return;
        }
        p = p->next;
    }
}
void menu()
{
    cout << "\t\t\t******************************************************************" << endl;
    cout << "\t\t\t*******************欢迎光临图书管理系统***************************" << endl;
    cout << "\t\t\t****************    1.输入-1  退出程序         *******************" << endl;
    cout << "\t\t\t****************    2.输入1   录入信息         *******************" << endl;
    cout << "\t\t\t****************    3.输入2   陈列信息         *******************" << endl;
    cout << "\t\t\t****************    4.输入3   按编号查找       *******************" << endl;
    cout << "\t\t\t****************    5.输入4   按书名查找       *******************" << endl;
    cout << "\t\t\t****************    6.输入5   删除             *******************" << endl;
    cout << "\t\t\t****************    7.输入6   插入             *******************" << endl;
    cout << "\t\t\t****************    8.输入7   修改             *******************" << endl;
    cout << "\t\t\t******************************************************************" << endl;
}
int main()
{
    strlonde L;
    char arr[100], arr2[100], arr4[100], arr5[100], arr6[100], arr7[100], arr8[100], arr9[100], arr10[100], arr11[100], arr12[100], arr13[100], arr14[100], arr15[100], arr16[100];
    int n = 0;
    int x = 0;
    menu();
    while (cin >> x)
    {
        if (x < 0)
        {
            break;
        }
        switch (x)
        {
        case 1:
            cout << "现在开始录入信息，请输入您要录入几本书的信息" << endl;
            cin >> n;
            londecreat(L, n);
            cout << "录入完成" << endl;
            break;
        case 2:
            display(L);
            break;
        case 3:
            cout << "请输入您要进行查找的图书的编号" << endl;
            cin >> arr;
            findname(arr);
            break;
        case 4:
            cout << "请输入您要进行查找图书名" << endl;
            cin >> arr2;
            findnum(arr2);
            break;
        case 5:
            cout << "请输入您要删除图书的编号" << endl;
            cin >> arr4;
            delete1(L, arr4);
            break;
        case 6:
            cout << "请输入您要进行插入地方图书的编号以及插入的图书编号，图书名，图书作者，图书出版社，价格" << endl;
            cin >> arr5 >> arr6 >> arr7 >> arr8 >> arr13 >> arr14;
            insert(L, arr5, arr6, arr7, arr8, arr13, arr14);
            break;
        case 7:
            cout << "请输入您要进行修改的用户的编号以及您需要修改的信息" << endl;
            cin >> arr9 >> arr10 >> arr11 >> arr12 >> arr15 >> arr16;
            modify(L, arr9, arr10, arr11, arr12, arr15, arr16);
            break;
        default:
            cout << "您的输入有误，请重新输入" << endl;
        }
    }
    return 0;
}