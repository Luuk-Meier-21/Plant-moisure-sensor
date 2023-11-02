#ifndef Duration_test_h
#define Duration_test_h

#include "./Duration.h"

test(Duration_fromSeconds)
{
  unsigned long a = Duration::fromSeconds(60);
  assertEqual(a, (unsigned long)60000);

  unsigned long b = Duration::fromSeconds(25);
  assertEqual(b, (unsigned long)25000);

  unsigned long c = Duration::fromSeconds(1);
  assertEqual(c, (unsigned long)1000);
};

test(Duration_fromMinutes)
{
  unsigned long a = Duration::fromMinutes(2);
  assertEqual(a, (unsigned long)120000);

  unsigned long b = Duration::fromMinutes(10);
  assertEqual(b, (unsigned long)600000);

  unsigned long c = Duration::fromMinutes(100);
  assertEqual(c, (unsigned long)6000000);
};

#endif
