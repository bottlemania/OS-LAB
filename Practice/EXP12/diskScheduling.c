#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to calculate the absolute difference between two numbers
int absDiff(int a, int b) {
    return abs(a - b);
}

// Function to perform FIFO disk scheduling
void FIFO(int requestQueue[], int n, int initialPosition) {
    int seekTime = 0;
    int currentPosition = initialPosition;

    // Iterate through the request queue
    for (int i = 0; i < n; i++) {
        // Calculate seek time for the current request
        seekTime += absDiff(currentPosition, requestQueue[i]);

        // Set the current position to the requested position
        currentPosition = requestQueue[i];
    }

    printf("FIFO Seek Time: %d\n", seekTime);
}

// Function to perform SCAN disk scheduling
void SCAN(int requestQueue[], int n, int initialPosition, int direction) {
    int seekTime = 0;
    int currentPosition = initialPosition;

    // Sort the request queue in ascending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (requestQueue[j] > requestQueue[j + 1]) {
                // Swap the elements if they are in the wrong order
                int temp = requestQueue[j];
                requestQueue[j] = requestQueue[j + 1];
                requestQueue[j + 1] = temp;
            }
        }
    }

    // Find the index of the current position in the sorted request queue
    int currentIndex;
    for (currentIndex = 0; currentIndex < n; currentIndex++) {
        if (requestQueue[currentIndex] >= currentPosition) {
            break;
        }
    }

    // Calculate seek time based on the direction
    if (direction == 1) {
        // Move from left to right
        for (int i = currentIndex; i < n; i++) {
            seekTime += absDiff(currentPosition, requestQueue[i]);
            currentPosition = requestQueue[i];
        }
        // Move to the end of the disk
        seekTime += absDiff(currentPosition, 199);
    } else {
        // Move from right to left
        for (int i = currentIndex - 1; i >= 0; i--) {
            seekTime += absDiff(currentPosition, requestQueue[i]);
            currentPosition = requestQueue[i];
        }
        // Move to the beginning of the disk
        seekTime += absDiff(currentPosition, 0);
    }

    printf("SCAN Seek Time: %d\n", seekTime);
}

// Function to perform C-SCAN disk scheduling
void CSCAN(int requestQueue[], int n, int initialPosition) {
    int seekTime = 0;
    int currentPosition = initialPosition;

    // Sort the request queue in ascending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (requestQueue[j] > requestQueue[j + 1]) {
                // Swap the elements if they are in the wrong order
                int temp = requestQueue[j];
                requestQueue[j] = requestQueue[j + 1];
                requestQueue[j + 1] = temp;
            }
        }
    }

    // Find the index of the current position in the sorted request queue
    int currentIndex;
    for (currentIndex = 0; currentIndex < n; currentIndex++) {
        if (requestQueue[currentIndex] >= currentPosition) {
            break;
        }
    }

    // Move from the current position to the end of the disk
    for (int i = currentIndex; i < n; i++) {
        seekTime += absDiff(currentPosition, requestQueue[i]);
        currentPosition = requestQueue[i];
    }

    // Move from the beginning of the disk to the start of the request queue
    seekTime += absDiff(currentPosition, 199);
    currentPosition = 0;

    // Move from the start of the request queue to the end of the request queue
    for (int i = 0; i < currentIndex; i++) {
        seekTime += absDiff(currentPosition, requestQueue[i]);
        currentPosition = requestQueue[i];
    }

    printf("C-SCAN Seek Time: %d\n", seekTime);
}

// Function to perform LOOK disk scheduling
void LOOK(int requestQueue[], int n, int initialPosition, int direction) {
    int seekTime = 0;
    int currentPosition = initialPosition;

    // Sort the request queue in ascending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (requestQueue[j] > requestQueue[j + 1]) {
                // Swap the elements if they are in the wrong order
                int temp = requestQueue[j];
                requestQueue[j] = requestQueue[j + 1];
                requestQueue[j + 1] = temp;
            }
        }
    }

    // Find the index of the current position in the sorted request queue
    int currentIndex;
    for (currentIndex = 0; currentIndex < n; currentIndex++) {
        if (requestQueue[currentIndex] >= currentPosition) {
            break;
        }
    }

    // Calculate seek time based on the direction
    if (direction == 1) {
        // Move from left to right
        for (int i = currentIndex; i < n; i++) {
            seekTime += absDiff(currentPosition, requestQueue[i]);
            currentPosition = requestQueue[i];
        }
    } else {
        // Move from right to left
        for (int i = currentIndex - 1; i >= 0; i--) {
            seekTime += absDiff(currentPosition, requestQueue[i]);
            currentPosition = requestQueue[i];
        }
    }

    printf("LOOK Seek Time: %d\n", seekTime);
}

// Function to perform C-LOOK disk scheduling
void CLOOK(int requestQueue[], int n, int initialPosition) {
    int seekTime = 0;
    int currentPosition = initialPosition;

    // Sort the request queue in ascending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (requestQueue[j] > requestQueue[j + 1]) {
                // Swap the elements if they are in the wrong order
                int temp = requestQueue[j];
                requestQueue[j] = requestQueue[j + 1];
                requestQueue[j + 1] = temp;
            }
        }
    }

    // Find the index of the current position in the sorted request queue
    int currentIndex;
    for (currentIndex = 0; currentIndex < n; currentIndex++) {
        if (requestQueue[currentIndex] >= currentPosition) {
            break;
        }
    }

    // Move from the current position to the end of the request queue
    for (int i = currentIndex; i < n; i++) {
        seekTime += absDiff(currentPosition, requestQueue[i]);
        currentPosition = requestQueue[i];
    }

    // Move from the start of the request queue to the current position
    for (int i = 0; i < currentIndex; i++) {
        seekTime += absDiff(currentPosition, requestQueue[i]);
        currentPosition = requestQueue[i];
    }

    printf("C-LOOK Seek Time: %d\n", seekTime);
}

// Function to perform SSTF disk scheduling
void SSTF(int requestQueue[], int n, int initialPosition) {
    int seekTime = 0;
    int currentPosition = initialPosition;

    // Sort the request queue based on the absolute difference from the current position
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (absDiff(currentPosition, requestQueue[j]) > absDiff(currentPosition, requestQueue[j + 1])) {
                // Swap the elements if they are in the wrong order
                int temp = requestQueue[j];
                requestQueue[j] = requestQueue[j + 1];
                requestQueue[j + 1] = temp;
            }
        }
    }

    // Iterate through the sorted request queue
    for (int i = 0; i < n; i++) {
        // Calculate seek time for the current request
        seekTime += absDiff(currentPosition, requestQueue[i]);

        // Set the current position to the requested position
        currentPosition = requestQueue[i];
    }

    printf("SSTF Seek Time: %d\n", seekTime);
}

int main() {
    int choice, n, initialPosition, direction;

    // Get the number of requests
    printf("Enter the number of requests: ");
    scanf("%d", &n);

    // Get the initial position of the disk head
    printf("Enter the initial position of the disk head: ");
    scanf("%d", &initialPosition);

    // Get the direction for SCAN and LOOK
    printf("Enter the direction for SCAN and LOOK (1 for left to right, -1 for right to left): ");
    scanf("%d", &direction);

    // Get the request queue
    int requestQueue[n];
    printf("Enter the request queue:\n");
    for (int i = 0; i < n; i++) {
        printf("Request %d: ", i + 1);
        scanf("%d", &requestQueue[i]);
    }

    // Display the menu
    printf("\nDisk Scheduling Techniques Menu:\n");
    printf("1. FIFO\n");
    printf("2. SCAN\n");
    printf("3. C-SCAN\n");
    printf("4. LOOK\n");
    printf("5. C-LOOK\n");
    printf("6. SSTF\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            FIFO(requestQueue, n, initialPosition);
            break;
        case 2:
            SCAN(requestQueue, n, initialPosition, direction);
            break;
        case 3:
            CSCAN(requestQueue, n, initialPosition);
            break;
        case 4:
            LOOK(requestQueue, n, initialPosition, direction);
            break;
        case 5:
            CLOOK(requestQueue, n, initialPosition);
            break;
        case 6:
            SSTF(requestQueue, n, initialPosition);
            break;
        default:
            printf("Invalid choice\n");
    }

    return 0;
}
