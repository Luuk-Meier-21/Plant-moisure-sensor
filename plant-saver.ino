
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#include "src/.env/env.h"
#include "src/MoistureSensor/MoistureSensor.h"

String serverName = "https://api.thingspeak.com/update";

unsigned long lastTime = 0;
unsigned long timerDelay = 5000;
unsigned int count = 0;

int id = 0;
int pin = A0;

MoistureSensor *moisture_sensor_a = new MoistureSensor(id, pin, analogRead);

void setup()
{
  Serial.begin(9600);

  WiFi.begin(_p.hotspot.ssid, _p.hotspot.password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop()
{
  // Send an HTTP POST request depending on timerDelay
  if ((millis() - lastTime) > timerDelay)
  {
    count = count + 1;

    // Check WiFi connection status
    if (WiFi.status() == WL_CONNECTED)
    {
      WiFiClientSecure client;
      // Very insecure, but it should not matter for this case.
      client.setInsecure();
      HTTPClient http;

      String serverPath = serverName + "?api_key=" + API_WRITE_KEY + "&field1=" + (String)count;

      Serial.print("Path: ");
      Serial.println(serverPath.c_str());

      // Your Domain name with URL path or IP address with path
      http.begin(client, serverPath.c_str());

      // If you need Node-RED/server authentication, insert user and password below
      // http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");

      // Send HTTP GET request
      int httpResponseCode = http.GET();

      if (httpResponseCode > 0)
      {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else
      {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else
    {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}