// Atomic Operations

// Atomic operations are essential in concurrent programming 
// to avoid race conditions, ensuring that a particular piece
// of code is executed without interruption.

// In C, atomic operations can be performed using built-in functions
// provided by the GCC compiler, starting from version 4.7, 
// or by using the stdatomic.h library introduced in the C11 standard.

#include <stdio.h>

int main() {
    int value = 0;

    // Atomic increment
    // Increment the value of `value` by 1 atomically.
    __sync_fetch_and_add(&value, 1);
    printf("Value after atomic increment: %d\n", value); // Output: 1

    // Atomic decrement
    // Decrement the value of `value` by 1 atomically.
    __sync_fetch_and_sub(&value, 1);
    printf("Value after atomic decrement: %d\n", value); // Output: 0

    // Atomic compare and swap
    // Atomically compare the value of `value` with `old_value` and if they are equal, replace the value of `value` with `new_value`.
    int old_value = value;
    int new_value = 42;
    if (__sync_bool_compare_and_swap(&value, old_value, new_value)) {
        printf("Atomic compare and swap successful, new value: %d\n", value); // Output: 42
    } else {
        printf("Atomic compare and swap failed, value: %d\n", value);
    }

    return 0;
}

