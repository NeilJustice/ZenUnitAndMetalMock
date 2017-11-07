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
   INLINE MultiTestClassRunner::MultiTestClassRunner()
      : _extraArgMemberForEacher(new ExtraArgMemberForEacherType)
      , _extraArgAnyer(new ExtraArgAnyerType)
      , _sorter(new Sorter<std::vector<std::unique_ptr<TestClassRunner>>>)
      , _transformer(new Transformer<std::unique_ptr<TestClassRunner>, TestClassResult>)
      , _watch(new Watch)
   {
   }

   INLINE MultiTestClassRunner::~MultiTestClassRunner() = default;

   INLINE void MultiTestClassRunner::AddTestClassRunner(TestClassRunner* testClassRunner)
   {
      _testClassRunners.emplace_back(testClassRunner);
   }

   INLINE void MultiTestClassRunner::ApplyRunFiltersIfAny(const std::vector<RunFilter>& runFilters)
   {
      if (!runFilters.empty())
      {
         _extraArgMemberForEacher->ExtraArgMemberForEach(&_testClassRunners, this,
            &MultiTestClassRunner::ResetTestClassRunnerWithNoOpIfNameDoesNotMatchRunFilter, runFilters);
      }
   }

   INLINE void MultiTestClassRunner::ResetTestClassRunnerWithNoOpIfNameDoesNotMatchRunFilter(
      std::unique_ptr<TestClassRunner>& testClassRunner, const std::vector<RunFilter>& runFilters)
   {
      const bool anyRunFilterMatchesTestClassName = _extraArgAnyer->ExtraArgAny(
         runFilters, TestClassNameMatchesRunFilter, &testClassRunner);
      if (!anyRunFilterMatchesTestClassName)
      {
         testClassRunner.reset(new NoOpTestClassRunner);
      }
   }

   INLINE bool MultiTestClassRunner::TestClassNameMatchesRunFilter(
      const RunFilter& runFilter, const std::unique_ptr<TestClassRunner>* testClassRunner)
   {
      const char* const testClassName = (*testClassRunner)->TestClassName();
      const bool testClassMatchesRunFilter = String::IgnoreCaseStrcmp(testClassName, runFilter.testClassName.c_str()) == 0;
      return testClassMatchesRunFilter;
   }

   INLINE size_t MultiTestClassRunner::NumberOfTestClassesToBeRun() const
   {
      size_t numberOfTestClassesToBeRun = 0;
      for (const std::unique_ptr<TestClassRunner>& testClassRunner : _testClassRunners)
      {
         const char* const testClassName = testClassRunner->TestClassName();
         if (strcmp(testClassName, "FilteredOut") != 0)
         {
            ++numberOfTestClassesToBeRun;
         }
      }
      return numberOfTestClassesToBeRun;
   }

   INLINE size_t MultiTestClassRunner::NumberOfTestCases() const
   {
      const size_t numberOfTestCases = std::accumulate(_testClassRunners.cbegin(), _testClassRunners.cend(),
         size_t(0), [](size_t cumulativeNumberOfTestCases, const std::unique_ptr<TestClassRunner>& testClassRunner)
      {
         return cumulativeNumberOfTestCases + testClassRunner->NumberOfTestCases();
      });
      return numberOfTestCases;
   }

   INLINE std::vector<TestClassResult> MultiTestClassRunner::RunTestClasses(ZenUnitArgs& zenUnitArgs)
   {
      if (zenUnitArgs.random)
      {
         if (!zenUnitArgs.randomseedsetbyuser)
         {
            zenUnitArgs.randomseed = _watch->SecondsSince1970CastToUnsignedShort();
         }
         const std::vector<TestClassResult> testClassResults = _transformer->RandomTransform(
            &_testClassRunners, &MultiTestClassRunner::RunTestClassRunner, zenUnitArgs.randomseed);
         return testClassResults;
      }
      else
      {
         _sorter->Sort(&_testClassRunners); // Sort test class runners by test class name
         const std::vector<TestClassResult> testClassResults = _transformer->Transform(
            &_testClassRunners, &MultiTestClassRunner::RunTestClassRunner);
         return testClassResults;
      }
   }

   INLINE TestClassResult MultiTestClassRunner::RunTestClassRunner(
      const std::unique_ptr<TestClassRunner>& testClassRunner)
   {
      const TestClassResult testClassResult = testClassRunner->RunTests();
      return testClassResult;
   }
}
