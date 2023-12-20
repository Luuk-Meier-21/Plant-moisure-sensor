#ifndef Timer_h
#define Timer_h

class Timer
{
  unsigned long delay;
  unsigned long last_time = 0;

public:
  Timer(unsigned long time) : delay(time){};

  unsigned long hasElapsed()
  {
    return (millis() - last_time) > delay;
  };

  void reset()
  {
    last_time = millis();
  }

  unsigned long currentDelay()
  {
    return delay;
  }
};

#endif
