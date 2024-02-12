#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 4096  // Assuming a page size of 4 KB

// Function to calculate the physical address
unsigned int translateAddress(unsigned int logicalAddress, unsigned int *pageTable, unsigned int pageSize) {
    unsigned int pageNumber = logicalAddress / pageSize;
    unsigned int offset = logicalAddress % pageSize;

    // Check if the page number is within the valid range
    if (pageNumber >= PAGE_SIZE) {
        printf("Error: Page number exceeds the maximum limit.\n");
        exit(1);
    }

    // Check if the page table entry is valid
    if (pageTable[pageNumber] == -1) {
        printf("Error: Page not in memory.\n");
        exit(1);
    }

    // Calculate the physical address
    unsigned int physicalAddress = (pageTable[pageNumber] * pageSize) + offset;
    return physicalAddress;
}

int main() {
    unsigned int logicalAddress, pageSize, pageCount, i;

    // Get the range of physical and logical addresses
    printf("Enter the range of logical addresses: ");
    scanf("%u", &pageCount);

    printf("Enter the page size: ");
    scanf("%u", &pageSize);

    // Allocate memory for the page table
    unsigned int *pageTable = (unsigned int *)malloc(pageCount * sizeof(unsigned int));

    // Initialize the page table entries (assuming -1 represents a page not in memory)
    for (i = 0; i < pageCount; i++) {
        pageTable[i] = -1;
    }

    // Populate the page table (you can modify this part based on your requirements)
    for (i = 0; i < pageCount; i++) {
        printf("Enter the frame number for page %u: ", i);
        scanf("%u", &pageTable[i]);
    }

    // Get the logical address to be translated
    printf("Enter the logical address to be translated: ");
    scanf("%u", &logicalAddress);

    // Translate the logical address to physical address and print the result
    unsigned int physicalAddress = translateAddress(logicalAddress, pageTable, pageSize);
    printf("Physical Address: %u\n", physicalAddress);

    // Free the allocated memory
    free(pageTable);

    return 0;
}
