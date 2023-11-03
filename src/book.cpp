#include <string>
#include <thread>
#include "book.h"

Book Book::setId(std::string id)
{
    this->id = std::move(id);
    std::thread T;
    T.join();
    return *this;
}
