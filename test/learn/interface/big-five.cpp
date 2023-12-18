
#include <cstring>
#include <iostream>
#include <ostream>
class MyString {
public:
    // 默认构造函数
    MyString() : _data(nullptr), _len(0) {}
    // 构造函数
    MyString(const char *p) : _len(strlen(p))
    {
        _init_data(p);
    }

    // 拷贝构造函数
    MyString(const MyString &str) : _len(str._len)
    {
        _init_data(str._data);
    }

    // 移动拷贝函数
    MyString(MyString &&str) noexcept : _data(str._data), _len(str._len)
    {
        str._data = nullptr;  // 原来的置为空
        str._len = 0;
    }

    // 赋值拷贝函数
    MyString &operator=(const MyString &str)
    {
        if (this != &str) {
            if (_data) {
                delete _data;
            }
            _len = str._len;
            _init_data(str._data);
        }

        return *this;
    }
    // 移动赋值拷贝函数
    MyString &operator=(MyString &&str) noexcept
    {
        if (this != &str) {
            if (_data) {
                delete _data;
            }
            // 浅拷贝 效率更高
            _len = str._len;
            _data = str._data;

            str._len = 0;
            str._data = nullptr;
        }

        return *this;
    }

    // 析构函数
    virtual ~MyString()
    {
        if (_data) {
            delete _data;
        }
    }

    char *getData()
    {
        return this->_data;
    }

private:
    char *_data;
    int _len;
    // 深拷贝
    void _init_data(const char *s)
    {
        _data = new char[_len + 1];
        memcpy(_data, s, _len);
        _data[_len] = '\0';
    }
};

int main(int argc, char **argv)
{
    MyString s("123");

    MyString s1(s);

    MyString s2(std::move(s));

    std::cout << s1.getData() << std::endl;

    std::cout << s2.getData() << std::endl;

    system("pause");
    return 0;
}
