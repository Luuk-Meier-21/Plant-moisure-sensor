#include "SoftwareSerial.h"
#include "ESP8266WiFi.h"

// #include <SoftwareSerial.h"
// SoftwareSerial mySUART(2, 3);

void setup()
{
  Serial.begin(115200);
  // mySUART.begin(115200);

  while (!Serial)
  {
    ;
  }
  // WiFi.begin("Famkampman", "bert1969");

  // Serial.print("Connecting");
  // while (WiFi.status() != WL_CONNECTED)
  // {
  //   delay(500);
  //   Serial.println("waiting");
  //   Serial.print(".");
  // }
  // Serial.println();

  // Serial.print("Connected, IP address: ");
  // Serial.println(WiFi.localIP());
}

void loop()
{
  if (Serial.available() > 0)
  {
    byte x = Serial.read();
    Serial.write(x);
  }
  // if (mySUART.available() > 0)
  // {
  //   Serial.write((char)mySUART.read());
  // }
}

// SoftwareSerial mySUART(4, 5); // D2, D1

// void setup()
// {
//   Serial.begin(115200);
//   Serial.println();

//   while (!Serial)
//   {
//     ;
//   }
//   WiFi.begin("Famkampman", "bert1969");

//   Serial.print("Connecting");
//   while (WiFi.status() != WL_CONNECTED)
//   {
//     delay(500);
//     Serial.println("waiting");
//     Serial.print(".");
//   }
//   Serial.println();

//   Serial.print("Connected, IP address: ");
//   Serial.println(WiFi.localIP());
// }

// void loop()
// {
//   Serial.println("Looping");
// }