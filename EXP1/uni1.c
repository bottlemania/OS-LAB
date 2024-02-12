#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

int main(){

    int fd[2];
    int pid;

    char in[10],out[10];

    if(pipe(fd)==-1)
        printf("pipe failed to create\n");

    pid=fork(); // Parent process gets the return value of child pid --- Child gets 0 as return value from fork

    if(pid==-1)
        printf("fork failed to create\n");

    if(pid){        //parent process (Case: pid>0)
        printf("Parent process with id:%d\n",getpid());
        printf("Type the data to be sent:\n");
        scanf("%c",out);
        write(fd[1],out,sizeof(out));
        wait(NULL);
        printf("Child terminated.\n");
        printf("Terminating parent....\n");
        exit(0);
        printf("parent terminated.");
    }

    else{           //child process (Case: return value (here pid)= 0)
        read(fd[0],in,sizeof(in));
        printf("Child process with id:%d\n",getpid);
        printf("Date Received: %c\n",in);
        printf("terminating child....\n");
        exit(0);
    }

    return 0;
}