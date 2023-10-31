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
#include "src/HTTPRequestClient/HTTPRequestClient.h"

#define sensor_pin A0
#define led_output_pin D0

const int sensor_count = 1;

// Steam
StreamReader serial_reader(&Serial);

// Sensor
MoistureSensor *sensor_a = new MoistureSensor(1, sensor_pin, analogRead);

Sensor *sensors[sensor_count] = {sensor_a};
SensorClient<sensor_count> sensor_client(sensors);

// Wifi:
DynamicWiFiNetwork<network_count> dynamic_network(private_networks);
DiscoveringWiFiClient<network_count> discovering_network_client(WiFi, &dynamic_network);

String server_name = "https://api.thingspeak.com/update";
String api_url = server_name + "?api_key=" + API_WRITE_KEY;

// timing TODO: abstract to Timer class
unsigned long lastTime = 0;

void setup()
{
  while (!Serial)
  {
  };
  Serial.begin(9600);

  if (!discovering_network_client.scan())
  {
    breakingError("No network found.");
  };

  if (!discovering_network_client.tryConnection(awaitConnection, 20000))
  {
    breakingError("Unable to connect to network.");
  };

  Serial.println("");
  Serial.println(WiFi.SSID());
  Serial.println(WiFi.localIP());
}

void loop()
{
  sensor_client.readAll();

  if ((millis() - lastTime) > 5000)
  {
    updateEndpoint(sensor_client);
    lastTime = millis();
  }

  delay(200);
}

template <size_t SIZE>
void updateEndpoint(SensorClient<SIZE> &sensor_client)
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println(WiFi.status());
    Serial.println("WiFi Disconnected!");
    return;
  };

  String url = api_url;

  for (size_t i = 0; i < sensor_client.count(); i++)
  {
    Sensor *sensor = sensor_client.getSensorOfIndex(i);
    url = url + "&" + sensor->getFieldName() + "=" + sensor->getCurrentReading();
  };

  WiFiClientSecure client;
  // Very insecure, but it should not matter for this case.
  client.setInsecure();

  HTTPClient http;
  HTTPRequestClient requestClient(&client, &http);

  int responseCode = requestClient.makeRequest(HTTP_GET, url);
  if (responseCode <= 0)
  {
    // Bad request:
    Serial.println("Bad request");
    return;
  }
  else
  {
    Serial.print("Send data: ");
    Serial.println(responseCode);
  }
}

void awaitConnection()
{
  Serial.print(".");
  delay(500);
}

void breakingError(String message)
{
  Serial.println(message);
  // Report to user! (blinking led?)
  while (true)
  {
  };
}