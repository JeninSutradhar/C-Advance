#include <stdio.h>

/**
 * @file meta_programming.c
 * @brief Example of meta programming in C.
 *
 * This example demonstrates various techniques for meta programming in C.
 * It includes conditional compilation, macros with arguments, string concatenation,
 * token pasting, and looping with recursive macros.
 *
 */

// Example 1: Conditional Compilation
#define DEBUG 1

/**
 * @brief Conditional compilation macro.
 *
 * Prints the value of a variable if DEBUG is defined.
 *
 * @param x The variable to print.
 */
#if DEBUG
    #define DEBUG_PRINT(x) printf("Debug: %s = %d\n", #x, x)
#else
    #define DEBUG_PRINT(x)
#endif

// Example 2: Macros with Arguments
/**
 * @brief Macro for finding the maximum of two values.
 *
 * @param a The first value.
 * @param b The second value.
 * @return The maximum of the two values.
 */
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// Example 3: String Concatenation
/**
 * @brief Macro for concatenating two tokens.
 *
 * @param x The first token.
 * @param y The second token.
 * @return The concatenated token.
 */
#define CONCAT(x, y) x ## y

// Example 4: Token Pasting
/**
 * @brief Macro for pasting two tokens.
 *
 * @param x The first token.
 * @param y The second token.
 * @return The pasted token.
 */
#define PASTE(x, y) x ## y

// Example 5: Looping with Recursive Macros (up to 10)
/**
 * @brief Recursive macro for looping from 0 to n.
 *
 * @param n The number to loop to.
 */
#define LOOP(n) LOOP_##n

/**
 * @brief Loop from 0 to 0.
 */
#define LOOP_0 printf("0\n");

/**
 * @brief Loop from 1 to n.
 */
#define LOOP_1 LOOP_0 printf("1\n");

/**
 * @brief Loop from 2 to n.
 */
#define LOOP_2 LOOP_1 printf("2\n");

/**
 * @brief Loop from 3 to n.
 */
#define LOOP_3 LOOP_2 printf("3\n");

/**
 * @brief Loop from 4 to n.
 */
#define LOOP_4 LOOP_3 printf("4\n");

/**
 * @brief Loop from 5 to n.
 */
#define LOOP_5 LOOP_4 printf("5\n");

/**
 * @brief Loop from 6 to n.
 */
#define LOOP_6 LOOP_5 printf("6\n");

/**
 * @brief Loop from 7 to n.
 */
#define LOOP_7 LOOP_6 printf("7\n");

/**
 * @brief Loop from 8 to n.
 */
#define LOOP_8 LOOP_7 printf("8\n");

/**
 * @brief Loop from 9 to n.
 */
#define LOOP_9 LOOP_8 printf("9\n");

int main() {
    // Example 1: Conditional Compilation
    int value = 42;
    DEBUG_PRINT(value);

    // Example 2: Macros with Arguments
    int max_value = MAX(10, 20);
    printf("Max value: %d\n", max_value);

    // Example 3: String Concatenation
    int CONCAT(var, 1) = 10;
    printf("Concatenated variable: %d\n", var1);

    // Example 4: Token Pasting
    int PASTE(num, 1) = 5;
    printf("Pasted variable: %d\n", num1);

    // Example 5: Looping with Recursive Macros
    LOOP(10);

    return 0;
}

