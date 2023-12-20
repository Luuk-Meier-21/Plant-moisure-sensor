#ifndef SensorClient_test_h
#define SensorClient_test_h

#include "../../src/SensorClient/SensorClient.h"
#include "../../src/MoistureSensor/MoistureSensor.h"

#define sensor_count 3

class SensorServiceTest
{
public:
  static int mockReadRandom(uint8_t pin)
  {
    (void)pin;

    return std::rand() > .5 ? HIGH : LOW;
  }
};

test(SensorService_readAll)
{
  MoistureSensor *sensor_a = new MoistureSensor(1, 1, SensorServiceTest::mockReadRandom);
  MoistureSensor *sensor_b = new MoistureSensor(2, 2, SensorServiceTest::mockReadRandom);
  MoistureSensor *sensor_c = new MoistureSensor(3, 3, SensorServiceTest::mockReadRandom);

  Sensor *sensors[] = {sensor_a, sensor_b, sensor_c};
  SensorClient<sensor_count> sensor_service(sensors);

  sensor_service.readAll();

  for (size_t i = 0; i < sensor_count; i++)
  {
    Sensor *sensor = sensor_service.getSensorOfIndex(i);

    int target_id = sensors[i]->getId();
    int id = sensor->getId();
    // printf("id%i: %i / %i\n", int(i), id, target_id);
    assertEqual(id, target_id);

    float target_value = sensors[i]->getCurrentReading();
    float value = sensor->getCurrentReading();
    // printf("value%i: %f / %f\n", int(i), value, target_value);
    assertEqual(value, target_value);
  }
}

#endif