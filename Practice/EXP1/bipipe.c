#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>


/*
Choose the way:
1.Server to Client
2.Client to Server
3.Both

create a child with above menu
if 1 -> use pipe1 and pause child
if 2 -> use pipe2 and pause parent
if 3 -> pipe1 first, then pipe2 coordinate the sync

*/

volatile sig_atomic_t parent_pause=0;
volatile sig_atomic_t child_pause=0;

void sc(int signo){
    parent_pause=0;
    child_pause=1;
}
void cs(int signo){
    parent_pause=1;
    child_pause=0;
}
int main(){

    signal(SIGUSR1,sc);
    signal(SIGUSR2,cs);

    int fd1[2],fd2[2];
    pid_t child_pid;

    char in[10],out[10];

    if(!(pipe(fd1)!=-1&&pipe(fd2)!=-1)){
        perror("pipe");
        _exit(EXIT_FAILURE);
    }

    child_pid=fork();

    if(child_pid==-1){
        perror("fork");
        _exit(EXIT_FAILURE);
    }
    else if(child_pid){      //parent process
        printf("Parent Process started. PID:%d\n", getpid());
        int choice;
        printf("\nChoose the way:\n1.Server to Client\n2.Client to Server\n3.Both\n");
        scanf("choice",&choice);
        switch (choice)
        {
        case 1:
            kill(child_pid,SIGUSR1);
            kill(getpid(),SIGUSR1);
            

            
            break;
        
        case 2:
            kill(child_pid,SIGUSR2);


            break;
        }

    }
    else{                   //child process






    }






    return 0;
}


