// Memory Mapped I/O (Input/Output)
// Allows device registers to be mapped to the system's memory address space.
// Interacts with hardware using standard memory access instructions.
// More efficient than using special I/O instructions.

// Example in C
// Device registers mapped to specific memory addresses.
// CPU can access device registers using regular memory instructions.

// Hypothetical Device Registers
// Control Register at 0x40000000
// Status Register at 0x40000004
// Data Register at 0x40000008


/// Step-by-Step Implementation :
#include <stdio.h>
#include <stdint.h>
/**
 * The device registers are mapped to specific memory addresses. The CPU can access device registers using regular memory instructions.
 *
 * @author [Your Name] <[Your Email]>
 * @date [Date]
 */

// Register Addresses

/**
 * @brief The base address of the device registers.
 */
#define DEVICE_BASE_ADDRESS 0x40000000

/**
 * @brief Pointer to the control register.
 */
volatile uint32_t *control_register = (uint32_t *)(DEVICE_BASE_ADDRESS + 0x00);

/**
 * @brief Pointer to the status register.
 */
volatile uint32_t *status_register = (uint32_t *)(DEVICE_BASE_ADDRESS + 0x04);

/**
 * @brief Pointer to the data register.
 */
volatile uint32_t *data_register = (uint32_t *)(DEVICE_BASE_ADDRESS + 0x08);

/**
 * @brief Writes a value to the control register.
 *
 * @param value The value to be written to the control register.
 */
void write_control_register(uint32_t value) {
    *control_register = value;
}

/**
 * @brief Reads the value from the status register.
 *
 * @return The value read from the status register.
 */
uint32_t read_status_register() {
    return *status_register;
}

/**
 * @brief Writes a value to the data register.
 *
 * @param value The value to be written to the data register.
 */
void write_data_register(uint32_t value) {
    *data_register = value;
}

/**
 * @brief Reads the value from the data register.
 *
 * @return The value read from the data register.
 */
uint32_t read_data_register() {
    return *data_register;
}

/**
 * @brief The main function that demonstrates how to write to and read from the device registers.
 *
 * @return 0 on success
 */
int main() {
    // Write to the control register
    write_control_register(0x01);
    printf("Wrote to control register: 0x01\n");

    // Read from the status register
    uint32_t status = read_status_register();
    printf("Status register value: 0x%08X\n", status);

    // Write to the data register
    write_data_register(0x12345678);
    printf("Wrote to data register: 0x12345678\n");

    // Read from the data register
    uint32_t data = read_data_register();
    printf("Data register value: 0x%08X\n", data);

    return 0;
}
