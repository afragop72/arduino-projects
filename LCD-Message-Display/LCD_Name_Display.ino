/*
 * LCD Scrolling Message Display
 * Scrolls a long message across a 16x2 HD44780 LCD
 * Board: Arduino Uno R3
 *
 * Potentiometers:
 *   - 10kΩ on LCD Pin 3 (V/O) for contrast  (hardware only, no code)
 *   - 10kΩ on A1 for brightness              (read by code, drives PWM)
 *
 * LEDs:
 *   - 3 LEDs on pins 7, 8, 9 cycle in a chase pattern with each scroll step
 */

#include <LiquidCrystal.h>

// LiquidCrystal(RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int LCD_COLS = 16;

// Brightness control
const int BRIGHTNESS_PIN = 6;   // PWM output to LCD backlight (via 220Ω)
const int BRIGHTNESS_POT = A1;  // Analog input from brightness potentiometer

// LED chase pins
const int LED_PINS[] = {7, 8, 9};
const int NUM_LEDS = 3;

// Messages to scroll (can be longer than 16 characters)
const char* line1 = "Hello! My name is Andreas Fragkopoulos!";
const char* line2 = "Coding with Arduino, rocks!";

int scrollPos = 0;
int maxLen;

void setup() {
  lcd.begin(LCD_COLS, 2);
  lcd.clear();

  // Set up brightness control
  pinMode(BRIGHTNESS_PIN, OUTPUT);

  // Set up LED pins
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    digitalWrite(LED_PINS[i], LOW);
  }

  // Calculate the longest message length for scroll wrapping
  int len1 = strlen(line1);
  int len2 = strlen(line2);
  maxLen = max(len1, len2);
}

void loop() {
  // Read brightness pot and set backlight
  int brightness = analogRead(BRIGHTNESS_POT);
  analogWrite(BRIGHTNESS_PIN, map(brightness, 0, 1023, 0, 255));

  // Scroll text
  lcd.setCursor(0, 0);
  printScrolled(line1, scrollPos);

  lcd.setCursor(0, 1);
  printScrolled(line2, scrollPos);

  // LED chase: light one LED per scroll step
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(LED_PINS[i], (i == scrollPos % NUM_LEDS) ? HIGH : LOW);
  }

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
