// Basic blink example.
// Connect the on-board LED (or any LED + resistor) to digital pin 13.
// The sketch toggles the LED every second using blocking delays for clarity.

#include <Arduino.h>

const uint8_t LED_PIN = 13;  // most Arduino boards expose the on-board LED here
const unsigned long BLINK_DELAY_MS = 1000;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);  // start in a known state
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(BLINK_DELAY_MS);

  digitalWrite(LED_PIN, LOW);
  delay(BLINK_DELAY_MS);
}
