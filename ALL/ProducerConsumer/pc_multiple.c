#include <stdlib.h>
#include <stdio.h>
#include<time.h>
#include<string.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>

pthread_t *producers;
pthread_t *consumers;

sem_t buf_mutex,empty_count,fill_count;
int *buf,buf_pos=-1,prod_count,con_count,buf_len;

int produce(pthread_t self)
{
	int i=0;
	int p=1+rand()%40;
	while(!pthread_equal(*(producers+i),self)&&i<prod_count)
	{
		i++;
	}
	printf("Producer %d produced-item  %d \n",i+1,p);
	return p;
}

void consume(int p,pthread_t self)
{
	int i=0;
	while(!pthread_equal(*(consumers+i),self)&&i<con_count)
	{
		i++;
	}
	printf("Buffer\n");
	for(i=0;i<buf_pos;i++)
		printf("%d\n",*(buf+i));
	printf("Consumer %d consumed %d in current buffer len %d\n",i+1,p,buf_pos);
}

void *producer(void *args)
{
	while(1)
	{
		sleep(1+rand()%3);
		int p=produce(pthread_self());
		sem_wait(&empty_count);
		sem_wait(&buf_mutex);
		++buf_pos;
		*(buf+buf_pos)=p;
		sem_post(&buf_mutex);
		sem_post(&fill_count);	
	}
}

void *consumer(void *args)
{
	int c;
	while(1)
	{
		sleep(1+rand()%6);
		sem_wait(&fill_count);
		sem_wait(&buf_mutex);
		c=*(buf+buf_pos);
		consume(c,pthread_self());
		--buf_pos;
		sem_post(& buf_mutex);
		sem_post(&empty_count);
	}
}

int main()
{
	int i,err;
	srand(time(NULL));
	
	sem_init(&buf_mutex,0,1);
	sem_init(&fill_count,0,0);
	
	printf("Enter number of producers : \n");
	scanf("%d",&prod_count);
	producers = (pthread_t*)malloc(prod_count*sizeof(pthread_t));
	printf("Enter no.of consumers : \n");
	scanf("%d",&con_count);
	consumers=(pthread_t*)malloc(con_count*sizeof(pthread_t));
	printf("Enter buffer capacity : \n");
	scanf("%d",&buf_len);
	buf=(int*) malloc(buf_len*sizeof(int));
	
	sem_init(&empty_count,0,buf_len);
	
	for(i=0;i<prod_count;i++)
	{
		err=pthread_create(producers+i,NULL,&producer,NULL);
		if(err!=0)
			printf("Error\n");	
		else
			printf("successful\n");
	}
	for(i=0;i<con_count;i++)
	{
		err==pthread_create(consumers+i,NULL,&consumer,NULL);
		if(err!=0)
			printf("Error\n");	
		else
			printf("successful\n");
	}

	for(i=0;i<prod_count;++i)
		pthread_join(*(producers+i),NULL);
	for(i=0;i<con_count;++i)
		pthread_join(*(consumers+i),NULL);
	return 0;
}