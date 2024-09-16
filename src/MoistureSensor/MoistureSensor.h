#ifndef MoistureSensor_h
#define MoistureSensor_h

#include "../../src/SensorClient/SensorClient.h"

class MoistureSensor : public Sensor
{
    uint8_t pin;
    int id;
    ReaderFunction read_func;
    SetupFunction setup_func;

    int is_high = 0;

    static void defaultSetup(uint8_t pin)
    {
        (void)pin;
    }

public:
    MoistureSensor(int sensor_id, uint8_t input, ReaderFunction read)
        : pin(input),
          id(sensor_id),
          read_func(read),
          setup_func(defaultSetup){};

    MoistureSensor(int sensor_id, uint8_t input, ReaderFunction read, SetupFunction setup)
        : pin(input),
          id(sensor_id),
          read_func(read),
          setup_func(setup){};

    void read()
    {
        is_high = read_func(pin);
    }

    void setup()
    {
        setup_func(pin);
    }

    float getCurrentReading()
    {
        return is_high;
    }

    int getId()
    {
        return id;
    }

    ~MoistureSensor() = default;
};

#endif
