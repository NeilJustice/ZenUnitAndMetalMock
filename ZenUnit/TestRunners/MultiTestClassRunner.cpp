#include "pch.h"
#include "ZenUnit/Args/ZenUnitArgs.h"
#include "ZenUnit/TestRunners/MultiTestClassRunner.h"
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
      _allTestClassRunners.emplace_back(testClassRunner);
   }

   void MultiTestClassRunner::ApplyRunFiltersIfAny(const std::vector<std::string>& runFilters)
   {
      if (!runFilters.empty())
      {
         _extraArgForEacher->ForEach(
            &_allTestClassRunners,
            MoveTestClassRunnerIfTestClassNameMatchesRunFilter,
            &_runFilteredTestClassRunners);
      }
   }

   void MultiTestClassRunner::MoveTestClassRunnerIfTestClassNameMatchesRunFilter(
      const std::unique_ptr<TestClassRunner>& testClassRunner,
      std::vector<std::unique_ptr<TestClassRunner>>* outRunFilteredTestClassRunners)
   {
      std::string();
   }

   size_t MultiTestClassRunner::NumberOfTestClassesToBeRun() const
   {
      const size_t numberOfTestClassesToBeRun = _allTestClassRunners.size();
      return numberOfTestClassesToBeRun;
   }

   size_t MultiTestClassRunner::NumberOfTestCases() const
   {
      const size_t numberOfTestCases = std::accumulate(_allTestClassRunners.cbegin(), _allTestClassRunners.cend(),
         size_t(0), [](size_t cumulativeNumberOfTestCases, const std::unique_ptr<TestClassRunner>& testClassRunner)
      {
         return cumulativeNumberOfTestCases + testClassRunner->NumberOfTestCases();
      });
      return numberOfTestCases;
   }

   std::vector<TestClassResult> MultiTestClassRunner::RunTestClasses(ZenUnitArgs& zenUnitArgs)
   {
      if (zenUnitArgs.runFilters.empty())
      {
         return RunAllTestClasses(zenUnitArgs);
      }
      else
      {
         return RunSpecifiedTestClassOrTest(zenUnitArgs);
      }
   }

   std::vector<TestClassResult> MultiTestClassRunner::RunAllTestClasses(ZenUnitArgs& zenUnitArgs)
   {
      _testClassResults.resize(_allTestClassRunners.size());
      if (zenUnitArgs.random)
      {
         if (!zenUnitArgs.randomseedsetbyuser)
         {
            zenUnitArgs.randomseed = _watch->SecondsSince1970CastToUnsignedShort();
         }
         _transformer->RandomTransform(
            &_allTestClassRunners, &_testClassResults, &MultiTestClassRunner::RunTestClassRunner, zenUnitArgs.randomseed);
      }
      else
      {
         _sorter->Sort(&_allTestClassRunners); // Sorts test class runners by test class name
         _transformer->Transform(
            &_allTestClassRunners, &_testClassResults, &MultiTestClassRunner::RunTestClassRunner);
      }
      return std::move(_testClassResults);
   }

   std::vector<TestClassResult> MultiTestClassRunner::RunSpecifiedTestClassOrTest(ZenUnitArgs& zenUnitArgs)
   {
      size_t numberOfTestsMatchingRunFilter = 0;
      //_testClassResults.resize(numberOfTestsMatchingRunFilter)
      if (numberOfTestsMatchingRunFilter == 0)
      {
      }
      //else if (numberOfTestsMatchingRunFilter == 1)
      //{
      //}
      //else
      //{
      //}
      return {};
   }

   TestClassResult MultiTestClassRunner::RunTestClassRunner(
      const std::unique_ptr<TestClassRunner>& testClassRunner)
   {
      TestClassResult testClassResult = testClassRunner->RunTests();
      return testClassResult;
   }
}
