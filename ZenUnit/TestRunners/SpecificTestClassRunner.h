#pragma once
#include "ZenUnit/Console/Console.h"
#include "ZenUnit/Results/TestResult.h"
#include "ZenUnit/TestRunners/TestClassRunner.h"
#include "ZenUnit/TestRunners/TestRunner.h"
#include "ZenUnit/Tests/NewDeleteTest.h"
#include "ZenUnit/Tests/Test.h"
#include "ZenUnit/Utils/Iteration/MemberForEacherExtraArg.h"
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
      using TestsMemberForEacherExtraArgType = MemberForEacherExtraArg<
         std::vector<std::unique_ptr<Test>>,
         SpecificTestClassRunner,
         void (SpecificTestClassRunner::*)(const std::unique_ptr<Test>& test, TestClassResult*) const, TestClassResult*>;
      std::unique_ptr<const TestsMemberForEacherExtraArgType> _testsMemberForEacherExtraArg;
      std::function<const ZenUnitArgs&()> _TestRunner_GetArgs_ZenMockable;
      const char* _testClassName;
      NewDeleteTest<TestClassType> _newDeleteTest;
      std::vector<std::unique_ptr<Test>> _tests;
      TestClassResult _testClassResult;
   public:
      explicit SpecificTestClassRunner(const char* testClassNamePossiblyTemplatized)
         : _console(new Console)
         , _testsMemberForEacherExtraArg(new TestsMemberForEacherExtraArgType)
         , _TestRunner_GetArgs_ZenMockable(TestRunner::GetArgs)
         , _testClassName(testClassNamePossiblyTemplatized)
         , _newDeleteTest(testClassNamePossiblyTemplatized)
      {
         _tests = TestClassType::GetTests(testClassNamePossiblyTemplatized);
      }

      const char* TestClassNameForSorting() const override
      {
         return _testClassName;
      }

      size_t NumberOfTestCases() const override
      {
         const size_t totalNumberOfTestCases = std::accumulate(_tests.cbegin(), _tests.cend(), size_t(),
            [](size_t cumulativeNumberOfTestCases, const std::unique_ptr<Test>& test)
            {
               size_t numberOfTestCases = test->NumberOfTestCases();
               return cumulativeNumberOfTestCases + numberOfTestCases;
            });
         return totalNumberOfTestCases;
      }

      TestClassResult RunTests() override
      {
         PrintTestClassNameAndNumberOfNamedTests();
         if (ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTests(&_newDeleteTest, &_testClassResult))
         {
            _testsMemberForEacherExtraArg->ForEach(
               &_tests, this, &SpecificTestClassRunner::RunTest, &_testClassResult);
         }
         PrintTestClassResultLine(&_testClassResult);
         _console->WriteNewline();
         return std::move(_testClassResult);
      }
   private:
      virtual void PrintTestClassNameAndNumberOfNamedTests() const
      {
         _console->WriteColor("@", Color::Green);
         _console->WriteColor(_testClassName, Color::Green);
         std::string spacePipeSpaceNumberOfNamedTests = String::Concat(
            " | ", _tests.size(), _tests.size() == 1 ? " named test" : " named tests");
         _console->WriteLine(spacePipeSpaceNumberOfNamedTests);
      }

      virtual bool ConfirmTestClassIsNewableAndDeletableAndRegisterNXNTests(
         Test* newDeleteTest, TestClassResult* outTestClassResult) const
      {
         const ZenUnitArgs& zenUnitArgs = _TestRunner_GetArgs_ZenMockable();
         _console->OptionallyWriteColor("|", Color::Green, !zenUnitArgs.minimal);
         static const std::string TestClassIsNewableAndDeletableString = "TestClassIsNewableAndDeletable -> ";
         _console->OptionallyWrite(TestClassIsNewableAndDeletableString, !zenUnitArgs.minimal);
         const std::vector<TestResult> newDeleteTestResult = newDeleteTest->Run();
         assert_true(newDeleteTestResult.size() == 1);
         outTestClassResult->AddTestResults(newDeleteTestResult);
         const bool testClassIsNewableAndDeletable = newDeleteTestResult[0].testOutcome == TestOutcome::Success;
         if (testClassIsNewableAndDeletable)
         {
            _console->OptionallyWriteLine("OK", !zenUnitArgs.minimal);
         }
         return testClassIsNewableAndDeletable;
      }

      void RunTest(const std::unique_ptr<Test>& test, TestClassResult* outTestClassResult) const
      {
         const ZenUnitArgs& zenUnitArgs = _TestRunner_GetArgs_ZenMockable();
         _console->OptionallyWriteColor("|", Color::Green, !zenUnitArgs.minimal);
         const char* const testName = test->Name();
         _console->OptionallyWrite(testName, !zenUnitArgs.minimal);
         test->OptionallyWritePostTestNameMessage(_console.get(), !zenUnitArgs.minimal);
         const std::vector<TestResult> testResults = test->Run();
         test->OptionallyWritePostTestCompletionMessage(_console.get(), testResults[0], !zenUnitArgs.minimal);
         outTestClassResult->AddTestResults(testResults);
      }

      virtual void PrintTestClassResultLine(const TestClassResult* testClassResult) const
      {
         testClassResult->PrintResultLine(_console.get());
      }
   };
}
