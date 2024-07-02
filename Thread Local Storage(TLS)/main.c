// Thread Local Storage (TLS) is a mechanism that allows each thread in a multi-threaded program to have its own private data.

// This data is local to the thread and not shared among other threads. TLS is particularly useful when you need to store thread-specific
// information without the overhead of synchronization or when you want to avoid the complexity of passing data explicitly between functions
// or modules.

// Implementing Thread Local Storage
// In C and C++, TLS is typically implemented using platform-specific APIs or language features. Here's a general overview of how TLS can be
// implemented:

// 1. Using Platform-Specific APIs
// Different platforms provide APIs to manage thread-local variables. Here's how TLS can be implemented using POSIX threads (pthread) in C:

#include <stdio.h>
#include <pthread.h>

// Define a thread-specific key
pthread_key_t tls_key;

// Function to initialize thread-specific data
//
// This function creates a key for accessing thread-specific data.
void init_tls() {
    pthread_key_create(&tls_key, NULL);
}

// Function to access thread-specific data
//
// This function retrieves the thread-specific data associated with the current thread.
void* get_tls_data() {
    return pthread_getspecific(tls_key);
}

// Function to set thread-specific data
//
// This function sets the thread-specific data associated with the current thread.
void set_tls_data(void* data) {
    pthread_setspecific(tls_key, data);
}

// Example usage in a thread
//
// This function demonstrates how to use TLS in a thread. It creates thread-specific data, sets the data, and retrieves it.
void* thread_function(void* arg) {
    int thread_id = *(int*)arg;
    char* thread_data = malloc(256);
    snprintf(thread_data, 256, "Thread %d data", thread_id);
    set_tls_data(thread_data);

    // Access thread-specific data
    printf("Thread %d: %s\n", thread_id, (char*)get_tls_data());

    // Cleanup
    free(thread_data);
    return NULL;
}

int main() {
    // Initialize TLS
    init_tls();

    pthread_t threads[3];
    int thread_ids[3] = {1, 2, 3};

    // Create threads
    for (int i = 0; i < 3; ++i) {
        pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
    }

    // Join threads
    for (int i = 0; i < 3; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Cleanup TLS key
    pthread_key_delete(tls_key);

    return 0;
}
