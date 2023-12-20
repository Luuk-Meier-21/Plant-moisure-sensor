#ifndef MoistureSensor_test_h
#define MoistureSensor_test_h

#include "../../src/SensorClient/SensorClient.h"
#include "../../src/MoistureSensor/MoistureSensor.h"

#include "stddef.h"
using namespace std;

unsigned const int id = 21;
unsigned const int pin = 4;

int mockReadHigh(uint8_t pin)
{
  (void)pin;

  return HIGH;
};

int mockReadLow(uint8_t pin)
{
  (void)pin;

  return LOW;
};

test(MoistureSensor_getCurrentReading_max)
{
  MoistureSensor sensor(id, pin, mockReadHigh);
  sensor.read();

  float percent = sensor.getCurrentReading();
  float target_percent = HIGH;

  assertEqual(percent, target_percent);
}

test(MoistureSensor_getCurrentReading_min)
{
  MoistureSensor sensor(id, pin, mockReadLow);
  sensor.read();

  float percent = sensor.getCurrentReading();
  float target_percent = LOW;

  assertEqual(percent, target_percent);
}

test(MoistureSensor_getId)
{
  MoistureSensor sensor(id, pin, mockReadLow);

  int sensor_id = sensor.getId();

  assertEqual(sensor_id, (int)id);
}

#endif