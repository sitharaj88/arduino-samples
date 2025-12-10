// Seven-segment display counter (0-9).
// Wire segments A-G to Arduino pins 8, 7, 6, 5, 4, 3, 2 respectively on a common-cathode display.
// The sketch advances one digit per second using a simple lookup table for segment patterns.

#include <Arduino.h>

const uint8_t SEGMENT_PINS[] = {8, 7, 6, 5, 4, 3, 2};  // A, B, C, D, E, F, G
const size_t SEGMENT_COUNT = sizeof(SEGMENT_PINS) / sizeof(SEGMENT_PINS[0]);

// Patterns are ordered A (bit 6) through G (bit 0). HIGH turns a segment on.
const byte DIGIT_PATTERNS[10] = {
  B1111110,  // 0
  B0110000,  // 1
  B1101101,  // 2
  B1111001,  // 3
  B0110011,  // 4
  B1011011,  // 5
  B1011111,  // 6
  B1110000,  // 7
  B1111111,  // 8
  B1111011   // 9
};

const unsigned long UPDATE_PERIOD_MS = 1000;
unsigned long lastUpdate = 0;
uint8_t currentDigit = 0;

void displayDigit(uint8_t digit);
void writeSegments(byte pattern);

void setup() {
  for (size_t i = 0; i < SEGMENT_COUNT; i++) {
    pinMode(SEGMENT_PINS[i], OUTPUT);
    digitalWrite(SEGMENT_PINS[i], LOW);
  }

  displayDigit(currentDigit);
  lastUpdate = millis();
}

void loop() {
  unsigned long now = millis();
  if (now - lastUpdate >= UPDATE_PERIOD_MS) {
    currentDigit = (currentDigit + 1) % 10;
    displayDigit(currentDigit);
    lastUpdate = now;
  }
}

void displayDigit(uint8_t digit) {
  if (digit >= 10) return;  // guard against invalid values
  writeSegments(DIGIT_PATTERNS[digit]);
}

void writeSegments(byte pattern) {
  for (size_t i = 0; i < SEGMENT_COUNT; i++) {
    // bitRead reads LSB first; subtract i from 6 to map to A..G ordering
    bool segmentOn = bitRead(pattern, SEGMENT_COUNT - 1 - i);
    digitalWrite(SEGMENT_PINS[i], segmentOn ? HIGH : LOW);
  }
}
