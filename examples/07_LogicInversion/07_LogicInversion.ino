// Demonstrates normal and inverted logical button states.

#include <SBK_Button.h>

constexpr uint8_t NORMAL_BUTTON_PIN = 2;
constexpr uint8_t INVERTED_BUTTON_PIN = 3;

Button normalButton(
    NORMAL_BUTTON_PIN,
    ButtonWiring::INTERNAL_PULLUP,
    ButtonLogic::NORMAL);

Button invertedButton(
    INVERTED_BUTTON_PIN,
    ButtonWiring::INTERNAL_PULLUP,
    ButtonLogic::INVERTED);

void setup()
{
    Serial.begin(9600);
    normalButton.begin();
    invertedButton.begin();
}

void loop()
{
    normalButton.update();
    invertedButton.update();

    if (normalButton.justPressed())
    {
        Serial.println(F("Normal input became logically pressed"));
    }

    if (invertedButton.justPressed())
    {
        Serial.println(F("Inverted input became logically pressed"));
    }
}
