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

| LCD Pin | Pin Name | Connection |
|---------|----------|------------|
| 1 | VSS | GND |
| 2 | VDD | 5V |
| 3 | VO | Potentiometer middle pin (contrast) |
| 4 | RS | Digital Pin 12 |
| 5 | RW | GND |
| 6 | E | Digital Pin 11 |
| 7 | D0 | Not connected |
| 8 | D1 | Not connected |
| 9 | D2 | Not connected |
| 10 | D3 | Not connected |
| 11 | D4 | Digital Pin 5 |
| 12 | D5 | Digital Pin 4 |
| 13 | D6 | Digital Pin 3 |
| 14 | D7 | Digital Pin 2 |
| 15 | A (LED+) | 5V through 220Ω resistor |
| 16 | K (LED-) | GND |

**Potentiometer Connections:**
- One outer pin → 5V
- Other outer pin → GND
- Middle pin → LCD Pin 3 (VO)

### Don't Have a Potentiometer? No Problem!

If you don't have a potentiometer, use one of these alternatives for LCD Pin 3 (VO):

**Option 1: Direct to Ground (Recommended)**
- Connect VO (Pin 3) directly to GND
- Provides maximum contrast
- Works for most HD44780 LCDs
- Simplest solution

**Option 2: Fixed Resistor Voltage Divider**
- 1kΩ resistor: 5V → VO (Pin 3)
- 10kΩ resistor: VO (Pin 3) → GND
- Creates ~0.45V for better contrast control
- Requires two resistors

**Option 3: 3.3V Connection**
- Connect VO (Pin 3) directly to Arduino 3.3V pin
- Works with some LCDs
- Easy to try if direct GND is too dark

**Option 4: Leave Floating (Not Recommended)**
- Leave VO unconnected
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
