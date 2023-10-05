#ifndef MoistureSensor_h
#define MoistureSensor_h

#include "Arduino.h"
#include "/Users/luukmeier/Documents/Arduino/plant-saver/lib/SensorService/SensorService.h"

class MoistureSensor : public Sensor
{
    uint8_t pin;
    int id;
    ReaderFunction readFunc = NULL;

    float moisture_percentage = 0;

public:
    static constexpr float output_lowest = 1023.00;
    static constexpr float output_highest = 0;

    MoistureSensor(int sensor_id, uint8_t analog_pin, ReaderFunction readFunction)
        : pin(analog_pin), id(sensor_id)
    {
        readFunc = readFunction;
    }
    virtual void read()
    {
        int sensor_reading = readFunc(pin);
        moisture_percentage = (100 - ((sensor_reading / output_lowest) * 100));
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

#endif
