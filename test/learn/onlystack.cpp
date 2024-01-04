
#include <cstddef>
class StackOnly {
public:
    StackOnly() {}
    int getNum() const
    {
        return this->i;
    }

private:
    // C++ 98
    // void *operator new(size_t size);
    // void operator delete(void *p);
    // C++ 11
    void *operator new(size_t size) = delete;
    void operator delete(void *p) = delete;
    int i = -1;
};

int main(int argc, char **argv)
{
    StackOnly so = StackOnly();
    StackOnly so1;

    return 0;
}
