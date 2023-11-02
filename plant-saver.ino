#define CORE

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

// Helper classes:
#include "src/Exception/Exception.h"
#include "src/Timer/Timer.h"
#include "src/Duration/Duration.h"

#include "src/.env/env.h"
#include "src/StreamReader/StreamReader.h"
#include "src/MoistureSensor/MoistureSensor.h"
#include "src/SensorClient/SensorClient.h"
#include "src/DynamicWiFiNetwork/DynamicWiFiNetwork.h"
#include "src/DiscoveringWiFiClient/DiscoveringWiFiClient.h"
#include "src/HTTPRequestClient/HTTPRequestClient.h"

#define sensor_pin A0
#define succes_pin D5
#define error_pin D8

// // Steam
// StreamReader serial_reader(&Serial);

// Sensor:
MoistureSensor *sensor_a = new MoistureSensor(1, sensor_pin, analogRead);
Sensor *sensors[] = {sensor_a};

const size_t sensor_count = *(&sensors + 1) - sensors;
SensorClient<sensor_count> sensor_client(sensors);

// WiFi:
DynamicWiFiNetwork<network_count> dynamic_network(private_networks);
DiscoveringWiFiClient<network_count> discovering_network_client(WiFi, &dynamic_network);

String server_name = "https://api.thingspeak.com/update";
String api_url = server_name + "?api_key=" + API_WRITE_KEY;

void setup()
{
  while (!Serial)
  {
  };
  Serial.begin(9600);
  pinMode(succes_pin, OUTPUT);
  pinMode(error_pin, OUTPUT);
  connectWiFi(discovering_network_client);

  Serial.print("\nConnected to: ");
  Serial.println(WiFi.SSID());
}

void loop()
{
  sensor_client.readAll();

  static Timer endpoint_timer(Duration::fromSeconds(5));
  if (endpoint_timer.hasElapsed())
  {
    updateEndpoint(sensor_client);
    endpoint_timer.reset();
  };

  delay(200);
}

// Arduino functions

void connectWiFi(DiscoveringWiFiClient<network_count> &discovering_network_client)
{
  if (!discovering_network_client.scan())
  {
    breakingError("No network found.", NETWORK_NOT_FOUND);
  };

  if (!discovering_network_client.tryConnection(awaitConnection, 20000))
  {
    breakingError("Unable to connect to network.", NETWORK_CONNECTION_FAILED);
  };
}

template <size_t SIZE>
void updateEndpoint(SensorClient<SIZE> &sensor_client)
{
  if (WiFi.status() != WL_CONNECTED)
  {
    breakingError("WiFi Disconnected!", NETWORK_DISCONNECTED);
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
  HTTPRequestClient request_client(&client, &http);

  static bool is_active = false;
  int response_code = request_client.makeRequest(HTTP_GET, url);
  if (response_code <= 0)
  {
    // Bad request:
    Serial.println("Bad request");
  }
  else
  {
    Serial.print("Send data: ");
    Serial.println(response_code);

    // Debug blinking:
    digitalWrite(succes_pin, is_active ? HIGH : LOW);
    is_active = !is_active;
  }
}

void awaitConnection()
{
  Serial.print(".");
  delay(500);
}

void breakingError(String message, ExceptionBlinkType blink_type)
{
  // Report to user! (blinking led?)
  while (true)
  {
    for (int i = 0; i < blink_type; i++)
    {
      digitalWrite(error_pin, HIGH);
      delay(200);
      digitalWrite(error_pin, LOW);
      delay(200);
    }
    Serial.println(message);
    delay(1000);
  };
}