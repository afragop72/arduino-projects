/*
 * LCD Scrolling Message Display
 * Scrolls a long message across a 16x2 HD44780 LCD
 * Board: Arduino Uno R3
 *
 * Power switch:
 *   - Slideswitch on pin 10                    (ON/OFF system toggle)
 *
 * Potentiometers:
 *   - 10kΩ on LCD Pin 3 (V/O) for contrast    (hardware only, no code)
 *   - 10kΩ on A1 for scroll speed              (read by code, adjusts delay)
 *
 * Backlight:
 *   - LCD Pin 15 (A) → 220Ω → 5V              (always on)
 *
 * LEDs:
 *   - 3 LEDs on pins 7, 8, 9 bounce in a Knight Rider pattern with each scroll step
 */

#include <LiquidCrystal.h>

// LiquidCrystal(RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int LCD_COLS = 16;

// Power switch
const int POWER_SWITCH = 10;
bool wasOff = true;  // Track state to re-init LCD when switching on

// Scroll speed control
const int SPEED_POT = A1;  // Analog input from speed potentiometer

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

  // Set up power switch
  pinMode(POWER_SWITCH, INPUT);

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
  // Check power switch
  if (digitalRead(POWER_SWITCH) == LOW) {
    // System OFF: clear LCD, turn off LEDs
    if (!wasOff) {
      lcd.clear();
      lcd.noDisplay();
      for (int i = 0; i < NUM_LEDS; i++) {
        digitalWrite(LED_PINS[i], LOW);
      }
      scrollPos = 0;
      wasOff = true;
    }
    delay(100);
    return;
  }

  // System ON: re-init display if just switched on
  if (wasOff) {
    lcd.display();
    lcd.clear();
    wasOff = false;
  }

  // Read speed pot: 0 = fast (100ms), 1023 = slow (500ms)
  int speedVal = analogRead(SPEED_POT);
  int scrollDelay = map(speedVal, 0, 1023, 100, 500);

  // Scroll text
  lcd.setCursor(0, 0);
  printScrolled(line1, scrollPos);

  lcd.setCursor(0, 1);
  printScrolled(line2, scrollPos);

  // LED bounce: Knight Rider pattern (0-1-2-1-0-1-2-1...)
  int bounceLen = (NUM_LEDS - 1) * 2;  // 4 for 3 LEDs
  int bouncePos = scrollPos % bounceLen;
  int activeLed = (bouncePos < NUM_LEDS) ? bouncePos : bounceLen - bouncePos;
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(LED_PINS[i], (i == activeLed) ? HIGH : LOW);
  }

  scrollPos++;
  if (scrollPos > maxLen) {
    scrollPos = 0;
  }

  delay(scrollDelay);
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
