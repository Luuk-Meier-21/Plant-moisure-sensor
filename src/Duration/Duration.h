#ifndef Duration_h
#define Duration_h

class Duration
{
  unsigned long miliseconds;

protected:
  Duration(unsigned long milis) : miliseconds(milis) {}

public:
  static Duration fromSeconds(unsigned long secs)
  {
    return Duration(1000 * secs);
  }

  static Duration fromMinutes(unsigned long mins)
  {
    return fromSeconds(mins * 60);
  }

  static Duration fromHours(unsigned long hours)
  {
    return fromMinutes(hours * 60);
  }

  unsigned long toHours()
  {
    return toMinutes() / 60;
  }

  unsigned long toMinutes()
  {
    return toSeconds() / 60;
  }

  unsigned long toSeconds()
  {
    return miliseconds / 100;
  }

  unsigned long toMiliseconds()
  {
    return miliseconds;
  }

  unsigned long toMicroseconds()
  {
    return miliseconds * 1000;
  }

  operator long() const
  {
    return miliseconds;
  }
};

#endif
