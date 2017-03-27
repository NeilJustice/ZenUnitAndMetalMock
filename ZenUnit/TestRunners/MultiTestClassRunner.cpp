#include "pch.h"
#include "ZenUnit/TestRunners/MultiTestClassRunner.h"
#include "ZenUnit/TestRunners/TestClassRunner.h"
#include "ZenUnit/Utils/Sorter.h"
#include "ZenUnit/Utils/Iteration/Transformer.h"

namespace ZenUnit
{
   MultiTestClassRunner::MultiTestClassRunner()
      : _transformer(new Transformer<
         vector<unique_ptr<TestClassRunner>>::const_iterator,
         vector<TestClassResult>,
         TestClassResult(*)(const unique_ptr<TestClassRunner>&)>)
      , _sorter(new Sorter<decltype(_testClassRunners)>)
   {
   }

   MultiTestClassRunner::~MultiTestClassRunner()
   {
   }

   size_t MultiTestClassRunner::NumberOfTestClasses() const
   {
      const size_t numberOfTestClasses = _testClassRunners.size();
      return numberOfTestClasses;
   }

   size_t MultiTestClassRunner::TotalNumberOfTestCases() const
   {
      const size_t numberOfTestCases = std::accumulate(_testClassRunners.cbegin(), _testClassRunners.cend(),
         size_t(0), [](size_t cumulativeNumberOfTestCases, const unique_ptr<TestClassRunner>& testClassRunner)
      {
         return cumulativeNumberOfTestCases + testClassRunner->NumberOfTestCases();
      });
      return numberOfTestCases;
   }

   void MultiTestClassRunner::AddTestClassRunner(TestClassRunner* testClassRunner)
   {
      _testClassRunners.emplace_back(testClassRunner);
   }

   vector<TestClassResult> MultiTestClassRunner::RunTestClasses()
   {
      _sorter->Sort(&_testClassRunners);
      _testClassResults.resize(_testClassRunners.size());
      _transformer->Transform(_testClassRunners.cbegin(), _testClassRunners.cend(),
         &_testClassResults, &MultiTestClassRunner::RunTestClassRunner);
      return std::move(_testClassResults);
   }

   TestClassResult MultiTestClassRunner::RunTestClassRunner(const unique_ptr<TestClassRunner>& testClassRunner)
   {
      const TestClassResult testClassResult = testClassRunner->RunTests();
      return testClassResult;
   }
}
