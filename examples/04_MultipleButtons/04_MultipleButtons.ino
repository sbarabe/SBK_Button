//=====================================================================
// MultipleButtons
//
// Demonstrates handling multiple buttons using the SBK_Button library.
//
// Connect normally-open push buttons between the specified pins and GND.
// The library uses the Arduino's internal pull-up resistors, so no
// external resistors are required.
//
// Press and release any button to print its corresponding event
// to the Serial Monitor.
//
//=====================================================================

#include <Arduino.h>
#include <SBK_Button.h>

// Button identifiers used to index the arrays.
enum ButtonIndex : uint8_t
{
    BUTTON_PREVIOUS,
    BUTTON_NEXT,
    BUTTON_SELECT,
    BUTTON_BACK,
    BUTTON_COUNT
};

// Button names and corresponding GPIO pins.
constexpr const char *const BUTTON_NAMES[] =
    {
        "PREVIOUS",
        "NEXT",
        "SELECT",
        "BACK"
    };

// Ensure that the number of button names matches the BUTTON_COUNT.
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

// Ensure that the number of button pins matches the BUTTON_COUNT.
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

// Ensure that the number of button objects matches the BUTTON_COUNT.
static_assert(sizeof(buttons) / sizeof(buttons[0]) == BUTTON_COUNT,
              "buttons must contain one entry per button.");

void setup()
{
    Serial.begin(115200);

    for (auto &button : buttons)
    {
        button.begin();
    }

    Serial.println(F("Press any button..."));
}

void loop()
{
    for (uint8_t i = 0; i < BUTTON_COUNT; i++)
    {
        buttons[i].update();

        if (buttons[i].justPressed())
        {
            Serial.print("Button ");
            Serial.print(BUTTON_NAMES[i]);
            Serial.println(" pressed");
        }

        if (buttons[i].justReleased())
        {
            Serial.print("Button ");
            Serial.print(BUTTON_NAMES[i]);
            Serial.println(" released");
        }
    }
}