// ———— Test entry point ————
// A test needs to be imported for the test runner to know about it.

#define TEST

#include <AUnitVerbose.h>

#include "../src/SensorClient/SensorClient.test.h"
#include "../src/MoistureSensor/MoistureSensor.test.h"
#include "../src/StreamReader/StreamReader.test.h"
#include "../src/WiFiNetwork/WiFiNetwork.test.h"
#include "../src/DynamicWiFiNetwork/DynamicWiFiNetwork.test.h"
#include "../src/DiscoveringWiFiClient/DiscoveringWiFiClient.test.h"

void setup()
{
}

void loop()
{
  aunit::TestRunner::run();
}
