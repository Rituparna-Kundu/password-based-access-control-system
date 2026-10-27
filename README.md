# 🔐 Password-Based Access Control System

A password-protected lock built and simulated in [Wokwi](https://wokwi.com). Type a code on a 4x4 keypad, watch the masked input on an OLED screen, and a relay switches on when the code is correct. Three wrong attempts lock the keypad for 30 seconds.

<img width="850" height="757" alt="image" src="https://github.com/user-attachments/assets/cfae5ff8-ea14-45c1-9c01-da394cf83188" />


**Try it live:** [Open the simulation in Wokwi](https://wokwi.com/projects/479050622954220545)

## How it works

- Type up to 4 characters. The OLED shows them as `*` so the password stays hidden.
- `#` submits the code, `*` clears what you typed.
- Correct code (default `123A`): the screen shows **ACCESS GRANTED** and the relay turns on for 5 seconds.
- Wrong code: the screen shows how many attempts are left.
- Three wrong attempts in a row: the screen shows **LOCKED** with a 30-second countdown, then resets.

## Components

| Part | Notes |
|------|-------|
| Arduino Uno | Main controller |
| 4x4 membrane keypad | Password input |
| SSD1306 OLED, 128x64 | I2C, address `0x3C` |
| Relay module | Stands in for a door lock or solenoid |

## Pin map

| Connection | Arduino Uno pin |
|------------|-----------------|
| Keypad rows R1 to R4 | 9, 8, 7, 6 |
| Keypad columns C1 to C4 | 5, 4, 3, 2 |
| Relay IN | 10 |
| OLED SDA | A4 |
| OLED SCL | A5 |

Power (VCC) and ground for the OLED and relay are connected as shown in `diagram.json`.

## Libraries

- Adafruit SSD1306
- Adafruit GFX Library
- Keypad

They are listed in `libraries.txt`, and Wokwi installs them automatically.

## Run it yourself

1. Open the Wokwi link above, or create a new Arduino Uno project on wokwi.com.
2. Copy `sketch.ino`, `diagram.json` and `libraries.txt` into the project.
3. Press the green play button and click the keypad. Try `123A` then `#`.

## Notes

- The password is hard-coded in `PASS` for demo purposes. A real lock would not keep its password in plain code.
- The relay is driven through the `ON` and `OFF` macros (currently active-low). If your relay module is active-high, swap the two definitions.
- The lockout uses `delay()`, so the keypad ignores input during the 30-second countdown. That is intentional.

## Ideas for next steps

- Add a buzzer for access granted and wrong-password feedback.
- Let the user change the password from the keypad and store it in EEPROM.
- Add a backup entry method such as an RFID card.
