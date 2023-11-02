#ifndef Timer_test_h
#define Timer_test_h

#include "./Timer.h"

test(Timer_hasElapsed_succes)
{
  String result = "";
  static Timer timer(30);
  for (size_t i = 0; i < 9; i++)
  {
    if (timer.hasElapsed())
    {
      result = result + "y";
      timer.reset();
    }
    else
    {
      result = result + "n";
    }
    delay(10);
  }
  assertEqual(result, "ynnynnynn");
};

test(Timer_hasElapsed_noReset)
{
  String result = "";
  static Timer timer(30);
  for (size_t i = 0; i < 9; i++)
  {
    if (timer.hasElapsed())
    {
      result = result + "y";
    }
    else
    {
      result = result + "n";
    }
    delay(10);
  }
  assertEqual(result, "yyyyyyyyy");
};

#endif
