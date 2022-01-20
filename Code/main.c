#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "lab1_IO.h"
#include "timer.h"

// Global variables for the matrices
int n;
int **A;
int **B;
int **C;

void *MatrixThreadCalculate(void *rank)
{
    long myRank = (long)rank;
    printf("Thread #%ld\n", myRank);
}

int main(int argc, char *argv[])
{
    // Get number of threads as an argument
    if (argc > 2)
    {
        printf("Too many arguments\n");
        printf("Proper usage:\n  main <number of threads>\n");
        return 1;
    }
    else if (argc == 1)
    {
        printf("Proper usage:\n  main <number of threads>\n");
        return 1;
    }
    int numThreads = strtol(argv[1], NULL, 10);

    // Load input of the matrices
    Lab1_loadinput(&A, &B, &n);
    C = malloc(n * sizeof(int *));

    printf("hello %d threads requested\n", numThreads);
    // Create an array of threads
    long thread;
    pthread_t *threadHandles;
    threadHandles = malloc(numThreads * sizeof(pthread_t));
    // Create threads and calculate matrix
    for (thread = 0; thread < numThreads; thread++)
    {
        pthread_create(&threadHandles[thread], NULL, MatrixThreadCalculate, (void *)thread);
    }

    for (thread = 0; thread < numThreads; thread++)
    {
        pthread_join(threadHandles[thread], NULL);
    }

    return 0;
}