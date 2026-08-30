# SBK_Button

**SBK_Button** is a lightweight push-button library for Arduino-compatible platforms. It provides the `Button` class for non-blocking debouncing, press and release events, push-on / push-off latching, long-press detection, and press/release duration tracking.

The `Button` class supports both active-low and active-high button circuits. Active-low buttons can use the microcontroller's internal pull-up resistor or an external pull-up resistor.

---

## Features

- Non-blocking button polling
- Configurable software debouncing
- Pressed and released state detection
- One-cycle `justPressed()` and `justReleased()` events
- Push-on / push-off latching state
- Configurable long-press delay
- One-cycle `justLongPressed()` event
- Continuous `isLongPressed()` state
- Pressed-time and released-time tracking
- Active-low and active-high input support
- Support for internal pull-up, external pull-up, and external pull-down wiring
- Event-clearing helpers

---

## Compatibility

**SBK_Button** uses only the standard Arduino API and is compatible with virtually all Arduino-supported architectures, including:

- AVR
- megaAVR
- SAMD
- ESP8266
- ESP32
- RP2040
- STM32
- Renesas RA (Uno R4)

---

## Installation

### Arduino Library Manager

Search for:

```text
SBK_Button
```

### Manual Installation

1. Download the latest release from GitHub.
2. In the Arduino IDE, select **Sketch > Include Library > Add .ZIP Library**.
3. Select the downloaded ZIP archive.

### PlatformIO

Add the library to `platformio.ini`:

```ini
lib_deps =
    SBK_Button
```

---

## Wiring

### Active-low button with internal pull-up

Connect the button between the GPIO pin and GND. This is the default configuration.

```cpp
Button button(2);
```

The GPIO is configured as `INPUT_PULLUP`. The button is considered pressed when the pin reads `LOW`.

### Active-low button with external pull-up

Connect an external pull-up resistor between the GPIO pin and VCC, and connect the button between the GPIO pin and GND.

```cpp
Button externalPullup(
    2,
    ButtonWiring::EXTERNAL_PULLUP);
```

The GPIO is configured as `INPUT` because the external resistor supplies the pull-up.

### Active-high button with external pull-down

Connect an external pull-down resistor between the GPIO pin and GND, and connect the button between the GPIO pin and VCC.

```cpp
Button externalPulldown(
    2,
    ButtonWiring::EXTERNAL_PULLDOWN);
```

The GPIO is configured as `INPUT`. AVR Arduino boards do not provide an internal pull-down resistor.

---

## Basic Example

```cpp
#include <SBK_Button.h>

Button button(2);

void setup()
{
    Serial.begin(9600);
    button.begin();
}

void loop()
{
    button.update();

    if (button.justPressed())
    {
        Serial.println("Button pressed");
    }

    if (button.justReleased())
    {
        Serial.println("Button released");
    }
}
```

Call `Button::update()` once during every iteration of `loop()`. Event functions such as `justPressed()` are valid only until the next call to `update()`.

For workflows that synchronize several components to one timestamp, read `millis()` once and pass it to the overload:

```cpp
void loop()
{
    uint32_t now = millis();
    button.update(now);
    // Update other components using the same value of now.
}
```

---

## Long-Press Example

```cpp
#include <SBK_Button.h>

Button button(2);

void setup()
{
    Serial.begin(9600);

    button.setLongPressDelay(1500);
    button.begin();
}

void loop()
{
    button.update();

    if (button.justLongPressed())
    {
        Serial.println("Long press reached");
    }

    if (button.isLongPressed())
    {
        // True while the button remains held after the threshold.
    }
}
```

`justLongPressed()` becomes true for one update cycle when the configured threshold is reached. `isLongPressed()` remains true while the button stays pressed after reaching that threshold.

---

## Constructor

```cpp
Button(uint8_t pin,
       ButtonWiring mode = ButtonWiring::INTERNAL_PULLUP,
       ButtonLogic logic = ButtonLogic::NORMAL);
```

| Parameter | Description |
|---|---|
| `pin` | Arduino GPIO connected to the button. |
| `mode` | Wiring configuration: `ButtonWiring::INTERNAL_PULLUP`, `ButtonWiring::EXTERNAL_PULLUP`, or `ButtonWiring::EXTERNAL_PULLDOWN`. |
| `logic` | Logical interpretation: `ButtonLogic::NORMAL` (default) or `ButtonLogic::INVERTED`. |

---

## ButtonWiring

### `enum class ButtonWiring`

Selects how the button is wired to the microcontroller.

| Value | Description |
|---|---|
| `ButtonWiring::INTERNAL_PULLUP` | Uses the MCU's internal pull-up resistor. Connect the button between the GPIO pin and **GND**. |
| `ButtonWiring::EXTERNAL_PULLUP` | Uses an external pull-up resistor. Connect the button between the GPIO pin and **GND**. |
| `ButtonWiring::EXTERNAL_PULLDOWN` | Uses an external pull-down resistor. Connect the button between the GPIO pin and **VCC**. |

**Note:** `ButtonWiring::INTERNAL_PULLUP` is the default configuration and is recommended whenever possible because it requires no external resistor.

---

## ButtonLogic

### `enum class ButtonLogic`

Controls how the configured wiring state is interpreted by the API.

| Value | Description |
|---|---|
| `ButtonLogic::NORMAL` | Uses the normal pressed state for the selected wiring mode. This is the default. |
| `ButtonLogic::INVERTED` | Swaps the logical pressed and released states, including edge events and timing. |

```cpp
Button normalButton(2, ButtonWiring::INTERNAL_PULLUP, ButtonLogic::NORMAL);
Button invertedButton(3, ButtonWiring::INTERNAL_PULLUP, ButtonLogic::INVERTED);
```

Logic inversion does not change the pin mode or its pull-up configuration; it only changes how the input state is reported.

This is especially useful for physical ON/OFF switches. If the installed switch position is opposite to the desired logical state, use `ButtonLogic::INVERTED` to swap ON and OFF in software without rotating the switch or changing the device wiring.

---

## API Reference

### Initialization and updating

#### `void begin()`

Configures the `Button` object's GPIO and initializes its internal state without generating a false startup event.

#### `void update()`

Reads and debounces the button's GPIO using the current value of `millis()`, updates timing values, and generates one-cycle events.

#### `void update(uint32_t now)`

Performs the same update using the supplied millisecond timestamp. This overload is useful when multiple buttons or other components must use one synchronized time value during a loop iteration.

### Configuration

#### `void setDebounceDelay(unsigned long delay)`

Sets the debounce delay in milliseconds. The default is `50 ms`.

#### `void setLongPressDelay(uint32_t delay)`

Sets the long-press threshold in milliseconds. The default is `1000 ms`.

#### `uint32_t longPressDelay() const`

Returns the configured long-press threshold in milliseconds.

### Current state

#### `bool isPressed() const`

Returns `true` while the debounced button state is pressed.

#### `bool isReleased() const`

Returns `true` while the debounced button state is released.

#### `bool isLongPressed() const`

Returns `true` while the button is pressed and its pressed time has reached the configured long-press threshold.

### Latching state

#### `bool latchedState() const`

Returns the button's push-on / push-off state. It starts as `false` and toggles once on every debounced release, so it can be read repeatedly without toggling again.

```cpp
button.update();
digitalWrite(LED_BUILTIN, button.latchedState());
```

#### `void setLatchedState(bool state)`

Sets the latching state without generating an event. Use it to choose an initial state, reset the latch, or override it from another part of the application.

### One-cycle events

#### `bool justPressed() const`

Returns `true` for one update cycle when the button changes from released to pressed.

#### `bool justReleased() const`

Returns `true` for one update cycle when the button changes from pressed to released.

#### `bool justLongPressed() const`

Returns `true` for one update cycle when the current press reaches the configured long-press threshold. It is generated only once per press.

### Timing

#### `uint32_t pressedTime() const`

While pressed, returns the duration of the current press in milliseconds. While released, returns the duration of the most recent press.

#### `uint32_t releasedTime() const`

While released, returns the duration of the current released period in milliseconds. While pressed, returns the duration of the preceding released period.

### Clearing events

Event flags are automatically reset at the start of each `update()` call, so they do not need to be cleared during normal use. The clearing functions are provided for specific control-flow needs. For example, they can mark an event as handled before another part of the same loop processes it, discard pending events when changing application modes or screens, or intentionally ignore an event that should not trigger further actions.

#### `void clearJustPressed()`

Clears the current `justPressed()` event.

#### `void clearJustReleased()`

Clears the current `justReleased()` event.

#### `void clearJustLongPressed()`

Clears the current `justLongPressed()` event.

#### `void clearEvents()`

Clears all three one-cycle event flags.

---

## Important Usage Notes

- Call `begin()` once before calling `update()`.
- Call `update()` frequently and avoid long blocking delays.
- Read one-cycle events after `update()` and before the next update.
- Configure the long-press threshold with `setLongPressDelay()`.
- `ButtonWiring::INTERNAL_PULLUP` is the recommended wiring configuration whenever possible.

---

## License

This project is released under the MIT License.

Copyright (c) 2026 Samuel Barabe (Smart Builds & Kits).
