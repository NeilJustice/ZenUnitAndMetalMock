#pragma once
#include "ZenUnit/TestRunners/TestClassRunner.h"

namespace ZenUnit
{
   class NoOpTestClassRunner : public TestClassRunner
   {
   public:
      const char* TestClassName() const override;
      size_t NumberOfTestCases() const override;
      TestClassResult RunTests() override;
      bool HasTestNameThatCaseInsensitiveMatchesPattern(const std::string& testNamePattern) const override;
   };
}
