#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
//#include "./mylib/myHMMheader.h"

#define NUM_ALLOCS 10000
#define MAX_SIZE 10240
#define MAX_ITERATIONS 1000000

void random_alloc_free_test() {
    srand((unsigned int)time(NULL));
    
    char* pointers[NUM_ALLOCS] = {NULL};  // Use char* for the pointers array
    
    for (int i = 0; i < MAX_ITERATIONS; ++i) {
        int index = rand() % NUM_ALLOCS;
        if (pointers[index] == NULL) {
            // Allocate memory
            size_t size = (size_t)(rand() % MAX_SIZE) + 1;
         //  sleep(1);
            pointers[index] = (char*)malloc(size);
            if (pointers[index] != NULL) {
                printf("Allocated memory of size %zu at address %p\n", size, pointers[index]);
                
                // Write data based on size allocated
                size_t dataSize = (size > 52) ? 52 : size; // Ensure the data fits
                for (size_t j = 0; j < dataSize; ++j) {
                    pointers[index][j] = 'A' + (j % 26); // Fill with A, B, C, etc.
                }
                pointers[index][dataSize] = '\0';  // Null-terminate string
                
                printf("Data written: %s\n", pointers[index]);
            } else {
                fprintf(stderr, "Allocation failed for size %zu\n", size);
            }
        } else {
            printf("Data read from allocated memory: %s\n", pointers[index]);
         //   pointers[index]=realloc(pointers[index],(size_t)(rand() % MAX_SIZE) + 1);
            // Free memory
            printf("Freeing memory at address %p\n", pointers[index]);
            free(pointers[index]);
            pointers[index] = NULL;
        }
    }

    // Free remaining allocated memory
    for (int i = 0; i < NUM_ALLOCS; ++i) {
        if (pointers[i] != NULL) {
            printf("Freeing remaining memory at address %p\n", pointers[i]);
            free(pointers[i]);
            pointers[i] = NULL;
        }
    }
}

int main() {
    printf("Starting random allocation and deallocation test...\n");
    random_alloc_free_test();
    printf("Test complete.\n");
    return 0;
}

