#ifndef SensorReading_h
#define SensorReading_h

/**
 * A wrapper struct holding multiple sensor readings.
 */
template <size_t SIZE>
class SensorResultsClient : public SensorResults<SIZE>
{
  SensorReading *readings[SIZE];

public:
  void set(SensorReading *set_readings[SIZE])
  {
    *readings = *set_readings;
  }

  void forEach(void (*onReading)(SensorReading *))
  {
    for (size_t i = 0; i < SIZE; i++)
    {
      if (readings[i]->value > 0)
      {
        onReading(readings[i]);
      }
    }
  }
};

#endif