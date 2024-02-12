#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>

/*
pause()
pid_t terminated_pid=waitpid(getppid(),&status,0);
if(terminated_pid==-1){
    perror("waitpid");
    _exit(EXIT_FAILURE);
}
*/

volatile sig_atomic_t parent_finished = 0;
volatile sig_atomic_t child_finished = 0;

void sigusr1_handler(int signo) {
    parent_finished = 1;
}
void sigusr2_handler(int signo) {
    child_finished = 1;
}

int main() {

    signal(SIGUSR1, sigusr1_handler);
    signal(SIGUSR2, sigusr2_handler);

    int fd[2];
    pid_t pid;

    char in[10], out[10];

    if (pipe(fd) == -1) {
        perror("Pipe Creation");
        _exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid == -1) {
        perror("fork");
        _exit(EXIT_SUCCESS);

    } else if (pid) {       //parent process 
        printf("Parent Process started. PID:%d\n", getpid());
        printf("Type the data to be sent:\n");
        scanf("%s", out);
        write(fd[1], out, sizeof(out));
        kill(pid, SIGUSR1);
        wait(NULL);
        // while(!child_finished);
        printf("Parent Terminated.\n");
        _exit(EXIT_SUCCESS);

    } else {                //child process
        while(!parent_finished);
        printf("Child process started. PID:%d\n", getpid());
        read(fd[0], in, sizeof(in));
        printf("Data Received: %s\n", in);
        printf("Child Terminated.\n");
        //kill(getppid(), SIGUSR2);
        _exit(EXIT_SUCCESS);
    }
    return 0;
}
