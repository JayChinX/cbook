

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <set>
#include <string>
#include <utility>

class Book {
  public:
    Book(std::string name) { this->name = name; }
    std::string getName() const { return this->name; }

  private:
    std::string name;
};

class BookCompare {
  public:
    bool operator()(Book book1, Book book2) const {
        return book1.getName() < book2.getName();
    }
};

int main(int argc, char **argv) {
    std::set<Book, BookCompare> sets;
    sets.insert(Book("1"));
    sets.insert(Book("2"));
    sets.insert(Book("0"));

    std::for_each(sets.begin(), sets.end(), [&](const Book &book) {
        std::cout << book.getName();
    });

    system("pause");
    return 0;
}
