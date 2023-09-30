#include <stdio.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#define SHMSZ 2000
int main()
{
	int shmid,len=0; 
	key_t key;
	char *shm,*s,c;
	key = 8899;
	//ERRORS
	if ((shmid = shmget(key, SHMSZ, 0666)) < 0) 
	{ 
		perror("shmget");
		exit(1);
	}
	if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) 
	{ 
		perror("shmat");
		exit(1);
	}
	printf("Original String: \n\n");
	// Read string in shm
	for (s = shm; *s !='\0'; s++){
		if(*s!=' ' && *s!='\n')
			len++;
		if(*s=='\n'){
			printf("\t\t\t---\tLength: %d",len);
			len=0;
		}
		putchar(*s);
	}
	printf("\n\nDo you want to continue the server? [y/n]\n");
	scanf("%c",&c);
	if(c=='n')
		*shm = '*';	
	exit(0);		
}
	
