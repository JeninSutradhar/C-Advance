/**
 * @file main.c
 * @brief Example of embedded systems programming in C for blinking an LED on an Arduino board.
 *
 * This example demonstrates how to blink an LED connected to pin 13 on an Arduino board.
 * It configures the GPIO pin as an output and toggles its state with delays to create the blinking effect.
 *
 * @author [Your Name] <[Your Email]>
 * @date [Date]
 */

// Include necessary Arduino library for digital I/O
#include <Arduino.h>

/**
 * @brief Define the pin for the LED.
 */
#define LED_PIN 13

/**
 * @brief Set up the LED pin as an output.
 *
 * This function is called once at the beginning of the program.
 */
void setup() {
  // Initialize the LED pin as an output
  pinMode(LED_PIN, OUTPUT);
}

/**
 * @brief Loop function that runs repeatedly.
 *
 * This function is called repeatedly after the setup function.
 */
void loop() {
  // Turn the LED on (HIGH) for 500ms
  digitalWrite(LED_PIN, HIGH);
  delay(500);

  // Turn the LED off (LOW) for 500ms
  digitalWrite(LED_PIN, LOW);
  delay(500);
}
