#pragma once
#include "ZenUnit/Results/TestClassResult.h"

namespace ZenUnit
{
   template<>
   TestResult Random<TestResult>();

   template<>
   TestClassResult Random<TestClassResult>();
}
