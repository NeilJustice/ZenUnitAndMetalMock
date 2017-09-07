#pragma once
#include "ZenUnit/Args/ZenUnitArgs.h"
#include "ZenUnit/Results/TestClassResult.h"

namespace ZenUnit
{
   class TestClassRunner;
   template<typename, typename> class Transformer;
   template<typename> class Sorter;

   class MultiTestClassRunner
   {
      friend class MultiTestClassRunnerTests;
   private:
      std::unique_ptr<const Sorter<std::vector<std::unique_ptr<TestClassRunner>>>> _sorter;
      std::unique_ptr<const Transformer<std::unique_ptr<TestClassRunner>, TestClassResult>> _transformer;
      std::vector<std::unique_ptr<TestClassRunner>> _testClassRunners;
      std::vector<TestClassResult> _testClassResults;
   public:
      MultiTestClassRunner();
      virtual ~MultiTestClassRunner();
      virtual size_t NumberOfTestClasses() const;
      virtual size_t NumberOfTestCases() const;
      virtual void AddTestClassRunner(TestClassRunner* testClassRunner);
      virtual std::vector<TestClassResult> RunTestClasses(const ZenUnitArgs& zenUnitArgs);
   private:
      static TestClassResult RunTestClassRunner(const std::unique_ptr<TestClassRunner>& testClassRunner);
   };
}
