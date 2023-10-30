#ifndef BOOKS_BOOK_H
#define BOOKS_BOOK_H

#include <string>

// 图书类 //类定义
class Book {
  public:
    Book() {}
    ~Book() {}
    std::string id;     // 编号
    std::string name;   // 名称
    std::string author; // 作者
    std::string press;  // 出版社
    std::string price;  // 价格

  public:
    Book setId(std::string id);
};

#endif