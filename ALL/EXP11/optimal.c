#include <stdio.h>
#include <limits.h>

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

int findOptimalIndex(int pages[], int frames[], int frameCount, int currentIndex, int n) {
    int index = -1;
    int farthest = currentIndex;

    for (int i = 0; i < frameCount; i++) {
        int j;
        for (j = currentIndex; j < n; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    index = i;
                }
                break;
            }
        }

        // If the page is not future referenced, break the loop
        if (j == n) {
            return i;
        }
    }

    if (index == -1) {
        return 0;
    } else {
        return index;
    }

}

void optimalPageReplacement(int pages[], int n, int frames[], int frameCount) {
    int pageFaults = 0;

    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1; // Initialize frames with -1 indicating empty
    }

    for (int i = 0; i < n; i++) {
        printf("Reference: %d - Frames:", pages[i]);
        printFrames(frames, frameCount);

        if (!isPageInFrames(frames, frameCount, pages[i])) {
            int index = findOptimalIndex(pages, frames, frameCount, i + 1, n);
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
    int pages[] = {7,0,1,2,0,3,0,4,2,3,0,3,2,1,2}; // Reference string
    int frameCount = MAX_FRAMES;
    int frames[MAX_FRAMES];

    optimalPageReplacement(pages, sizeof(pages) / sizeof(pages[0]), frames, frameCount);

    return 0;
}
