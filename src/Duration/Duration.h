#ifndef Duration_h
#define Duration_h

class Duration
{
public:
  static unsigned long fromSeconds(unsigned long secs)
  {
    return 1000 * secs;
  }

  static unsigned long fromMinutes(unsigned long mins)
  {
    return Duration::fromSeconds(60 * mins);
  }

  static unsigned long fromHours(unsigned long hours)
  {
    return Duration::fromMinutes(60 * hours);
  }
};

#endif
