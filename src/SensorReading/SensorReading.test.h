#include <AUnitVerbose.h>

#include "../../src/SensorReading/SensorReading.h"

#include "stddef.h"
using namespace std;

SensorReading mockSensorReading(int seed)
{
  SensorReading reading;
  reading.id = seed;
  reading.value = seed * 5;
  return reading;
}

test(SensorReadingResults_constructor)
{
  const size_t c = 3;
  SensorReading readings[c] = {mockSensorReading(1), mockSensorReading(2), mockSensorReading(3)};
  SensorReadingResults<c> results;
  results.readings = readings;
}
