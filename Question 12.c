#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define LEFT (philosopher_id + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS
#define RIGHT (philosopher_id + 1) % NUM_PHILOSOPHERS

pthread_mutex_t mutex;
pthread_mutex_t forks[NUM_PHILOSOPHERS];
int philosopher_state[NUM_PHILOSOPHERS];

void *philosopher(void *arg) {
    int philosopher_id = *((int*)arg);

    while (1) {
        printf("Philosopher %d is thinking\n", philosopher_id);

        pthread_mutex_lock(&mutex);
        philosopher_state[philosopher_id] = HUNGRY;
        printf("Philosopher %d is hungry\n", philosopher_id);
        pthread_mutex_unlock(&mutex);

        pthread_mutex_lock(&forks[philosopher_id]);
        pthread_mutex_lock(&forks[RIGHT]);

        pthread_mutex_lock(&mutex);
        philosopher_state[philosopher_id] = EATING;
        printf("Philosopher %d is eating\n", philosopher_id);
        pthread_mutex_unlock(&mutex);

        sleep(rand() % 3 + 1); // Eating time

        pthread_mutex_unlock(&forks[philosopher_id]);
        pthread_mutex_unlock(&forks[RIGHT]);

        pthread_mutex_lock(&mutex);
        philosopher_state[philosopher_id] = THINKING;
        printf("Philosopher %d finished eating and is thinking\n", philosopher_id);
        pthread_mutex_unlock(&mutex);

        sleep(rand() % 3 + 1); // Thinking time
    }

    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}

