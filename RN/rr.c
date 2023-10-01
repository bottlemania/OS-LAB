#include <stdio.h>

struct Process {
    char name;
    int arrival_time;
    int burst_time;
    int remaining_time;  // Remaining burst time for the process
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

void round_robin_scheduling(struct Process processes[], int n, int time_quantum) {

    int current_time = 0;
    int done = 0;
    
    while (done<n) {
        

        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {

                if (processes[i].remaining_time > time_quantum) {
                    current_time += time_quantum;
                    processes[i].remaining_time -= time_quantum;
                } else {
                    current_time += processes[i].remaining_time;
                    processes[i].completion_time = current_time;
                    processes[i].remaining_time = 0;
                    done++;
                }
            }
        }

    }

    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
    }

    printf("Process | Arrival_Time | Burst_Time | Completion_Time | Turnaround_Time | Waiting_Time\n");
    for (int i = 0; i < n; i++) {
        printf("%c\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].name,
               processes[i].arrival_time, processes[i].burst_time, processes[i].completion_time,
               processes[i].turnaround_time, processes[i].waiting_time);
    }
}

int main() {
    int n, time_quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        printf("Enter the name of process %d: ", i + 1);
        scanf(" %c", &processes[i].name);
        printf("Enter arrival time for process %c: ", processes[i].name);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for process %c: ", processes[i].name);
        scanf("%d", &processes[i].burst_time);

        // Initialize remaining time and other attributes
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completion_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].waiting_time = 0;
    }

    round_robin_scheduling(processes, n, time_quantum);

    return 0;
}
