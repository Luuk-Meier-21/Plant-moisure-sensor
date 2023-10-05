#include "/Users/luukmeier/Documents/Arduino/libraries/EpoxyDuino/EpoxyDuino.h"
#include "/Users/luukmeier/Documents/Arduino/libraries/AUnit/src/AUnitVerbose.h"

#include "/Users/luukmeier/Documents/Arduino/plant-saver/lib/SensorService/SensorService.h"
#include "/Users/luukmeier/Documents/Arduino/plant-saver/lib/MoistureSensor/MoistureSensor.h"

#include "stddef.h"
using namespace std;

const int sensor_count = 3;

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

test(SensorService_getCurrentReading)
{
  SensorService<sensor_count> sensor_service = construct_service();

  sensor_service.readAll();

  SensorReadingResults<sensor_count> result = sensor_service.getCurrentReadings();

  for (int i = 0; i < sensor_count; i++)
  {
    float value = result.readings[i].value;
    float target_value = 100;
    assertEqual(value, target_value);
  }
}