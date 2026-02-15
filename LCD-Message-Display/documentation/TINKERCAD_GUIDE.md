# TinkerCad Simulation Guide

Test your LCD project in TinkerCad before building the physical circuit. This helps catch wiring errors and verify your code without risking hardware damage.

## Getting Started

1. **Visit** [tinkercad.com](https://www.tinkercad.com)
2. **Sign in** with your account (or create a free one)
3. **Navigate to** Circuits section
4. **Click** "Create new Circuit"

## Adding Components

From the components panel on the right, search and add:

| Component | Quantity | Notes |
|-----------|----------|-------|
| Arduino Uno R3 | 1 | Pre-configured board |
| LCD 16x2 | 1 | Search "LCD 16 x 2" |
| Potentiometer | 2 | 10kΩ — one for contrast, one for scroll speed |
| Resistor (220Ω) | 4 | 1 for backlight, 3 for LEDs |
| LED | 3 | Any colour (e.g., red, yellow, green) |
| Breadboard | 1 | Full-size recommended |

## Wiring the Circuit

### Power Connections

- LCD Pin 1 (GND/VSS) → Arduino GND
- LCD Pin 2 (VCC/VDD) → Arduino 5V

### Contrast Potentiometer (Pot 1 — hardware only)

- Terminal 1 → Arduino 5V
- Wiper (middle) → LCD Pin 3 (V/O)
- Terminal 2 → Arduino GND

This pot adjusts contrast directly via voltage — no code needed.

### Scroll Speed Potentiometer (Pot 2 — software controlled)

- Terminal 1 → Arduino 5V
- Wiper (middle) → Arduino A1
- Terminal 2 → Arduino GND

The Arduino reads this pot on A1 and adjusts the scroll delay (100ms–500ms). Turning the pot changes how fast text scrolls and LEDs chase.

### Control Pins

- LCD Pin 4 (RS) → Arduino Digital Pin 12
- LCD Pin 5 (RW/R/W) → Arduino GND
- LCD Pin 6 (E) → Arduino Digital Pin 11

### Data Pins (4-bit mode)

- LCD Pin 11 (DB4/D4) → Arduino Digital Pin 5
- LCD Pin 12 (DB5/D5) → Arduino Digital Pin 4
- LCD Pin 13 (DB6/D6) → Arduino Digital Pin 3
- LCD Pin 14 (DB7/D7) → Arduino Digital Pin 2
- (Pins 7-10 are not connected in 4-bit mode)

### Backlight (always on)

- LCD Pin 15 (LED+/A) → 220Ω resistor → Arduino 5V
- LCD Pin 16 (LED-/K) → Arduino GND

The backlight connects directly to 5V (through a resistor) so it is always on.

### LED Chase Lights (3 LEDs)

Each LED connects through a 220Ω resistor to its Arduino pin:

| LED | Colour (suggested) | Arduino Pin | Resistor |
|-----|---------------------|-------------|----------|
| LED 1 | Red | Pin 7 | 220Ω |
| LED 2 | Yellow | Pin 8 | 220Ω |
| LED 3 | Green | Pin 9 | 220Ω |

**Wiring per LED:**

```text
Arduino Pin → 220Ω resistor → LED Anode (+, longer leg) → LED Cathode (-, shorter leg) → GND
```

Connect all LED cathodes to the GND rail on the breadboard.

## Adding the Code

1. **Click** the "Code" button above the circuit
2. **Switch** from "Blocks" to "Text" using the dropdown
3. **Delete** the default code
4. **Copy and paste** the code from `LCD_Name_Display.ino`

```cpp
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int LCD_COLS = 16;
const int SPEED_POT = A1;
const int LED_PINS[] = {7, 8, 9};
const int NUM_LEDS = 3;

const char* line1 = "Hello! My name is Andreas Fragkopoulos!";
const char* line2 = "Coding with Arduino, rocks!";

int scrollPos = 0;
int maxLen;

void setup() {
  lcd.begin(LCD_COLS, 2);
  lcd.clear();
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    digitalWrite(LED_PINS[i], LOW);
  }
  int len1 = strlen(line1);
  int len2 = strlen(line2);
  maxLen = max(len1, len2);
}

void loop() {
  int speedVal = analogRead(SPEED_POT);
  int scrollDelay = map(speedVal, 0, 1023, 100, 500);

  lcd.setCursor(0, 0);
  printScrolled(line1, scrollPos);
  lcd.setCursor(0, 1);
  printScrolled(line2, scrollPos);

  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(LED_PINS[i], (i == scrollPos % NUM_LEDS) ? HIGH : LOW);
  }

  scrollPos++;
  if (scrollPos > maxLen) scrollPos = 0;
  delay(scrollDelay);
}

void printScrolled(const char* msg, int offset) {
  int len = strlen(msg);
  for (int i = 0; i < LCD_COLS; i++) {
    int idx = offset + i;
    if (idx < len) lcd.write(msg[idx]);
    else lcd.write(' ');
  }
}
```

## Running the Simulation

1. **Click** "Start Simulation" (green button)
2. **Adjust the contrast pot** — turn it until text is clearly visible on the LCD
3. **Adjust the scroll speed pot** — turn it to speed up or slow down the scrolling text and LED chase
4. **Observe the LEDs** — they should chase in sequence (red → yellow → green) in sync with the scrolling text
5. **Verify** both messages scroll across the LCD

## What to Expect

- **Contrast pot**: Turning it changes text visibility (too light ↔ clear ↔ too dark). Find the sweet spot.
- **Scroll speed pot**: Turning it makes the text and LEDs scroll faster (100ms delay) or slower (500ms delay).
- **LEDs**: One LED lights up at a time, cycling through all three with each scroll step. The chase pattern repeats continuously.
- **Backlight**: Always on (connected directly to 5V).

## Troubleshooting in TinkerCad

### No text visible

- **Adjust the contrast pot** (Pot 1) — this is the most common issue
- **Check** VCC/VDD (Pin 2) is connected to 5V
- **Check** GND/VSS (Pin 1) is connected to GND

### Backlight not working

- **Verify** LCD Pin 15 (A) goes through 220Ω to **5V** rail
- **Verify** LCD Pin 16 (K) is connected to GND

### LEDs not lighting up

- **Check** each LED has a 220Ω resistor in series
- **Verify** LED anodes go to pins 7, 8, 9 (through resistors)
- **Verify** LED cathodes go to GND
- **Check** LED polarity — longer leg is anode (+)

### Scroll speed pot has no effect

- **Verify** pot wiper (middle pin) is connected to Arduino **A1**
- **Ensure** both outer pot terminals go to 5V and GND

### Garbled characters

- **Verify** data pins DB4-DB7 (LCD pins 11-14) are connected to Arduino pins 5, 4, 3, 2
- **Double-check** you haven't mixed up the data pin order
- **Ensure** RW (Pin 5) is grounded

### Compilation errors

- **Make sure** you included `#include <LiquidCrystal.h>`
- **Verify** the LiquidCrystal initialization uses pins: `(12, 11, 5, 4, 3, 2)`
- **Check** for typos in function names

### LCD shows rectangles (blocks)

- This means the LCD is powered but not receiving data correctly
- **Adjust the contrast pot** to find the right level
- **Check** RS (Pin 4) and E (Pin 6) connections
- **Verify** RW (Pin 5) is grounded

## TinkerCad-Specific Features

### Adjusting Potentiometers

- Click and drag the slider on each pot to adjust
- The LCD and LEDs respond immediately to changes

### Serial Monitor

- Click the "Serial Monitor" button to see debug output
- Add `Serial.begin(9600);` and `Serial.println()` statements if needed

### Sharing Your Circuit

- Click "Share" to get a public link
- Great for getting help or showing your work

## Complete Pin Summary

| Arduino Pin | Connected To | Purpose |
|-------------|-------------|---------|
| 5V | LCD Pin 2, LCD Pin 15 (via 220Ω), Pot 1 Terminal, Pot 2 Terminal | Power |
| GND | LCD Pins 1/5/16, Pot terminals, LED cathodes | Ground |
| Pin 12 | LCD Pin 4 (RS) | Register Select |
| Pin 11 | LCD Pin 6 (E) | Enable |
| Pin 5 | LCD Pin 11 (DB4) | Data bit 4 |
| Pin 4 | LCD Pin 12 (DB5) | Data bit 5 |
| Pin 3 | LCD Pin 13 (DB6) | Data bit 6 |
| Pin 2 | LCD Pin 14 (DB7) | Data bit 7 |
| Pin 7 | LED 1 via 220Ω | Chase LED (red) |
| Pin 8 | LED 2 via 220Ω | Chase LED (yellow) |
| Pin 9 | LED 3 via 220Ω | Chase LED (green) |
| A1 | Pot 2 wiper | Scroll speed reading |
| — | Pot 1 wiper → LCD Pin 3 | Contrast (hardware) |

## Moving to Physical Hardware

Once your simulation works:

1. **Take a screenshot** of your TinkerCad circuit for reference
2. **Follow the same wiring** on your physical breadboard
3. **Upload the code** to your real Arduino using Arduino IDE
4. **Adjust contrast** by turning the contrast potentiometer
5. **Adjust scroll speed** by turning the speed potentiometer

## Additional Resources

- [TinkerCad Circuits Tutorial](https://www.tinkercad.com/learn/circuits)
- [Arduino Reference](https://www.arduino.cc/reference/en/)
- [LiquidCrystal Library](https://www.arduino.cc/en/Reference/LiquidCrystal)
