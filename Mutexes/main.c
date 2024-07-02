// Mutexes

// Mutexes (mutual exclusions) are synchronization primitives used
//  to protect shared data from being simultaneously accessed by multiple threads. 

// A mutex can be locked and unlocked by threads to ensure that only one 
//  thread accesses the critical section of code at a time.

#include <stdio.h>
#include <pthread.h>

// Mutex to protect the shared resource
pthread_mutex_t mutex;

// Shared resource that can be accessed by multiple threads
int shared_resource = 0;

/**
 * Thread function that increments the shared resource and prints its value
 * @param arg The argument passed to the thread
 * @return NULL
 */
void* thread_function(void* arg) {
    // Lock the mutex to ensure exclusive access to the shared resource
    pthread_mutex_lock(&mutex);

    // Increment the shared resource and print its value
    shared_resource++;
    printf("Thread %ld, Shared resource: %d\n", (long)arg, shared_resource);

    // Unlock the mutex to allow other threads to access the shared resource
    pthread_mutex_unlock(&mutex);

    return NULL;
}

/**
 * Main function that creates multiple threads and protects the shared resource with a mutex
 * @return 0 on success
 */
int main() {
    // Array to store the threads
    pthread_t threads[5];

    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);

    // Create threads
    for (long i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, thread_function, (void*)i);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}

