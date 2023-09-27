#ifndef HFButton_h
#define HFButton_h

#include "Arduino.h"

extern "C"
{
    typedef void (*callbackFunction)(void);
    typedef void (*parameterizedCallbackFunction)(void *);
}

template <typename PT, typename OT>
class HFButton
{
public:
    typedef void (*Callable)(PT, OT);

    HFButton(int pin);
    void tick();

    void attachPress(callbackFunction newFunction);
    void attachPress(Callable newFunction, char param);
    void attachRelease(callbackFunction newFunction);
    void attachRelease(Callable newFunction, char param);
    void attachClick(callbackFunction pressFunction, callbackFunction releaseFunction);
    void attachClick(Callable pressFunction, Callable releaseFunction, PT param);
    void attachClick(Callable pressFunction, Callable releaseFunction, PT param, OT options);
    // void attachPress(parameterizedCallbackFunction newFunction, void *parameter);
private:
    int _pin;
    int _state = HIGH;
    int _prevState = HIGH;
    bool _wasPressed = false;
    unsigned long _lastDebounceTime = 0;
    unsigned long _debounceDelay = 50;

    callbackFunction _pressFunc = NULL;
    callbackFunction _releaseFunc = NULL;

    Callable _paramPressFunc = NULL;
    Callable _paramReleaseFunc = NULL;
    PT _param;
    OT _options = OT();
};
#endif;