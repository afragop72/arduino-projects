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
| Potentiometer | 1 | 10kΩ (optional - see alternatives) |
| Resistor | 1 | 220Ω for backlight |
| Breadboard | 1 | Optional but recommended |

## Wiring the Circuit

Wire according to the main wiring diagram. The LCD pins in TinkerCad are numbered 1-16. Your physical LCD may have labels (GND, VCC, V/O, etc.) instead - both formats are shown below.

### Power Connections
- LCD Pin 1 (GND/VSS) → Arduino GND
- LCD Pin 2 (VCC/VDD) → Arduino 5V

### Contrast Control

**Option A: With Potentiometer (adjustable contrast)**
- Potentiometer Terminal 1 → Arduino 5V
- Potentiometer Wiper (middle) → LCD Pin 3 (V/O)
- Potentiometer Terminal 2 → Arduino GND

**Option B: Without Potentiometer (recommended for beginners)**
- LCD Pin 3 (V/O) → Arduino GND (direct connection)
- This gives maximum contrast and works for most LCDs
- If text is invisible, try connecting Pin 3 to Arduino 3.3V instead

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

### Backlight (Optional in TinkerCad)
- LCD Pin 15 (LED+/A) → 220Ω resistor → Arduino 5V
- LCD Pin 16 (LED-/K) → Arduino GND

**Note:** In TinkerCad, the backlight works even without the resistor, but include it for real-world accuracy.

## Adding the Code

1. **Click** the "Code" button above the circuit
2. **Switch** from "Blocks" to "Text" using the dropdown
3. **Delete** the default code
4. **Copy and paste** the code from `LCD_Name_Display.ino`
5. **Edit** line 19 to change "Your Full Name" to your actual name

```cpp
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Your Full Name");  // <- Edit this line
  lcd.setCursor(0, 1);
  lcd.print("Arduino Uno R3");
}

void loop() {
  // Nothing here
}
```

## Running the Simulation

1. **Click** "Start Simulation" (green button)
2. **Observe** the LCD display
3. **Adjust** the potentiometer by clicking and dragging the slider
4. **Verify** your name appears on the first line

## Troubleshooting in TinkerCad

### No text visible
- **If using potentiometer:** Adjust the potentiometer slider (contrast control)
- **If Pin 3 is grounded:** Try connecting Pin 3 (V/O) to 3.3V instead
- **Check** VCC/VDD (Pin 2) is connected to 5V
- **Check** GND/VSS (Pin 1) is connected to GND

### Garbled characters
- **Verify** data pins DB4-DB7 (LCD pins 11-14) are connected to Arduino pins 5, 4, 3, 2
- **Double-check** you haven't mixed up the data pin order
- **Ensure** RW (Pin 5) is grounded - LCD must be in write mode
- **Ensure** connections are secure (not connected to breadboard holes with no continuity)

### Compilation errors
- **Make sure** you included `#include <LiquidCrystal.h>`
- **Verify** the LiquidCrystal initialization uses pins: `(12, 11, 5, 4, 3, 2)`
- **Check** for typos in function names

### LCD shows rectangles (blocks)
- This is normal! It means the LCD is powered but not receiving data correctly
- **If using potentiometer:** Adjust it to find the right contrast
- **If Pin 3 grounded:** This might be a contrast issue - try 3.3V instead
- **Check** RS (Pin 4) and E (Pin 6) connections
- **Verify** RW (Pin 5) is grounded

## TinkerCad-Specific Features

### Adjusting Contrast
- Unlike physical hardware, you can drag a slider to adjust the potentiometer
- The LCD responds immediately to contrast changes

### Serial Monitor
- Click the "Serial Monitor" button to see debug output
- Add `Serial.begin(9600);` and `Serial.println()` statements if needed

### Sharing Your Circuit
- Click "Share" to get a public link
- Great for getting help or showing your work

### Exporting
- You can export your circuit as a PDF or image
- Download the code as a `.ino` file

## Advantages of Simulating First

✅ **Safe testing** - No risk of damaging components with incorrect wiring
✅ **Instant feedback** - See results immediately without uploading code
✅ **Easy debugging** - Quickly rewire and test different configurations
✅ **Learning tool** - Understand how components interact before building
✅ **Documentation** - Save and share your working circuit design

## Moving to Physical Hardware

Once your simulation works:

1. **Take a screenshot** of your TinkerCad circuit for reference
2. **Note your LCD pin labels** - Your physical LCD may have labels (GND, VCC, V/O, RS, RW, E, DB0-DB7, LED) instead of numbers (1-16). See QUICK_REFERENCE.md for labeled pin mapping.
3. **Follow the same wiring** on your physical breadboard
4. **Upload the code** to your real Arduino using Arduino IDE
5. **Adjust contrast**:
   - If you have a potentiometer: Turn it until text is clearly visible
   - If no potentiometer: Connect V/O (Pin 3) directly to GND (or try 3.3V if needed)

## Additional Resources

- [TinkerCad Circuits Tutorial](https://www.tinkercad.com/learn/circuits)
- [Arduino Reference](https://www.arduino.cc/reference/en/)
- [LiquidCrystal Library](https://www.arduino.cc/en/Reference/LiquidCrystal)

## Common TinkerCad Limitations

- Simulation runs slower than real hardware
- Some advanced Arduino features may not be available
- Real-world timing may differ slightly
- Component values are idealized

Despite these limitations, TinkerCad is excellent for learning and prototyping!
