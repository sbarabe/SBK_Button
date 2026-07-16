//=====================================================================
// BasicButton
//
// Demonstrates the basic use of the SBK_Button library.
//
// Connect a normally-open push button between BUTTON_PIN and GND.
// The library uses the Arduino's internal pull-up resistor, so no
// external resistor is required.
//
// Press and release the button to print messages to the Serial Monitor.
//
// Rapidly tap the button. Despite the mechanical bouncing of the
// switch contacts, each physical press and release generates only
// one event.
//
// Demonstrates:
//   - Button initialization
//   - Press detection
//   - Release detection
//   - Software debouncing
//=====================================================================

#include <Arduino.h>
#include <SBK_Button.h>

constexpr uint8_t BUTTON_PIN = 2;

Button button(BUTTON_PIN);

void setup()
{
    Serial.begin(115200);

    button.begin();

    // Optional: Override the default debounce delay (50 ms).
    // Try shorter or longer values to observe how the button
    // responsiveness changes.
    //
    // button.setDebounceDelay(20);

    Serial.println(F("Press the button..."));
}

void loop()
{
    button.update();

    if (button.justPressed())
    {
        Serial.println(F("Pressed"));
    }

    if (button.justReleased())
    {
        Serial.println(F("Released"));
    }
}