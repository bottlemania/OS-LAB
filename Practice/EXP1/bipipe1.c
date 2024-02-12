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

volatile sig_atomic_t parent_finished=0;
volatile sig_atomic_t child_finished=0;

void sigusr1_handler(int signo){
    parent_finished=1;
}
void sigusr2_handler(int signo){
    child_finished=1;
}
int main(){

    signal(SIGUSR1,sigusr1_handler);
    signal(SIGUSR2,sigusr2_handler);

    int fd1[2],fd2[2];
    pid_t child_pid;

    char in[100],out[100];

    if(!(pipe(fd1)!=-1&&pipe(fd2)!=-1)){
        perror("pipe");
        _exit(EXIT_FAILURE);
    }

    int choice;
    printf("\nChoose the way:\n1.Server to Client\n2.Client to Server\n3.Both\nYOUR CHOICE:");
    scanf("%d",&choice);
    child_pid=fork();
    if(child_pid==-1){
        perror("fork");
        _exit(EXIT_FAILURE);
    }
    else if(child_pid){      //parent process
        switch (choice)
        {
        case 1:
            printf("\nParent Process started. PID:%d\n", getpid());
            printf("Data from Server: ");
            scanf("%[^\n]s",out);
            write(fd1[1],out,sizeof(out));
            kill(child_pid,SIGUSR1);
            while(!child_finished);
            printf("Parent Terminated.\n");
            break;
        case 2:
            while(!child_finished);
            printf("\nParent Process started. PID:%d\n", getpid());
            read(fd2[0],in,sizeof(in));
            printf("Server Received: %s\n",in);
            printf("Parent Terminated.");
            kill(child_pid,SIGUSR2);
            break;
        default:
            printf("\nParent Process started. PID:%d\n", getpid());
            printf("Data from Server: ");
            scanf("%s",out);
            write(fd1[1],out,sizeof(out));
            kill(child_pid,SIGUSR1);
            while(!child_finished);
            read(fd2[0],in,sizeof(in));
            printf("Server Received: %s\n",in);
            printf("\nParent Terminated.");
            break; 
        }
        _exit(EXIT_SUCCESS);
    }
    else{                   //child process
        switch (choice)
        {
        case 1:
            while(!parent_finished);
            printf("\nChild Process started. PID:%d\n", getpid());
            read(fd1[0],in,sizeof(in));
            printf("Client Received: %s\n",in);
            printf("\nChild Terminated.\n");
            kill(getppid(),SIGUSR2);
            break;
        case 2:
            printf("\nChild Process started. PID:%d\n", getpid());
            printf("Data from Client: ");
            scanf("%[^\n]s",out);
            write(fd2[1],out,sizeof(out));
            kill(getppid(),SIGUSR2);
            while(!parent_finished);
            printf("Child Terminated.\n");
            break;
        default:
            while(!parent_finished);
            printf("\nChild Process started. PID:%d\n", getpid());
            read(fd1[0],in,sizeof(in));
            printf("Client Received: %s\n\n",in);
            printf("Data from Client: ");
            scanf("%s",out);
            write(fd2[1],out,sizeof(out));
            kill(getppid(),SIGUSR2);
            printf("\nChild Terminated.\n");
            break;
        }
        _exit(EXIT_SUCCESS);
    }
    return 0;
}


