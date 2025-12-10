// Servo sweep example.
// Connect servo signal to pin 9, power to 5V, and ground to GND (share common ground with the board).
// The sketch sweeps the servo smoothly between 0° and 180° with adjustable dwell time at each end.

#include <Arduino.h>
#include <Servo.h>

const uint8_t SERVO_PIN = 10;  // PWM-capable pin suitable for Servo library on most boards
const int MIN_ANGLE = 0;
const int MAX_ANGLE = 180;
const int STEP_DEGREES = 3;           // smaller steps = smoother but slower sweep
const unsigned long STEP_DELAY_MS = 20;  // delay between each incremental move
const unsigned long DWELL_MS = 750;      // pause at each extreme

Servo arm;

void setup() {
  arm.attach(SERVO_PIN);
  arm.write(MIN_ANGLE);
  delay(DWELL_MS);
}

void loop() {
  // Sweep up
  for (int angle = MIN_ANGLE; angle <= MAX_ANGLE; angle += STEP_DEGREES) {
    arm.write(angle);
    delay(STEP_DELAY_MS);
  }
  delay(DWELL_MS);

  // Sweep back down
  for (int angle = MAX_ANGLE; angle >= MIN_ANGLE; angle -= STEP_DEGREES) {
    arm.write(angle);
    delay(STEP_DELAY_MS);
  }
  delay(DWELL_MS);
}
