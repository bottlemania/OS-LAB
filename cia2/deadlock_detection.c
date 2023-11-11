#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int allocation[MAX_PROCESSES][MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int available[MAX_RESOURCES];
int marked[MAX_PROCESSES];

int num_processes, num_resources;

int is_safe(int process) {
    int i, j;
    int work[MAX_RESOURCES];

    for (i = 0; i < num_resources; i++) {
        work[i] = available[i];
    }

    for (i = 0; i < num_processes; i++) {
        if (!marked[i]) {
            int can_allocate = 1;
            for (j = 0; j < num_resources; j++) {
                if (maximum[i][j] - allocation[i][j] > work[j]) {
                    can_allocate = 0;
                    break;
                }
            }

            if (can_allocate) {
                marked[i] = 1;
                for (j = 0; j < num_resources; j++) {
                    work[j] += allocation[i][j];
                }
                i = -1;  // Start over from the beginning
            }
        }
    }

    int deadlockDetected = 0;
    for (i = 0; i < num_processes; i++) {
        if (!marked[i]) {
            printf("Deadlock detected for Process %d\n", i);
            deadlockDetected = 1;
        }
    }

    return deadlockDetected ? 0 : 1;  // Return 1 if no deadlock, 0 if deadlock detected
}

int main() {
    int i, j;

    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    printf("Enter the number of resources: ");
    scanf("%d", &num_resources);

    printf("Enter Allocation matrix:\n");
    for (i = 0; i < num_processes; i++) {
        for (j = 0; j < num_resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter Maximum matrix:\n");
    for (i = 0; i < num_processes; i++) {
        for (j = 0; j < num_resources; j++) {
            scanf("%d", &maximum[i][j]);
        }
    }

    printf("Enter Available vector:\n");
    for (i = 0; i < num_resources; i++) {
        scanf("%d", &available[i]);
    }

    for (i = 0; i < num_processes; i++) {
        marked[i] = 0;
    }

    if (is_safe(0)) {
        printf("System is in a safe state.\n");
    }
else {
        printf("Deadlock detected.\n");
    }

    return 0;
}