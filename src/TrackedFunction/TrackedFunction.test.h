#ifndef TrackedFunction_test_h
#define TrackedFunction_test_h

#include "./TrackedFunction.h"

void mockTrackedFunction(int &num)
{
  num = num + 1;
};

typedef RecursiveTrackedFunction<bool, int &> RecursiveTypedFunc;
bool mockRecursiveTrackedFunction(RecursiveTypedFunc *self, int &num)
{
  if (self->count() > 4)
  {
    return false;
  }

  num = num + 1;
  return self->call(num);
}

test(TrackedFunction_call)
{
  TrackedFunction<void, int &> func(mockTrackedFunction);
  int intp = 0;

  func.call(intp);

  assertEqual(intp, 1);
};

test(TrackedFunction_count)
{
  TrackedFunction<void, int &> func(mockTrackedFunction);
  int intp = 0;
  int max = 4;

  for (size_t i = 0; i <= 10; i++)
  {
    if (func.count() >= max)
    {
      break;
    }
    else
    {
      func.call(intp);
    }
  }

  assertEqual(intp, max);
};

test(RecursiveTrackedFunction_count_call)
{
  RecursiveTypedFunc recursive_func(mockRecursiveTrackedFunction);
  int intp = 0;
  int max = 4;

  bool exception_return = recursive_func.call(intp);

  assertEqual(intp, max);
  assertFalse(exception_return);
};

#endif
