//=====================================================================
// ExternalResistors
//
// Demonstrates using the SBK_Button library with internal and external
// pull-up resistors, and with an external pull-down resistor.
//
// Three buttons are used:
//
//   Pin 2 - Internal pull-up resistor
//   Pin 3 - External pull-up resistor
//   Pin 4 - External pull-down resistor
//
// Wiring:
//
//   Internal pull-up (Pin 2)
//
//      Pin 2
//        |
//     Push button
//        |
//       GND
//
//   External pull-up (Pin 3)
//
//       VCC
//        |
//      10 kΩ
//        |
//        +------ Pin 3
//        |
//     Push button
//        |
//       GND
//
//   External pull-down (Pin 4)
//
//      Pin 4
//        |
//        +------ 10 kΩ ----- GND
//        |
//     Push button
//        |
//       VCC
//
// Press any button to print its corresponding events to the
// Serial Monitor.
//
//=====================================================================

#include <Arduino.h>
#include <Button.h>

// Button identifiers used to index the arrays.
enum ButtonIndex : uint8_t
{
BUTTON_INTERNAL_PULLUP,
BUTTON_EXTERNAL_PULLUP,
BUTTON_EXTERNAL_PULLDOWN,
BUTTON_COUNT
};

// Human-readable names for each button.
constexpr const char *const BUTTON_NAMES[] =
{
"INTERNAL PULL-UP",
"EXTERNAL PULL-UP",
"EXTERNAL PULL-DOWN"
};

// Ensure that the number of button names matches BUTTON_COUNT.
static_assert(sizeof(BUTTON_NAMES) / sizeof(BUTTON_NAMES[0]) == BUTTON_COUNT,
"BUTTON_NAMES must contain one entry per button.");

// GPIO pins for each button.
constexpr uint8_t BUTTON_PINS[] =
{
2,
3,
4
};

// Ensure that the number of button pins matches BUTTON_COUNT.
static_assert(sizeof(BUTTON_PINS) / sizeof(BUTTON_PINS[0]) == BUTTON_COUNT,
"BUTTON_PINS must contain one entry per button.");

// Create Button objects for each wiring configuration.
//
// Internal pull-up:
//   The Arduino enables its internal pull-up resistor.
//   The button is active when the pin is connected to GND.
//
// External pull-up:
//   The pin uses INPUT mode because the resistor is external.
//   The button is active when the pin is connected to GND.
//
// External pull-down:
//   The pin uses INPUT mode because the resistor is external.
//   The button is active when the pin is connected to VCC.
Button buttons[] =
{
Button(BUTTON_PINS[BUTTON_INTERNAL_PULLUP], ButtonWiring::INTERNAL_PULLUP),
Button(BUTTON_PINS[BUTTON_EXTERNAL_PULLUP], ButtonWiring::EXTERNAL_PULLUP),
Button(BUTTON_PINS[BUTTON_EXTERNAL_PULLDOWN], ButtonWiring::EXTERNAL_PULLDOWN)
};

// Ensure that the number of button objects matches BUTTON_COUNT.
static_assert(sizeof(buttons) / sizeof(buttons[0]) == BUTTON_COUNT,
"buttons must contain one entry per button.");

// Print a button event to the Serial Monitor.
void printButtonEvent(ButtonIndex buttonIndex,
const __FlashStringHelper *event)
{
Serial.print(F("Button "));
Serial.print(BUTTON_NAMES[buttonIndex]);
Serial.print(F(": "));
Serial.println(event);
}

void setup()
{
Serial.begin(115200);

for (auto &button : buttons)
{
    button.begin();
}

Serial.println(F("SBK_Button wiring configuration example"));
Serial.println(F("Press any button."));
Serial.println();

}

void loop()
{
for (uint8_t i = 0; i < BUTTON_COUNT; i++)
{
buttons[i].update();

    ButtonIndex buttonIndex = static_cast<ButtonIndex>(i);

    if (buttons[i].justPressed())
    {
        printButtonEvent(buttonIndex, F("PRESSED"));
    }

    if (buttons[i].justReleased())
    {
        printButtonEvent(buttonIndex, F("RELEASED"));
    }
}

}
