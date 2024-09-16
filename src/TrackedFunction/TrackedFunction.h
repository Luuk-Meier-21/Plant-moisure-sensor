#ifndef TrackedFunction_h
#define TrackedFunction_h

class Counting
{
protected:
  Counting() = default;

  int _count = 0;

  void updateCount()
  {
    _count = _count + 1;
  }

public:
  int count()
  {
    return _count;
  }

  void resetCount()
  {
    Serial.println("RESET COUNT");
    _count = 0;
  }
};

/*
 * Decorator for tracking the number of times a function is called.
 * For use in handling errors without creating infinite loops.
 */
template <typename ReturnType, typename... Args>
class TrackedFunction : public Counting
{
  ReturnType (*function)(Args...);

protected:
public:
  TrackedFunction(ReturnType (*f)(Args...)) : Counting(), function(f){};

  ReturnType call(Args... args)
  {
    this->updateCount();
    return function(args...);
  }
};

/*
 * Decorator for tracking the number of times a recursive function is called.
 * For use in handling errors without creating infinite loops.
 */
template <typename ReturnType, typename... Args>
class RecursiveTrackedFunction : public Counting
{
  ReturnType (*function)(RecursiveTrackedFunction<ReturnType, Args...> *, Args...);

public:
  RecursiveTrackedFunction(ReturnType (*f)(RecursiveTrackedFunction<ReturnType, Args...> *, Args...)) : Counting(), function(f){};

  ReturnType call(Args... args)
  {
    this->updateCount();
    return function(this, args...);
  }
};

#endif
