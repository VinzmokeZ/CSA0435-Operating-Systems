#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

#define MAX_FILENAME_LEN 256

// Function to create directories
void createDirectories() {
    mkdir("dir1", 0777);
    mkdir("dir2", 0777);
}

// Function to move files into directories
void moveFiles() {
    // Move files to dir1
    system("mv file1.txt dir1/");
    system("mv file2.txt dir1/");

    // Move files to dir2
    system("mv file3.txt dir2/");
    system("mv file4.txt dir2/");
}

// Function to list contents of directories
void listDirectories() {
    DIR *dir;
    struct dirent *ent;
    struct stat st;
    char filename[MAX_FILENAME_LEN];

    // List contents of dir1
    printf("Contents of dir1:\n");
    dir = opendir("dir1");
    while ((ent = readdir(dir)) != NULL) {
        snprintf(filename, sizeof(filename), "dir1/%s", ent->d_name);
        if (stat(filename, &st) == 0 && S_ISREG(st.st_mode)) {
            printf("%s\n", ent->d_name);
        }
    }
    closedir(dir);

    // List contents of dir2
    printf("\nContents of dir2:\n");
    dir = opendir("dir2");
    while ((ent = readdir(dir)) != NULL) {
        snprintf(filename, sizeof(filename), "dir2/%s", ent->d_name);
        if (stat(filename, &st) == 0 && S_ISREG(st.st_mode)) {
            printf("%s\n", ent->d_name);
        }
    }
    closedir(dir);
}

int main() {
    // Create directories
    createDirectories();

    // Move files into directories
    moveFiles();

    // List contents of directories
    listDirectories();

    return 0;
}

