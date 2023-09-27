#ifndef MoistureSensor_h
#define MoistureSensor_h

#include "Arduino.h"
#include "/Users/luukmeier/Documents/Arduino/plant-saver/lib/SensorService/SensorService.h"

class MoistureSensor : public Sensor
{
    uint8_t pin;
    int id;

    const float output_upper = 1023.00;
    const float output_lower = 0;

    float moisture_percentage = 0;

public:
    MoistureSensor(int sensor_id, uint8_t analog_pin) : pin(analog_pin)
    {
        id = sensor_id;
        pin = analog_pin;
    };
    virtual void read()
    {
        int sensor_analog = analogRead(pin);
        moisture_percentage = (100 - ((sensor_analog / output_upper) * 100));
    };
    virtual float getCurrentReading()
    {
        return moisture_percentage;
    };
    virtual int getId()
    {
        return id;
    }
    virtual ~MoistureSensor() = default;
};

#endif;