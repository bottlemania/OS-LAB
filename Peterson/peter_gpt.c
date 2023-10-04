#include <stdio.h>
#include <pthread.h>

#define TRUE 1
#define FALSE 0

int turn;
int flag[2];

void* thread0(void* arg) {
    int i;
    for (i = 0; i < 5; i++) {
        flag[0] = TRUE;
        turn = 1;
        while (flag[1] && turn == 1)
            ; // Busy-wait

        // Critical section
        printf("Thread 0 is in critical section (%d)\n", i);

        flag[0] = FALSE;

        // Non-critical section
        printf("Thread 0 is in non-critical section (%d)\n", i);
    }
}

void* thread1(void* arg) {
    int i;
    for (i = 0; i < 5; i++) {
        flag[1] = TRUE;
        turn = 0;
        while (flag[0] && turn == 0)
            ; // Busy-wait

        // Critical section
        printf("Thread 1 is in critical section (%d)\n", i);

        flag[1] = FALSE;

        // Non-critical section
        printf("Thread 1 is in non-critical section (%d)\n", i);
    }
}

int main() {
    pthread_t tid0, tid1;
    flag[0] = FALSE;
    flag[1] = FALSE;
    
    pthread_create(&tid0, NULL, thread0, NULL);
    pthread_create(&tid1, NULL, thread1, NULL);
    
    pthread_join(tid0, NULL);
    pthread_join(tid1, NULL);

    return 0;
}
