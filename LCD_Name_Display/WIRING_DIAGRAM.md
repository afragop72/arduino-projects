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
                    │   Pin 12 ├────────────┼───────────────┤ 4 (RS)          │
                    │          │            │               │                 │
                    │   Pin 11 ├────────────┼───────────────┤ 6 (E)           │
                    │          │            │               │                 │
                    │    Pin 5 ├────────────┼───────────────┤ 11 (D4)         │
                    │          │            │               │                 │
                    │    Pin 4 ├────────────┼───────────────┤ 12 (D5)         │
                    │          │            │               │                 │
                    │    Pin 3 ├────────────┼───────────────┤ 13 (D6)         │
                    │          │            │               │                 │
                    │    Pin 2 ├────────────┼───────────────┤ 14 (D7)         │
                    │          │            │               │                 │
                    └──────────┘            │               │ 3 (VO) ─────┐   │
                                            │               │             │   │
                    10kΩ Potentiometer      │               │ 7-10 (D0-D3)│   │
                    (for contrast)          │               │ Not         │   │
                                            │               │ Connected   │   │
                         ┌─────┐            │               │             │   │
                    5V ──┤  o  ├────────────┘               │ 15 (A/LED+) │   │
                         │  │  │                            │      │      │   │
                     VO ─┤  o  ├────────────────────────────┘      │      │   │
                         │  │  │                                   │      │   │
                    GND ─┤  o  ├────────────────────────────┐      │      │   │
                         └─────┘                            │      │      │   │
                                                            │   ┌──┴──┐   │   │
                                                            │   │ 220Ω│   │   │
                                                            │   └──┬──┘   │   │
                                                            │      │      │   │
                                                            │  5V ─┘      │   │
                                                            │             │   │
                                                            └─────────────────┤ 16 (K/LED-)
                                                                          │   │
                                                                          └───┘
```

## Pin-by-Pin Connection Table

### LCD to Arduino

| LCD Pin | Function  | Connection         | Notes                          |
|---------|-----------|-------------------|--------------------------------|
| 1       | VSS       | Arduino GND       | Ground                         |
| 2       | VDD       | Arduino 5V        | Power supply                   |
| 3       | VO        | Pot middle pin (or see alternatives) | Contrast adjustment |
| 4       | RS        | Arduino Pin 12    | Register Select                |
| 5       | RW        | Arduino GND       | Read/Write (always write)      |
| 6       | E         | Arduino Pin 11    | Enable signal                  |
| 7       | D0        | Not connected     | Data bit 0 (4-bit mode)        |
| 8       | D1        | Not connected     | Data bit 1 (4-bit mode)        |
| 9       | D2        | Not connected     | Data bit 2 (4-bit mode)        |
| 10      | D3        | Not connected     | Data bit 3 (4-bit mode)        |
| 11      | D4        | Arduino Pin 5     | Data bit 4                     |
| 12      | D5        | Arduino Pin 4     | Data bit 5                     |
| 13      | D6        | Arduino Pin 3     | Data bit 6                     |
| 14      | D7        | Arduino Pin 2     | Data bit 7                     |
| 15      | A (LED+)  | 5V via 220Ω resistor | Backlight positive          |
| 16      | K (LED-)  | Arduino GND       | Backlight negative             |

### Potentiometer Connections (10kΩ)

| Pot Pin       | Connection    | Purpose                    |
|---------------|---------------|----------------------------|
| Pin 1 (outer) | Arduino 5V    | High voltage reference     |
| Pin 2 (middle)| LCD Pin 3 (VO)| Variable voltage output    |
| Pin 3 (outer) | Arduino GND   | Low voltage reference      |

### No Potentiometer? Alternative Connections for LCD Pin 3 (VO)

If you don't have a potentiometer, use one of these alternatives:

**Option 1: Direct to Ground (Simplest)**
```
LCD Pin 3 (VO) → Arduino GND
```
- Maximum contrast
- Works for most LCDs
- Start with this option

**Option 2: Fixed Resistor Voltage Divider**
```
Arduino 5V → 1kΩ resistor → LCD Pin 3 (VO) → 10kΩ resistor → Arduino GND
```
- Creates ~0.45V at VO
- Better contrast control
- Requires two resistors

**Option 3: Direct to 3.3V**
```
LCD Pin 3 (VO) → Arduino 3.3V pin
```
- Works with some LCDs
- Easy to try if GND is too dark

**Option 4: Leave Floating**
```
LCD Pin 3 (VO) → Not connected
```
- Not recommended
- Unpredictable results
- Last resort only

## Breadboard Layout Guide

### Recommended Layout

1. **Place Arduino** on the left side of breadboard
2. **Place LCD** on the right side (may need two breadboards)
3. **Place Potentiometer** below LCD for easy contrast adjustment
4. **Power Rails**:
   - Connect Arduino 5V to breadboard + rail
   - Connect Arduino GND to breadboard - rail

### Connection Order (Recommended)

Do connections in this order to avoid mistakes:

1. ✅ **Power connections first**
   - LCD Pin 1 (VSS) → GND rail
   - LCD Pin 2 (VDD) → 5V rail

2. ✅ **Potentiometer for contrast**
   - Wire to LCD Pin 3 (VO)
   - Connect to 5V and GND

3. ✅ **Control pins**
   - LCD Pin 4 (RS) → Arduino Pin 12
   - LCD Pin 5 (RW) → GND rail
   - LCD Pin 6 (E) → Arduino Pin 11

4. ✅ **Data pins (D4-D7 only)**
   - LCD Pin 11 (D4) → Arduino Pin 5
   - LCD Pin 12 (D5) → Arduino Pin 4
   - LCD Pin 13 (D6) → Arduino Pin 3
   - LCD Pin 14 (D7) → Arduino Pin 2

5. ✅ **Backlight (last)**
   - LCD Pin 15 (A) → 220Ω resistor → 5V
   - LCD Pin 16 (K) → GND rail

## Troubleshooting Tips

### No Display
- Check 5V and GND connections
- Verify VDD (Pin 2) has 5V
- Verify VSS (Pin 1) is grounded

### Display has blocks/rectangles
- This is normal! Adjust the potentiometer
- Turn slowly until characters appear clearly

### Gibberish characters
- Double-check data pins D4-D7 (pins 11-14 on LCD)
- Verify they go to Arduino pins 5, 4, 3, 2 respectively

### Backlight not working
- Check 220Ω resistor is connected
- Verify Pin 15 (A) goes to 5V through resistor
- Verify Pin 16 (K) is grounded

### Nothing happens when uploading code
- Make sure RW (Pin 5) is grounded
- Check RS and E connections (pins 4 and 6)

## Component Checklist

Before starting, verify you have:

- [ ] Arduino Uno R3
- [ ] 16x2 LCD with HD44780 controller
- [ ] 10kΩ potentiometer (for contrast)
- [ ] 220Ω resistor (for backlight)
- [ ] Breadboard (full-size recommended)
- [ ] ~20 male-to-male jumper wires
- [ ] USB cable for Arduino
