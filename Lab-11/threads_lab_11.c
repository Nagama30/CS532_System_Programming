/* 
  Simple Pthread Program to find the sum of a vector.
  Uses mutex locks to update the global sum. 

  To Compile: gcc -O -Wall threads_lab_11.c -lpthread
  To Run: ./a.out 1000 4
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Initialize a mutex for synchronizing access to shared resources
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

// Define a structure to pass multiple data items to threads
typedef struct {
    double *a;         // Pointer to the array of elements
    double partialSum; // Sum computed by this thread
    int N;             // Total number of elements in the array
    int size;          // Total number of threads
    long tid;          // Thread ID
} t_data;

// Thread function to compute part of the sum
void *compute(void *arg) {
    t_data *data = (t_data *)arg;
    int myStart, myEnd, myN, i;

    // Calculate the portion of the array this thread will sum
    myN = data->N / data->size;
    myStart = data->tid * myN;
    myEnd = myStart + myN;
    // Last thread may have more elements to cover the remainder
    if (data->tid == (data->size - 1)) myEnd = data->N;

    // Compute the partial sum for this thread's segment of the array
    data->partialSum = 0.0;
    for (i = myStart; i < myEnd; i++)
      data->partialSum += data->a[i];

    // Lock the mutex before updating the global sum to prevent race conditions
    pthread_mutex_lock(&mutex);
    // Update the global sum with this thread's partial sum
    *((double*)arg) += data->partialSum;
    // Unlock the mutex after updating
    pthread_mutex_unlock(&mutex);

    return NULL;
}

// Main function
int main(int argc, char **argv) {
    long i;
    pthread_t *threads;
    t_data *threadData;
    double globalSum = 0.0;
    double *a;
    int N, size;

    // Check for correct number of command-line arguments
    if (argc != 3) {
       printf("Usage: %s <# of elements> <# of threads>\n",argv[0]);
       exit(-1);
    }

    // Convert command-line arguments to integers
    N = atoi(argv[1]); // Total number of elements
    size = atoi(argv[2]); // Total number of threads

    // Allocate memory for threads and thread data
    threads = (pthread_t *)malloc(sizeof(pthread_t) * size);
    threadData = (t_data *)malloc(sizeof(t_data) * size);
    // Allocate and initialize the array of elements
    a = (double *)malloc(sizeof(double) * N);
    for (i = 0; i < N; i++)
        a[i] = (double)(i + 1);

    // Create threads to compute parts of the sum
    for (i = 0; i < size; i++) {
        threadData[i].a = a;
        threadData[i].N = N;
        threadData[i].size = size;
        threadData[i].tid = i;
        pthread_create(&threads[i], NULL, compute, (void *)&threadData[i]);
    }
    
    // Wait for all threads to complete
    for (i = 0; i < size; i++) {
        pthread_join(threads[i], NULL);
        // Accumulate the global sum
        globalSum += threadData[i].partialSum;
    }
    
    // Print the total sum and verify it against the expected result
    printf("The total is %g, it should be equal to %g\n", 
           globalSum, ((double)N*(N+1))/2);
    
    // Program finished
    return 0;
}
