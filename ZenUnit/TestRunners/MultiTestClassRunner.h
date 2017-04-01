#pragma once
#include "ZenUnit/Args/ZenUnitArgs.h"
#include "ZenUnit/Results/TestClassResult.h"

namespace ZenUnit
{
   class TestClassRunner;
   template<typename, typename, typename> class Transformer;
   template<typename> class Sorter;

   class MultiTestClassRunner
   {
      friend class MultiTestClassRunnerTests;
   private:
      std::unique_ptr<const Transformer<
         std::vector<std::unique_ptr<TestClassRunner>>::const_iterator,
         std::vector<TestClassResult>,
         TestClassResult (*)(const std::unique_ptr<TestClassRunner>&)>> _transformer;
      std::vector<std::unique_ptr<TestClassRunner>> _testClassRunners;
      std::unique_ptr<const Sorter<decltype(_testClassRunners)>> _sorter;
      vector<TestClassResult> _testClassResults;
   public:
      MultiTestClassRunner();
      virtual ~MultiTestClassRunner();
      virtual size_t NumberOfTestClasses() const;
      virtual size_t TotalNumberOfTestCases() const;
      virtual void AddTestClassRunner(TestClassRunner* testClassRunner);
      virtual vector<TestClassResult> RunTestClasses();
   private:
      static TestClassResult RunTestClassRunner(const std::unique_ptr<TestClassRunner>& testClassRunner);
   };
}
