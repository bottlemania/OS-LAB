#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<wait.h>
int main(){
	int fd[2];
	char in[20],out[20];
	pipe(fd);
	int pid=fork();
	if(pid==-1){
		printf("Fork failed to create");
	}
	if(pid){
		close(fd[0]);
		printf("Parent process with id: %d\n",getpid());
		printf("\nType the data to be sent: ");
		scanf("%s",out);
		write(fd[1],out,sizeof(out));
		close(fd[1]);
		wait(NULL);
		printf("				Child process terminated.\n");
		printf("\nTerminating parent process...\r");
		printf("				Parent process terminated.\n\n");
		exit(0);
	}
	else{
		close(fd[1]);
		read(fd[0],in,20);
		close(fd[0]);
		printf("\nChild process with id: %d\n",getpid());
		printf("\nChild's parent id: %d\n",getppid());
		printf("\nData received by the child: %s\n",in);
		printf("\nTerminating Child process...\r");
		exit(0);
	}
	return 0;
}
