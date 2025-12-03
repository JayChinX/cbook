
#include <list>
#include <vector>
#include <stack>
int main(int argc, char **argv)
{
    std::stack<int> st1;
    std::stack<int, std::vector<int>> st2;
    std::stack<int, std::list<int>> st3;

    printf("st1 is null %d \n", st1.empty());
    printf("st2 count = %lu \n", st2.size());

    st1.push(0);
    st1.push(1);
    st1.push(2);
    st1.push(3);

    while (!st1.empty()) {
        printf("%d ", st1.top());
        st1.pop();
    }

    st2.push(0);
    st2.push(1);
    st2.push(2);
    st2.push(3);

    return 0;
}
