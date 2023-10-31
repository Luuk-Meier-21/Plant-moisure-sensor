#ifndef SensorService_h
#define SensorService_h

/**
 * Interface for different Sensor services.
 */
class Sensor
{
public:
    typedef int (*ReaderFunction)(uint8_t);

    virtual void read() = 0;
    virtual float getCurrentReading() = 0;
    virtual int getId() = 0;
    virtual String getFieldName() = 0;
    virtual ~Sensor() = default;
};

/**
 * Client for manipulating passed Sensor services.
 */
template <size_t SIZE>
class SensorClient
{
    Sensor *sensors[SIZE];

public:
    SensorClient(Sensor *_sensors[SIZE])
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

    void forEach(void (*func)(Sensor *))
    {
        for (size_t i = 0; i < SIZE; i++)
        {
            func(sensors[i]);
        };
    };

    size_t count()
    {
        return SIZE;
    }

    Sensor *getSensorOfIndex(size_t index)
    {
        if (index > SIZE)
        {
            return NULL;
        }
        return sensors[index];
    }

    // template <class DataType>
    // void toArray(DataType *array[SIZE], DataType (*factory)(Sensor *))
    // {
    //     for (size_t i = 0; i < SIZE; i++)
    //     {
    //         sensors[i]->read();
    //         DataType data = factory(sensors[i]);
    //         // TIL: for some reason `array = &data` works but `*array = data` does not.
    //         // Expected: because data goes out of scope at function end, a pointer to it
    //         // would also fall out of scope at :78
    //         // Instead: it only works when the adress to data is pass to the array, why?
    //         array[i] = &data;
    //     }
    // }

    // void readAllToSensorReadingArray(SensorReading *array[SIZE])
    // {
    //     for (size_t i = 0; i < SIZE; i++)
    //     {
    //         sensors[i]->read();
    //         SensorReading reading(sensors[i]);
    //         *array[i] = reading;
    //     }
    // }

    // void readAllToSensorReadingArray(SensorReading *array[SIZE])
    // {
    //     for (size_t i = 0; i < SIZE; i++)
    //     {
    //         sensors[i]->read();
    //         SensorReading reading(sensors[i]);
    //         array[i] = &reading;
    //     }
    // }

    // void readAllToResults(SensorResults<SIZE> *results)
    // {
    //     for (size_t i = 0; i < SIZE; i++)
    //     {
    //         sensors[i]->read();
    //     }
    //     results->resultsFromSensors(sensors);
    // }
};

#endif
