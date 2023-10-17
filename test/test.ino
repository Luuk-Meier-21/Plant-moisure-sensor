// ———— Test entry point ————
// A test needs to be imported for the test runner to know about it.

#include "/Users/luukmeier/Documents/Arduino/libraries/EpoxyDuino/EpoxyDuino.h"
#include "/Users/luukmeier/Documents/Arduino/libraries/AUnit/src/AUnitVerbose.h"

#include "../src/SensorService/SensorService.test.h"
#include "../src/MoistureSensor/MoistureSensor.test.h"
#include "../src/StreamReader/StreamReader.test.h"

void setup()
{
}

void loop()
{
  aunit::TestRunner::run();
}
