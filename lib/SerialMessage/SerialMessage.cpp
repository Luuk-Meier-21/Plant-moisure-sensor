#include "Arduino.h"
#include "HFButton.h"

template <typename PT, typename OT>
HFButton<PT, OT>::HFButton(int pin)
{
    pinMode(pin, INPUT_PULLUP);
    _pin = pin;
}

// Void functions:
template <typename PT, typename OT>
void HFButton<PT, OT>::attachPress(callbackFunction newFunction)
{
    _pressFunc = newFunction;
}

template <typename PT, typename OT>
void HFButton<PT, OT>::attachRelease(callbackFunction newFunction)
{
    _releaseFunc = newFunction;
}

// Param functions:
template <typename PT, typename OT>
void HFButton<PT, OT>::attachPress(Callable newFunction, char param)
{
    _paramPressFunc = newFunction;
    _param = param;
}

template <typename PT, typename OT>
void HFButton<PT, OT>::attachRelease(Callable newFunction, char param)
{
    _paramReleaseFunc = newFunction;
    _param = param;
}

template <typename PT, typename OT>
void HFButton<PT, OT>::attachClick(callbackFunction pressFunction, callbackFunction releaseFunction)
{
    _pressFunc = releaseFunction;
    _releaseFunc = releaseFunction;
}

template <typename PT, typename OT>
void HFButton<PT, OT>::attachClick(Callable pressFunction, Callable releaseFunction, PT param)
{
    _paramPressFunc = pressFunction;
    _paramReleaseFunc = releaseFunction;
    _param = param;
}

template <typename PT, typename OT>
void HFButton<PT, OT>::attachClick(Callable pressFunction, Callable releaseFunction, PT param, OT options)
{
    _paramPressFunc = pressFunction;
    _paramReleaseFunc = releaseFunction;
    _param = param;
    _options = options;
}

template <typename PT, typename OT>
void HFButton<PT, OT>::tick()
{
    // get current reading.
    int reading = digitalRead(_pin);

    // check if reading is the same as _prevState (reading from last tick call).
    if (reading != _prevState)
    {
        // set to current time.
        _lastDebounceTime = millis();
    }

    // check if current time - last debounce time is higher then debounce delay.
    if ((millis() - _lastDebounceTime) > _debounceDelay)
    {
        // check if reading is different than the reading made x seconds back.
        // if true set the _state.
        if (reading != _state)
            _state = reading;
    }

    // handle debounce safe state:
    if (_state == LOW && !_wasPressed)
    {
        // on first press:
        if (_pressFunc)
            _pressFunc();
        if (_paramPressFunc)
            _paramPressFunc(_param, _options);
        _wasPressed = true;
    }
    else if (_state == HIGH && _wasPressed)
    {
        // on release:
        if (_releaseFunc)
            _releaseFunc();
        if (_paramReleaseFunc)
            _paramReleaseFunc(_param, _options);
        _wasPressed = false;
    }

    // set prev state:
    _prevState = reading;
}

// Reference fix:
template class HFButton<char, ListenerOptions>;