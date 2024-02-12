#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>

#define SHMSZ 1024

int main(){
    int shmid;
    key_t key=1234;
    shmid=shmget(key,SHMSZ,IPC_CREAT|0666);

    char *shmaddr;
    shmaddr=shmat(shmid,NULL,0);

    printf("Client received:\n %s\n", shmaddr);
    shmdt(shmaddr);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;    
}