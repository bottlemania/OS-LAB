#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h> 
#include <stdlib.h>
#include <unistd.h>
#define SHMSZ 2000
int main(){
	char c;
	int shmid,len; 
	key_t key; 
	char *shm, *s;
	key = 8899; 
	// ERRORS
	if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) 
	{ 
		perror("shmget");
		exit(1);
	}
	if ((shm = shmat(shmid, NULL, 0)) == (char *)-1) 
	{
		perror("shmat");
		exit(1);
	}	
	printf("Enter the multiple lines (press ; to stop): \n\n");
	// assign shared memory to string pointer
	s=shm;
 	while((c=getchar())!=';'){
   		*s++=c;
   	}
	*s ='\0';
	printf("\n\n-------Waiting for client to finish-----\n\n");
	// wait till client reads and modifies the first char into *
	while (*shm != '*') 
	sleep(1);

	exit(0);
}	
