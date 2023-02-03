
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int count = 0;

void *thread_add_count(void*) {
    sleep(5); // sleep 5 second
    count++;
}

int main(int argc, char *argv[]) {
    pthread_t tid;         // thread id
    pthread_attr_t thattr; // thread attr
    int therr;             // pthread_create return value

    pthread_attr_init(&thattr); // init thread attr
    pthread_attr_setdetachstate(
        &thattr, PTHREAD_CREATE_JOINABLE); // set thread joinable

    if ((therr = pthread_create(&tid, &thattr, &thread_add_count, NULL)) != 0) {
        printf("create thread error\n");
        exit(EXIT_FAILURE);
    }

    // pthread_attr_destory(&thattr);   //destory thread

    /*block main thread wait for thread tid end，before end we release thread
    tid resource WARNING pass a thread to this function rather than thread id
    POINTER!!!*/
    pthread_join(tid, NULL);

    printf("count is %d\n", count);

    return 0;
}
