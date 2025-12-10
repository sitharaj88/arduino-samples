// 16x2 LCD marquee demo using LiquidCrystal.
// Wire RS->12, EN->11, D4->5, D5->4, D6->3, D7->2 and a 10k trim pot for contrast.
// The sketch scrolls a friendly greeting left, right, then returns to center.

#include <Arduino.h>
#include <LiquidCrystal.h>

constexpr uint8_t RS_PIN = 12;
constexpr uint8_t EN_PIN = 11;
constexpr uint8_t D4_PIN = 5;
constexpr uint8_t D5_PIN = 4;
constexpr uint8_t D6_PIN = 3;
constexpr uint8_t D7_PIN = 2;

constexpr uint8_t LCD_COLUMNS = 16;
constexpr uint8_t LCD_ROWS = 2;
constexpr unsigned long SCROLL_DELAY_MS = 150;
constexpr unsigned long PAUSE_BETWEEN_CYCLES_MS = 1000;

LiquidCrystal lcd(RS_PIN, EN_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN);
const String MESSAGE = "Hello, Friends!!";  // shorter than 2 rows to keep the animation smooth

void scrollLeft(uint8_t steps);
void scrollRight(uint8_t steps);

void setup() {
  lcd.begin(LCD_COLUMNS, LCD_ROWS);
  lcd.print(MESSAGE);
  delay(PAUSE_BETWEEN_CYCLES_MS);
}

void loop() {
  // move message fully off-screen to the left
  scrollLeft(LCD_COLUMNS);
  // then fully off-screen to the right (text length + display width)
  scrollRight(LCD_COLUMNS + MESSAGE.length());
  // and finally back to the starting position
  scrollLeft(LCD_COLUMNS);

  delay(PAUSE_BETWEEN_CYCLES_MS);
}

void scrollLeft(uint8_t steps) {
  for (uint8_t i = 0; i < steps; i++) {
    lcd.scrollDisplayLeft();
    delay(SCROLL_DELAY_MS);
  }
}

void scrollRight(uint8_t steps) {
  for (uint8_t i = 0; i < steps; i++) {
    lcd.scrollDisplayRight();
    delay(SCROLL_DELAY_MS);
  }
}
