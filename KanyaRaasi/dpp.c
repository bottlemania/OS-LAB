#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (phil_num + N - 1) % N
#define RIGHT (phil_num + 1) % N

int state[N]; // for state of each philosopher
sem_t mutex;  // mutual exclusion
sem_t chopstick[N]; // semaphores for each chopstick

void test(int phil_num)
{
    if (state[phil_num] == HUNGRY
        && state[LEFT] != EATING
        && state[RIGHT] != EATING)
    {
        sleep(2);
        // ensures the chopsticks released when not in use
        sem_post(&chopstick[LEFT]);
        sem_post(&chopstick[phil_num]);
    }
}

// take up chopsticks
void take_chopstick(int phil_num)
{
    sem_wait(&mutex);   // activate mutual exclusion

    // state that hungry
    state[phil_num] = HUNGRY;

    printf("Philosopher %d is Hungry\n", phil_num + 1);

    test(phil_num);

    sem_post(&mutex);   // deactivate mutual exclusion

    sem_wait(&chopstick[LEFT]);
    printf("Philosopher %d picked up left chopstick %d\n", phil_num + 1, LEFT + 1);
   
    sem_wait(&chopstick[phil_num]);
    printf("Philosopher %d picked up right chopstick %d\n", phil_num + 1, phil_num + 1);

    // progress only when both forks are available

    printf("----Philosopher %d has both chopsticks %d and %d\n",phil_num + 1, LEFT + 1, phil_num + 1);

    state[phil_num] = EATING;

    printf("Philosopher %d is Eating\n", phil_num + 1);

    sleep(5);  

}


// put down chopsticks
void put_chopstick(int phil_num)
{
    sem_wait(&mutex);   // activate mutual exclusion

    // release both forks

    sem_post(&chopstick[LEFT]);
    sem_post(&chopstick[phil_num]);
    
    printf("----Philosopher %d puts down both chopsticks %d and %d \n",phil_num + 1, LEFT + 1, phil_num + 1);

    // change philosopher state to thinking
    state[phil_num] = THINKING;

    printf("Philosopher %d is thinking\n", phil_num + 1);

    test(LEFT);     // to avoid greedy philosophers
    test(RIGHT);    // check upon adjacent philosophers

    sem_post(&mutex);    // deactivate mutual exclusion
}

void *philosopher(void *num)
{
    while (1)
    {
        int *i = num;

        sleep(2);

        take_chopstick(*i);

        sleep(2);

        put_chopstick(*i);
    }
}

int main()
{
    int i;
    pthread_t thread_id[N];
    int phil[N];

    sem_init(&mutex, 0, 1); // initialize mutex

    for (i = 0; i < N; i++)
        sem_init(&chopstick[i], 0, 0); // initialize the chopstick semaphores

    for (i = 0; i < N; i++)
    { // create philosopher processes
        phil[i] = i;

        pthread_create(&thread_id[i], NULL, philosopher, &phil[i]);

        printf("Philosopher %d is thinking\n", i + 1);
    }

    for (i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);
}
