#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

pthread_mutex_t mutex;
sem_t writer_sem, reader_sem;
int reader_count = 0;

void *reader(void *arg) {
    while (1) {
        // Reader entry section
        sem_wait(&reader_sem);
        pthread_mutex_lock(&mutex);
        reader_count++;
        if (reader_count == 1) {
            sem_wait(&writer_sem); // No writers can write while readers are reading
        }
        pthread_mutex_unlock(&mutex);
        sem_post(&reader_sem);

        // Reading section
        printf("Reader %d is reading\n", *(int *)arg);
        sleep(1); // Simulate reading time

        // Reader exit section
        pthread_mutex_lock(&mutex);
        reader_count--;
        if (reader_count == 0) {
            sem_post(&writer_sem); // Allow writers to write now
        }
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void *writer(void *arg) {
    while (1) {
        sem_wait(&writer_sem);

        // Writing section
        printf("Writer %d is writing\n", *(int *)arg);
        sleep(2); // Simulate writing time

        sem_post(&writer_sem);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];

    // Initialize mutex and semaphores
    pthread_mutex_init(&mutex, NULL);
    sem_init(&writer_sem, 0, 1);
    sem_init(&reader_sem, 0, NUM_READERS);

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Join threads
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroy mutex and semaphores
    pthread_mutex_destroy(&mutex);
    sem_destroy(&writer_sem);
    sem_destroy(&reader_sem);

    return 0;
}

