#pragma once
#include "ZenUnit/Console/Console.h"
#include "ZenUnit/Tests/Test.h"

namespace ZenUnit
{
   template<typename TestClassType, size_t N, typename... TestCaseArgTypes>
   class TestNXN : public Test
   {
      friend class TestNXNTests;
   private:
      std::unique_ptr<const Console> _console;
      std::function<const ZenUnitArgs&()> _TestRunner_GetArgs_ZenMockable;
      std::unique_ptr<TestClassType> _testClass;
      const char* const _testCaseArgsText;
      std::function<std::vector<std::string>(const char*)> _String_CommaSplitExceptQuotedCommas;
      size_t _testCaseArgsIndex;
   protected:
      const std::tuple<typename std::decay<TestCaseArgTypes>::type...> _testCaseArgs;
   public:
      TestNXN(
         const char* testClassName,
         const char* testName,
         const char* testCaseArgsText,
         TestCaseArgTypes&&... testCaseArgs)
         : Test(testClassName, testName, N)
         , _console(new Console)
         , _TestRunner_GetArgs_ZenMockable(TestRunner::GetArgs)
         , _testCaseArgsText(testCaseArgsText)
         , _String_CommaSplitExceptQuotedCommas(String::CommaSplitExceptQuotedCommas)
         , _testCaseArgsIndex(0)
         , _testCaseArgs(std::forward<TestCaseArgTypes>(testCaseArgs)...)
      {
      }

      size_t NumberOfTestCases() const override
      {
         constexpr size_t numberOfTestCases = sizeof...(TestCaseArgTypes) / N;
         return numberOfTestCases;
      }

      void NewTestClass() override
      {
         _testClass = std::make_unique<TestClassType>();
      }

      void Startup() override
      {
         _testClass->Startup();
      }

      void TestBody() override
      {
         RunNXNTestCase(_testClass.get(), _testCaseArgsIndex);
      }

      virtual void RunNXNTestCase(TestClassType*, size_t)
      {
      }

      std::vector<TestResult> Run() override
      {
         std::vector<TestResult> testResults;
         const size_t numberOfTestCases = NumberOfTestCases();
         testResults.reserve(numberOfTestCases);
         assert_true(_testCaseArgsIndex == 0);
         std::vector<std::string> splitTestCaseArgs = _String_CommaSplitExceptQuotedCommas(_testCaseArgsText);
         const ZenUnitArgs& zenUnitArgs = _TestRunner_GetArgs_ZenMockable();
         constexpr size_t NumberOfTestCaseArgs = sizeof...(TestCaseArgTypes);
         for (unsigned short testCaseIndex = 0;
              _testCaseArgsIndex < NumberOfTestCaseArgs;
              _testCaseArgsIndex += N, ++testCaseIndex)
         {
            PrintTestCaseNumberArgsThenArrow(testCaseIndex, splitTestCaseArgs, zenUnitArgs);
            TestResult testResult = MockableCallBaseRunTestCase();
            testResult.testCaseIndex = testCaseIndex;
            testResults.push_back(testResult);
            OptionallyWriteOKIfTestPassed(testResult, !zenUnitArgs.abridged);
         }
         _testCaseArgsIndex = 0;
         return testResults;
      }

      void Cleanup() override
      {
         _testClass->Cleanup();
      }

      void DeleteTestClass() override
      {
         _testClass.reset();
      }
   private:
      virtual TestResult MockableCallBaseRunTestCase()
      {
         const TestResult testResult = RunTestCase();
         return testResult;
      }

      virtual void PrintTestCaseNumberArgsThenArrow(
         unsigned short testCaseIndex, const std::vector<std::string>& splitTestCaseArgs, const ZenUnitArgs& zenUnitArgs) const
      {
         assert_true(testCaseIndex >= 0);
         _console->OptionallyWriteColor(" [", Color::Green, !zenUnitArgs.abridged);
         const std::string testCaseNumber = std::to_string(testCaseIndex + 1);
         _console->OptionallyWrite(testCaseNumber, !zenUnitArgs.abridged);
         _console->OptionallyWriteColor("]", Color::Green, !zenUnitArgs.abridged);
         _console->OptionallyWrite(" (", !zenUnitArgs.abridged);
         const size_t testCaseArgsPrintingStartIndex = static_cast<size_t>(testCaseIndex) * N;
         _console->OptionallyWriteStringsCommaSeparated(
            splitTestCaseArgs, testCaseArgsPrintingStartIndex, N, !zenUnitArgs.abridged);
         _console->OptionallyWrite(") -> ", !zenUnitArgs.abridged);
      }

      virtual void OptionallyWriteOKIfTestPassed(const TestResult& testResult, bool doPrintOK) const
      {
         testResult.OptionallyWriteOKIfTestPassed(_console.get(), doPrintOK);
      }
   };
}
