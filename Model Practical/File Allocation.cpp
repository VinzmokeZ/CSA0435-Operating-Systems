#include <stdio.h>
#include <string.h>

#define MAX_FILES 10
#define DISK_SIZE 1000

struct File {
    char name[20];
    int start;
    int size;
};

struct File files[MAX_FILES];
int fileCount = 0;
int disk[DISK_SIZE] = {0};

int allocateFile(char name[], int size) {
    if (fileCount >= MAX_FILES) {
        printf("Error: Maximum file limit reached.\n");
        return -1;
    }

    int start = -1;

    for (int i = 0; i <= DISK_SIZE - size; i++) {
        int freeSpace = 1;
        for (int j = 0; j < size; j++) {
            if (disk[i + j] != 0) {
                freeSpace = 0;
                break;
            }
        }

        if (freeSpace) {
            start = i;
            break;
        }
    }

    if (start == -1) {
        printf("Error: Not enough contiguous space available.\n");
        return -1;
    }

    for (int i = start; i < start + size; i++) {
        disk[i] = 1;
    }

    strcpy(files[fileCount].name, name);
    files[fileCount].start = start;
    files[fileCount].size = size;
    fileCount++;

    printf("File '%s' allocated at starting block %d with size %d.\n", name, start, size);
    return start;
}

void displayFiles() {
    printf("File Allocation Table:\n");
    printf("Name\tStart\tSize\n");
    for (int i = 0; i < fileCount; i++) {
        printf("%s\t%d\t%d\n", files[i].name, files[i].start, files[i].size);
    }
}

int main() {
    allocateFile("file1.txt", 200);
    allocateFile("file2.txt", 300);
    allocateFile("file3.txt", 100);
    allocateFile("file4.txt", 150);

    displayFiles();

    return 0;
}
