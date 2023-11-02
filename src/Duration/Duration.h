#ifndef Duration_h
#define Duration_h

class Duration
{
public:
  static unsigned long fromSeconds(unsigned long sec)
  {
    return 1000 * sec;
  }

  static unsigned long fromMinutes(unsigned long min)
  {
    return 60000 * min;
  }
};

#endif
