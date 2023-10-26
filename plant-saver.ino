#define CORE

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#include "src/.env/env.h"
#include "src/StreamReader/StreamReader.h"
#include "src/MoistureSensor/MoistureSensor.h"
#include "src/SensorClient/SensorClient.h"
#include "src/DynamicWiFiNetwork/DynamicWiFiNetwork.h"

#include "src/DiscoveringWiFiClient/DiscoveringWiFiClient.h"

#define sensor_pin A0
const int sensor_count = 1;

// Steam
StreamReader serial_reader(&Serial);

// Sensor
MoistureSensor *sensor_a = new MoistureSensor(1, sensor_pin, analogRead);

Sensor *sensors[sensor_count] = {sensor_a};
SensorClient<sensor_count> sensor_service(sensors);

// Wifi:
DynamicWiFiNetwork<network_count> dynamic_network(private_networks);
DiscoveringWiFiClient<network_count> discoveringNetworkClient(WiFi, &dynamic_network);

void setup()
{
  while (!Serial)
  {
  };
  Serial.begin(9600);

  if (discoveringNetworkClient.scan() == false)
  {
    reportError("No network found.");
  }

  discoveringNetworkClient.beginConnection();

  if (discoveringNetworkClient.awaitConnection(awaitConnection, 5000) == false)
  {
    reportError("Unable to connect to network.");
  }
  // Sure of connection from here:

  Serial.println("");
  Serial.println(WiFi.localIP());
}

void awaitConnection()
{
  Serial.print(".");
  delay(500);
}

void loop()
{
  sensor_service.readAll();
  sensor_service.forEach(onSensor);

  if (WiFi.status() == WL_CONNECTED)
  {
    WiFiClientSecure client;
    // Very insecure, but it should not matter for this case.
    client.setInsecure();
    HTTPClient http;

    // String serverPath = serverName + "?api_key=" + API_WRITE_KEY + "&field1=" + (String)count;
  };

  delay(100);
}

void onSensor(Sensor *sensor)
{
  Serial.print("Value: ");
  Serial.print(sensor->getCurrentReading());
  Serial.print(":");
  Serial.println(sensor->getId());
}

void reportError(String message)
{
  Serial.println(message);
  // Report to user! (blinking led?)
  while (true)
  {
  };
}