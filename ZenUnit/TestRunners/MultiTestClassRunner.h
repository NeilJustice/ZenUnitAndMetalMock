#pragma once
#include "ZenUnit/Results/TestClassResult.h"

namespace ZenUnit
{
   struct ZenUnitArgs;
   class TestClassRunner;
   template<typename CollectionType, typename FunctionType, typename ExtraArgType> class ExtraArgForEacher;
   //template<typename CollectionType, typename FunctionType, typename ExtraArgType> class ExtraArgAny;
   template<typename T, typename TransformedT> class Transformer;
   template<typename T> class Sorter;
   class Watch;

   class MultiTestClassRunner
   {
      friend class MultiTestClassRunnerTests;
   private:
      using ExtraArgForEacherType = ExtraArgForEacher<
         std::vector<std::unique_ptr<TestClassRunner>>,
         bool(*)(std::unique_ptr<TestClassRunner>&, const std::vector<std::string>&),
         const std::vector<std::string>&>;
      std::unique_ptr<const ExtraArgForEacherType> _extraArgForEacher;

      //using ExtraArgAnyType = ExtraArgAny<
      //   std::unique_ptr<TestClassRunner>,
      //   decltype(TestClassNameMatchesAnyRunFilter),
      //   const std::vector<std::string>&>;

      std::unique_ptr<const Sorter<std::vector<std::unique_ptr<TestClassRunner>>>> _sorter;
      std::unique_ptr<const Transformer<std::unique_ptr<TestClassRunner>, TestClassResult>> _transformer;
      std::unique_ptr<const Watch> _watch;
      std::vector<std::unique_ptr<TestClassRunner>> _testClassRunners;
      std::vector<TestClassResult> _testClassResults;
   public:
      MultiTestClassRunner();
      virtual ~MultiTestClassRunner();
      virtual void AddTestClassRunner(TestClassRunner* testClassRunner);
      virtual void ApplyRunFiltersIfSpecified(const std::vector<std::string>& runFilters);
      virtual size_t NumberOfTestClassesToBeRun() const;
      virtual size_t NumberOfTestCases() const;
      virtual std::vector<TestClassResult> RunTestClasses(ZenUnitArgs& zenUnitArgs);
   private:
      static bool ResetWithNoOpIfNameDoesNotMatchRunFilter(
         std::unique_ptr<TestClassRunner>& testClassRunner,
         const std::vector<std::string>& runFilters);
      static bool TestClassNameMatchesAnyRunFilter(
         const std::unique_ptr<TestClassRunner>& testClassRunner, const std::vector<std::string>& runFilters);
      static TestClassResult RunTestClassRunner(const std::unique_ptr<TestClassRunner>& testClassRunner);
      static bool VectorCaseInsensitiveContains(
         const std::vector<std::string>& strings, const char* searchString);
   };
}
