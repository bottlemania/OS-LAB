#include <stdio.h>
#include <stdlib.h>

// Define the page table structure
struct PageTableEntry {
    int page_number;
    int frame_number;
};

int main() {
    int logical_address_range, physical_address_range, page_size;
    int num_pages, num_frames;

    // Input the range of logical and physical addresses
    printf("Enter the range of logical addresses: ");
    scanf("%d", &logical_address_range);

    printf("Enter the range of physical addresses: ");
    scanf("%d", &physical_address_range);

    // Input the page size
    printf("Enter the page size: ");
    scanf("%d", &page_size);

    // Calculate the number of pages and frames
    num_pages = logical_address_range / page_size;
    num_frames = physical_address_range / page_size;

    // Allocate memory for the page table
    struct PageTableEntry *page_table = (struct PageTableEntry *)malloc(num_pages * sizeof(struct PageTableEntry));

    // Construct the page table by mapping logical address to physical address
    for (int i = 0; i < num_pages; i++) {
        page_table[i].page_number = i;
        page_table[i].frame_number = rand() % num_frames; // Simulated frame assignment
    }

    // Simulate address translation
    int logical_address, page_number, offset, physical_address;
   
    printf("Enter a logical address to translate (0 - %d): ", logical_address_range - 1);
    scanf("%d", &logical_address);

    // Calculate page number and offset
    page_number = logical_address / page_size;
    offset = logical_address % page_size;

    // Search the page table to locate the base address
    int frame_number = -1;
    for (int i = 0; i < num_pages; i++) {
        if (page_table[i].page_number == page_number) {
            frame_number = page_table[i].frame_number;
            break;
        }
    }

    if (frame_number != -1) {
        // Calculate the physical address
        physical_address = frame_number * page_size + offset;
        printf("Logical Address: %d -> Physical Address: %d\n", logical_address, physical_address);
    } else {
        printf("Page not found in the page table. Page fault!\n");
    }

    free(page_table);
    return 0;
}