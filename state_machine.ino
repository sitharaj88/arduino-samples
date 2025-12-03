// Finite state machine demo: Idle -> Arming -> Armed -> Firing -> Idle
// Uses non-blocking timing with millis(); button on D2 steps through states.

const uint8_t LED_PIN    = LED_BUILTIN;
const uint8_t BUTTON_PIN = 2;  // wire button to GND, uses internal pull-up

enum class State { Idle, Arming, Armed, Firing };
State currentState = State::Idle;

unsigned long stateStartedAt = 0;
unsigned long lastButtonRead = 0;
bool lastButtonState = HIGH;
bool buttonPressed = false;

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

    case State::Arming:  // slow blink for 3s
      blink(500);
      if (millis() - stateStartedAt >= 3000) transitionTo(State::Armed);
      break;

    case State::Armed:  // steady on, wait for trigger
      digitalWrite(LED_PIN, HIGH);
      if (buttonPressed) transitionTo(State::Firing);
      break;

    case State::Firing:  // rapid blink for 2s, then reset
      blink(120);
      if (millis() - stateStartedAt >= 2000) transitionTo(State::Idle);
      break;
  }

  buttonPressed = false;  // consume edge
}

void transitionTo(State next) {
  currentState = next;
  stateStartedAt = millis();
}

void readButton() {
  // basic debounce (20 ms)
  const unsigned long debounceMs = 20;
  bool raw = digitalRead(BUTTON_PIN);
  unsigned long now = millis();

  if (raw != lastButtonState) {
    lastButtonRead = now;
    lastButtonState = raw;
  }
  if ((now - lastButtonRead) > debounceMs && raw == LOW) {
    buttonPressed = true;  // register press on falling edge
  }
}

void blink(unsigned long periodMs) {
  unsigned long phase = (millis() - stateStartedAt) % periodMs;
  digitalWrite(LED_PIN, phase < periodMs / 2 ? HIGH : LOW);
}
