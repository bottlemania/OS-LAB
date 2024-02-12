#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FRAMES 3

void printFrames(int frames[], int n) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == -1) {
            printf(" - ");
        } else {
            printf(" %d ", frames[i]);
        }
    }
    printf("\n");
}

int isPageInFrames(int frames[], int n, int page) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == page) {
            return 1;
        }
    }
    return 0;
}

void randomPageReplacement(int pages[], int n, int frames[], int frameCount) {
    int pageFaults = 0;

    srand(time(NULL)); // Seed for the random number generator

    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1; // Initialize frames with -1 indicating empty
    }

    for (int i = 0; i < n; i++) {
        printf("Reference: %d - Frames:", pages[i]);
        printFrames(frames, frameCount);

        if (!isPageInFrames(frames, frameCount, pages[i])) {
            // Randomly select an index to replace
            int index = rand() % frameCount;
            frames[index] = pages[i];
            pageFaults++;
            printf("Page Fault!\n");
        } else {
            printf("Page Hit!\n");
        }
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);
}

int main() {
    int pages[] = {1, 3, 0, 3, 5, 6, 3}; // Reference string
    int frameCount = MAX_FRAMES;
    int frames[MAX_FRAMES];

    randomPageReplacement(pages, sizeof(pages) / sizeof(pages[0]), frames, frameCount);

    return 0;
}
