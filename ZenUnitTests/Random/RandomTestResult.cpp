#include "pch.h"
#include "ZenUnitTests/Random/RandomTestResult.h"

namespace ZenUnit
{
   template<>
   TestResult Random<TestResult>()
   {
      TestResult randomTestResult;
      randomTestResult.milliseconds = ZenUnit::Random<unsigned>();
      return randomTestResult;
   }
}
