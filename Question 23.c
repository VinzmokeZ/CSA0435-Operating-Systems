#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 10
#define MAX_PROCESSES 10

int blocks[MAX_BLOCKS];
int processes[MAX_PROCESSES];
int block_count, process_count;

void first_fit() {
    int allocation[MAX_PROCESSES];

    for (int i = 0; i < process_count; i++) {
        allocation[i] = -1; // Initialize allocation for each process

        for (int j = 0; j < block_count; j++) {
            if (blocks[j] >= processes[i]) {
                allocation[i] = j; // Allocate process to block j
                blocks[j] -= processes[i];
                break;
            }
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < process_count; i++) {
        printf("%d\t\t%d\t\t", i + 1, processes[i]);
        if (allocation[i] != -1) {
            printf("%d\n", allocation[i] + 1);
        } else {
            printf("Not Allocated\n");
        }
    }
}

int main() {
    printf("Enter the number of memory blocks: ");
    scanf("%d", &block_count);

    printf("Enter the size of each memory block:\n");
    for (int i = 0; i < block_count; i++) {
        scanf("%d", &blocks[i]);
    }

    printf("Enter the number of processes: ");
    scanf("%d", &process_count);

    printf("Enter the size of each process:\n");
    for (int i = 0; i < process_count; i++) {
        scanf("%d", &processes[i]);
    }

    first_fit();

    return 0;
}

