#ifndef SensorReading_h
#define SensorReading_h

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

  void forEach(void (*onReading)(SensorReading))
  {
    for (size_t i = 0; i < SIZE; i++)
    {
      if (readings[i].value > 0)
      {
        onReading(readings[i]);
      }
    }
  }
};

#endif