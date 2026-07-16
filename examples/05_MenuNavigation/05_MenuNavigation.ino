//=====================================================================
// MenuNavigation
//
// Demonstrates using multiple buttons to navigate a simple menu with
// the SBK_Button library.
//
// Connect normally-open push buttons between the specified pins and GND.
// The library uses the Arduino's internal pull-up resistors, so no
// external resistors are required.
//
// Button controls:
//
//   PREVIOUS - Select the previous menu item
//   NEXT     - Select the next menu item
//   SELECT   - Open the selected menu item
//   BACK     - Return to the main menu
//
// Menu activity is printed to the Serial Monitor.
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

// Menu item identifiers.
enum MenuItem : uint8_t
{
MENU_START,
MENU_SETTINGS,
MENU_INFORMATION,
MENU_ITEM_COUNT
};

// Human-readable names for each menu item.
constexpr const char *const MENU_ITEM_NAMES[] =
{
"Start",
"Settings",
"Information"
};

// Ensure that the number of menu names matches MENU_ITEM_COUNT.
static_assert(sizeof(MENU_ITEM_NAMES) / sizeof(MENU_ITEM_NAMES[0]) ==
MENU_ITEM_COUNT,
"MENU_ITEM_NAMES must contain one entry per menu item.");

// Currently selected menu item.
MenuItem selectedMenuItem = MENU_START;

// True while a menu item is open.
bool menuItemOpen = false;

// Print the currently selected menu item.
void showSelectedMenuItem()
{
Serial.print(F("Selected: "));
Serial.println(MENU_ITEM_NAMES[selectedMenuItem]);
}

// Return to the main menu.
void showMainMenu()
{
menuItemOpen = false;

Serial.println();
Serial.println(F("Main menu"));
showSelectedMenuItem();

}

// Open the currently selected menu item.
void openSelectedMenuItem()
{
menuItemOpen = true;

Serial.println();
Serial.print(F("Opened: "));
Serial.println(MENU_ITEM_NAMES[selectedMenuItem]);
Serial.println(F("Press BACK to return to the main menu."));

}

// Select the previous menu item, wrapping to the last item when needed.
void selectPreviousMenuItem()
{
if (selectedMenuItem == MENU_START)
{
selectedMenuItem = static_cast<MenuItem>(MENU_ITEM_COUNT - 1);
}
else
{
selectedMenuItem =
static_cast<MenuItem>(selectedMenuItem - 1);
}

showSelectedMenuItem();

}

// Select the next menu item, wrapping to the first item when needed.
void selectNextMenuItem()
{
selectedMenuItem =
static_cast<MenuItem>((selectedMenuItem + 1) % MENU_ITEM_COUNT);

showSelectedMenuItem();

}

void setup()
{
Serial.begin(115200);

for (auto &button : buttons)
{
    button.begin();
}

Serial.println(F("SBK_Button menu navigation example"));
showMainMenu();

}

void loop()
{
// Every button must be updated once during each loop iteration.
for (auto &button : buttons)
{
button.update();
}

// While a menu item is open, only the Back button is handled.
if (menuItemOpen)
{
    if (buttons[BUTTON_BACK].justPressed())
    {
        showMainMenu();
    }

    return;
}

if (buttons[BUTTON_PREVIOUS].justPressed())
{
    selectPreviousMenuItem();
}

if (buttons[BUTTON_NEXT].justPressed())
{
    selectNextMenuItem();
}

if (buttons[BUTTON_SELECT].justPressed())
{
    openSelectedMenuItem();
}

}
