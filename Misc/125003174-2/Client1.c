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
	int shmid; 
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
	for (s = shm; *s !='\0'; s++) 
		putchar(*s);	
	pid_t pid = fork();		//forking
	if (pid < 0) {			//forking failed
		perror("fork");
		exit(1);
	} 
	else if (pid == 0) {		// Child process
		printf("\n\nUPPERCASE String: \n\n");
		for (s = shm; *s !='\0'; s++)  {
		    printf("%c",toupper(*s));
		}
	} 
	else {				// Parent process
		wait(NULL); // Wait for the child to finish
		printf("\n\nlowercase String: \n\n");
		for (s = shm; *s !='\0'; s++)  {
		    printf("%c",tolower(*s));
		}
		printf("\n\nDo you want to continue the server? [y/n]");
		scanf("%c",&c);
		if(c=='n')
			*shm = '*';
	}
	exit(0);		
}
	
