# LCD Name Display

Display your name on a 16x2 HD44780 LCD using Arduino Uno R3, with adjustable contrast, adjustable scroll speed, and LED chase lights.

![Arduino](https://img.shields.io/badge/Arduino-Uno%20R3-00979D?logo=arduino&logoColor=white)
![Status](https://img.shields.io/badge/Status-Ready-success)
![Difficulty](https://img.shields.io/badge/Difficulty-Beginner-brightgreen)

## Overview

This project demonstrates how to interface a 16x2 character LCD (HD44780 controller) with an Arduino Uno R3 to display scrolling custom text. It includes two potentiometers (contrast and scroll speed) and three LEDs that chase in sequence with the scrolling text.

**Features:**
- Scrolling text across both LCD lines
- 4-bit mode connection (saves Arduino pins)
- Potentiometer for contrast control (hardware)
- Potentiometer for scroll speed control (software)
- 3 LEDs that cycle in a chase pattern with each scroll step
- Includes TinkerCad simulation guide
- Complete wiring diagrams and troubleshooting

## What You'll Need

### Hardware

- Arduino Uno R3
- 16x2 LCD with HD44780 controller (white on blue backlight)
- 10kΩ potentiometer x2 (contrast + scroll speed)
- 220Ω resistor x4 (1 for backlight, 3 for LEDs)
- LED x3 (red, yellow, green)
- Breadboard (full-size recommended) and jumper wires

### Software

- [Arduino IDE](https://www.arduino.cc/en/software) (version 2.x recommended)
- LiquidCrystal library (built-in, no installation needed)

## Quick Start

### 1. Wire the LCD

Connect your LCD to the Arduino following this pinout:

| LCD Pin | Label | Arduino     |
| ------- | ----- | ----------- |
| 1       | GND   | GND         |
| 2       | VCC   | 5V          |
| 3       | V/O   | Contrast pot wiper |
| 4       | RS    | Pin 12      |
| 5       | RW    | GND         |
| 6       | E     | Pin 11      |
| 11      | DB4   | Pin 5       |
| 12      | DB5   | Pin 4       |
| 13      | DB6   | Pin 3       |
| 14      | DB7   | Pin 2       |
| 15      | LED+  | 5V via 220Ω |
| 16      | LED-  | GND         |

*Note: Pins 7-10 (DB0-DB3) are not connected in 4-bit mode.*

### 2. Wire the Potentiometers

| Pot          | Terminal 1 | Wiper (middle) | Terminal 2 |
| ------------ | ---------- | -------------- | ---------- |
| Contrast     | 5V         | LCD V/O        | GND        |
| Scroll Speed | 5V         | Arduino A1     | GND        |

### 3. Wire the LEDs

Each LED connects through a 220Ω resistor:

| LED    | Arduino Pin | Resistor | Cathode |
| ------ | ----------- | -------- | ------- |
| Red    | Pin 7       | 220Ω     | GND     |
| Yellow | Pin 8       | 220Ω     | GND     |
| Green  | Pin 9       | 220Ω     | GND     |

### 4. Upload the Code

1. Open `LCD_Name_Display.ino` in Arduino IDE
2. Edit lines 32-33 to customise the scrolling messages
3. Select **Tools > Board > Arduino Uno**
4. Select your COM port under **Tools > Port**
5. Click **Upload** (or press Ctrl+U)

### 5. Adjust Controls

- **Contrast pot**: Turn until text is clearly visible on the LCD
- **Scroll speed pot**: Turn to speed up or slow down scrolling and LED chase
- **LEDs**: They chase automatically in sync with scrolling text

## Documentation

| Document | Description |
| -------- | ----------- |
| [Full Documentation](documentation/README.md) | Complete setup guide with troubleshooting |
| [Wiring Diagram](documentation/WIRING_DIAGRAM.md) | Detailed pin-by-pin connections |
| [Quick Reference](documentation/QUICK_REFERENCE.md) | Fast lookup for labeled LCD modules |
| [Parts List](documentation/PARTS_LIST.md) | All components needed |
| [TinkerCad Guide](documentation/TINKERCAD_GUIDE.md) | Test your circuit in simulation first |

## Test Before Building

Try your circuit in [TinkerCad](https://www.tinkercad.com) first! See the [TinkerCad Guide](documentation/TINKERCAD_GUIDE.md) for step-by-step simulation instructions.

## The Code

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
  maxLen = max(strlen(line1), strlen(line2));
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

## Pin Summary

| Arduino Pin | Purpose                |
| ----------- | ---------------------- |
| Pin 12      | LCD RS                 |
| Pin 11      | LCD E                  |
| Pin 5       | LCD DB4                |
| Pin 4       | LCD DB5                |
| Pin 3       | LCD DB6                |
| Pin 2       | LCD DB7                |
| Pin 7       | LED 1 (red)            |
| Pin 8       | LED 2 (yellow)         |
| Pin 9       | LED 3 (green)          |
| A1          | Scroll speed pot input |

## Troubleshooting

| Problem | Solution |
| ------- | -------- |
| **No text visible** | Adjust contrast pot; check power connections |
| **Gibberish characters** | Check data pins DB4-DB7 (pins 11-14) to Arduino pins 5, 4, 3, 2 |
| **Nothing on screen** | Verify VCC to 5V, GND to GND |
| **Backlight not working** | Verify LCD Pin 15 goes through 220Ω to 5V rail |
| **LEDs not lighting** | Check 220Ω resistors and LED polarity (longer leg = anode) |
| **Upload error** | Check board selection and COM port |

**Full troubleshooting guide in [documentation/README.md](documentation/README.md)**

## Project Structure

```
LCD_Name_Display/
├── README.md                    # This file
├── LCD_Name_Display.ino         # Arduino sketch
└── documentation/
    ├── README.md                # Full documentation
    ├── WIRING_DIAGRAM.md        # Detailed wiring
    ├── QUICK_REFERENCE.md       # Labeled LCD pin guide
    ├── PARTS_LIST.md            # Components list
    ├── TINKERCAD_GUIDE.md       # Simulation guide
    └── designs/
        ├── LCS-Display-Name-CAD.pdf
        └── connections-view.png
```

## Next Steps

Once you've got this working, try:
- Change the LED chase to a bounce pattern (1-2-3-2-1 instead of 1-2-3-1-2-3)
- Display sensor data (temperature, distance, etc.)
- Add button input to change the message
- Create a simple menu system

## License

This project is open source and available for educational purposes.

## Contributing

Found an issue or want to improve the documentation? Feel free to submit a pull request!

---

**Made with Arduino**

*Part of the [arduino-projects](https://github.com/afragop72/arduino-projects) collection*
