#ifndef SensorService_h
#define SensorService_h

#include "../../src/SensorReading/SensorReading.h"

/**
 * Sensor interface
 * Provides all required methods for injecting a class into `SensorService`
 */
class Sensor
{
public:
    typedef int (*ReaderFunction)(uint8_t);

    virtual void read() = 0;
    virtual float getCurrentReading() = 0;
    virtual int getId() = 0;
    virtual ~Sensor() = default;
};

// template <size_t SIZE>
// class SensorResults
// {
// public:
//     virtual void set() = 0;
//     virtual get() = 0;
//     virtual ~SensorResults() = default;
// };

template <size_t SIZE>
class SensorService
{
    Sensor *sensors[SIZE];

public:
    SensorService(Sensor *_sensors[SIZE])
    {
        for (size_t i = 0; i < SIZE; i++)
        {
            sensors[i] = _sensors[i];
        }
    }
    void readAll()
    {
        for (size_t i = 0; i < SIZE; i++)
        {
            sensors[i]->read();
        }
    }

    SensorReadingResults<SIZE> getCurrentReadings()
    {
        SensorReading readings[SIZE];
        for (size_t i = 0; i < SIZE; i++)
        {
            readings[i].id = sensors[i]->getId();
            readings[i].value = sensors[i]->getCurrentReading();
        }
        SensorReadingResults<SIZE> data;

        for (size_t i = 0; i < SIZE; i++)
        {
            data.readings[i] = readings[i];
        }

        return data;
    }
};

#endif
