#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./header.h"


#define NUM_OPERATIONS 10000 // Number of allocation/free operations
#define MAX_ALLOC_SIZE 10240 // Max allocation size of 1 kB

// Placeholder functions for your custom heap manager
void* HmmAlloc(size_t size);
void HmmFree(void* ptr);

int main() {
    // Seed the random number generator
    srand((unsigned)time(NULL));

    // Array to hold pointers to allocated memory
    void* pointers[NUM_OPERATIONS] = {NULL};
    
    // Perform random allocations and frees
    for (int i = 0; i < NUM_OPERATIONS; i++) {
        // Randomly decide to allocate or free
        if (rand() % 2 == 0 || pointers[i] == NULL) {
            // Allocate memory of a random size
            size_t size = rand() % MAX_ALLOC_SIZE + 1;
            pointers[i] = HmmAlloc(size);
            if (pointers[i] == NULL) {
                printf("Allocation failed at operation\n");
            }else {
        	printf("Allocation Done at address %p\n",pointers[i]);
            // Free a random pointer
            int index = rand() % (i + 1);
            if (pointers[index] != NULL) {
            	printf("Freeing Allocation %p\n",pointers[index]);
                HmmFree(pointers[index]);
                pointers[index] = NULL;
            }
        } 
        }
    }

    // Cleanup: Free any remaining allocated memory
    for (int i = 0; i < NUM_OPERATIONS; i++) {
        if (pointers[i] != NULL) {
            HmmFree(pointers[i]);
            pointers[i] = NULL;
        }
    }

    printf("Test completed successfully.\n");
    return 0;
}


