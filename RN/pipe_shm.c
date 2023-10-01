#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>

#define SHMSZ 50

void main(){
	int pid, shmid;
	key_t key;
	key = 9000;
	char *shm, *s;
	pid = fork();
	if(pid){
		printf("In parent process :-\n");
		shmid = shmget(key,SHMSZ,IPC_CREAT|0666);
		shm = (char*)shmat(shmid,NULL,0);
		s = shm;
		printf("Enter message to be sent to child : ");
		scanf("%s",s);
		while(*shm!='*')
			sleep(1);
	}
	else{
		sleep(5);
		printf("In child process :-\n");
		shmid = shmget(key,SHMSZ,0666);
		shm = (char*)shmat(shmid,NULL,0);
		printf("Parent said ");
		for(s = shm;*s!='\0';s++)
			putchar(*s);
		**shm = '**';
	}
}