# Arduino Samples

A small collection of ready-to-upload Arduino sketches that demonstrate common tasks with clear wiring notes and inline comments. Each example is provided as both a `.ino` and a `.cpp` file so you can drop it straight into the Arduino IDE or copy the code into an existing project.

## Getting started
1. Install the [Arduino IDE](https://www.arduino.cc/en/software) or the [Arduino CLI](https://arduino.github.io/arduino-cli/latest/installation/).
2. Select your board/port (e.g., **Arduino Uno** on the default USB/serial port).
3. Open the desired `.ino` sketch from this repository.
4. Click **Verify/Upload** (or run `arduino-cli compile --upload --fqbn arduino:avr:uno <sketch>` if using the CLI).

## Examples

### 1) Blink (blinky.ino / blinky.cpp)
- **What it shows:** Toggling the on-board LED with fixed delays.
- **Wiring:** Use the built-in LED on pin `13` or connect an external LED + 220 Ω resistor from pin `13` to GND.
- **Behavior:** LED turns on for 1 s, then off for 1 s, repeating.

### 2) 16x2 LCD marquee (lcd.ino / lcd.cpp)
- **What it shows:** Scrolling text across an HD44780-compatible 16x2 LCD using the `LiquidCrystal` library.
- **Wiring:** RS→`12`, EN→`11`, D4→`5`, D5→`4`, D6→`3`, D7→`2`, plus power/contrast (10 kΩ potentiometer on VO).
- **Behavior:** "Hello, Friends!!" scrolls left, then right, then returns to center with adjustable pauses between cycles.

### 3) Seven-segment counter (7seg_display.ino / 7seg_display.cpp)
- **What it shows:** Driving a single common-cathode 7-seg display without driver ICs.
- **Wiring:** Connect segments A–G to pins `8, 7, 6, 5, 4, 3, 2` respectively; tie the display cathode to GND through an appropriate resistor network.
- **Behavior:** Counts upward once per second, lighting only the segments needed for each digit.

### 4) Button-driven state machine (state_machine.ino)
- **What it shows:** A simple finite state machine with debounced input and non-blocking timing via `millis()`.
- **Wiring:** Momentary button between pin `2` and GND (internal pull-up enabled); use the built-in LED on `LED_BUILTIN`.
- **Behavior:**
  - **Idle:** LED off until the button is pressed.
  - **Arming:** Slow blink for 3 seconds.
  - **Armed:** LED on solid; button press advances to Firing.
  - **Firing:** Fast blink for 2 seconds, then return to Idle.


### 5) Traffic light controller (traffic_light.ino / traffic_light.cpp)
- **What it shows:** A timed finite-state machine controlling multiple outputs without `delay()`.
- **Wiring:** Red LED→`10`, Yellow LED→`9`, Green LED→`8` (each LED in series with ~220 Ω resistor to GND).
- **Behavior:** Cycles Green (5 s) → Yellow (1.5 s) → Red (4 s), then repeats.

### 6) Potentiometer PWM dimmer (pwm_dimmer.ino / pwm_dimmer.cpp)
- **What it shows:** Mapping analog sensor input to PWM brightness output.
- **Wiring:** Potentiometer ends to 5V/GND with wiper to `A0`; LED + resistor from PWM pin `9` to GND.
- **Behavior:** Rotating the potentiometer smoothly changes LED brightness.

## Tips
- If you change the pin assignments, update the `constexpr` pin constants at the top of each sketch.
- For boards with a different built-in LED pin, set `LED_PIN` accordingly.
- Use a common-ground reference when powering external components (LCD, 7-seg display, buttons) from separate supplies.

## Suggested next samples
If you want to grow this collection, these are high-value additions that stay beginner-friendly while introducing practical patterns:

1. **Servo sweep with easing (`servo_sweep.ino`)**
   - Teaches the `Servo` library and safe power/wiring practices.
   - Can include both blocking and non-blocking movement styles.

2. **Ultrasonic distance meter (`ultrasonic_distance.ino`)**
   - Teaches timing pulses (`pulseIn`) and converting time-of-flight to centimeters.
   - Easy to pair with serial output and LED/LCD feedback.

3. **Serial command parser (`serial_commands.ino`)**
   - Teaches reading text commands from Serial Monitor (e.g., `LED ON`, `LED OFF`, `BLINK 250`).
   - Introduces robust parsing and validation without advanced dependencies.

4. **Non-blocking multi-task loop (`millis_scheduler.ino`)**
   - Teaches scheduling several periodic tasks without `delay()`.
   - Reinforces production-style Arduino structure and responsiveness.

5. **I2C sensor basics (`i2c_bme280.ino` or `i2c_bh1750.ino`)**
   - Teaches I2C wiring, external libraries, and structured sensor reads.
   - Good first step toward IoT-style projects.

6. **EEPROM settings example (`eeprom_settings.ino`)**
   - Teaches persistent configuration storage and data validation on boot.
   - Useful for mode/state retention across resets.
