#include <AUnit.h>
#include <AUnitVerbose.h>

#include <EpoxyDuino.h>

#include "SoftwareSerial.h"

#include "/Users/luukmeier/Documents/Arduino/plant-saver/lib/SerialReader/SerialReader.h"
#include "/Users/luukmeier/Documents/Arduino/plant-saver/lib/serial.h"
#include "/Users/luukmeier/Documents/Arduino/plant-saver/lib/Sensors/MoistureSensor.h"
#include "/Users/luukmeier/Documents/Arduino/plant-saver/lib/SensorService/SensorService.h"

#define sensor_pin_a A1
const int sensor_count = 3;

SoftwareSerial EspSerial(12, 13); // RX | TX

SerialReader serial_reader(&Serial), esp_serial_reader(&EspSerial);

MoistureSensor *sensor_a = new MoistureSensor(1, sensor_pin_a, analogRead);
MoistureSensor *sensor_b = new MoistureSensor(2, sensor_pin_a, analogRead);
MoistureSensor *sensor_c = new MoistureSensor(3, sensor_pin_a, analogRead);

Sensor *sensors[sensor_count] = {sensor_a, sensor_b, sensor_c};
SensorService<sensor_count> sensor_service(sensors);

void setup()
{
  Serial.begin(9600);
  EspSerial.begin(9600);
  while (!Serial)
  {
    ;
  }
  pinMode(4, OUTPUT);
}

void loop()
{
  serial_reader.readAvailable();
  if (serial_reader.hasData())
  {
    String data = serial_reader.extractData();
    EspSerial.print(data);
  }

  esp_serial_reader.readAvailable();
  if (esp_serial_reader.hasData())
  {
    String data = esp_serial_reader.extractData();
    Serial.print(data);
  }

  sensor_service.readAll();
  SensorReadingResults<sensor_count> data = sensor_service.getCurrentReadings();

  for (size_t i = 0; i < sensor_count; i++)
  {
    if (data.readings[i].value > 0)
    {
      Serial.print("Reading id: ");
      Serial.print(data.readings[i].id);
      Serial.print(" value: ");
      Serial.print(data.readings[i].value);
      Serial.print("%\n\n");
    }
  }
}
