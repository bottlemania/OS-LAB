#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define LEFT (philosopher_number + N - 1) % N
#define RIGHT (philosopher_number + 1) % N

sem_t chopsticks[N];
sem_t mutex;
int state[N];

void test(int philosopher_number) {
    if (state[philosopher_number] == HUNGRY &&
        state[LEFT] != EATING &&
        state[RIGHT] != EATING) {
        state[philosopher_number] = EATING;
        sem_post(&chopsticks[philosopher_number]);
    }
}

void think(int philosopher_number) {
    printf("Philosopher %d is thinking\n", philosopher_number);
    sleep(rand()%(30-15 + 1) + 15);  // Sleep for a longer time (0 to 4 seconds)
}

void eat(int philosopher_number) {
    printf("Philosopher %d is eating\n", philosopher_number);
    sleep(rand()%(30-15 + 1) + 15);  // Sleep for a longer time (0 to 4 seconds)
}

void take_chopsticks(int philosopher_number) {
    sem_wait(&mutex);
    state[philosopher_number] = HUNGRY;
    printf("Philosopher %d is hungry\n", philosopher_number);
    test(philosopher_number);
    sem_post(&mutex);
    sem_wait(&chopsticks[philosopher_number]);
}

void put_chopsticks(int philosopher_number) {
    sem_wait(&mutex);
    state[philosopher_number] = THINKING;
    printf("Philosopher %d is putting down chopsticks\n", philosopher_number);
    test(LEFT);
    test(RIGHT);
    sem_post(&mutex);
}

void* philosopher(void* arg) {
    int philosopher_number = *((int*)arg);
    while (1) {
        think(philosopher_number);
        take_chopsticks(philosopher_number);
        eat(philosopher_number);
        put_chopsticks(philosopher_number);
    }
}
void* philosopher(void* arg) {
    int philosopher_number = *((int*)arg);
    while (1) {
        think(philosopher_number);
        take_chopsticks(philosopher_number);
        eat(philosopher_number);
        put_chopsticks(philosopher_number); // Add this line to put back chopsticks
    }
}


int main() {
    pthread_t philosophers[N];
    int philosopher_numbers[N];

    sem_init(&mutex, 0, 1);

    for (int i = 0; i < N; i++) {
        sem_init(&chopsticks[i], 0, 1);  // Initialize chopstick semaphores to 1
    }

    for (int i = 0; i < N; i++) {
        philosopher_numbers[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_numbers[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}
