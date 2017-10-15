#pragma once
#include "ZenUnit/TestRunners/TestClassRunner.h"

namespace ZenUnit
{
   class NoOpTestClassRunner : public TestClassRunner
   {
   public:
      virtual const char* TestClassName() const;
      virtual size_t NumberOfTestCases() const;
      virtual TestClassResult RunTests();
   };
}
