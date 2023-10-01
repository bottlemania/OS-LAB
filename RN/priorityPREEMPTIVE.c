#include <stdio.h>
#include <stdbool.h>

struct Process {
    char name;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
    bool completed;

    int priority;
};
void srt_scheduling(struct Process processes[], int n) {
    int current_time = 0;
    int completed_processes = 0;

    printf("Process | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time | Finish Time | Response Time\n");

    while (completed_processes < n) {
            int high = 100;
            int shortest_index = -1;

            for (int i = 0; i < n; i++) {
                if (!processes[i].completed && processes[i].arrival_time <= current_time) {
                    if (processes[i].priority < high) {
                        high = processes[i].priority;
                        shortest_index = i;
                    }
                }
            }

        if (shortest_index == -1) {
            // No process is ready, move time forward
            current_time++;
        } else {
            // Execute the shortest job
            if (processes[shortest_index].response_time == -1) {
                processes[shortest_index].response_time = current_time - processes[shortest_index].arrival_time;
            }

            processes[shortest_index].remaining_time--;

            if (processes[shortest_index].remaining_time == 0) {
                // Process has completed
                processes[shortest_index].completed = true;
                completed_processes++;
                processes[shortest_index].completion_time = current_time + 1;
                processes[shortest_index].turnaround_time = processes[shortest_index].completion_time - processes[shortest_index].arrival_time;
                processes[shortest_index].waiting_time = processes[shortest_index].turnaround_time - processes[shortest_index].burst_time;
            }

            current_time++;
        }
    }

    // Print process details
    for (int i = 0; i < n; i++) {
        printf("%c\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].name,
               processes[i].arrival_time, processes[i].burst_time, processes[i].completion_time,
               processes[i].turnaround_time, processes[i].waiting_time,
               processes[i].completion_time, processes[i].response_time);
    }
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        printf("Enter the name of process %d     : ", i + 1);
        scanf(" %c", &processes[i].name);
        printf("Enter arrival time for process %c: ", processes[i].name);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter priority for process %c    : ", processes[i].name);
        scanf("%d", &processes[i].priority);
        printf("Enter burst time for process %c  : ", processes[i].name);
        scanf("%d", &processes[i].burst_time);

        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completed = false;
        processes[i].response_time = -1;
    }

    srt_scheduling(processes, n);

    return 0;
}
