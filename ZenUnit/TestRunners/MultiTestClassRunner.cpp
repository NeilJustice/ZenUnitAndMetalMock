#include "pch.h"
#include "ZenUnit/Args/ZenUnitArgs.h"
#include "ZenUnit/TestRunners/MultiTestClassRunner.h"
#include "ZenUnit/TestRunners/NoOpTestClassRunner.h"
#include "ZenUnit/TestRunners/TestClassRunner.h"
#include "ZenUnit/Utils/Iteration/ExtraArgForEacher.h"
#include "ZenUnit/Utils/Iteration/Transformer.h"
#include "ZenUnit/Utils/Sorter.h"
#include "ZenUnit/Utils/Time/Watch.h"

namespace ZenUnit
{
   MultiTestClassRunner::MultiTestClassRunner()
      : _extraArgForEacher(new ExtraArgForEacherType)
      , _sorter(new Sorter<std::vector<std::unique_ptr<TestClassRunner>>>)
      , _transformer(new Transformer<std::unique_ptr<TestClassRunner>, TestClassResult>)
      , _watch(new Watch)
   {
   }

   MultiTestClassRunner::~MultiTestClassRunner() = default;

   void MultiTestClassRunner::AddTestClassRunner(TestClassRunner* testClassRunner)
   {
      _testClassRunners.emplace_back(testClassRunner);
   }

   void MultiTestClassRunner::ApplyRunFiltersIfSpecified(const std::vector<std::string>& runFilters)
   {
      if (!runFilters.empty())
      {
         _extraArgForEacher->NonConstExtraArgForEach(
            &_testClassRunners, ResetWithNoOpIfNameDoesNotMatchRunFilter, runFilters);
      }
   }

   bool MultiTestClassRunner::ResetWithNoOpIfNameDoesNotMatchRunFilter(
      std::unique_ptr<TestClassRunner>& testClassRunner,
      const std::vector<std::string>& runFilters)
   {
      //const char* const testClassRunnerName = testClassRunner->TestClassName();
      //bool anyRunFilterMatchesTestClassName = _extraArgAny->ExtraArgAny(
      //   runFilters, TestClassRunnerNameMatchesRunFilter, testClassRunnerName);
      // if (!anyRunFilterMatchesTestClassName)
      // {
      //    testClassRunner.reset(new NoOpTestClassRunner);
      // }
      return false;
   }

   bool MultiTestClassRunner::TestClassNameMatchesAnyRunFilter(
      const std::unique_ptr<TestClassRunner>& testClassRunner, const std::vector<std::string>& runFilters)
   {
      // for (const std::string& runFilter : runFilters)
      // {
      //    if (_strcmpi(runFilter.c_str(), testClassRunnerName) == 0)
      //    {
      //       return true;
      //    }
      // }
      return false;
   }

   size_t MultiTestClassRunner::NumberOfTestClassesToBeRun() const
   {
      const size_t numberOfTestClassesToBeRun = _testClassRunners.size();
      return numberOfTestClassesToBeRun;
   }

   size_t MultiTestClassRunner::NumberOfTestCases() const
   {
      const size_t numberOfTestCases = std::accumulate(_testClassRunners.cbegin(), _testClassRunners.cend(),
         size_t(0), [](size_t cumulativeNumberOfTestCases, const std::unique_ptr<TestClassRunner>& testClassRunner)
      {
         return cumulativeNumberOfTestCases + testClassRunner->NumberOfTestCases();
      });
      return numberOfTestCases;
   }

   std::vector<TestClassResult> MultiTestClassRunner::RunTestClasses(ZenUnitArgs& zenUnitArgs)
   {
      _testClassResults.resize(_testClassRunners.size());
      if (zenUnitArgs.random)
      {
         if (!zenUnitArgs.randomseedsetbyuser)
         {
            zenUnitArgs.randomseed = _watch->SecondsSince1970CastToUnsignedShort();
         }
         _transformer->RandomTransform(&_testClassRunners, &_testClassResults,
            &MultiTestClassRunner::RunTestClassRunner, zenUnitArgs.randomseed);
      }
      else
      {
         _sorter->Sort(&_testClassRunners); // Sort test class runners by test class name
         _transformer->Transform(&_testClassRunners, &_testClassResults,
            &MultiTestClassRunner::RunTestClassRunner);
      }
      return std::move(_testClassResults);
   }

   TestClassResult MultiTestClassRunner::RunTestClassRunner(
      const std::unique_ptr<TestClassRunner>& testClassRunner)
   {
      const TestClassResult testClassResult = testClassRunner->RunTests();
      return testClassResult;
   }
}
