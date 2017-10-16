#include "pch.h"
#include "ZenUnit/Args/ZenUnitArgs.h"
#include "ZenUnit/TestRunners/MultiTestClassRunner.h"
#include "ZenUnit/TestRunners/NoOpTestClassRunner.h"
#include "ZenUnit/TestRunners/TestClassRunner.h"
#include "ZenUnit/Utils/Iteration/ExtraArgAnyer.h"
#include "ZenUnit/Utils/Iteration/ExtraArgMemberForEacher.h"
#include "ZenUnit/Utils/Iteration/Transformer.h"
#include "ZenUnit/Utils/StringUtil.h"
#include "ZenUnit/Utils/Sorter.h"
#include "ZenUnit/Utils/Time/Watch.h"

namespace ZenUnit
{
   MultiTestClassRunner::MultiTestClassRunner()
      : _extraArgMemberForEacher(new ExtraArgMemberForEacherType)
      , _extraArgAnyer(new ExtraArgAnyerType)
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
         _extraArgMemberForEacher->ExtraArgMemberForEach(&_testClassRunners, this,
            &MultiTestClassRunner::ResetTestClassRunnerWithNoOpIfNameDoesNotMatchRunFilter, runFilters);
      }
   }

   void MultiTestClassRunner::ResetTestClassRunnerWithNoOpIfNameDoesNotMatchRunFilter(
      std::unique_ptr<TestClassRunner>& testClassRunner, const std::vector<std::string>& runFilters)
   {
      const bool anyRunFilterMatchesTestClassName = _extraArgAnyer->ExtraArgAny(
         runFilters, TestClassMatchesRunFilter, &testClassRunner);
      if (!anyRunFilterMatchesTestClassName)
      {
         testClassRunner.reset(new NoOpTestClassRunner);
      }
   }

   bool MultiTestClassRunner::TestClassMatchesRunFilter(
      const std::string& runFilter, const std::unique_ptr<TestClassRunner>* testClassRunner)
   {
      const char* const testClassName = (*testClassRunner)->TestClassName();
      const bool testClassMatchesRunFilter = String::IgnoreCaseStrcmp(runFilter.c_str(), testClassName) == 0;
      return testClassMatchesRunFilter;
   }

   size_t MultiTestClassRunner::NumberOfTestClassesToBeRun() const
   {
      size_t numberOfTestClassesToBeRun = 0;
      for (const std::unique_ptr<TestClassRunner>& testClassRunner : _testClassRunners)
      {
         const char* const testClassName = testClassRunner->TestClassName();
         if (strcmp(testClassName, "NoOpTestClassRunner") != 0)
         {
            ++numberOfTestClassesToBeRun;
         }
      }
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
