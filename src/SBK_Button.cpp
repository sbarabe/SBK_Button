//=====================================================================
// SBK_Button Library - Implementation
//=====================================================================
//
// SPDX-License-Identifier: MIT
//
// Implementation of the Button class.
//
// Copyright (c) 2026 Samuel Barabe
// Licensed under the MIT License.
//=====================================================================

#include "SBK_Button.h"

Button::Button(uint8_t pin, ButtonWiring mode)
    : _pin(pin),
      _mode(mode),
      _currentState(false),
      _previousState(false),
      _lastReading(false),
      _justPressed(false),
      _justReleased(false),
      _justLongPressed(false),
      _longPressReported(false),
      _lastChangeTime(0),
      _debounceDelay(50),
      _pressStartTime(0),
      _pressedTime(0),
      _releaseStartTime(0),
      _releasedTime(0),
      _longPressDelay(1000) // Default long press delay set to 1000 ms
{
}

void Button::begin()
{
    // Configure the GPIO according to the selected wiring mode.
    switch (_mode)
    {
    case ButtonWiring::INTERNAL_PULLUP:
        pinMode(_pin, INPUT_PULLUP);
        break;

    case ButtonWiring::EXTERNAL_PULLUP:
    case ButtonWiring::EXTERNAL_PULLDOWN:
        pinMode(_pin, INPUT);
        break;

    default:
        pinMode(_pin, INPUT_PULLUP);
        break;
    }

    // Read the initial pin state.
    // All state variables are initialized to the same value so that
    // no false button events are generated on startup.
    _currentState = digitalRead(_pin);
    _previousState = _currentState;
    _lastReading = _currentState;
    _lastChangeTime = millis();
}

void Button::update()
{
    uint32_t now = millis();

    // Reset events at the start of each update cycle. This ensures that events are only reported once per update.
    _justPressed = false;
    _justReleased = false;
    _justLongPressed = false;

    // Read the current electrical level.
    bool reading = digitalRead(_pin);

    // If the raw input changed, restart the debounce timer.
    if (reading != _lastReading)
    {
        _lastChangeTime = now;
        _lastReading = reading;
    }

    // Accept the new state only if it remained stable long enough.
    if ((now - _lastChangeTime) >= _debounceDelay)
    {
        if (reading != _currentState)
        {
            // Save the previous stable state so edge detection
            // (justPressed/justReleased) works correctly.
            _previousState = _currentState;
            _currentState = reading;

            // Update the justPressed and justReleased flags based on the new state.
            _justPressed = isPressed();
            _justReleased = isReleased();
        }
        else
        {
            // Once the edge has been reported, keep previous and current
            // synchronized so the event is generated only once.
            _previousState = _currentState;
        }
    }

    // Update the pressed time based on the current state.
    _pressedTimeUpdate(now);

    // Update the released time based on the current state.
    _releasedTimeUpdate(now);

    // Handle long press detection after time has been updated to ensure accurate timing.

    // Rearm long-press detection when a new press begins.
    if (justReleased())
    {
        _longPressReported = false;
    }

    // Generate one long-press event when the configured delay is reached.
    if (isPressed() && !_longPressReported && pressedTime() >= _longPressDelay)
    {
        _justLongPressed = true;
        _longPressReported = true; // Prevent multiple long press events for the same press.
    }
}

// Returns the electrical level corresponding to a pressed button.
// This allows the same code to support both:
//   - Active LOW buttons  (pressed = LOW)
//   - Active HIGH buttons (pressed = HIGH)
bool Button::_activeState() const
{
    return _mode == ButtonWiring::EXTERNAL_PULLDOWN ? HIGH : LOW;
}

void Button::_pressedTimeUpdate(uint32_t now)
{
    // If the button was just pressed, record the start time and reset the
    // pressed time.
    if (justPressed())
    {
        _pressStartTime = now;
        _pressedTime = 0;
    }
    // If the button is currently pressed or just released, calculate the
    // pressed time as the difference between the current time and the press
    // start time.
    // If just released, freeze the pressed time to the duration of the last
    // press.
    else if (justReleased() || isPressed())
    {
        _pressedTime = now - _pressStartTime;
    }
}

void Button::_releasedTimeUpdate(uint32_t now)
{
    // If the button was just released, record the start time and reset the
    // released time.
    if (justReleased())
    {
        _releaseStartTime = now;
        _releasedTime = 0;
    }
    // If the button is currently released or just pressed, calculate the
    // released time as the difference between the current time and the release
    // start time.
    // If just pressed, freeze the released time to the duration of the last
    // release.
    else if (justPressed() || isReleased())
    {
        _releasedTime = now - _releaseStartTime;
    }
}

// Clears all button events before the update call.
// This is useful if you want to ignore all events after they have been handled
void Button::clearEvents()
{
    _justPressed = false;
    _justReleased = false;
    _justLongPressed = false;
}

// Returns true while the button has been pressed
// for at least the specified delay (milliseconds).
bool Button::isLongPressed() const
{
    return isPressed() && (pressedTime() >= _longPressDelay);
}
