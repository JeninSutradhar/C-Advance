/**
 * Memory barriers (also known as memory fences) are synchronization primitives used in concurrent programming to enforce ordering of memory accesses. They ensure that memory operations performed by threads are visible in a predictable order across different processors or cores in a multi-core system.
 */

/**
 * Purpose of Memory Barriers
 * Memory barriers are used to:
 * - Order Memory Accesses: Ensure that memory operations appear to execute in a certain order, even if the underlying hardware or compiler optimizations could reorder them.
 * - Synchronize Threads: Coordinate the visibility of changes made by one thread to other threads, ensuring that changes are observable in a consistent manner.
 */

/**
 * Types of Memory Barriers
 * There are generally two types of memory barriers:
 * - Compiler Memory Barriers: Instruct the compiler to not reorder memory accesses across the barrier.
 * - CPU Memory Barriers: Instruct the CPU to enforce ordering of memory accesses, ensuring visibility across cores or processors.
 */

/**
 * Memory Barriers in C
 * In C, memory barriers are typically implemented using compiler-specific built-in functions or macros. Here's how they are commonly used:
 */

/**
 * Compiler Memory Barriers
 * Compiler memory barriers prevent the compiler from reordering memory accesses across the barrier. They ensure that certain operations appear in the order written in the code.
 */

/**
 * CPU Memory Barriers
 * CPU memory barriers enforce ordering of memory accesses at the hardware level. They ensure that all memory accesses before the barrier are completed before any memory accesses after the barrier.
 */

#include <stdatomic.h>
#include <pthread.h>

/**
 * Example with CPU memory barrier and mutex
 */
pthread_mutex_t mutex;
atomic_int shared_value = 0;

/**
 * Thread function that demonstrates the use of a CPU memory barrier and a mutex for synchronization.
 * @param arg The argument passed to the thread function (unused in this example).
 * @return NULL
 */
void* thread_function(void* arg) {
    int local_value = atomic_load_explicit(&shared_value, memory_order_relaxed);
    
    // Perform some operations
    local_value++;
    
    atomic_store_explicit(&shared_value, local_value, memory_order_relaxed);
    
    // CPU memory barrier (full fence)
    atomic_thread_fence(memory_order_seq_cst);
    
    // Critical section protected by mutex
    pthread_mutex_lock(&mutex);
    // Perform some operations protected by the mutex
    pthread_mutex_unlock(&mutex);
    
    return NULL;
}
