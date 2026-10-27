# RFID-Controlled LED Lamp

**Arduino | C++ | RFID | SPI | FastLED**

An Arduino-based lighting system that uses RFID cards to control an addressable LED strip. The project explores an alternative approach to traditional switches and Bluetooth-based lighting by using RFID technology for interactive lighting automation.

Developed as a group project for CS 578 at San Diego State University.

## Features

- **RFID Color Control:** Scan programmed RFID cards to change LED colors (red, blue, green).
- **On/Off Toggle:** Scanning the currently active color card again turns off the LEDs.
- **Color Mixing:** Scanning designated blue and red RFID cards in sequence within three seconds activates purple lighting.
- **Serial Monitoring:** Displays detected RFID UIDs and system status for debugging.

## Hardware & Technologies

| Component | Purpose |
|---|---|
| Arduino Uno | Processes RFID input and controls LEDs |
| MFRC522 RFID Reader | Reads RFID card UIDs through SPI |
| WS2812B LED Strip | Displays selected colors (60 LEDs) |
| 5V 3A Power Supply | Powers the LED strip |
| Breadboard & Jumper Wires | Connects the prototype hardware |

**Programming:** Arduino C++  
**Libraries:** FastLED, MFRC522, SPI  
**Development Environment:** Arduino IDE

## How It Works

1. The MFRC522 reader detects an RFID card and sends its UID to the Arduino.
2. The Arduino compares the UID against predefined identifiers.
3. A recognized card triggers a corresponding LED color or toggle action.
4. The system tracks the previous UID and scan timestamp to detect color-mixing sequences.
5. The FastLED library updates the LED strip accordingly.

## Results & Challenges

The prototype successfully detected RFID cards and controlled LED colors in response to scanned inputs. It also demonstrated timed color mixing using two designated RFID cards.

During development, improper circuit grounding initially caused unstable LED behavior. Correcting the grounding connections resolved the issue.

## Future Improvements

- Expand RFID color mixing to support more RGB combinations.
- Implement additional lighting effects, including fading and rainbow animations.
- Introduce RFID-based brightness control.
- Replace the breadboard prototype with a compact, permanent circuit.

## Contributors

**CS 578 — Group 8**

- Minh Tran
- Lucas Coglianese
- Quinn Ferguson