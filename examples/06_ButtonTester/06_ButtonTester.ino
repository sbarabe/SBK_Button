//=====================================================================
// ButtonTester
//
// Diagnostic example for testing buttons with the SBK_Button library.
//
// Connect normally-open push buttons between the specified pins and GND.
// The library uses the Arduino's internal pull-up resistors, so no
// external resistors are required.
//
// The sketch prints the following events to the Serial Monitor:
//
//   - Button pressed
//   - Long press detected
//   - Button released
//
// This example can be used to verify button wiring, debouncing, and
// long-press detection before integrating the buttons into a project.
//
//=====================================================================

#include <Arduino.h>
#include <Button.h>

// Define the long-press delay in milliseconds.
constexpr uint16_t LONG_PRESS_DELAY = 1000;

// Button identifiers used to index the arrays.
enum ButtonIndex : uint8_t
{
BUTTON_PREVIOUS,
BUTTON_NEXT,
BUTTON_SELECT,
BUTTON_BACK,
BUTTON_COUNT
};

// Human-readable names for each button.
constexpr const char *const BUTTON_NAMES[] =
{
"PREVIOUS",
"NEXT",
"SELECT",
"BACK"
};

// Ensure that the number of button names matches BUTTON_COUNT.
static_assert(sizeof(BUTTON_NAMES) / sizeof(BUTTON_NAMES[0]) == BUTTON_COUNT,
"BUTTON_NAMES must contain one entry per button.");

// GPIO pins for each button.
constexpr uint8_t BUTTON_PINS[] =
{
2,
3,
4,
5
};

// Ensure that the number of button pins matches BUTTON_COUNT.
static_assert(sizeof(BUTTON_PINS) / sizeof(BUTTON_PINS[0]) == BUTTON_COUNT,
"BUTTON_PINS must contain one entry per button.");

// Create Button objects for each button.
Button buttons[] =
{
Button(BUTTON_PINS[BUTTON_PREVIOUS]),
Button(BUTTON_PINS[BUTTON_NEXT]),
Button(BUTTON_PINS[BUTTON_SELECT]),
Button(BUTTON_PINS[BUTTON_BACK])
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

    // Pad shorter button names for neat alignment.
    for (size_t i = strlen(BUTTON_NAMES[buttonIndex]); i < 8; i++)
    {
        Serial.print(' ');
    }

    Serial.print(F(" : "));
    Serial.println(event);
}

void setup()
{
Serial.begin(115200);


for (auto &button : buttons)
{
    button.begin();
    button.setLongPressDelay(LONG_PRESS_DELAY);
}
Serial.print(F("Long press delay: "));
Serial.print(LONG_PRESS_DELAY);
Serial.println(F(" ms"));
Serial.println();

Serial.println(F("SBK_Button button tester"));
Serial.println(F("Press, hold, and release any button."));
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

    if (buttons[i].justLongPressed())
    {
        printButtonEvent(buttonIndex, F("LONG PRESS"));
    }

    if (buttons[i].justReleased())
    {
        printButtonEvent(buttonIndex, F("RELEASED"));
    }
}

}
