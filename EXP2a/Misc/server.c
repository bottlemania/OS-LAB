#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdlib.h>
#include<string.h>
#define SHMSZ 50
void main()
{
    char c;
    int shmid;
    key_t key;
    char*shm,*s;
    key=5678; // A random number used as key
    shmid=shmget(key,SHMSZ,IPC_CREAT|0666); // Create shared
    //memory
    shm=(char*)shmat(shmid,NULL,0); //Attach shared memory
    s=shm; // Temporary pointer to avoid moving shm from base address of
    //shared memory
    printf("Enter the message you want to send: ");
    scanf("%s", s); // Message copied into Shared memory directly through
    //spointer
    while(*shm!='*') // Sender waits until received acknowledge it has read
    //by appending * into shared memory
    sleep(1);
}