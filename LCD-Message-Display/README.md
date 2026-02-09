# LCD Name Display

Display your name on a 16x2 HD44780 LCD using Arduino Uno R3.

![Arduino](https://img.shields.io/badge/Arduino-Uno%20R3-00979D?logo=arduino&logoColor=white)
![Status](https://img.shields.io/badge/Status-Ready-success)
![Difficulty](https://img.shields.io/badge/Difficulty-Beginner-brightgreen)

## Overview

This project demonstrates how to interface a 16x2 character LCD (HD44780 controller) with an Arduino Uno R3 to display custom text. Perfect for beginners learning Arduino and LCD interfacing!

**Features:**
- Simple 4-bit mode connection (saves Arduino pins)
- Works with or without a potentiometer for contrast control
- Supports both numbered and labeled LCD pins
- Includes TinkerCad simulation guide
- Complete wiring diagrams and troubleshooting

## What You'll Need

### Hardware
- Arduino Uno R3
- 16x2 LCD with HD44780 controller (white on blue backlight)
- 220Ω resistor (for backlight)
- Breadboard and jumper wires
- **Optional:** 10kΩ potentiometer (for adjustable contrast)

### Software
- [Arduino IDE](https://www.arduino.cc/en/software) (version 2.x recommended)
- LiquidCrystal library (built-in, no installation needed)

## Quick Start

### 1. Wire the LCD

Connect your LCD to the Arduino following this pinout:

| LCD Pin | Label | Arduino |
|---------|-------|---------|
| 1 | GND | GND |
| 2 | VCC | 5V |
| 3 | V/O | GND (or 3.3V if too dark) |
| 4 | RS | Pin 12 |
| 5 | RW | GND |
| 6 | E | Pin 11 |
| 11 | DB4 | Pin 5 |
| 12 | DB5 | Pin 4 |
| 13 | DB6 | Pin 3 |
| 14 | DB7 | Pin 2 |
| 15 | LED+ | 5V (via 220Ω resistor) |
| 16 | LED- | GND |

*Note: Pins 7-10 (DB0-DB3) are not connected in 4-bit mode.*

**📖 For detailed wiring instructions, see [WIRING_DIAGRAM.md](documentation/WIRING_DIAGRAM.md)**

### 2. Upload the Code

1. Open `LCD_Name_Display.ino` in Arduino IDE
2. Edit line 19 to replace `"Your Full Name"` with your name (max 16 characters)
3. Select **Tools → Board → Arduino Uno**
4. Select your COM port under **Tools → Port**
5. Click **Upload** (or press Ctrl+U)

### 3. Adjust Contrast

If you connected V/O (Pin 3) to GND and the text is too dark or invisible, try connecting it to the Arduino's 3.3V pin instead.

## Documentation

| Document | Description |
|----------|-------------|
| [📖 Full Documentation](documentation/README.md) | Complete setup guide with troubleshooting |
| [🔌 Wiring Diagram](documentation/WIRING_DIAGRAM.md) | Detailed pin-by-pin connections |
| [⚡ Quick Reference](documentation/QUICK_REFERENCE.md) | Fast lookup for labeled LCD modules |
| [🔧 Parts List](documentation/PARTS_LIST.md) | All components needed |
| [💻 TinkerCad Guide](documentation/TINKERCAD_GUIDE.md) | Test your circuit in simulation first |

## Key Features

### No Potentiometer? No Problem!

This project works perfectly **without** a potentiometer. Simply connect LCD Pin 3 (V/O) directly to GND for maximum contrast. If the text is too dark, connect to 3.3V instead.

**See [documentation/README.md](documentation/README.md#dont-have-a-potentiometer-no-problem) for all contrast control options.**

### Labeled vs Numbered LCD Pins

Your LCD may have:
- **Numbered pins:** 1, 2, 3, 4... 16
- **Labeled pins:** GND, VCC, V/O, RS, RW, E, DB0-DB7, LED

Both formats are supported! Check the [Quick Reference](documentation/QUICK_REFERENCE.md) for labeled pin mapping.

## Test Before Building

Try your circuit in [TinkerCad](https://www.tinkercad.com) first! See the [TinkerCad Guide](documentation/TINKERCAD_GUIDE.md) for step-by-step simulation instructions.

## The Code

```cpp
#include <LiquidCrystal.h>

// Initialize LCD: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  lcd.begin(16, 2);                // Initialize 16x2 LCD
  lcd.setCursor(0, 0);             // First line, first position
  lcd.print("Your Full Name");     // <- Edit this
  lcd.setCursor(0, 1);             // Second line
  lcd.print("Arduino Uno R3");
}

void loop() {
  // Display stays on screen
}
```

## Troubleshooting

| Problem | Solution |
|---------|----------|
| **No text visible** | Adjust V/O connection: try GND or 3.3V |
| **Gibberish characters** | Check data pins DB4-DB7 (pins 11-14) → Arduino pins 5,4,3,2 |
| **Nothing on screen** | Verify power connections: VCC→5V, GND→GND |
| **Upload error** | Check board selection and COM port |
| **Backlight not working** | Verify 220Ω resistor and LED pins |

**📖 Full troubleshooting guide in [documentation/README.md](documentation/README.md#troubleshooting)**

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
    └── TINKERCAD_GUIDE.md       # Simulation guide
```

## Next Steps

Once you've got this working, try:
- Add a scrolling message with `lcd.scrollDisplayLeft()`
- Display sensor data (temperature, distance, etc.)
- Add button input to change the message
- Create a simple menu system

## License

This project is open source and available for educational purposes.

## Contributing

Found an issue or want to improve the documentation? Feel free to submit a pull request!

---

**Made with ❤️ for Arduino beginners**

*Part of the [arduino-projects](https://github.com/afragop72/arduino-projects) collection*
