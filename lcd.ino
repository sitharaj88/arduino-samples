#include <LiquidCrystal.h>

#define RS 12
#define EN 11
#define  D4 5
#define D5 4
#define  D6 3
#define D7 2

#define LCD_CHAR_LENGTH 16
#define NO_LCD_LINES 2

void scrollLeft();
void scrollRight();
void scrollToInitialPosition();

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

int positionCounter = 0;
String text  = "Hello, Friends!!";
int textLength = text.length();

void setup() {
  lcd.begin(LCD_CHAR_LENGTH, NO_LCD_LINES);
  lcd.print(text);
  delay(1000);
}

void loop() {
  scrollLeft();
  scrollRight();
  scrollToInitialPosition();
  delay(1000);
}

void scrollLeft() {
  for (positionCounter = 0; positionCounter < LCD_CHAR_LENGTH; positionCounter++) {
    lcd.scrollDisplayLeft();
    delay(150);
  }
}

void scrollRight() {
  int maxScroll = LCD_CHAR_LENGTH + textLength;
  for (positionCounter = 0; positionCounter < maxScroll; positionCounter++) {
    lcd.scrollDisplayRight();
    delay(150);
  }
}

void scrollToInitialPosition() {
  for (positionCounter = 0; positionCounter < LCD_CHAR_LENGTH; positionCounter++) {
    lcd.scrollDisplayLeft();
    delay(150);
  }
}
