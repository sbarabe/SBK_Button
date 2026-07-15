#pragma once

#include <Arduino.h>

//=====================================================================
// Button Library
//=====================================================================
//
// SPDX-License-Identifier: MIT
//
// Lightweight push-button library for Arduino-compatible AVR boards.
//
// Features:
//   - Debouncing
//   - Press / release detection
//   - Long-press detection
//   - Active-high or active-low inputs
//
// Copyright (c) 2026 Samuel Barabe
// Licensed under the MIT License.
//=====================================================================

class Button
{
public:
    // Creates a button object.
    // pin        : Arduino GPIO connected to the push button.
    // activeHigh : true  = button is pressed when pin is HIGH.
    //              false = button is pressed when pin is LOW.
    // useExternalPullup : true  = button uses an external pull-up resistor.
    //                     false = button uses internal pull-up resistor if activeLow.
    Button(uint8_t pin, bool activeHigh = false, bool useExternalPullup = false);

    // Initializes the GPIO pin.
    // Active LOW buttons automatically enable the internal pull-up resistor.
    void begin();

    // Sets the debounce delay in milliseconds.
    // Default value is 50 ms.
    void setDebounceDelay(unsigned long delay) { _debounceDelay = delay; } // Set debounce delay in milliseconds

    // Updates the button state.
    // This function should be called every iteration of loop().
    void update();

    // Returns true while the button is being held down.
    bool isPressed() const { return _currentState == _activeState(); };

    // Returns true while the button is released.
    bool isReleased() const { return !isPressed(); }

    // Returns true only once when the button changes
    // from released to pressed.
    bool justPressed() const { return _justPressed; }

    // Returns true only once when the button changes
    // from pressed to released.
    bool justReleased() const { return _justReleased; }

    // Sets the duration required to recognize a long press.
    // Default value is 1000 ms.
    void setLongPressDuration(uint32_t duration) { _longPressDuration = duration; }

    // Returns the configured long-press duration, in milliseconds.
    uint32_t longPressDuration() const { return _longPressDuration; }

    // Returns true once when the button is pressed for at
    // least the set duration (milliseconds)
    bool isLongPressed() const;

    // Returns true for one update cycle when the button
    // reaches the configured long-press duration.
    bool justLongPressed() const { return _justLongPressed; }

    // Clears the justPressed state before the update call.
    // This is useful if you want to ignore a justPressed event after it has been handled
    void clearJustPressed() { _justPressed = false; }

    // Clears the justReleased state before the update call.
    // This is useful if you want to ignore a justReleased event after it has been handled
    void clearJustReleased() { _justReleased = false; }

    // Clears the justLongPressed state before the update call.
    // This is useful if you want to ignore a justLongPressed event after it has been handled
    void clearJustLongPressed() { _justLongPressed = false; }

    // Clears all button events before the update call.
    // This is useful if you want to ignore all events after they have been handled
    void clearEvents();

    // Returns how long the button has been continuously
    // pressed, in milliseconds.
    //
    // Returns the last press duration if the button is currently released.
    uint32_t pressedTime() const { return _pressedTime; }

    // Returns how long the button has been continuously
    // released, in milliseconds.
    //
    // Returns the last release duration if the button is currently pressed.
    uint32_t releasedTime() const { return _releasedTime; }

private:
    // Returns the electrical level corresponding to a pressed button.
    // Active LOW  -> LOW
    // Active HIGH -> HIGH
    bool _activeState() const;

    // Updates the pressed time counter.
    // Called when the button is pressed.
    void _pressedTimeUpdate(uint32_t now);

    // Updates the released time counter.
    // Called when the button is released.
    void _releasedTimeUpdate(uint32_t now);

    // Arduino GPIO pin number.
    uint8_t _pin;

    // Button polarity.
    // false = Active LOW
    // true  = Active HIGH
    bool _activeHigh;

    // True if an external pull-up resistor is used.
    // When false and the button is active LOW,
    // the internal pull-up resistor is enabled.
    bool _useExternalPullup;

    // Current debounced electrical state (HIGH or LOW).
    bool _currentState;

    // Previous debounced electrical state.
    bool _previousState;

    // Last raw pin reading used by the debounce algorithm.
    bool _lastReading;

    // True if the button was just pressed.
    bool _justPressed;

    // True if the button was just released.
    bool _justReleased;

    // True if a long press was just long pressed.
    bool _justLongPressed;

    // True if a long press event has been reported for the current press.
    bool _longPressReported;

    // Time (millis) when the raw reading last changed.
    uint32_t _lastChangeTime;

    // Debounce time in milliseconds.
    uint32_t _debounceDelay = 50;

    // Time (millis) when the current button press started.
    uint32_t _pressStartTime;

    // Time (millis) when the button was last pressed.
    uint32_t _pressedTime;

    // Time (millis) when the current button release started.
    uint32_t _releaseStartTime;

    // Time (millis) when the button was last released.
    uint32_t _releasedTime;

    // Duration (milliseconds) for long press detection
    uint32_t _longPressDuration;
};
