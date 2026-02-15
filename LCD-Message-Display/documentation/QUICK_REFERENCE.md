# Quick Reference for Labeled LCD Modules

Your LCD has **labeled pins** on the PCB instead of just numbers. Use this guide for quick wiring.

## Pin Mapping (Left to Right)

Reading your LCD pins from **left to right** as shown on the PCB:

```
GND → VCC → V/O → RS → RW → E → DB0 → DB1 → DB2 → DB3 → DB4 → DB5 → DB6 → DB7 → LED → LED
```

## LCD Wiring Table

| LCD Label       | Arduino Connection         | Notes                         |
| --------------- | -------------------------- | ----------------------------- |
| **GND**         | GND                        | Ground                        |
| **VCC**         | 5V                         | Power                         |
| **V/O**         | Contrast pot wiper          | Pot between 5V and GND        |
| **RS**          | Pin 12                     | Register Select               |
| **RW**          | GND                        | Read/Write (always GND)       |
| **E**           | Pin 11                     | Enable                        |
| **DB0**         | --                         | Not connected                 |
| **DB1**         | --                         | Not connected                 |
| **DB2**         | --                         | Not connected                 |
| **DB3**         | --                         | Not connected                 |
| **DB4**         | Pin 5                      | Data                          |
| **DB5**         | Pin 4                      | Data                          |
| **DB6**         | Pin 3                      | Data                          |
| **DB7**         | Pin 2                      | Data                          |
| **LED** (left)  | 5V via 220Ω                | Backlight + (always on)       |
| **LED** (right) | GND                        | Backlight -                   |

## Potentiometer Connections

| Pot          | Terminal 1 | Wiper (middle) | Terminal 2 |
| ------------ | ---------- | -------------- | ---------- |
| Contrast     | 5V         | LCD V/O        | GND        |
| Scroll Speed | 5V         | Arduino A1     | GND        |

## LED Chase Connections

| LED            | Arduino Pin | Resistor | Cathode |
| -------------- | ----------- | -------- | ------- |
| Red            | Pin 7       | 220Ω     | GND     |
| Yellow         | Pin 8       | 220Ω     | GND     |
| Green          | Pin 9       | 220Ω     | GND     |

## Step-by-Step Wiring

**1. Power connections:**

- GND → Arduino GND
- VCC → Arduino 5V

**2. Contrast pot:**

- Pot outer pins → 5V and GND
- Pot wiper → LCD V/O

**3. Scroll speed pot:**

- Pot outer pins → 5V and GND
- Pot wiper → Arduino A1

**4. Control signals:**

- RS → Arduino Pin 12
- RW → Arduino GND
- E → Arduino Pin 11

**5. Data lines (4-bit mode):**

- DB4 → Arduino Pin 5
- DB5 → Arduino Pin 4
- DB6 → Arduino Pin 3
- DB7 → Arduino Pin 2
- (DB0-DB3 not connected)

**6. Backlight:**

- LED (left) → 220Ω resistor → 5V
- LED (right) → Arduino GND

**7. Chase LEDs:**

- Pin 7 → 220Ω → Red LED → GND
- Pin 8 → 220Ω → Yellow LED → GND
- Pin 9 → 220Ω → Green LED → GND

## Code Pin Configuration

Make sure your Arduino code matches:

```cpp
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
//               RS  E  D4 D5 D6 D7

const int SPEED_POT = A1;            // Scroll speed pot input
const int LED_PINS[] = {7, 8, 9};    // Chase LEDs
```

## Important Notes

- **RW must be grounded** - This puts LCD in write mode
- **DB0-DB3 stay disconnected** - We're using 4-bit mode to save Arduino pins
- **220Ω resistors are required** - One for backlight, one per LED
- **Backlight goes to 5V** (through 220Ω) - Always on
- **Scroll speed pot wiper goes to A1** - The code reads this to set scroll delay
