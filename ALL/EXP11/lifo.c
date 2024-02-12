#include <stdio.h>

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

void lifoPageReplacement(int pages[], int n, int frames[], int frameCount) {
    int pageFaults = 0;

    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1; // Initialize frames with -1 indicating empty
    }

    for (int i = 0; i < n; i++) {
        printf("Reference: %d - Frames:", pages[i]);
        printFrames(frames, frameCount);

        if (!isPageInFrames(frames, frameCount, pages[i])) {
            // Find the index of the last frame for replacement (LIFO)
            int lastInIndex = frameCount - 1;

            // Shift frames to make room for the new page
            for (int j = lastInIndex; j > 0; j--) {
                frames[j] = frames[j - 1];
            }

            // Bring the new page into the memory
            frames[0] = pages[i];

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

    lifoPageReplacement(pages, sizeof(pages) / sizeof(pages[0]), frames, frameCount);

    return 0;
}
