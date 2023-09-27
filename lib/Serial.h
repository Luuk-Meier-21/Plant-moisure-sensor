#include "Arduino.h"

String readSerial()
{
  String data = "";
  while (Serial.available())
  {
    delay(10);
    char c = Serial.read();
    data += c;
  }
  return data;
}