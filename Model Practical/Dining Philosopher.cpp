#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define LEFT (ph_num + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS
#define RIGHT (ph_num + 1) % NUM_PHILOSOPHERS

pthread_mutex_t mutex;
int state[NUM_PHILOSOPHERS];
pthread_mutex_t S[NUM_PHILOSOPHERS];

void *philosopher(void *num);
void take_forks(int ph_num);
void put_forks(int ph_num);
void test(int ph_num);

int main() {
    pthread_t tid[NUM_PHILOSOPHERS];
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_mutex_init(&S[i], NULL);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_create(&tid[i], NULL, philosopher, (void *)&i);
        printf("Philosopher %d is thinking\n", i + 1);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_join(tid[i], NULL);

    pthread_mutex_destroy(&mutex);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_mutex_destroy(&S[i]);

    return 0;
}

void *philosopher(void *num) {
    int ph_num = *((int *)num);

    while (1) {
        sleep(rand() % 5 + 1); // thinking
        take_forks(ph_num);
        sleep(rand() % 3 + 1); // eating
        put_forks(ph_num);
    }
}

void take_forks(int ph_num) {
    pthread_mutex_lock(&mutex);
    state[ph_num] = HUNGRY;
    printf("Philosopher %d is Hungry\n", ph_num + 1);
    test(ph_num);
    pthread_mutex_unlock(&mutex);
    pthread_mutex_lock(&S[ph_num]);
}

void put_forks(int ph_num) {
    pthread_mutex_lock(&mutex);
    state[ph_num] = THINKING;
    printf("Philosopher %d putting forks down\n", ph_num + 1);
    printf("Philosopher %d is thinking\n", ph_num + 1);
    test(LEFT);
    test(RIGHT);
    pthread_mutex_unlock(&mutex);
}

void test(int ph_num) {
    if (state[ph_num] == HUNGRY &&
        state[LEFT] != EATING &&
        state[RIGHT] != EATING) {
        state[ph_num] = EATING;
        printf("Philosopher %d takes forks %d and %d\n", ph_num + 1, LEFT + 1, ph_num + 1);
        printf("Philosopher %d is Eating\n", ph_num + 1);
        pthread_mutex_unlock(&S[ph_num]);
    }
}

