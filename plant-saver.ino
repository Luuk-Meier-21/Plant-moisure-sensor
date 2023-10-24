#include <ESP8266WiFi.h>

#include "src/.env/env.h"
#include "src/StreamReader/StreamReader.h"
#include "src/MoistureSensor/MoistureSensor.h"
#include "src/SensorService/SensorService.h"

#define sensor_pin A0
const int sensor_count = 1;

StreamReader serial_reader(&Serial);

MoistureSensor *sensor_a = new MoistureSensor(1, sensor_pin, analogRead);

Sensor *sensors[sensor_count] = {sensor_a};
SensorService<sensor_count> sensor_service(sensors);

void setup()
{
  while (!Serial)
  {
    ;
  };
  Serial.begin(9600);
}

void loop()
{
  sensor_service.readAll();
  sensor_service.forEach(onSensor);
  delay(100);
}

void onSensor(Sensor *sensor)
{
  Serial.print("Value: ");
  Serial.print(sensor->getCurrentReading());
  Serial.print(":");
  Serial.println(sensor->getId());
}