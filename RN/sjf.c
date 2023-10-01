#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
struct Process {
    char name;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    bool completed;
};

void sjf_scheduling(struct Process processes[], int n) {
    int current_time = 0;
    int completed_processes = 0;

    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");

    while (completed_processes < n) {
        int shortest_index = -1;
        int shortest_burst_time = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && processes[i].arrival_time <= current_time) {
                if (processes[i].burst_time < shortest_burst_time) {
                    shortest_burst_time = processes[i].burst_time;
                    shortest_index = i;
                }
            }
        }

        if (shortest_index == -1) {
            // No process is ready, move time forward
            current_time++;
        } else {
            // Execute the shortest job
            processes[shortest_index].completion_time = current_time + processes[shortest_index].burst_time;
            processes[shortest_index].turnaround_time = processes[shortest_index].completion_time - processes[shortest_index].arrival_time;
            processes[shortest_index].waiting_time = processes[shortest_index].turnaround_time - processes[shortest_index].burst_time;
            processes[shortest_index].completed = true;
            completed_processes++;

            printf("%c\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[shortest_index].name,
                   processes[shortest_index].arrival_time, processes[shortest_index].burst_time,
                   processes[shortest_index].completion_time, processes[shortest_index].turnaround_time,
                   processes[shortest_index].waiting_time);

            current_time = processes[shortest_index].completion_time;
        }
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
        processes[i].completed = false;
    }

    sjf_scheduling(processes, n);

    return 0;
}
