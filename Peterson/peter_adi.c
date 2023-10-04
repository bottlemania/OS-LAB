#include <stdio.h>
#include <pthread.h>
#include <stdio.h>

int flag[2];
int count=-1;
int turn;

void lock_init()
{
   
    flag[0] = flag[1] = 0;
    turn = 0;
}

void lock(int self)
{
    flag[self] = 1;
    turn = 1-self;
    count++;
     printf("\n\tValue of count: %d\n\n",count);
    while (flag[1-self]==1 && turn==1-self);
  
}

void unlock(int self)
{
    count--; 
    printf("\n\tValue of count: %d\n\n",count);
    flag[self] = 0;
}

void* thread0(void *s)
{
    
    int self = (int *)s;
    while(1)
    {	
        lock(self); 
        printf("P%d is in Critical Section\n", self);
        sleep(1);
      
       printf("P%d leaving Critical Section\n", self);
        unlock(self);
    }
}

void *thread1(void *s)
{
    
    int self = (int *)s;
    while(1)
    {
    	
        lock(self); 
        printf("P%d is in Critical Section\n", self);
       	sleep(1);
        
         printf("P%d leaving Critical Section\n", self);
        unlock(self);
        
    }
}
int main()
{
    pthread_t p1, p2;
    lock_init();
	pthread_create(&p1, NULL, thread0, (void*)0);
	pthread_create(&p2, NULL, thread1, (void*)1);
	pthread_join(p1, NULL);
	pthread_join(p2, NULL);
	return 0;
}