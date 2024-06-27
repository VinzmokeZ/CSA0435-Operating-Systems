#include <stdio.h> 
#include <stdlib.h> 
 
int main() { 
    FILE *file; // File pointer 
 
    // File creation and writing     file = fopen("example.txt", "w");     if (file == NULL) {         perror("Error creating file"); 
        exit(EXIT_FAILURE); 
    } 
 
    fprintf(file, "Hello, File Management!\n"); 
    fclose(file); 
 
    printf("File 'example.txt' created and written to.\n"); 
 
    // File reading     file = fopen("example.txt", "r");     if (file == NULL) {         perror("Error opening file for reading");         exit(EXIT_FAILURE); 
    } 
 
    char buffer[100];     fgets(buffer, sizeof(buffer), file); 
 
    printf("Content read from file: %s", buffer); 
 
    fclose(file); 
 
    return 0; 
} 
