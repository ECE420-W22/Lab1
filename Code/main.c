#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>
#include "lab1_IO.h"
#include "timer.h"

// Global variables for the matrices
int n;
int **A;
int **B;
int **C;
int numThreads;

// Thread creation function for calculating its block
void *MatrixThreadCalculate(void *rank)
{
    long myRank = (long)rank;
    // Calculate block coordinates that thread is responsible for computing
    int x = myRank / (int)sqrt(numThreads);
    int y = myRank % (int)sqrt(numThreads);
    // Calculate product matrix index range that thread is responsible for
    int x_begin = (n / (int)sqrt(numThreads)) * x;
    int x_end = (n / (int)sqrt(numThreads)) * (x + 1);
    int y_begin = (n / (int)sqrt(numThreads)) * y;
    int y_end = (n / (int)sqrt(numThreads)) * (y + 1);
    // Solve the block
    for (int i = x_begin; i < x_end; i++)
    {
        for (int j = y_begin; j < y_end; j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main(int argc, char *argv[])
{
    double startTime;
    double endTime;
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
    numThreads = strtol(argv[1], NULL, 10);

    // Load input of the matrices
    Lab1_loadinput(&A, &B, &n);
    // malloc for the resultant matrix
    C = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        C[i] = malloc(n * sizeof(int));
    // Create an array of threads
    long thread;
    pthread_t *threadHandles;
    threadHandles = malloc(numThreads * sizeof(pthread_t));
    // Create threads and calculate matrix
    GET_TIME(startTime);
    for (thread = 0; thread < numThreads; thread++)
    {
        pthread_create(&threadHandles[thread], NULL, MatrixThreadCalculate, (void *)thread);
    }
    // Join all threads, waiting for them to finish calculating
    for (thread = 0; thread < numThreads; thread++)
    {
        pthread_join(threadHandles[thread], NULL);
    }
    GET_TIME(endTime);

    // Write the output
    Lab1_saveoutput(C, &n, endTime - startTime);

    // Free the matrices after done calculating
    for (int i = 0; i < n; i++)
    {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}