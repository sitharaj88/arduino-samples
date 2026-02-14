// Traffic light controller with timed state transitions.
// Wire red/yellow/green LEDs (through 220 ohm resistors) to pins 10, 9, and 8.
// The sketch cycles Green -> Yellow -> Red using millis() (no blocking delay).

#include <Arduino.h>

constexpr uint8_t RED_PIN = 10;
constexpr uint8_t YELLOW_PIN = 9;
constexpr uint8_t GREEN_PIN = 8;

constexpr unsigned long GREEN_DURATION_MS = 5000;
constexpr unsigned long YELLOW_DURATION_MS = 1500;
constexpr unsigned long RED_DURATION_MS = 4000;

enum class LightState { Green, Yellow, Red };
LightState currentState = LightState::Green;
unsigned long stateStartedAt = 0;

void enterState(LightState next);
unsigned long durationFor(LightState state);

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);

  enterState(LightState::Green);
}

void loop() {
  unsigned long now = millis();
  if (now - stateStartedAt >= durationFor(currentState)) {
    switch (currentState) {
      case LightState::Green:
        enterState(LightState::Yellow);
        break;
      case LightState::Yellow:
        enterState(LightState::Red);
        break;
      case LightState::Red:
        enterState(LightState::Green);
        break;
    }
  }
}

void enterState(LightState next) {
  currentState = next;
  stateStartedAt = millis();

  digitalWrite(RED_PIN, currentState == LightState::Red ? HIGH : LOW);
  digitalWrite(YELLOW_PIN, currentState == LightState::Yellow ? HIGH : LOW);
  digitalWrite(GREEN_PIN, currentState == LightState::Green ? HIGH : LOW);
}

unsigned long durationFor(LightState state) {
  switch (state) {
    case LightState::Green:
      return GREEN_DURATION_MS;
    case LightState::Yellow:
      return YELLOW_DURATION_MS;
    case LightState::Red:
      return RED_DURATION_MS;
  }

  return GREEN_DURATION_MS;  // defensive fallback
}
