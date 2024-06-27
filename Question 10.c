#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define MSG_SIZE 256  // Maximum size of the message

// Structure for the message
struct msg_buffer {
    long msg_type;  // Message type (must be greater than 0)
    char msg_text[MSG_SIZE];  // Message content
};

int main() {
    key_t key = 1234;  // Unique key for the message queue
    int msgid;
    struct msg_buffer message;

    // Create the message queue
    if ((msgid = msgget(key, IPC_CREAT | 0666)) == -1) {
        perror("msgget");
        exit(1);
    }

    // Fork a child process
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // Child process (receiver)
        // Receive the message from the message queue
        if (msgrcv(msgid, &message, sizeof(message), 1, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }

        printf("Message received by the child process: %s\n", message.msg_text);
    } else {
        // Parent process (sender)
        // Prepare the message
        message.msg_type = 1;  // Message type
        strcpy(message.msg_text, "Hello from the parent process!");  // Message content

        // Send the message to the message queue
        if (msgsnd(msgid, &message, sizeof(message), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }

        printf("Message sent by the parent process\n");
    }

    return 0;
}

