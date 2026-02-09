# Quick Reference for Labeled LCD Modules

Your LCD has **labeled pins** on the PCB instead of just numbers. Use this guide for quick wiring.

## Pin Mapping (Left to Right)

Reading your LCD pins from **left to right** as shown on the PCB:

```
GND → VCC → V/O → RS → RW → E → DB0 → DB1 → DB2 → DB3 → DB4 → DB5 → DB6 → DB7 → LED → LED
```

## Wiring Table

| LCD Label | Arduino Connection | Notes |
|-----------|-------------------|-------|
| **GND** | GND | Ground |
| **VCC** | 5V | Power |
| **V/O** | GND | Contrast (start with GND) |
| **RS** | Pin 12 | Register Select |
| **RW** | GND | Read/Write (always GND) |
| **E** | Pin 11 | Enable |
| **DB0** | — | Not connected |
| **DB1** | — | Not connected |
| **DB2** | — | Not connected |
| **DB3** | — | Not connected |
| **DB4** | Pin 5 | Data |
| **DB5** | Pin 4 | Data |
| **DB6** | Pin 3 | Data |
| **DB7** | Pin 2 | Data |
| **LED** (left) | 5V via 220Ω | Backlight + |
| **LED** (right) | GND | Backlight - |

## Step-by-Step Wiring

**1. Power connections:**
- GND → Arduino GND
- VCC → Arduino 5V

**2. Contrast (no potentiometer needed):**
- V/O → Arduino GND

**3. Control signals:**
- RS → Arduino Pin 12
- RW → Arduino GND
- E → Arduino Pin 11

**4. Data lines (4-bit mode):**
- DB4 → Arduino Pin 5
- DB5 → Arduino Pin 4
- DB6 → Arduino Pin 3
- DB7 → Arduino Pin 2
- (DB0-DB3 not connected)

**5. Backlight:**
- LED (left) → 220Ω resistor → Arduino 5V
- LED (right) → Arduino GND

## Important Notes

- **V/O to GND works for most LCDs** - Try this first! If text is invisible or too dark, connect V/O to 3.3V instead
- **RW must be grounded** - This puts LCD in write mode
- **DB0-DB3 stay disconnected** - We're using 4-bit mode to save Arduino pins
- **220Ω resistor protects backlight** - Don't skip it on physical hardware

## Code Pin Configuration

Make sure your Arduino code matches:
```cpp
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
//               RS  E  D4 D5 D6 D7
```

This is already correct in `LCD_Name_Display.ino`.
