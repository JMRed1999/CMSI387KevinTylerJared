#include <stdio.h>
#include <stdlib.h>

#define MAX_THREADS 8
#define QUANTUM 40

struct ThreadContainer
{
    char *label;
    int timeslice;
};

int allThreadsCompleted(struct ThreadContainer containers[], int threadCount)
{
    for (int i = 0; i < threadCount; i++)
    {
        if (containers[i].timeslice > 0)
        {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        return 0;
    }

    int threadCount = 0;
    struct ThreadContainer containers[MAX_THREADS];

    for (int j = 1; j < argc; j += 2)
    {
        containers[threadCount].label = argv[j];
        containers[threadCount].timeslice = atoi(argv[j + 1]);
        threadCount++;
    }

    printf("\n%s\n\n", "KEY -- thread:used:remaining");

    char tsString[50];
    int currentThreadIndex = 0;
    struct ThreadContainer *currentThread = &containers[currentThreadIndex];

    while (!allThreadsCompleted(containers, threadCount))
    {
        if (currentThread->timeslice <= 0)
        {
            currentThread = &containers[++currentThreadIndex % threadCount];
            continue;
        }

        int diff = currentThread->timeslice >= QUANTUM ? QUANTUM : currentThread->timeslice;
        currentThread->timeslice -= diff;

        sprintf(tsString, "%d", currentThread->timeslice);
        printf("%s:%d:%s\n", currentThread->label, diff, currentThread->timeslice > 0 ? tsString : "done");

        currentThread = &containers[++currentThreadIndex % threadCount];
    }
}
