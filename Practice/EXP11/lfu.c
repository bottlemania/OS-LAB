#include <stdio.h>

#define MAX_FRAMES 3

void printFrames(int frames[], int counters[], int n) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == -1) {
            printf(" - ");
        } else {
            printf(" %d(%d) ", frames[i], counters[i]);
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

int findLFUIndex(int counters[], int n) {
    int min = counters[0];
    int minIndex = 0;

    for (int i = 1; i < n; i++) {
        if (counters[i] < min) {
            min = counters[i];
            minIndex = i;
        }
    }

    return minIndex;
}

void lfu(int pages[], int pcount, int frames[], int fcount) {
    int faults=0,hit=0;
    int counter[MAX_FRAMES];

    for (int i = 0; i < fcount; i++) {
        frames[i] = -1; // Initialize frames with -1 indicating empty
        counter[i] = 0;
    }

    for (int i = 0; i < pcount; i++) {
        printf("Reference: %d - Frames:", pages[i]);
        printFrames(frames, counter, fcount);

        if (!isPageInFrames(frames, fcount, pages[i])) {
            int lfuIndex = findLFUIndex(counter, fcount);
            frames[lfuIndex] = pages[i];
            counter[lfuIndex] = 1;
            faults++;
            printf("Page Fault!\n");
        } else {
            // Update counter for the page hit
            for (int j = 0; j < fcount; j++) {
                if (frames[j] == pages[i]) {
                    counter[j]++;
                    break;
                }
            }
            hit++;
            printf("Page Hit!\n");
        }
    }
    float hitRatio = (float)hit/pcount;
    float missRatio = (float)faults/pcount;
    printf("\nNo of page faults: %d \n",faults);
    printf("No of hits: %d \n",hit);
    printf("Hit Ratio : %.2f \n",hitRatio*100);
    printf("Miss Ratio : %.2f \n",missRatio*100);
}

int main() {
    int pages[] = {7,0,1,2,0,3,0,4,2,3,0,3,2,1,2}; // Reference string
    int frameCount = MAX_FRAMES;
    int frames[MAX_FRAMES];
    lfu(pages, sizeof(pages) / sizeof(pages[0]), frames, frameCount);
    return 0;
}
