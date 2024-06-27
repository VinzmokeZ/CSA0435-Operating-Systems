#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 3

pthread_mutex_t mutex;
int counter = 0;

void *thread_function(void *arg) {
    // Acquire mutex lock
    pthread_mutex_lock(&mutex);

    // Critical section
    counter++;
    printf("Thread %d: Counter value = %d\n", *(int *)arg, counter);

    // Release mutex lock
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
    }

    // Join threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}

