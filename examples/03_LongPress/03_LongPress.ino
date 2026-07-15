//=====================================================================
// LongPress
//
// Demonstrates long press detection using the SBK_Button library.
//
// Connect a normally-open push button between BUTTON_PIN and GND.
// The library uses the Arduino's internal pull-up resistor, so no
// external resistor is required.
//=====================================================================

#include <Arduino.h>
#include <Button.h>

constexpr uint8_t BUTTON_PIN = 2;

Button button(BUTTON_PIN);

void setup()
{
    Serial.begin(115200);

    button.begin();
}

void loop()
{
    button.update();

    if (button.justPressed())
        Serial.println("Pressed");

    if (button.justLongPressed())
        Serial.println("Long press");

    if (button.justReleased())
        Serial.println("Released");
}