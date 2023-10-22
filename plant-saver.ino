#include <ESP8266WiFi.h>

#include "src/.env/env.h"
#include "src/StreamReader/StreamReader.h"
#include "src/MoistureSensor/MoistureSensor.h"
#include "src/SensorService/SensorService.h"
#include "src/SensorReading/SensorReading.h"

#define sensor_pin A0
const int sensor_count = 1;

StreamReader serial_reader(&Serial);

MoistureSensor *sensor_a = new MoistureSensor(1, sensor_pin, analogRead);

Sensor *sensors[sensor_count] = {sensor_a};
SensorService<sensor_count> sensor_service(sensors);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  SensorResultsClient<sensor_count> results;
  sensor_service.readAllToResults(&results);

  results.forEach(sensorReading);
}

void sensorReading(SensorReading *reading)
{
  Serial.print("Reading id: ");
  Serial.print(reading->id);
  Serial.print(" value: ");
  Serial.print(reading->value);
  Serial.print("%\n\n");
  delay(100);
}