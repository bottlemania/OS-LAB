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

int state[N];      // for state of each philosopher

sem_t mutex;       // mutual exclusion 
sem_t S[N];        // semaphores for each philosopher

void test(int phil_num) 
{ 
	if (state[phil_num] == HUNGRY 
		&& state[LEFT] != EATING 
		&& state[RIGHT] != EATING) { 
		// state that eating 
		state[phil_num] = EATING; 

		sleep(2); 

		printf("----Philosopher %d takes fork %d and %d\n", 
					phil_num + 1, LEFT + 1, phil_num + 1); 

		printf("Philosopher %d is Eating\n", phil_num + 1); 

		// sem_post(&S[phil_num]) has no effect 
		// during takefork 
		// used to wake up hungry philosophers 
		// during putfork 
		sem_post(&S[phil_num]); 
	} 
} 

// take up chopsticks 
void take_fork(int phil_num) 
{ 

	sem_wait(&mutex); 

	// state that hungry 
	state[phil_num] = HUNGRY; 

	printf("Philosopher %d is Hungry\n", phil_num + 1); 

	// eat if neighbours are not eating 
	test(phil_num); 

	sem_post(&mutex); 

	// if unable to eat wait to be signalled 
	sem_wait(&S[phil_num]); 

	sleep(1); 
} 

// put down chopsticks 
void put_fork(int phil_num) 
{ 

	sem_wait(&mutex); 

	// state that thinking 
	state[phil_num] = THINKING; 

	printf("----Philosopher %d puts down fork %d and %d \n", 
		phil_num + 1, LEFT + 1, phil_num + 1); 
	printf("Philosopher %d is thinking\n", phil_num + 1); 

	test(LEFT); 
	test(RIGHT); 

	sem_post(&mutex); 
} 

void* philospher(void* num) 
{ 

	while (1) { 

		int* i = num; 

		sleep(1); 

		take_fork(*i); 

		sleep(0); 

		put_fork(*i); 
	} 
} 

int main() 
{ 

	int i; 
	pthread_t thread_id[N]; 
    int phil[N];    

	
	sem_init(&mutex, 0, 1);     // initialize mutex

	for (i = 0; i < N; i++) 

		sem_init(&S[i], 0, 0);  // initialize the semaphores 

	for (i = 0; i < N; i++) {   // create philosopher processes 
        phil[i]=i;

		pthread_create(&thread_id[i], NULL,philospher, &phil[i]); 

		printf("Philosopher %d is thinking\n", i + 1); 
	} 

	for (i = 0; i < N; i++) 

		pthread_join(thread_id[i], NULL); 
} 