#include <queue>

int main(int argc, char **argv)
{
    std::queue<int> q1;

    q1.push(5);
    q1.push(0);
    q1.push(1);
    q1.push(2);
    q1.push(3);

    printf("queue size = %lu \n", q1.size());

    while (!q1.empty()) {
        printf("%d ", q1.front());
        q1.pop();
    }

    // std::priority_queue<int> pq;
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    pq.push(5);
    pq.push(0);
    pq.push(1);
    pq.push(2);
    pq.push(3);
    pq.push(4);

    printf("priority queue size = %lu \n", pq.size());

    while (!pq.empty()) {
        printf("%d ", pq.top());
        pq.pop();
    }
    system("pause");
    return 0;
}
