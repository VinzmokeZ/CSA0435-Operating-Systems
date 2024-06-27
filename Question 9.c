#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 1024  // Size of the shared memory segment

int main() {
    key_t key = 1234;  // Unique key for the shared memory segment
    int shmid;
    char *shmaddr;

    // Create the shared memory segment
    if ((shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    // Attach the shared memory segment to the writer's address space
    if ((shmaddr = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    // Write a message into the shared memory
    strcpy(shmaddr, "Hello from the writer!");

    // Detach the shared memory segment from the writer's address space
    shmdt(shmaddr);

    // Fork a new process for the reader
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // Child process (reader)
        // Attach the shared memory segment to the reader's address space
        if ((shmaddr = shmat(shmid, NULL, 0)) == (char *) -1) {
            perror("shmat");
            exit(1);
        }

        // Read and print the message from the shared memory
        printf("Message read by the reader: %s\n", shmaddr);

        // Detach the shared memory segment from the reader's address space
        shmdt(shmaddr);
    } else {
        // Parent process (writer)
        // Wait for the child process to finish
        wait(NULL);
    }

    // Delete the shared memory segment
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
