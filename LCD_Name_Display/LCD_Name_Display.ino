/*
 * LCD Name Display
 * Displays your full name on a 16x2 HD44780 LCD
 * Board: Arduino Uno R3
 */

#include <LiquidCrystal.h>

// Initialize the library with the numbers of the interface pins
// LiquidCrystal(RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // Set up the LCD's number of columns and rows
  lcd.begin(16, 2);

  // Print your name to the LCD
  lcd.setCursor(0, 0);  // First line, first position
  lcd.print("Your Full Name");

  lcd.setCursor(0, 1);  // Second line, first position
  lcd.print("Arduino Uno R3");
}

void loop() {
  // Nothing to do here - message stays on screen
}
