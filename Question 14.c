#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file1, *file2, *file3;

    // Create three files in the current directory
    file1 = fopen("file1.txt", "w");
    if (file1 == NULL) {
        perror("Unable to create file1.txt");
        exit(1);
    }
    fprintf(file1, "This is file1.txt\n");
    fclose(file1);

    file2 = fopen("file2.txt", "w");
    if (file2 == NULL) {
        perror("Unable to create file2.txt");
        exit(1);
    }
    fprintf(file2, "This is file2.txt\n");
    fclose(file2);

    file3 = fopen("file3.txt", "w");
    if (file3 == NULL) {
        perror("Unable to create file3.txt");
        exit(1);
    }
    fprintf(file3, "This is file3.txt\n");
    fclose(file3);

    // Open and read each file
    file1 = fopen("file1.txt", "r");
    if (file1 == NULL) {
        perror("Unable to open file1.txt");
        exit(1);
    }
    printf("Contents of file1.txt:\n");
    char c;
    while ((c = fgetc(file1)) != EOF) {
        putchar(c);
    }
    fclose(file1);

    file2 = fopen("file2.txt", "r");
    if (file2 == NULL) {
        perror("Unable to open file2.txt");
        exit(1);
    }
    printf("\n\nContents of file2.txt:\n");
    while ((c = fgetc(file2)) != EOF) {
        putchar(c);
    }
    fclose(file2);

    file3 = fopen("file3.txt", "r");
    if (file3 == NULL) {
        perror("Unable to open file3.txt");
        exit(1);
    }
    printf("\n\nContents of file3.txt:\n");
    while ((c = fgetc(file3)) != EOF) {
        putchar(c);
    }
    fclose(file3);

    return 0;
}
