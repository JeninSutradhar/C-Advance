// Variadic functions are functions that accept a variable number of arguments. 
// They are useful when you need to create functions that can handle different numbers and types of arguments.

/// DECLARATION
// Variadic functions are declared using an ellipsis (...) in the parameter list.
// The last parameter must be of type va_list.

/// ACCESSING ARGUMENTS
// You can access the arguments passed to the function using the va_arg() function.
// The va_list variable is initialized using va_start() before the loop,
// and cleaned up using va_end() after the loop.

/**
 * Custom printf-like function that can handle a few specific format specifiers
 * (%d for integers, %c for characters, and %s for strings).
 * 
 * @param format The format string
 * @param args The variable arguments
 */
#include <stdarg.h>
#include <stdio.h>

void my_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    const char *p = format;
    while (*p != '\0') {
        if (*p == '%' && *(p + 1) != '\0') {
            switch (*(++p)) {
                case 'd':
                    printf("%d", va_arg(args, int));
                    break;
                case 'c':
                    printf("%c", (char) va_arg(args, int));
                    break;
                case 's':
                    printf("%s", va_arg(args, char *));
                    break;
                default:
                    printf("Unknown format specifier: %%%c\n", *p);
                    break;
            }
        } else {
            putchar(*p);
        }
        p++;
    }

    va_end(args);
}

int main() {
    my_printf("Hello, %s!\n", "User");
    my_printf("Character: %c, Integer: %d\n", 'A', 123);
    return 0;
}

