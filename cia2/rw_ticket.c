#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

sem_t mutex;
sem_t rw_mutex;

int readcount = 0;
int ticket = 0;

void book(){
    ticket++;
}

void cancel(){
    ticket--;
}

void *reader(){
    while (1)
    {
        sem_wait(&mutex);
        readcount++;
        if (readcount == 1)
            sem_wait(&rw_mutex);
        sem_post(&mutex);

        printf("\nTicket value = %d", ticket);

        sem_wait(&mutex);
        readcount--;
        if (readcount == 0)
            sem_post(&rw_mutex);
        sem_post(&mutex);
        sleep(3);
    }
}

void *writer(){
    char op;
    while (1)
    {
        sleep(3);
        sem_wait(&rw_mutex);

        printf("\nEnter b to book, c to cancel : ");
        scanf(" %c", &op);
        if (op == 'b')
            book();
        if (op == 'c')
            cancel();
            
        sem_post(&rw_mutex);
    }
}

int main(){
    pthread_t r_tid;
    pthread_t w_tid;
    sem_init(&mutex, 0, 1);
    sem_init(&rw_mutex, 0, 1);
    pthread_create(&r_tid, NULL, reader, 0);
    pthread_create(&w_tid, NULL, writer, 0);
    pthread_join(r_tid, NULL);
    pthread_join(w_tid, NULL);
    return 0;
}