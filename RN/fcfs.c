#include <stdio.h>

struct Process {
    char name;
    int arrival_time;
    int burst_time;
};

void fcfs_scheduling(struct Process processes[], int n) {
    int completion_time = 0;
    int turnaround_time, waiting_time;

    printf("Process | ArrivalTime | BurstTime | CompletionTime | TurnaroundTime | WaitingTime\n");
    int st=0;
    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time > completion_time) {
            completion_time = processes[i].arrival_time;
        }
        if(i==0)
            st=0;
        else
            st=st+processes[i-1].burst_time;

            
        completion_time += processes[i].burst_time;
        turnaround_time = completion_time - processes[i].arrival_time;
        waiting_time = turnaround_time - processes[i].burst_time;

        printf("%c\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].name,
               processes[i].arrival_time, processes[i].burst_time, completion_time, turnaround_time, waiting_time,st);
    }
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        printf("Enter the name of process %d: ", i + 1);
        scanf(" %c", &processes[i].name);
        printf("Enter arrival time for process %c: ", processes[i].name);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for process %c: ", processes[i].name);
        scanf("%d", &processes[i].burst_time);
    }

    fcfs_scheduling(processes, n);

    return 0;
}
