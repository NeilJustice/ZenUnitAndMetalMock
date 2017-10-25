#pragma once
#include "ZenUnit/Results/TestClassResult.h"

namespace ZenUnit
{
   struct ZenUnitArgs;
   class TestClassRunner;
   template<typename T, typename ClassType, typename FunctionType, typename ExtraArgType> class ExtraArgMemberForEacher;
   template<typename CollectionType, typename FunctionType, typename ExtraArgType> class ExtraArgAnyer;
   template<typename T, typename TransformedT> class Transformer;
   template<typename T> class Sorter;
   class Watch;

   class MultiTestClassRunner
   {
      friend class MultiTestClassRunnerTests;
   private:
      using ExtraArgMemberForEacherType = ExtraArgMemberForEacher<
         std::unique_ptr<TestClassRunner>,
         MultiTestClassRunner,
         void(MultiTestClassRunner::*)(std::unique_ptr<TestClassRunner>&, const std::vector<RunFilter>&),
         const std::vector<RunFilter>&>;
      std::unique_ptr<const ExtraArgMemberForEacherType> _extraArgMemberForEacher;

      using ExtraArgAnyerType = ExtraArgAnyer<
         std::vector<RunFilter>,
         bool(*)(const RunFilter&, const std::unique_ptr<TestClassRunner>*),
         const std::unique_ptr<TestClassRunner>*>;
      std::unique_ptr<const ExtraArgAnyerType> _extraArgAnyer;

      std::unique_ptr<const Sorter<std::vector<std::unique_ptr<TestClassRunner>>>> _sorter;
      std::unique_ptr<const Transformer<std::unique_ptr<TestClassRunner>, TestClassResult>> _transformer;
      std::unique_ptr<const Watch> _watch;
      std::vector<std::unique_ptr<TestClassRunner>> _testClassRunners;
      std::vector<TestClassResult> _testClassResults;
   public:
      MultiTestClassRunner();
      virtual ~MultiTestClassRunner();
      virtual void AddTestClassRunner(TestClassRunner* testClassRunner);
      virtual void ApplyRunFiltersIfAny(const std::vector<RunFilter>& runFilters);
      virtual size_t NumberOfTestClassesToBeRun() const;
      virtual size_t NumberOfTestCases() const;
      virtual std::vector<TestClassResult> RunTestClasses(ZenUnitArgs& zenUnitArgs);
   private:
      void ResetTestClassRunnerWithNoOpIfNameDoesNotMatchRunFilter(
         std::unique_ptr<TestClassRunner>& testClassRunner, const std::vector<RunFilter>& runFilters);
      static bool TestClassNameMatchesRunFilter(
         const RunFilter& runFilter, const std::unique_ptr<TestClassRunner>* testClassRunner);
      static TestClassResult RunTestClassRunner(const std::unique_ptr<TestClassRunner>& testClassRunner);
      static bool VectorCaseInsensitiveContains(
         const std::vector<std::string>& strings, const char* searchString);
   };
}
