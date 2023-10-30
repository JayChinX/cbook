#include <book.h>
#include <string>
#include <thread>

Book Book::setId(std::string id) {
    this->id = id;
    std::thread T;
    T.join();
    return *this;
}
