#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <fcntl.h> 
 
int main() {     // File descriptor     int fd; 
    // Create a new file or open an existing file for writing 
    fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR); 
    if (fd == -1) {         perror("open"); 
        exit(EXIT_FAILURE); 
    } 
    // Write data to the file 
    const char *data = "Hello, UNIX System Calls!";     ssize_t bytes_written = write(fd, data, strlen(data));     if (bytes_written == -1) {         perror("write");         close(fd); 
        exit(EXIT_FAILURE); 
    } 
    printf("Data written to the file: %s\n", data); 
 
    // Close the file     if (close(fd) == -1) {         perror("close"); 
        exit(EXIT_FAILURE); 
    } 
 
    // Open the file for reading 
    fd = open("example.txt", O_RDONLY); 
    if (fd == -1) {         perror("open"); 
        exit(EXIT_FAILURE); 
    } 
    // Read data from the file     char buffer[100];     ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);     if (bytes_read == -1) {         perror("read");         close(fd); 
        exit(EXIT_FAILURE); 
    } 
    buffer[bytes_read] = '\0'; // Null-terminate the string     printf("Data read from the file: %s\n", buffer); 
    // Close the file     if (close(fd) == -1) {         perror("close"); 
        exit(EXIT_FAILURE); 
    }     return 0; 
} 
