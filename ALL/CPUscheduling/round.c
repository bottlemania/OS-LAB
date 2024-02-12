#include <stdio.h>
#include<stdlib.h>
struct process {
    int pid, at, bt, ct, tat, wt, rt;
};

void roundRobin(struct process *p, int n, int timeQuantum) {
    int remainingTime[n];
    for (int i = 0; i < n; i++)
        remainingTime[i] = p[i].bt;

    int currentTime = 0;
    int flag = 0; // Flag to check if any process is still remaining

    while (1) {
        flag = 0;

        for (int i = 0; i < n; i++) {
            if (remainingTime[i] > 0) {
                flag = 1;

                if (remainingTime[i] > timeQuantum) {
                    currentTime += timeQuantum;
                    remainingTime[i] -= timeQuantum;
                } else {
                    currentTime += remainingTime[i];
                    p[i].ct = currentTime;
                    remainingTime[i] = 0;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                }
            }
        }

        if (flag == 0)
            break;
    }
}

int main() {
    int n, timeQuantum;
    printf("Enter number of Processes: ");
    scanf("%d", &n);
    struct process *p = malloc(n * sizeof(struct process));

    for (int i = 0; i < n; i++) {
        printf("\nEnter details of process %d:\n", i + 1);
        printf("PID: ");
        scanf("%d", &p[i].pid);
        printf("Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
        p[i].ct = p[i].tat = p[i].wt = 0;
        p[i].rt = 0;
    }

    printf("\nEnter Time Quantum: ");
    scanf("%d", &timeQuantum);

    roundRobin(p, n, timeQuantum);

    printf("\nGantt Chart:\n\n");
    for (int i = 0; i < n; i++) {
        printf("P%d(%d-%d)", p[i].pid, p[i].ct - p[i].bt, p[i].ct);
        if (i != n - 1 && p[i].ct < p[i + 1].at) {
            printf(", idle(%d-%d), ", p[i].ct, p[i + 1].at);
        }
    }

    free(p);

    return 0;
}
