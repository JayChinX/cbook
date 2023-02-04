
#include <iostream>
#include <mutex>
#include <pthread.h>
#include <unistd.h>

struct data {
    int id;
    char *message;
};
pthread_mutex_t mutex;

void *fun(void *args) {
    struct data *data = (struct data *)args;
    // 互斥锁加锁
    int res = pthread_mutex_lock(&mutex);
    if (res) {
        //  互斥锁解锁
        pthread_mutex_unlock(&mutex);
        pthread_exit(NULL);
    }
    sleep(1);
    std::cout << "Thread tid = " << data->id << ", message = " << data->message
              << std::endl;
    //  互斥锁解锁
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
    return 0;
}

int main(int argc, char *const argv[]) {
    pthread_t tids[5];
    struct data td[5];
    // 互斥锁初始化
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < 5; ++i) {
        td[i].id = i;
        td[i].message = (char *)"This is message.";
        int ret = pthread_create(&tids[i], NULL, fun, (void *)&(td[i]));
        if (ret != 0) {
            std::cout << "pthread_create error:error_code = " << ret
                      << std::endl;
        }
    }
    // pthread_cancel(tids[2]);

    void *status;
    for (int i = 0; i < 5; ++i) {
        int ret = pthread_join(tids[i], &status);
        if (ret) { std::cout << "Error: can't join: " << ret << std::endl; }
        std::cout << "Main: completed thread id: " << i;
        std::cout << "  Exiting with status: " << status << std::endl;
    }

    // 互斥锁销毁
    pthread_mutex_destroy(&mutex);
    return 0;
}