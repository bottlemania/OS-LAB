#include <stdio.h>

#define MAX_PROCESSES 100
#define MAX_CORES 10

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
}Process;

void sort_by_arrival_time(Process *processes, int num_processes) {
    for (int i = 0; i < num_processes - 1; i++) {
        for (int j = 0; j < num_processes - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

void schedule_processes(Process *processes, int num_processes, int num_cores) {
    int core_completion_time[MAX_CORES] = {0};

    for (int core = 0; core < num_cores; core++) {
        printf("Core %d:\n", core);
        int core_idle = 0;

        for (int i = 0; i < num_processes; i++) {
            int core_index = i % num_cores;
            if (core_index == core) {
                Process *current_process = &processes[i];

                if (core_completion_time[core] < current_process->arrival_time) {
                    if (core_idle == 0) {
                        printf("Idle(%d-%d) | ", core_completion_time[core], current_process->arrival_time);
                    } else {
                        printf("P%d(%d-%d) | ", core_index + 1, core_completion_time[core], current_process->arrival_time);
                    }
                    core_idle = 1;
                    core_completion_time[core] = current_process->arrival_time;
                }

                current_process->completion_time = core_completion_time[core] + current_process->burst_time;
                current_process->turnaround_time = current_process->completion_time - current_process->arrival_time;
                current_process->waiting_time = current_process->turnaround_time - current_process->burst_time;

                printf("P%d(%d-%d) | ", current_process->process_id, core_completion_time[core], current_process->completion_time);

                core_completion_time[core] = current_process->completion_time;
                core_idle = 0;
            }
        }
        printf("\n");
    }
}

int main() {
    int num_processes, num_cores;

    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    Process processes[MAX_PROCESSES];

    for (int i = 0; i < num_processes; i++) {
        processes[i].process_id = i + 1;
        printf("Enter arrival time for Process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
    }

    printf("Enter the number of processor cores: ");
    scanf("%d", &num_cores);

    sort_by_arrival_time(processes, num_processes);
    schedule_processes(processes, num_processes, num_cores);
    
    printf("\nMultiprocessor Scheduling Results : ");
    printf("\nProcessID\tArrivalTime\tBurstTime\tCompletionTime\tTurnAroundTime\tWaitingTime\n");
    for(int i=0;i<num_processes;i++){
    	printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",processes[i].process_id,processes[i].arrival_time,processes[i].burst_time,processes[i].completion_time,processes[i].turnaround_time,processes[i].waiting_time);
    
    }
    
    

    return 0;
}

