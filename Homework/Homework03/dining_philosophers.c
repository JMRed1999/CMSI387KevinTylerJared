#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#ifdef _WIN32
#include <semaphore.h>
#endif

#ifdef __APPLE__
#include <dispatch/dispatch.h>
#endif

#define NUM_PHILOSOPHERS 5
#define IDLE 2
#define HUNGRY 1
#define EATING 0
#define LEFT (philosopher + 4) % NUM_PHILOSOPHERS
#define RIGHT (philosopher + 1) % NUM_PHILOSOPHERS

int state[NUM_PHILOSOPHERS];
int philosophers[NUM_PHILOSOPHERS] = {0, 1, 2, 3, 4};

#ifdef _WIN32
sem_t mutex;
sem_t sticks[NUM_PHILOSOPHERS];
#endif

#ifdef __APPLE__
dispatch_semaphore_t mutex;
dispatch_semaphore_t sticks[NUM_PHILOSOPHERS];
#endif

void scan_neighbors(int philosopher)
{
    if (state[philosopher] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
    {
        state[philosopher] = EATING;

        // Wait before broadcasting to other philosophers that the current philosopher is eating.
        sleep(1);

        printf("Philosopher %d takes chopstick #%d from their left and chopstick %d from their right\n",
               philosopher + 1, LEFT + 1, philosopher + 1);

        printf("Philosopher %d is now eating\n", philosopher + 1);
    }
}

void pickup_chopstick(int philosopher)
{
    // Wait until the neighboring philosopher broadcasts that they are done eating before attempting to acquire a chopstick
    if (TARGET_OS_WIN32)
    {
        sem_wait(&mutex);
    }
    else
    {
        dispatch_semaphore_wait(mutex, 0);
    }

    state[philosopher] = HUNGRY;

    printf("Philosopher %d is Hungry and needs a chopstick\n", philosopher + 1);

    // Scan each neighbor and begin eating only if both chopsticks are available
    scan_neighbors(philosopher);

    // Unlock the universal mutex after scanning neighbors.
    if (TARGET_OS_WIN32)
    {
        sem_post(&mutex);
    }
    else
    {
        dispatch_semaphore_signal(mutex);
    }

    // Wait until chopsticks are available.
    if (TARGET_OS_WIN32)
    {
        sem_wait(&sticks[philosopher]);
    }
    else
    {
        dispatch_semaphore_wait(mutex, 0);
    }

    sleep(1);
}

void putdown_chopstick(int philosopher)
{

    // Wait until the neighboring philosopher broadcasts that they are done eating before attempting to put down a chopstick
    if (TARGET_OS_WIN32)
    {
        sem_wait(&mutex);
    }
    else
    {
        dispatch_semaphore_wait(mutex, 0);
    }

    // Update state to "IDLE" since the philosopher is releasing their chopsticks
    state[philosopher] = IDLE;

    printf("Philosopher %d is putting down chopstick #%d from their left and chopstick #%d from their right\n",
           philosopher + 1, LEFT + 1, philosopher + 1);
    printf("Philosopher %d is IDLE\n", philosopher + 1);

    // Examine the philosopher's state to the current philosopher's left.
    scan_neighbors(LEFT);
    // Examine the philosopher's state to the current philosopher's right.
    scan_neighbors(RIGHT);

    // After scanning their neighbors, notify the philosophers that the current philosopher is now idle unlocking the global state.
    if (TARGET_OS_WIN32)
    {
        sem_post(&mutex);
    }
    else
    {
        dispatch_semaphore_signal(mutex);
    }
}

void *dine(void *philosopher)
{

    while (1)
    {

        int *p_pointer = philosopher;

        // Wait before picking up another stick (in case another philosopher is eating)
        sleep(1);

        // Acquire the chopstick
        pickup_chopstick(*p_pointer);

        // Release the chopstick
        putdown_chopstick(*p_pointer);
    }
}

void commence_dining(pthread_t *threads)
{
    // Fork a thread for each philosopher in order to start the simulation
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_create(&threads[i], NULL, dine, &philosophers[i]);
    }

    // Wait for each thread to finish executing; however, for this problem the simulation is endless.
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_join(threads[i], NULL);
    }
}

int mac_start()
{
    // Declare threads
    pthread_t threads[NUM_PHILOSOPHERS];

    // Create universal mutex to handle synchronization among threads.
    mutex = dispatch_semaphore_create(1);

    // Initialize semaphores for synchronization among occupying chopsticks
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        sticks[i] = dispatch_semaphore_create(0);
    }

    // Commence "dining" simulation
    commence_dining(threads);

    return 0;
}

int win_start()
{
    // Declare threads
    pthread_t threads[NUM_PHILOSOPHERS];

    // Create universal mutex to handle synchronization among threads.
    sem_init(&mutex, 0, 1);

    // Initialize semaphores for synchronization among occupying chopsticks
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        sem_init(&sticks[i], 0, 0);
    }

    // Commence "dining" simulation
    commence_dining(threads);

    return 0;
}

int main()
{
    if (TARGET_OS_OSX)
    {
        return mac_start();
    }
    if (TARGET_OS_WIN32)
    {
        return win_start();
    }

    printf("Valid implementation provided for Windows and OSX Operating Systems only.\n");
    return 0;
}
