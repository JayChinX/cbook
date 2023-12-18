#include <cstddef>
#include <istream>
namespace cl {

// 模拟实现 string 类
class string {
public:
    using iterator = char *;
    using const_iterator = const char *;

    // 默认成员函数 big three
    string(const char *str = "");        // 构造函数 默认参数写在声明中
    string(const string &s);             // 拷贝构造
    string &operator=(const string &s);  // 拷贝赋值函数
    string(string &&s) noexcept;  // 移动拷贝构造 含有指针成员，需要修改实参，形参不加 const
    string &operator=(string &&s) noexcept;  // 移动拷贝赋值函数
    ~string();                               // 析构函数

    // 迭代器相关
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    // 容量和大小相关的函数
    size_t size();                          // 返回大小
    size_t capacity();                      // 返回容量
    void reserve(size_t n);                 // 扩大容量
    void resize(size_t n, char ch = '\0');  // 改变大小
    bool empty() const;                     // 判空

    // 修改字符串相关函数
    void push_back(char ch);                      // 尾部追加
    void append(const char *str);                 // 拼接
    string &operator+=(char ch);                  // += 运算符重载，进行追加操作
    string &operator+=(const char *str);          // += 运算符重载，进行字符串拼接
    string &insert(size_t pos, char ch);          // pos 位置插入字符
    string &insert(size_t pos, const char *str);  // pos 位置插入字符串
    string &erase(size_t pos, size_t len);        // 删除
    void clear();
    void swap(string &s) noexcept;  // 与 s 交换内容
    const char *c_str() const;      // string 转换为字符串

    // 访问字符串相关函数
    char &operator[](size_t i);  // 访问下标字符
    const char &operator[](size_t i) const;
    size_t find(char ch, size_t pos = 0) const;          // 查找字符
    size_t find(const char *str, size_t pos = 0) const;  // 查找字符串
    size_t rfind(char ch, size_t pos = 0) const;         // 反查
    size_t rfind(const char *str, size_t pos = 0) const;

    // 关系运算符重载
    bool operator>(const string &s) const;
    bool operator>=(const string &s) const;
    bool operator<(const string &s) const;
    bool operator<=(const string &s) const;
    bool operator==(const string &s) const;
    bool operator!=(const string &s) const;

private:
    char *_str;                // 存储字符串
    size_t _size;              // 记录字符串当前的有效长度
    size_t _capacity;          // 记录字符串当前的容量
    static const size_t npos;  // 静态成员变量（整型最大值）
};

// 常量
const size_t string::npos = -1;

// io 输出 << 和 输入 >> 运算符重载
std::istream &operator>>(std::istream &in, string &s);
std::ostream &operator<<(std::ostream &out, string &s);
std::istream &getline(std::istream &in, string &s);
}  // namespace cl
