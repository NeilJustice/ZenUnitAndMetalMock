#pragma once
#include "ZenUnit/Console/Console.h"
#include "ZenUnit/Results/TestResult.h"
#include "ZenUnit/TestRunners/TestClassRunner.h"
#include "ZenUnit/TestRunners/TestRunner.h"
#include "ZenUnit/Tests/NewDeleteTest.h"
#include "ZenUnit/Tests/Test.h"
#include "ZenUnit/Utils/Iteration/ExtraArgMemberForEacher.h"
#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable: 4365) // signed / unsigned mismatch
#endif
#include <numeric>
#ifdef _WIN32
#pragma warning(pop)
#endif

namespace ZenUnit
{
   template<typename TestClassType>
   class SpecificTestClassRunner : public TestClassRunner
   {
      friend class SpecificTestClassRunnerTests;
   private:
      std::unique_ptr<const Console> _console;
      using ExtraArgMemberForEacherType = ExtraArgMemberForEacher<
         std::unique_ptr<Test>,
         SpecificTestClassRunner,
         void (SpecificTestClassRunner::*)(const std::unique_ptr<Test>& test, TestClassResult*) const,
         TestClassResult*>;
      std::unique_ptr<const ExtraArgMemberForEacherType> _extraArgMemberForEacher;
      std::function<const ZenUnitArgs&()> call_TestRunner_GetArgs;
      const char* _testClassName;
      NewDeleteTest<TestClassType> _newDeleteTest;
      std::vector<std::unique_ptr<Test>> _tests;
      TestClassResult _testClassResult;
   public:
      explicit SpecificTestClassRunner(const char* testClassNamePossiblyTemplatized)
         : _console(new Console)
         , _extraArgMemberForEacher(new ExtraArgMemberForEacherType)
         , call_TestRunner_GetArgs(TestRunner::GetArgs)
         , _testClassName(testClassNamePossiblyTemplatized)
         , _newDeleteTest(testClassNamePossiblyTemplatized)
      {
         _tests = TestClassType::GetTests(testClassNamePossiblyTemplatized);
      }

      const char* TestClassName() const override
      {
         return _testClassName;
      }

      bool HasTestNameThatCaseInsensitiveMatchesPattern(const std::string& testNamePattern) const override
      {
         for (const std::unique_ptr<Test>& test : _tests)
         {
            const char* const containedTestName = test->Name();
            if (String::IgnoreCaseStrcmp(containedTestName, testNamePattern.c_str()) == 0)
            {
               return true;
            }
         }
         return false;
      }

      size_t NumberOfTestCases() const override
      {
         const size_t totalNumberOfTestCases = std::accumulate(_tests.cbegin(), _tests.cend(), size_t(),
            [](size_t cumulativeNumberOfTestCases, const std::unique_ptr<Test>& test)
            {
               const size_t numberOfTestCases = test->NumberOfTestCases();
               return cumulativeNumberOfTestCases + numberOfTestCases;
            });
         return totalNumberOfTestCases;
      }

      TestClassResult RunTests() override
      {
         NonMinimalPrintTestClassNameAndNumberOfNamedTests();
         if (ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTests(&_newDeleteTest, &_testClassResult))
         {
             DoRunTests();
         }
         const ZenUnitArgs& zenUnitArgs = call_TestRunner_GetArgs();
         NonMinimalPrintResultLine(&_testClassResult, zenUnitArgs.printMode);
         _console->NonMinimalWriteNewLine(zenUnitArgs.printMode);
         return std::move(_testClassResult);
      }
   private:
      virtual void DoRunTests()
      {
         const ZenUnitArgs& zenUnitArgs = call_TestRunner_GetArgs();
         if (zenUnitArgs.random)
         {
            _extraArgMemberForEacher->RandomExtraArgMemberForEach(
               &_tests, this, &SpecificTestClassRunner::RunTest, &_testClassResult, zenUnitArgs.randomseed);
         }
         else
         {
            _extraArgMemberForEacher->ExtraArgMemberForEach(
               &_tests, this, &SpecificTestClassRunner::RunTest, &_testClassResult);
         }
      }

      virtual void NonMinimalPrintTestClassNameAndNumberOfNamedTests() const
      {
         const ZenUnitArgs& zenUnitArgs = call_TestRunner_GetArgs();
         _console->NonMinimalWriteColor("@", Color::Green, zenUnitArgs.printMode);
         _console->NonMinimalWriteColor(_testClassName, Color::Green, zenUnitArgs.printMode);
         const std::string spacePipeSpaceNumberOfNamedTests = String::Concat(
            " | ", _tests.size(), _tests.size() == 1 ? " named test" : " named tests");
         _console->NonMinimalWriteLine(spacePipeSpaceNumberOfNamedTests, zenUnitArgs.printMode);
      }

      virtual bool ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTests(
         Test* newDeleteTest, TestClassResult* outTestClassResult) const
      {
         const ZenUnitArgs& zenUnitArgs = call_TestRunner_GetArgs();
         _console->NonMinimalWriteColor("|", Color::Green, zenUnitArgs.printMode);
         static const std::string TestClassIsNewableAndDeletableString = "TestClassIsNewableAndDeletable -> ";
         _console->NonMinimalWrite(TestClassIsNewableAndDeletableString, zenUnitArgs.printMode);
         const std::vector<TestResult> newDeleteTestResult = newDeleteTest->Run();
         assert_true(newDeleteTestResult.size() == 1);
         outTestClassResult->AddTestResults(newDeleteTestResult);
         const bool testClassIsNewableAndDeletable = newDeleteTestResult[0].testOutcome == TestOutcome::Success;
         if (testClassIsNewableAndDeletable)
         {
            _console->NonMinimalWriteLine("OK", zenUnitArgs.printMode);
         }
         return testClassIsNewableAndDeletable;
      }

      void RunTest(const std::unique_ptr<Test>& test, TestClassResult* outTestClassResult) const
      {
         const ZenUnitArgs& zenUnitArgs = call_TestRunner_GetArgs();
         _console->NonMinimalWriteColor("|", Color::Green, zenUnitArgs.printMode);
         const char* const testName = test->Name();
         _console->NonMinimalWrite(testName, zenUnitArgs.printMode);
         test->NonMinimalWritePostTestNameMessage(_console.get(), zenUnitArgs.printMode);
         const std::vector<TestResult> testResults = test->Run();
         test->NonMinimalWritePostTestCompletionMessage(_console.get(), testResults[0], zenUnitArgs.printMode);
         outTestClassResult->AddTestResults(testResults);
      }

      virtual void NonMinimalPrintResultLine(const TestClassResult* testClassResult, PrintMode printMode) const
      {
         testClassResult->NonMinimalPrintResultLine(_console.get(), printMode);
      }
   };
}
