/*
 * LCD Scrolling Message Display
 * Scrolls a long message across a 16x2 HD44780 LCD
 * Board: Arduino Uno R3
 *
 * Potentiometers:
 *   - 10kΩ on LCD Pin 3 (V/O) for contrast
 *   - 10kΩ on LCD Pin 15 (A) via 220Ω resistor for brightness
 */

#include <LiquidCrystal.h>

// LiquidCrystal(RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int LCD_COLS = 16;

// Messages to scroll (can be longer than 16 characters)
const char* line1 = "Hello! My name is Andreas Fragkopoulos!";
const char* line2 = "Coding with Arduino, rocks!";

int scrollPos = 0;
int maxLen;

void setup() {
  lcd.begin(LCD_COLS, 2);
  lcd.clear();

  // Calculate the longest message length for scroll wrapping
  int len1 = strlen(line1);
  int len2 = strlen(line2);
  maxLen = max(len1, len2);
}

void loop() {
  lcd.setCursor(0, 0);
  printScrolled(line1, scrollPos);

  lcd.setCursor(0, 1);
  printScrolled(line2, scrollPos);

  scrollPos++;
  if (scrollPos > maxLen) {
    scrollPos = 0;
  }

  delay(300);  // Scroll speed in ms (lower = faster)
}

// Prints a scrolling window of 16 characters from the message.
// Pads with spaces so short segments don't leave stale characters.
void printScrolled(const char* msg, int offset) {
  int len = strlen(msg);
  for (int i = 0; i < LCD_COLS; i++) {
    int idx = offset + i;
    if (idx < len) {
      lcd.write(msg[idx]);
    } else {
      lcd.write(' ');
    }
  }
}
