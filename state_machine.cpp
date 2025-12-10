// Finite state machine demo: Idle -> Arming -> Armed -> Firing -> Idle.
// Wire a momentary push button between digital pin 2 and GND (internal pull-up enabled).
// Uses millis() for non-blocking timing and debounced button edges to advance the state.

#include <Arduino.h>

const uint8_t LED_PIN = LED_BUILTIN;
const uint8_t BUTTON_PIN = 2;
const unsigned long ARMING_DURATION_MS = 3000;
const unsigned long FIRING_DURATION_MS = 2000;
const unsigned long ARMING_BLINK_PERIOD_MS = 500;
const unsigned long FIRING_BLINK_PERIOD_MS = 120;
const unsigned long DEBOUNCE_MS = 20;

enum class State { Idle, Arming, Armed, Firing };
State currentState = State::Idle;

unsigned long stateStartedAt = 0;
unsigned long lastButtonRead = 0;
bool lastButtonState = HIGH;
bool buttonPressed = false;

void transitionTo(State next);
void readButton();
void blink(unsigned long periodMs);

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  transitionTo(State::Idle);
}

void loop() {
  readButton();

  switch (currentState) {
    case State::Idle:
      digitalWrite(LED_PIN, LOW);
      if (buttonPressed) transitionTo(State::Arming);
      break;

    case State::Arming:  // slow blink for 3 s
      blink(ARMING_BLINK_PERIOD_MS);
      if (millis() - stateStartedAt >= ARMING_DURATION_MS) transitionTo(State::Armed);
      break;

    case State::Armed:  // steady on, wait for trigger
      digitalWrite(LED_PIN, HIGH);
      if (buttonPressed) transitionTo(State::Firing);
      break;

    case State::Firing:  // rapid blink for 2 s, then reset
      blink(FIRING_BLINK_PERIOD_MS);
      if (millis() - stateStartedAt >= FIRING_DURATION_MS) transitionTo(State::Idle);
      break;
  }

  buttonPressed = false;  // consume edge
}

void transitionTo(State next) {
  currentState = next;
  stateStartedAt = millis();
}

void readButton() {
  // basic debounce on a falling edge (button press)
  bool raw = digitalRead(BUTTON_PIN);
  unsigned long now = millis();

  if (raw != lastButtonState) {
    lastButtonRead = now;
    lastButtonState = raw;
  }

  bool stableLow = (now - lastButtonRead) > DEBOUNCE_MS && raw == LOW;
  if (stableLow) {
    buttonPressed = true;
  }
}

void blink(unsigned long periodMs) {
  unsigned long phase = (millis() - stateStartedAt) % periodMs;
  digitalWrite(LED_PIN, phase < periodMs / 2 ? HIGH : LOW);
}
