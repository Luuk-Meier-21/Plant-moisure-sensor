// ———— Test entry point ————
// A test needs to be imported for the test runner to know about it.

#define TEST

#include "stddef.h"
using namespace std;

#include "/Users/luukmeier/Documents/Arduino/libraries/AUnit/src/AUnit.h"

#include "../src/SensorClient/SensorClient.test.h"
#include "../src/MoistureSensor/MoistureSensor.test.h"
#include "../src/StreamReader/StreamReader.test.h"
#include "../src/WiFiNetwork/WiFiNetwork.test.h"
#include "../src/DynamicWiFiNetwork/DynamicWiFiNetwork.test.h"
#include "../src/DiscoveringWiFiClient/DiscoveringWiFiClient.test.h"
#include "../src/HTTPRequestClient/HTTPRequestClient.test.h"
#include "../src/Timer/Timer.test.h"
#include "../src/Duration/Duration.test.h"
#include "../src/TrackedFunction/TrackedFunction.test.h"

// %TEST_INCLUDE%

void setup()
{
}

void loop()
{
  aunit::TestRunner::run();
}
