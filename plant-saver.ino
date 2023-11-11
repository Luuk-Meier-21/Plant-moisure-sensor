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
#include "src/TrackedFunction/TrackedFunction.h"

#define sensor_pin A0
#define succes_pin D5
#define error_pin D8

#define connect_tries_setup 4
#define connect_tries_runtime 4

// Sensor:
MoistureSensor *sensor_a = new MoistureSensor(1, sensor_pin, analogRead);
Sensor *sensors[] = {sensor_a};

const size_t sensor_count = *(&sensors + 1) - sensors;
SensorClient<sensor_count> sensor_client(sensors);

// WiFi:
DynamicWiFiNetwork<network_count> dynamic_network(private_networks);
DiscoveringWiFiClient<network_count> discovering_network_client(WiFi, &dynamic_network);

typedef RecursiveTrackedFunction<void, DiscoveringWiFiClient<network_count> &> RecursiveConnectWiFiFunc;
RecursiveConnectWiFiFunc connection_func(connectWiFi);

// HTTP:
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
  connection_func.call(discovering_network_client);

  Serial.print("\nConnected to: ");
  Serial.println(WiFi.SSID());
}

void loop()
{
  // Read all sensors in `sensor_client`.
  sensor_client.readAll();

  // Reset connecion retry count every `y` minutes. Runtime gets `n` retries every `y` minutes.
  static Timer retries_reset_timer(Duration::fromHours(2));
  if (retries_reset_timer.hasElapsed())
  {
    connection_func.resetCount();
    retries_reset_timer.reset();
  };

  // Update enpoint every `y` minutes.
  static Timer endpoint_timer(Duration::fromMinutes(5));
  if (endpoint_timer.hasElapsed())
  {
    updateEndpoint(sensor_client);
    endpoint_timer.reset();
  };

  delay(200);
}

// Arduino functions
void connectWiFi(RecursiveConnectWiFiFunc *self, DiscoveringWiFiClient<network_count> &discovering_network_client)
{
  bool has_found_networks = discovering_network_client.scan();
  if (has_found_networks == false)
  {
    if (self->count() > connect_tries_setup)
    {
      breakingError("No matching network found.", NETWORK_NOT_FOUND);
    }

    self->call(discovering_network_client);
    return;
  };

  bool has_connected = discovering_network_client.tryConnection(awaitConnection, 20000);
  if (has_connected == false)
  {
    if (self->count() > connect_tries_setup)
    {
      breakingError("Unable to connect to network.", NETWORK_CONNECTION_FAILED);
    }

    self->call(discovering_network_client);
    return;
  };
}

template <size_t SIZE>
void updateEndpoint(SensorClient<SIZE> &sensor_client)
{
  if (WiFi.status() != WL_CONNECTED)
  {
    if (connection_func.count() > connect_tries_runtime)
    {
      breakingError("Unable to (re)connect to network.", NETWORK_DISCONNECTED);
    }

    connection_func.call(discovering_network_client);
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