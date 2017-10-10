#pragma once
#include "ZenUnit/Results/TestClassResult.h"

namespace ZenUnit
{
   struct ZenUnitArgs;
   class TestClassRunner;
   template<typename IterableType, typename FunctionType, typename ExtraArgType> class ExtraArgForEacher;
   template<typename T, typename TransformedT> class Transformer;
   template<typename T> class Sorter;
   class Watch;

   class MultiTestClassRunner
   {
      friend class MultiTestClassRunnerTests;
   private:
      using ExtraArgForEacherType = ExtraArgForEacher<
         std::vector<std::unique_ptr<TestClassRunner>>,
         void(*)(const std::unique_ptr<TestClassRunner>&, std::vector<std::unique_ptr<TestClassRunner>>*),
         std::vector<std::unique_ptr<TestClassRunner>>*>;
      std::unique_ptr<const ExtraArgForEacherType> _extraArgForEacher;
      std::unique_ptr<const Sorter<std::vector<std::unique_ptr<TestClassRunner>>>> _sorter;
      std::unique_ptr<const Transformer<std::unique_ptr<TestClassRunner>, TestClassResult>> _transformer;
      std::unique_ptr<const Watch> _watch;
      std::vector<std::unique_ptr<TestClassRunner>> _allTestClassRunners;
      std::vector<std::unique_ptr<TestClassRunner>> _runFilteredTestClassRunners;
      std::vector<TestClassResult> _testClassResults;
   public:
      MultiTestClassRunner();
      virtual ~MultiTestClassRunner();
      virtual void AddTestClassRunner(TestClassRunner* testClassRunner);
      virtual void ApplyRunFiltersIfAny(const std::vector<std::string>& runFilters);
      virtual size_t NumberOfTestClassesToBeRun() const;
      virtual size_t NumberOfTestCases() const;
      virtual std::vector<TestClassResult> RunTestClasses(ZenUnitArgs& zenUnitArgs);
   private:
      static void MoveTestClassRunnerIfTestClassNameMatchesRunFilter(
         const std::unique_ptr<TestClassRunner>& testClassRunner, std::vector<std::unique_ptr<TestClassRunner>>* outRunFilteredTestClassRunners);
      virtual std::vector<TestClassResult> RunAllTestClasses(ZenUnitArgs& zenUnitArgs);
      virtual std::vector<TestClassResult> RunSpecifiedTestClassOrTest(ZenUnitArgs& zenUnitArgs);
      static TestClassResult RunTestClassRunner(const std::unique_ptr<TestClassRunner>& testClassRunner);
   };
}
