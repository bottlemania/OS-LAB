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
		sleep(1000);
	}
	else if(pid==0){	//Child process
		printf("\nChild pid: %d\n",getpid());
		printf("\nChild's parent pid: %d\n",getppid());		
		exit(0);
	}
	return 0;
}
	
			
