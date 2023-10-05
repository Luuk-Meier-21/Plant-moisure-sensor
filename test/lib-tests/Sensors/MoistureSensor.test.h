#include "/Users/luukmeier/Documents/Arduino/libraries/EpoxyDuino/EpoxyDuino.h"
#include "/Users/luukmeier/Documents/Arduino/libraries/AUnit/src/AUnitVerbose.h"

#include "/Users/luukmeier/Documents/Arduino/plant-saver/lib/SensorService/SensorService.h"
#include "/Users/luukmeier/Documents/Arduino/plant-saver/lib/Sensors/MoistureSensor.h"

#include "stddef.h"
using namespace std;

unsigned const int id = 21;
unsigned const int pin = 4;

int mockReadMax(uint8_t pin)
{
  (void)pin;

  return MoistureSensor::output_highest;
}

int mockReadMin(uint8_t pin)
{
  (void)pin;

  return MoistureSensor::output_lowest;
}

test(MoistureSensor_getCurrentReading_max)
{
  MoistureSensor sensor(id, pin, mockReadMax);
  sensor.read();

  float percent = sensor.getCurrentReading();
  float target_percent = 100;

  assertEqual(percent, target_percent);
}

test(MoistureSensor_getCurrentReading_min)
{
  MoistureSensor sensor(id, pin, mockReadMin);
  sensor.read();

  float percent = sensor.getCurrentReading();
  float target_percent = 0;

  assertEqual(percent, target_percent);
}

test(MoistureSensor_getId)
{
  MoistureSensor sensor(id, pin, mockReadMin);

  int sensor_id = sensor.getId();

  assertEqual(sensor_id, (int)id);
}