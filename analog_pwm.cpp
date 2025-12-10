// Potentiometer-controlled LED brightness via PWM.
// Wire a 10 kΩ potentiometer center wiper to analog input A0, outer legs to 5V and GND.
// Connect an LED + 220 Ω resistor to PWM-capable pin 9 (or adjust LED_PIN below).
// The sketch reads the potentiometer, maps the value to 0-255, and drives the LED with analogWrite.

#include <Arduino.h>

const uint8_t POT_PIN = A0;   // analog input for potentiometer
const uint8_t LED_PIN = 9;    // PWM-capable digital pin
const unsigned long PRINT_PERIOD_MS = 200;  // how often to log readings over serial

unsigned long lastPrint = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(POT_PIN, INPUT);
  analogWrite(LED_PIN, 0);  // start with LED off

  Serial.begin(9600);
  while (!Serial) {
    ;  // wait for serial monitor on boards that require it
  }
  Serial.println(F("Potentiometer PWM demo: adjust knob to change brightness"));
}

void loop() {
  int rawValue = analogRead(POT_PIN);           // 0-1023
  int brightness = map(rawValue, 0, 1023, 0, 255);
  brightness = constrain(brightness, 0, 255);   // guard bounds

  analogWrite(LED_PIN, brightness);

  unsigned long now = millis();
  if (now - lastPrint >= PRINT_PERIOD_MS) {
    Serial.print(F("Raw: "));
    Serial.print(rawValue);
    Serial.print(F(" -> PWM: "));
    Serial.println(brightness);
    lastPrint = now;
  }
}
