#include "/Users/luukmeier/Documents/Arduino/libraries/EpoxyDuino/EpoxyDuino.h"
#include "/Users/luukmeier/Documents/Arduino/libraries/AUnit/src/AUnitVerbose.h"

#include "../../src/SensorService/SensorService.h"
#include "../../src/MoistureSensor/MoistureSensor.h"
#include "../../src/SensorReading/SensorReading.h"

#include "stddef.h"
using namespace std;

#define sensor_count 3

int mockRead(uint8_t pin)
{
  (void)pin;

  return MoistureSensor::output_highest;
}

// TODO: add more abstractions of Sensor class here:
SensorService<sensor_count> construct_service()
{
  MoistureSensor *sensor_a = new MoistureSensor(1, 1, mockRead);
  MoistureSensor *sensor_b = new MoistureSensor(2, 2, mockRead);
  MoistureSensor *sensor_c = new MoistureSensor(3, 3, mockRead);

  Sensor *sensors[sensor_count] = {sensor_a, sensor_b, sensor_c};
  SensorService<sensor_count> sensor_service(sensors);
  return sensor_service;
}

test(SensorService_readAllToResult)
{
  SensorService<sensor_count> sensor_service = construct_service();
  SensorResultsClient<sensor_count> results;

  sensor_service.readAllToResults(&results);

  float value = reading.value;
  float target_value = 100;
}