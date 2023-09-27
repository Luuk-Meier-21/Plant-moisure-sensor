#ifndef SensorService_h
#define SensorService_h

#include "Arduino.h"

/**
 * Sensor interface
 * Provides all required methods for injecting a class into `SensorService`
 */
class Sensor
{
    int id = 0;

public:
    virtual void read() = 0;
    virtual float getCurrentReading() = 0;
    virtual int getId() = 0;
    virtual ~Sensor() = default;
};

/**
 * A struct holding a id, and matching value of a sensor reading.
 */
struct SensorReading
{
    int id;
    float value;
};

/**
 * A wrapper struct holding multiple sensor readings.
 */
template <size_t SIZE>
struct SensorReadingResults
{
    SensorReading readings[SIZE];
};

template <size_t SIZE>
class SensorService
{
    Sensor *sensors[SIZE];

public:
    SensorService(Sensor *_sensors[SIZE])
    {
        for (int i = 0; i < SIZE; i++)
        {
            sensors[i] = _sensors[i];
        }
    }
    readAll()
    {
        for (int i = 0; i < SIZE; i++)
        {
            sensors[i]->read();

            // if (sensors[i]->getCurrentReading() > 0)
            // {
            //     Serial.print("Reading id:");
            //     Serial.print(sensors[i]->getId());
            //     Serial.print("value:");
            //     Serial.print(sensors[i]->getCurrentReading());
            //     Serial.print("%\n\n");
            // }
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

        for (int i = 0; i < SIZE; i++)
        {
            data.readings[i] = readings[i];
        }

        return data;
    }
};

#endif;