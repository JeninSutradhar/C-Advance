// Inline Assembly
// - Allows embedding assembly language instructions in C/C++ code.
// - Useful for performance-critical sections or operations not easily achievable with standard C constructs.

// Key Points
// - Syntax: `asm` keyword for GCC (GNU Compiler Collection).
// - Clobbered Registers: Inform the compiler about modified registers.
// - Input and Output Operands: Specify C variables as inputs and outputs.

#include <stdio.h>

int main() {
    // Inline Assembly with single instruction and output operand
    int result1;

    asm("addl %%ebx, %%eax;" // Add b to a
        : "=a" (result1)      // Output operand list
        : "a" (5), "b" (10)   // Input operand list
    );

    printf("Result: %d\n", result1); // Output: Result: 15


    // Inline Assembly with Multiple Instructions and Clobbers
    int result2;

    asm volatile(
        "movl %1, %%eax;"  // Move a into eax
        "movl %2, %%ebx;"  // Move b into ebx
        "addl %%ebx, %%eax;" // Add ebx to eax
        "movl %%eax, %0;"  // Move eax into result
        : "=r" (result2)    // Output operand
        : "r" (5), "r" (10) // Input operands
        : "%eax", "%ebx"   // Clobbered registers
    );

    printf("Result: %d\n", result2); // Output: Result: 15


    // Inline Assembly for Specific Use Cases
    int result3;

    // Performs a bitwise AND operation between a and b, and stores the result in result
    asm("andl %1, %0"
        : "=r" (result3)
        : "r" (10), "0" (6)
    );

    printf("Result: %d\n", result3); // Output: Result: 2 (010 in binary)

    return 0;
}

