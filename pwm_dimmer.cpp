// Potentiometer-controlled PWM dimmer.
// Wire potentiometer ends to 5V/GND and the wiper to A0.
// Wire an LED + resistor to PWM pin 9 (or use another PWM-capable pin).

#include <Arduino.h>

constexpr uint8_t POT_PIN = A0;
constexpr uint8_t LED_PWM_PIN = 9;

constexpr unsigned long UPDATE_PERIOD_MS = 10;
constexpr uint16_t ANALOG_MAX = 1023;
constexpr uint8_t PWM_MAX = 255;

unsigned long lastUpdate = 0;

void setup() {
  pinMode(LED_PWM_PIN, OUTPUT);
  analogWrite(LED_PWM_PIN, 0);
}

void loop() {
  unsigned long now = millis();
  if (now - lastUpdate < UPDATE_PERIOD_MS) return;

  lastUpdate = now;

  int raw = analogRead(POT_PIN);
  uint8_t duty = map(raw, 0, ANALOG_MAX, 0, PWM_MAX);
  analogWrite(LED_PWM_PIN, duty);
}
