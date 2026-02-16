# LCD Wiring Diagram

## Visual Connection Diagram

```
                    ARDUINO UNO R3                          16x2 LCD (HD44780)

                    ┌──────────┐                            ┌─────────────────┐
                    │          │                            │                 │
                    │      5V  ├────────────┬───────────────┤ 2 (VDD)         │
                    │          │            │               │                 │
                    │     GND  ├─────┬──────┼────┬──────────┤ 1 (VSS)         │
                    │          │     │      │    │          │                 │
                    │          │     │      │    └──────────┤ 5 (RW)          │
                    │          │     │      │               │                 │
                    │   Pin 12 ├─────┼──────┼───────────────┤ 4 (RS)          │
                    │          │     │      │               │                 │
                    │   Pin 11 ├─────┼──────┼───────────────┤ 6 (E)           │
                    │          │     │      │               │                 │
                    │    Pin 5 ├─────┼──────┼───────────────┤ 11 (D4)         │
                    │          │     │      │               │                 │
                    │    Pin 4 ├─────┼──────┼───────────────┤ 12 (D5)         │
                    │          │     │      │               │                 │
                    │    Pin 3 ├─────┼──────┼───────────────┤ 13 (D6)         │
                    │          │     │      │               │                 │
                    │    Pin 2 ├─────┼──────┼───────────────┤ 14 (D7)         │
                    │          │     │      │               │                 │
                    │   Pin 10 ├──── Slideswitch common      │ 3 (VO) ─────┐   │
                    │          │     │      │               │             │   │
                    │    Pin 7 ├──[220Ω]──LED1 (red)        │             │   │
                    │          │     │      │               │             │   │
                    │    Pin 8 ├──[220Ω]──LED2 (yellow)     │ 15 (A/LED+)│   │
                    │          │     │      │               │      │      │   │
                    │    Pin 9 ├──[220Ω]──LED3 (green)      │   ┌──┴──┐   │   │
                    │          │     │      │               │   │ 220Ω│   │   │
                    │       A1 ├─────┼──────┼──┐            │   └──┬──┘   │   │
                    │          │     │      │  │            │      │      │   │
                    └──────────┘     │      │  │            │  5V ─┘      │   │
                                     │      │  │            │             │   │
                    Pot 1 (Contrast)─┼──────┼──┼────────────│─────────────┘   │
                    (hardware only)  │      │  │            │                 │
                         ┌─────┐     │      │  │            │ 7-10 (D0-D3)   │
                    5V ──┤  o  ├─────┘      │  │            │ Not Connected   │
                         │  │  │            │  │            │                 │
                     VO ─┤  o  ├────────────┼──┼──LCD Pin 3 │ 16 (K/LED-)    │
                         │  │  │            │  │            └──────┬──────────┘
                    GND ─┤  o  ├────────────┘  │                   │
                         └─────┘               │                   │
                                               │                GND rail
                    Pot 2 (Scroll Speed)       │
                    (software read on A1)      │
                         ┌─────┐               │
                    5V ──┤  o  ├───────────────┘
                         │  │  │
                     A1 ─┤  o  ├── Arduino A1
                         │  │  │
                    GND ─┤  o  ├── GND rail
                         └─────┘
```

## Pin-by-Pin Connection Table

### LCD to Arduino

**Note:** Your LCD may have numbered pins (1-16) OR labeled pins (GND, VCC, etc.) - both are shown.

| Pin # | PCB Label | Function   | Connection                              | Notes                          |
| ----- | --------- | ---------- | --------------------------------------- | ------------------------------ |
| 1     | GND       | Ground     | Arduino GND                             | Ground                         |
| 2     | VCC       | Power      | Arduino 5V                              | Power supply                   |
| 3     | V/O       | Contrast   | Pot 1 wiper (middle pin)                | Contrast adjustment            |
| 4     | RS        | Register   | Arduino Pin 12                          | Register Select                |
| 5     | RW        | R/W        | Arduino GND                             | Read/Write (always write)      |
| 6     | E         | Enable     | Arduino Pin 11                          | Enable signal                  |
| 7     | DB0       | Data 0     | Not connected                           | 4-bit mode                     |
| 8     | DB1       | Data 1     | Not connected                           | 4-bit mode                     |
| 9     | DB2       | Data 2     | Not connected                           | 4-bit mode                     |
| 10    | DB3       | Data 3     | Not connected                           | 4-bit mode                     |
| 11    | DB4       | Data 4     | Arduino Pin 5                           | Data bit 4                     |
| 12    | DB5       | Data 5     | Arduino Pin 4                           | Data bit 5                     |
| 13    | DB6       | Data 6     | Arduino Pin 3                           | Data bit 6                     |
| 14    | DB7       | Data 7     | Arduino Pin 2                           | Data bit 7                     |
| 15    | LED       | LED+       | 5V via 220Ω resistor                    | Backlight positive (always on) |
| 16    | LED       | LED-       | Arduino GND                             | Backlight negative             |

### Contrast Potentiometer (Pot 1 - 10kΩ, hardware only)

| Pot Pin        | Connection     | Purpose                    |
| -------------- | -------------- | -------------------------- |
| Pin 1 (outer)  | Arduino 5V     | High voltage reference     |
| Pin 2 (middle) | LCD Pin 3 (VO) | Variable voltage output    |
| Pin 3 (outer)  | Arduino GND    | Low voltage reference      |

### Scroll Speed Potentiometer (Pot 2 - 10kΩ, software controlled)

| Pot Pin        | Connection  | Purpose                             |
| -------------- | ----------- | ----------------------------------- |
| Pin 1 (outer)  | Arduino 5V  | High voltage reference              |
| Pin 2 (middle) | Arduino A1  | Analog input read by code           |
| Pin 3 (outer)  | Arduino GND | Low voltage reference               |

The Arduino reads the voltage on A1 (0-1023) and maps it to a scroll delay (100ms–500ms), controlling how fast text scrolls and LEDs chase.

### Power Switch (Slideswitch — SPDT)

| Switch Pin     | Connection  | Purpose                             |
| -------------- | ----------- | ----------------------------------- |
| Terminal 1     | Arduino 5V  | ON position (HIGH)                  |
| Common (middle)| Arduino Pin 10 | Digital input read by code       |
| Terminal 2     | Arduino GND | OFF position (LOW)                  |

When the switch connects pin 10 to 5V, the system runs. When it connects to GND, the LCD clears and LEDs turn off.

### LED Bounce Lights

| LED            | Arduino Pin | Resistor | Cathode |
| -------------- | ----------- | -------- | ------- |
| LED 1 (red)    | Pin 7       | 220Ω     | GND     |
| LED 2 (yellow) | Pin 8       | 220Ω     | GND     |
| LED 3 (green)  | Pin 9       | 220Ω     | GND     |

**Per LED:** Arduino Pin → 220Ω resistor → LED anode (+) → LED cathode (-) → GND rail

## Breadboard Layout Guide

### Recommended Layout

1. **Place Arduino** on the left side of breadboard
2. **Place LCD** on the right side (may need two breadboards)
3. **Place Pot 1 (contrast)** near LCD Pin 3 for short wiring
4. **Place Pot 2 (scroll speed)** near Arduino A1
5. **Place LEDs** in a row near the Arduino for visibility
6. **Power Rails**:
   - Connect Arduino 5V to breadboard + rail
   - Connect Arduino GND to breadboard - rail

### Connection Order (Recommended)

Do connections in this order to avoid mistakes:

1. **Power connections first**
   - LCD Pin 1 (VSS) → GND rail
   - LCD Pin 2 (VDD) → 5V rail

2. **Contrast potentiometer**
   - Pot 1 outer pins → 5V and GND rails
   - Pot 1 wiper → LCD Pin 3 (VO)

3. **Scroll speed potentiometer**
   - Pot 2 outer pins → 5V and GND rails
   - Pot 2 wiper → Arduino A1

4. **Power switch**
   - Slideswitch Terminal 1 → 5V rail
   - Slideswitch Common → Arduino Pin 10
   - Slideswitch Terminal 2 → GND rail

5. **Control pins**
   - LCD Pin 4 (RS) → Arduino Pin 12
   - LCD Pin 5 (RW) → GND rail
   - LCD Pin 6 (E) → Arduino Pin 11

6. **Data pins (D4-D7 only)**
   - LCD Pin 11 (D4) → Arduino Pin 5
   - LCD Pin 12 (D5) → Arduino Pin 4
   - LCD Pin 13 (D6) → Arduino Pin 3
   - LCD Pin 14 (D7) → Arduino Pin 2

7. **Backlight (always on)**
   - LCD Pin 15 (A) → 220Ω resistor → 5V rail
   - LCD Pin 16 (K) → GND rail

8. **LEDs (last)**
   - LED 1: Pin 7 → 220Ω → red LED → GND rail
   - LED 2: Pin 8 → 220Ω → yellow LED → GND rail
   - LED 3: Pin 9 → 220Ω → green LED → GND rail

## Troubleshooting Tips

### No Display

- Check 5V and GND connections
- Verify VDD (Pin 2) has 5V
- Verify VSS (Pin 1) is grounded

### Display has blocks/rectangles

- Adjust the contrast potentiometer (Pot 1)
- Turn slowly until characters appear clearly

### Gibberish characters

- Double-check data pins D4-D7 (pins 11-14 on LCD)
- Verify they go to Arduino pins 5, 4, 3, 2 respectively

### Backlight not working

- Verify LCD Pin 15 (A) connects through 220Ω to **5V** rail
- Verify LCD Pin 16 (K) is connected to GND

### LEDs not chasing

- Verify each LED has a 220Ω series resistor
- Check LED polarity (longer leg = anode = positive)
- Confirm pins 7, 8, 9 are wired correctly

### Scroll speed pot has no effect

- Verify pot wiper (middle pin) goes to Arduino **A1**
- Ensure outer terminals go to 5V and GND

### Nothing happens when uploading code

- Make sure RW (Pin 5) is grounded
- Check RS and E connections (pins 4 and 6)

## Component Checklist

Before starting, verify you have:

- [ ] Arduino Uno R3
- [ ] 16x2 LCD with HD44780 controller
- [ ] 10kΩ potentiometer x2 (contrast + scroll speed)
- [ ] SPDT slideswitch x1 (power ON/OFF)
- [ ] 220Ω resistor x4 (1 for backlight, 3 for LEDs)
- [ ] LED x3 (red, yellow, green)
- [ ] Breadboard (full-size recommended)
- [ ] ~25 male-to-male jumper wires
- [ ] USB cable for Arduino
