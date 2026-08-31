# Liar's Bar: Tabletop Hardware Edition

An interactive, embedded implementation of the *Liar's Bar* revolver / Russian Roulette game mechanic built on Arduino. The project features randomized chamber states, dynamic LED indicator animations, synchronized audio cues via a DFPlayer Mini, real-time life tracking on a 7-segment display, and a dedicated 3D-printable square enclosure with heat-set threaded inserts.

---

## Features

* **True-Random Cylinder Spin:** Seeds pseudo-random generation using floating analog noise on pin `A0` combined with a Fisher-Yates array shuffle.
* **Synchronized Audio System:** Multi-channel sound effects driven by the DFPlayer Mini:
  * Cylinder spinning & cocking on startup/reload
  * Hammer cock on trigger pull
  * Dry fire click on safe rounds
  * Gunshot on live rounds
* **Visual Status Indicators:**
  * **TM1637 4-Digit Display:** Tracks remaining chamber counts (`6` down to `1`) and displays a custom `dEAd` segment pattern on elimination.
  * **6-LED Array:** 5 Green LEDs (safe chambers) and 1 Red LED (lethal chamber) with dynamic spinning deceleration sequences.
* **Rugged Enclosure Design:** Two-part square enclosure (base + lid) joined via four M3 heat-set brass inserts, featuring front-facing power and status readouts and top-mounted player controls.

---

## System Architecture & Pinout

```
                           +-------------------+
                           |    Arduino Uno/   |
                           |     Nano (MCU)    |
                           +---------+---------+
                                     |
      +---------------+--------------+--------------+---------------+
      |               |              |              |               |
+-----+-----+   +-----+-----+  +-----+-----+  +-----+-----+   +-----+-----+
|  TM1637   |   | DFPlayer  |  | 6x LED    |  | Fire      |  | Power     |
| 7-Segment |   |   Mini    |  | Array     |  | Pushbutton|  | Rocker    |
| (CLK/DIO) |   | (Software |  | (5G / 1R) |  | (Pullup)  |  | Switch    |
|           |   |  Serial)  |  |           |  |           |  |           |
+-----------+   +-----------+  +-----------+  +-----------+  +-----------+
```

### Pin Assignment Table

| Arduino Pin | Connected Hardware | Signal / Mode | Description |
| :--- | :--- | :--- | :--- |
| **D2** | Green LED 1 (`G1`) | `OUTPUT` | Safe Chamber 1 Indicator |
| **D3** | Green LED 2 (`G2`) | `OUTPUT` | Safe Chamber 2 Indicator |
| **D4** | Green LED 3 (`G3`) | `OUTPUT` | Safe Chamber 3 Indicator |
| **D5** | Green LED 4 (`G4`) | `OUTPUT` | Safe Chamber 4 Indicator |
| **D6** | Green LED 5 (`G5`) | `OUTPUT` | Safe Chamber 5 Indicator |
| **D7** | Red LED 1 (`R1`) | `OUTPUT` | Lethal Chamber Indicator |
| **D8** | TM1637 Display | `OUTPUT` | Display Clock (`CLK`) |
| **D9** | Push Button | `INPUT_PULLUP`| Fire / Trigger / Reset Action |
| **D10** | TM1637 Display | `OUTPUT` | Display Data I/O (`DIO`) |
| **D11** | DFPlayer Mini `RX` | `OUTPUT` (SoftSerial) | Arduino TX → DFPlayer RX (via 1kΩ resistor) |
| **D12** | DFPlayer Mini `TX` | `INPUT` (SoftSerial) | Arduino RX ← DFPlayer TX |
| **A0** | *Unconnected* | `INPUT` | Floating ADC input for random entropy |
| **A1** | DFPlayer Mini `BUSY`| `INPUT` | Audio playback status monitoring |

---

## Bill of Materials (BOM)

### Electronics
* 1x Arduino Nano, Uno, or Pro Micro (ATmega328P based)
* 1x DFPlayer Mini MP3 Module
* 1x MicroSD Card (FAT32 formatted, 32GB max)
* 1x 8Ω 0.5W–3W Dynamic Speaker
* 1x TM1637 4-Digit 7-Segment Display Module
* 5x 5mm Green LEDs
* 1x 5mm Red LED
* 6x 220Ω–330Ω Current-Limiting Resistors (for LEDs)
* 1x 1kΩ Resistor (serial line noise suppression between Arduino D11 & DFPlayer RX)
* 1x SPST Rocker Switch (panel-mount)
* 1x SPST Momentary Push Button (panel-mount, top trigger)
* 1x 9V Battery clip or 5V USB breakout board for power

### Hardware & Enclosure
* 4x M3 Brass Heat-Set Threaded Inserts (e.g., M3 x 4mm or M3 x 5.7mm OD)
* 4x M3 Button Head / Socket Head Machine Screws (M3 x 8mm–12mm)
* 1x 3D-Printed Custom Base Enclosure
* 1x 3D-Printed Custom Top Lid

---

## Enclosure Layout & Mechanical Details

* **Front Panel:**
  * Rectangular cutout for the 4-digit TM1637 7-segment display.
  * Rectangular/round cutout for the main SPST rocker power switch.
* **Top Panel (Lid):**
  * Central mounting hole for the trigger push button.
  * 6x Circular bezel holes arranged in an arc/circle for the 5 green LEDs and 1 red LED.
* **Base Mounting:**
  * Four internal corner bosses with pilot holes sized for M3 heat-set inserts.
  * The top lid secures to the base using four countersunk M3 machine screws.

```
       +------------------------------------+
       |  (G1)    (G2)    (G3)    (G4)  (G5)|
       |                                    |
       |             [ TRIGGER ]            |  <-- TOP PANEL (Lid)
       |                                    |
       |                (R1)                |
       +------------------------------------+
       |   +--------------+                 |
       |   | [8][8][8][8] |     [ POWER ]   |  <-- FRONT PANEL
       |   +--------------+                 |
       +------------------------------------+
```

---

## MicroSD Card Setup

1. Format your MicroSD card to **FAT32**.
2. Create a root folder named `01`.
3. Add the following audio files formatted as standard MP3s:

```text
SD_CARD_ROOT/
└── 01/
    ├── 001.mp3  # Spare / reserved
    ├── 002.mp3  # Hammer cock / trigger pull
    ├── 003.mp3  # Dry fire / safe chamber click
    ├── 004.mp3  # Cylinder spin & reload sound
    └── 005.mp3  # Gunshot / lethal round
```

---

## Software Installation & Dependencies

### 1. Required Libraries
Install the following libraries via the Arduino IDE Library Manager (**Sketch → Include Library → Manage Libraries**):
* **`TM1637Display`** by Avishay Orpaz
* **`DFRobotDFPlayerMini`** by DFRobot
* **`SoftwareSerial`** (Included standard with the Arduino AVR core)

### 2. Flashing the Firmware
1. Clone this repository:
   ```bash
   git clone https://github.com/your-username/liars-bar-arduino.git
   ```
2. Open `liars_bar_arduino.ino` in the Arduino IDE.
3. Under **Tools → Board**, select your target board (e.g., **Arduino Nano**).
4. Select the correct **Processor** (e.g., ATmega328P or ATmega328P Old Bootloader) and **Port**.
5. Compile and upload the sketch.

---

## State Machine & Game Logic Flow

```
   [ POWER ON ]
        │
        ▼
   [ State 7: Spin / Init ] ──> Play Sound 004 & Decelerating LED Spin
        │
        ▼ (Press Fire Button)
  ┌─────┴────────────────────────────────────────────────┐
  │ Check randomPins[current_round]                      │
  ├──────────────────────────────┬───────────────────────┤
  │ If Safe Pin (Pins 2-6)       │ If Lethal Pin (Pin 7) │
  ▼                              ▼                       ▼
[ Dry Fire ]                   [ Wet Fire ]
- Decrement lives (6 -> 1)     - Play Sound 002 -> 005
- Play Sound 002 -> 003        - Flash Pin 7 (Red LED)
- Flash corresponding Pin      - Display "dEAd"
- Advance State (8 -> 12)      - Move to State 13 (Game Over)
  │                              │
  └──────────────┬───────────────┘
                 │
                 ▼
         [ State 13: Game Over ]
                 │
                 ▼ (Press Fire Button)
         [ Reset Game ]
         - Re-seed & Fisher-Yates array shuffle
         - Reset display to 6 lives
         - Trigger reload sound & spin sequence
         - Return to State 7
```

---

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
