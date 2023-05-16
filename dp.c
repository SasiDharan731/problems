#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define LEFT (i + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS
#define RIGHT (i + 1) % NUM_PHILOSOPHERS

pthread_mutex_t chopsticks[NUM_PHILOSOPHERS];

void *philosopher(void *arg)
{
    int i = *(int *)arg;
    while (1)
    {
        printf("Philosopher %d is thinking...\n", i);
        usleep(rand() % 1000000); // wait for random time
        printf("Philosopher %d is hungry and wants to eat.\n", i);
        pthread_mutex_lock(&chopsticks[LEFT]);
        printf("Philosopher %d picks up left chopstick %d.\n", i, LEFT);
        pthread_mutex_lock(&chopsticks[RIGHT]);
        printf("Philosopher %d picks up right chopstick %d.\n", i, RIGHT);
        printf("Philosopher %d is eating.\n", i);
        usleep(rand() % 1000000); // eat for random time
        pthread_mutex_unlock(&chopsticks[LEFT]);
        printf("Philosopher %d puts down left chopstick %d.\n", i, LEFT);
        pthread_mutex_unlock(&chopsticks[RIGHT]);
        printf("Philosopher %d puts down right chopstick %d.\n", i, RIGHT);
    }
}

int main()
{
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    // Initialize the mutexes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_mutex_init(&chopsticks[i], NULL);
    }

    // Create the philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Wait for the philosopher threads to finish
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy the mutexes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_mutex_destroy(&chopsticks[i]);
    }

    return 0;
}
