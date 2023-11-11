#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

int front = 0;
int rear = -1;
int array[5];

sem_t mutex;
sem_t emptyCount;
sem_t fullCount;

int produce_item(){
    static int a = 1;
    return a++;
}

void insert_item(int item){
    rear = rear + 1;
    rear = rear % 5;
    array[rear] = item;
}

int remove_item(){
    int item = array[front];
    front = front + 1;
    front = front % 5;
    return item;
}


void *produce(){
    int item;
    while (1)
    {
        item = produce_item();
        sem_wait(&emptyCount); // to see whether empty spaces available
        sem_wait(&mutex);      // to ensure that consumer is not using the buffer
        printf("\nProducer entering the critical section");
        insert_item(item);
        printf("\nProducer inserting an item[%d] at %d", item, rear);
        sem_post(&mutex);     // release mutex to let consumer to access buf
        sem_post(&fullCount); // to let consumer take the new data
    }
}


void *consumer(){
    int item;
    while (1)
    {
        sleep(5);
        sem_wait(&fullCount); // to see whether there is data in buffer
        sem_wait(&mutex);     // to ensure that producer is not using the buffer
        printf("\nConsumer entering the critical region");
        item = remove_item();
        printf("\nConsumer consumed item[%d]", item);
        sem_post(&mutex); // release mutual exclusion
        printf("\nConsumer leaving the critical region");
        sem_post(&emptyCount); // Increment no of empty slots and
        // unblock producer if it was blocked
    }
}

int main(){
    pthread_t p_tid;
    pthread_t c_tid;

    sem_init(&mutex, 0, 1);
    sem_init(&emptyCount, 0, 5);
    sem_init(&fullCount, 0, 0);
    
    pthread_create(&p_tid, NULL, produce, 0);
    pthread_create(&c_tid, NULL, consumer, 0);
    pthread_join(p_tid, NULL);
    pthread_join(c_tid, NULL);
    return 0;
}
