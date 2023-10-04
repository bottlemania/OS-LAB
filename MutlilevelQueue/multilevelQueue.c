#include <stdio.h>
#include <stdlib.h>

// Process structure
struct Process {
    int id;          // Process ID
    int arrivalTime; // Arrival time
    int burstTime;   // Burst time
    int waitingTime; // Waiting time
};

// Function to execute processes using FCFS
void executeFCFS(struct Process processes[], int n) {
    int currentTime = 0;
    
    for (int i = 0; i < n; i++) {
        if (processes[i].arrivalTime > currentTime) {
            currentTime = processes[i].arrivalTime;
        }
        
        processes[i].waitingTime = currentTime - processes[i].arrivalTime;
        currentTime += processes[i].burstTime;
    }
}

// Function to execute processes using Round Robin
void executeRR(struct Process processes[], int n, int quantum) {
    int currentTime = 0;
    int remainingTime[n];
    
    for (int i = 0; i < n; i++) {
        remainingTime[i] = processes[i].burstTime;
    }
    
    int completed = 0;
    
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && remainingTime[i] > 0) {
                int executeTime = (remainingTime[i] < quantum) ? remainingTime[i] : quantum;
                currentTime += executeTime;
                remainingTime[i] -= executeTime;
                
                if (remainingTime[i] == 0) {
                    completed++;
                    processes[i].waitingTime = currentTime - processes[i].arrivalTime - processes[i].burstTime;
                }
            }
        }
    }
}

int main() {
    int n, quantum;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    struct Process processes[n];
    
    printf("Enter time quantum for Round Robin: ");
    scanf("%d", &quantum);
    
    printf("Enter process details (Arrival Time and Burst Time):\n");
    
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Process %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrivalTime);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burstTime);
    }
    
    // Execute processes using FCFS
    executeFCFS(processes, n);
    
    // Promote processes that waited for more than 5 units to RR
    for (int i = 0; i < n; i++) {
        if (processes[i].waitingTime > 5) {
            processes[i].arrivalTime = 0;
        }
    }
    
    // Execute processes using Round Robin
    executeRR(processes, n, quantum);
    
    // Calculate and display turnaround time
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\n");
    
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrivalTime, processes[i].burstTime, processes[i].waitingTime);
    }
    
    return 0;
}