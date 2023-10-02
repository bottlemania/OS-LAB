#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<wait.h>
int main(){
	pid_t pid;
	pid=fork();
	if(pid==-1){		//Fork failed
		printf("Fork failed to create");
	}
	if(pid>0){			//Parent process
		printf("Parent pid: %d\n",getpid());
		sleep(10);
		printf("\nTerminating parent...\n");
		sleep(3);
		exit(0);
	}
	else if(pid==0){	//Child process
		printf("\nChild pid: %d\n",getpid());
		sleep(15);
		printf("\nChild still alive\n");
		printf("\nChild's parent pid: %d\n",getppid());	
		sleep(50);
		printf("\nChild terminated...PRESS ENTER\n");
	}
	return 0;
}
