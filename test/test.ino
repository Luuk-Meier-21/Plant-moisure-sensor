// ———— Test entry point ————
// A test needs to be imported for the test runner to know about it.

#include "/Users/luukmeier/Documents/Arduino/libraries/EpoxyDuino/EpoxyDuino.h"
#include "/Users/luukmeier/Documents/Arduino/libraries/AUnit/src/AUnitVerbose.h"

#include "/Users/luukmeier/Documents/Arduino/plant-saver/lib/SensorService/SensorService.test.h"
#include "/Users/luukmeier/Documents/Arduino/plant-saver/lib/MoistureSensor/MoistureSensor.test.h"
#include "/Users/luukmeier/Documents/Arduino/plant-saver/lib/SerialReader/SerialReader.test.h"

void setup()
{
}

void loop()
{
  aunit::TestRunner::run();
}
