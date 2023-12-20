#define CORE

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#include "src/Macros/Macros.h"

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

#define analog_input_pin A0
#define digital_input_pin_a D2
#define digital_input_pin_b D1

#define connection_timeout_milisec 20000

#define succes_pin D5
#define error_pin D8

#define connect_tries_setup 4
#define connect_tries_runtime 4

// void setupSensor(uint8_t pin)
// {
//     // pinMode(pin, INPUT);
// }

// Sensor:
// BUG: passing `setupSensor` to `MoistureSensor` causes c++ to lose the typedef of `connectWiFi`, god knows why.
MoistureSensor *moisture_sensor_a = new MoistureSensor(1, digital_input_pin_a, digitalRead);
MoistureSensor *moisture_sensor_b = new MoistureSensor(2, digital_input_pin_b, digitalRead);
Sensor *sensors[] = {moisture_sensor_a, moisture_sensor_b};

const size_t sensor_count = LENGTH(sensors);
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
    Serial.begin(9600);
    Serial.println("\nWaking from sleep, running setup.");

    pinMode(digital_input_pin_a, INPUT_PULLUP);
    pinMode(digital_input_pin_b, INPUT_PULLUP);
    pinMode(succes_pin, OUTPUT);
    pinMode(error_pin, OUTPUT);

    // sensor_client.setupAll();

    connection_func.call(discovering_network_client);

    Serial.print("\nConnected to: ");
    Serial.println(WiFi.SSID());
}

void loop()
{
    sensor_client.readAll();

    updateEndpoint(sensor_client);

    int minutes = 5;
    unsigned long sleep_time = Duration::fromSeconds(minutes).toMicroseconds();

    Serial.print("Starting deep sleep for ");
    Serial.print(minutes);
    Serial.print(" minutes. \n\n");

    ESP.deepSleep(sleep_time);
};

void awaitConnection()
{
    Serial.print(".");
    delay(400);
};

void connectWiFi(RecursiveConnectWiFiFunc *self, DiscoveringWiFiClient<network_count> &discovering_network_client)
{
    bool has_found_networks = discovering_network_client.scan();
    if (has_found_networks == false)
    {
        if (self->count() > connect_tries_setup)
        {
            throwBreaking("No matching network found.", NETWORK_NOT_FOUND);
        }

        self->call(discovering_network_client);
        return;
    };

    bool has_connected = discovering_network_client.tryConnection(awaitConnection, connection_timeout_milisec);
    if (has_connected == false)
    {
        if (self->count() > connect_tries_setup)
        {
            throwBreaking("Unable to connect to network.", NETWORK_CONNECTION_FAILED);
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
            throwBreaking("Unable to (re)connect to network.", NETWORK_DISCONNECTED);
        }

        connection_func.call(discovering_network_client);
        return;
    };

    String url = api_url;
    for (size_t i = 0; i < sensor_client.count(); i++)
    {
        Sensor *sensor = sensor_client.getSensorOfIndex(i);
        url = url + "&field" + sensor->getId() + "=" + sensor->getCurrentReading();
    };

    Serial.println(url);

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
        Serial.println(url);

        // Debug blinking:
        digitalWrite(succes_pin, is_active ? HIGH : LOW);
        is_active = !is_active;
    }
}

void throwBreaking(String message, ExceptionBlinkType blink_type)
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
};