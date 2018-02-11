#include "pch.h"
#include "ZenUnitTests/Random/RandomTestResult.h"

namespace ZenUnit
{
   template<>
   TestResult Random<TestResult>()
   {
      TestResult randomTestResult;
      randomTestResult.microseconds = ZenUnit::Random<unsigned>();
      return randomTestResult;
   }
}
