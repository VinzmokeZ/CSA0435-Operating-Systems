#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_ITEMS 10

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t mutex, full, empty;

void *producer(void *arg) {
    for (int i = 0; i < NUM_ITEMS; ++i) {
        sem_wait(&empty);
        sem_wait(&mutex);

        // Produce item
        buffer[in] = i;
        printf("Produced item %d\n", i);
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex);
        sem_post(&full);

        // Sleep to simulate production time
        usleep(100000); // 100ms
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    for (int i = 0; i < NUM_ITEMS; ++i) {
        sem_wait(&full);
        sem_wait(&mutex);

        // Consume item
        int item = buffer[out];
        printf("Consumed item %d\n", item);
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&mutex);
        sem_post(&empty);

        // Sleep to simulate consumption time
        usleep(200000); // 200ms
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t prod_thread, cons_thread;

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, BUFFER_SIZE);

    // Create producer and consumer threads
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // Join threads
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

    return 0;
}

