#ifndef SensorService_h
#define SensorService_h

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

struct SensorReading
{
    int id;
    float value;

    SensorReading(int id, float value) : id(id), value(value){};
    SensorReading(Sensor *sensor)
    {
        id = sensor->getId();
        value = sensor->getCurrentReading();
    }
    SensorReading(){};
    static SensorReading empty()
    {
        SensorReading empty_reading;
        return empty_reading;
    }
};

template <size_t SIZE>
class SensorResults
{
public:
    virtual void set(SensorReading *readings[SIZE]) = 0;
    virtual ~SensorResults() = default;
};

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

    // void readAllToArray(SensorReading *array[SIZE])
    // {
    //     SensorReading readings[SIZE];
    //     for (size_t i = 0; i < SIZE; i++)
    //     {
    //         sensors[i]->read();
    //         readings[i](sensors[i]);
    //     }
    //     *array = readings;
    // }

    void readAllToResults(SensorResults<SIZE> *results)
    {
        SensorReading *readings[SIZE];
        for (size_t i = 0; i < SIZE; i++)
        {
            sensors[i]->read();
            SensorReading a(sensors[i]);
            readings[i] = &a;
        }
        results->set(readings);
    }

    // template <size_t SIZE, class ResultType>
    // SensorResults<SIZE> getCurrentReadings()
    // {
    //     SensorReading readings[SIZE];
    //     for (size_t i = 0; i < SIZE; i++)
    //     {
    //         readings[i].id = sensors[i]->getId();
    //         readings[i].value = sensors[i]->getCurrentReading();
    //     }
    //     SensorResults<SIZE> data;

    //     for (size_t i = 0; i < SIZE; i++)
    //     {
    //         data.readings[i] = readings[i];
    //     }

    //     return data;
    // }
};

#endif
