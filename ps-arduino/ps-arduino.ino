
// #include "/Users/luukmeier/Documents/Arduino/plant-saver/lib/serial.h"
// #include "/Users/luukmeier/Documents/Arduino/plant-saver/lib/Sensors/MoistureSensor.h"
// #include "/Users/luukmeier/Documents/Arduino/plant-saver/lib/SensorService/SensorService.h"

#include "SoftwareSerial.h"
SoftwareSerial mySUART(12, 13); // SRX = Din-2, STX = Dpin-3

void setup()
{
  Serial.begin(115200);
  mySUART.begin(115200);
  while (!Serial)
  {
    ;
  }
  pinMode(4, OUTPUT);
}

void loop()
{

  // // Serial.println("loop");
  if (Serial.available() > 0)
  {

    byte x = Serial.read();
    Serial.write(x);
    mySUART.write(x);
  }
  if (mySUART.available() > 0)
  {
    digitalWrite(4, HIGH); // Turn the LED on (Note that LOW is the voltage level)
    delay(50);             // Wait for a second
    digitalWrite(4, LOW);  // Turn the LED off by making the voltage HIGH
    delay(50);
    Serial.write(mySUART.read());
  }
}

// #define sensor_pin_a A1

// const int sensor_count = 3;

// MoistureSensor *sensor_a = new MoistureSensor(1, sensor_pin_a);
// MoistureSensor *sensor_b = new MoistureSensor(2, sensor_pin_a);
// MoistureSensor *sensor_c = new MoistureSensor(3, sensor_pin_a);

// Sensor *sensors[sensor_count] = {sensor_a, sensor_b, sensor_c};
// SensorService<sensor_count> sensor_service(sensors);

// void setup()
// {
//   Serial.begin(9600);
// }

// void loop()
// {
//   // String serial_message = readSerial();

//   // // Use Serial message
//   // if (serial_message.length() > 0)
//   // {
//   //   float percentage = serial_message.toFloat();

//   //   serial_message = "";
//   // }

//   sensor_service.readAll();
//   SensorReadingResults<sensor_count> data = sensor_service.getCurrentReadings();

//   for (size_t i = 0; i < sensor_count; i++)
//   {
//     if (data.readings[i].value > 0)
//     {
//       Serial.print("Reading id: ");
//       Serial.print(data.readings[i].id);
//       Serial.print(" value: ");
//       Serial.print(data.readings[i].value);
//       Serial.print("%\n\n");
//     }
//   }

//   delay(500);
// }
