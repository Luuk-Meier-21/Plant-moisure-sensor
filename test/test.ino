#include "/Users/luukmeier/Documents/Arduino/libraries/EpoxyDuino/EpoxyDuino.h"
#include "/Users/luukmeier/Documents/Arduino/libraries/AUnit/src/AUnit.h"
#include "/Users/luukmeier/Documents/Arduino/libraries/AUnit/src/AUnitVerbose.h"

test(simple1)
{
  assertTrue(true);
}

test(simple2)
{
  assertTrue(true);
}

void setup()
{
#if !defined(EPOXY_DUINO)
  delay(1000); // wait for stability on some boards to prevent garbage Serial
#endif
  Serial.begin(115200); // ESP8266 default of 74880 not supported on Linux
  while (!Serial)
    ; // for the Arduino Leonardo/Micro only
#if defined(EPOXY_DUINO)
  Serial.setLineModeUnix();
#endif

  Serial.println(F("This test should produce the following:"));
  Serial.println(
      F("1 passed, 1 failed, 0 skipped, 0 timed out, out of 2 test(s)."));
  Serial.println(F("----"));
}

void loop()
{
  aunit::TestRunner::run();
}
