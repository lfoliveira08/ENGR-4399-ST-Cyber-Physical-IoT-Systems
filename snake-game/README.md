# ESP32 Snake Game (Wokwi)

Classic Snake game on an ESP32 with an SSD1306 OLED display and an analog joystick, simulated in Wokwi.

- **Wokwi project:** https://wokwi.com/projects/475718288309291009
- **Libraries:** Adafruit SSD1306, Adafruit GFX Library, Adafruit BusIO (see `libraries.txt`)

## Files
| File | Purpose |
|---|---|
| `sketch.ino` | Main loop: start screen, game over, movement, collision, drawing |
| `snake.cpp` / `snake.h` | Snake state, movement, boundary check |
| `food.cpp` | Food generation and collision |
| `Joystick.cpp` / `Joystick.h` | Joystick direction and button reading |
| `score.cpp` / `score.h` | Score tracking |
| `diagram.json` | Wokwi circuit |

## Run
Open the Wokwi link above (or create an ESP32 project, paste these files, add the libraries) and press Start. Press the joystick button to begin, move the joystick to steer.
