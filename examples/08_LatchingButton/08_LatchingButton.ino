//=====================================================================
// LatchingButton
//=====================================================================
// Turns a momentary push button into a push-on / push-off control.

#include <SBK_Button.h>

constexpr uint8_t BUTTON_PIN = 2;

Button button(BUTTON_PIN);

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    button.begin();
}

void loop()
{
    button.update();

    // One complete press and release toggles the output state.
    digitalWrite(LED_BUILTIN, button.latchedState());
}
