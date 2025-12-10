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

### 4) Button-driven state machine (state_machine.ino / state_machine.cpp)
- **What it shows:** A simple finite state machine with debounced input and non-blocking timing via `millis()`.
- **Wiring:** Momentary button between pin `2` and GND (internal pull-up enabled); use the built-in LED on `LED_BUILTIN`.
- **Behavior:**
  - **Idle:** LED off until the button is pressed.
  - **Arming:** Slow blink for 3 seconds.
  - **Armed:** LED on solid; button press advances to Firing.
  - **Firing:** Fast blink for 2 seconds, then return to Idle.

### 5) Potentiometer PWM dimmer (analog_pwm.ino / analog_pwm.cpp)
- **What it shows:** Reading an analog value and scaling it to PWM output for LED brightness control.
- **Wiring:** 10 kΩ potentiometer wiper to `A0`, outer legs to 5V and GND; LED + 220 Ω resistor to PWM pin `9`.
- **Behavior:** LED brightness follows the knob position; serial monitor logs raw ADC and mapped PWM values every ~0.2 s.

### 6) Servo sweep (servo_sweep.ino / servo_sweep.cpp)
- **What it shows:** Driving a hobby servo with the `Servo` library and sweeping through its full range.
- **Wiring:** Servo signal to pin `10`, power to 5V, and ground to GND (ensure a shared ground and adequate 5V supply).
- **Behavior:** Servo sweeps from 0° to 180° in small steps, pauses briefly, then sweeps back.

## Tips
- If you change the pin assignments, update the `constexpr` pin constants at the top of each sketch.
- For boards with a different built-in LED pin, set `LED_PIN` accordingly.
- Use a common-ground reference when powering external components (LCD, 7-seg display, buttons) from separate supplies.
