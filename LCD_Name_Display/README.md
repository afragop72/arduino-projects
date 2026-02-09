# LCD Name Display

Displays your full name on a 16x2 HD44780 parallel LCD using Arduino Uno R3.

## Hardware Requirements

- Arduino Uno R3
- 16x2 LCD with HD44780 controller (white on blue)
- 10kΩ potentiometer (for contrast adjustment) - *Optional, see alternatives below*
- 220Ω resistor (for backlight)
- Breadboard and jumper wires

## Wiring Diagram

**Arduino Uno R3 → LCD Pin Connections:**

*Note: Your LCD may have numbered pins (1-16) OR labeled pins (GND, VCC, etc.). Both are shown below.*

| Pin # | Label on PCB | Function | Connection |
|-------|--------------|----------|------------|
| 1 | GND | Ground | Arduino GND |
| 2 | VCC | Power | Arduino 5V |
| 3 | V/O | Contrast | GND (or see alternatives below) |
| 4 | RS | Register Select | Arduino Digital Pin 12 |
| 5 | RW | Read/Write | Arduino GND |
| 6 | E | Enable | Arduino Digital Pin 11 |
| 7 | DB0 | Data 0 | Not connected (4-bit mode) |
| 8 | DB1 | Data 1 | Not connected (4-bit mode) |
| 9 | DB2 | Data 2 | Not connected (4-bit mode) |
| 10 | DB3 | Data 3 | Not connected (4-bit mode) |
| 11 | DB4 | Data 4 | Arduino Digital Pin 5 |
| 12 | DB5 | Data 5 | Arduino Digital Pin 4 |
| 13 | DB6 | Data 6 | Arduino Digital Pin 3 |
| 14 | DB7 | Data 7 | Arduino Digital Pin 2 |
| 15 | LED (left) | Backlight + | 5V through 220Ω resistor |
| 16 | LED (right) | Backlight - | Arduino GND |

**Potentiometer Connections (if you have one):**
- One outer pin → Arduino 5V
- Other outer pin → Arduino GND
- Middle pin → LCD Pin 3 (V/O)

### Don't Have a Potentiometer? No Problem!

If you don't have a potentiometer, use one of these alternatives for LCD Pin 3 (V/O):

**Option 1: Direct to Ground (Recommended)**
- Connect V/O (Pin 3) directly to Arduino GND
- Provides maximum contrast
- Works for most HD44780 LCDs
- Simplest solution

**Option 2: Fixed Resistor Voltage Divider**
- 1kΩ resistor: 5V → V/O (Pin 3)
- 10kΩ resistor: V/O (Pin 3) → GND
- Creates ~0.45V for better contrast control
- Requires two resistors

**Option 3: 3.3V Connection**
- Connect V/O (Pin 3) directly to Arduino 3.3V pin
- Works with some LCDs
- Easy to try if direct GND is too dark

**Option 4: Leave Floating (Not Recommended)**
- Leave V/O unconnected
- May work but contrast is unpredictable
- Try only if other options fail

**Recommendation:** Start with Option 1 (direct to GND). If the text is too dark or invisible, try Option 3 (3.3V).

## Installation

1. Wire the LCD to the Arduino following the diagram above
2. Open `LCD_Name_Display.ino` in Arduino IDE
3. Edit line 18 to replace `"Your Full Name"` with your actual name
4. Select **Tools → Board → Arduino AVR Boards → Arduino Uno**
5. Select the correct COM port under **Tools → Port**
6. Click the **Upload** button (→) or press Ctrl+U

## Usage

Once uploaded, your name will display immediately on the LCD screen. Adjust the potentiometer to control contrast until the text is clearly visible.

## Troubleshooting

- **No text visible**: Adjust the contrast potentiometer
- **Gibberish characters**: Check all data pin connections (D4-D7)
- **Nothing on screen**: Verify power connections (VSS, VDD, and backlight)
- **Upload error**: Make sure the correct board and port are selected
