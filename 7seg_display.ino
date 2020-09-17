#include <Arduino.h>

void displayNumber(int number);

//0 - 9 numbers mapping to seven segment display pattern
const byte numbers[10] = {
    B11111100, B01100000, B11011010, B11110010, B01100110,
    B10110110, B10111110, B11100000, B11111110, B11100110};

void setup()
{
  //Make arduino pin 2-8 as output for connecting seven segment display
  for (int i = 8; i >= 2; i--)
  {
    pinMode(i, OUTPUT);
  }
}

int counter = 0;

void loop()
{
  counter = (counter + 1) % 10;
  displayNumber(counter);
  delay(1000);
}

void displayNumber(int number)
{
  // Given number should be between 0 - 9
  if (number < 0 || number > 9)
  {
    return;
  }

  byte mask = numbers[number];
  byte currentPinMask = B10000000;
  /*
    loop over pin 2 to 9 and 
    check whether pin enabled/displayed 
    based on seven segment pattern
  */
  for (int i = 8; i >= 2; i--)
  {
    if (mask & currentPinMask)
    {
      digitalWrite(i, HIGH);
    }
    else
    {
      digitalWrite(i, LOW);
    }
    currentPinMask = currentPinMask >> 1; // move to next arduino pin
  }
}
