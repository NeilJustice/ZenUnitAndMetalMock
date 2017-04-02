#pragma once
#include "ZenUnit/Tests/Test.h"
#include "ZenUnit/Console/Console.h"

namespace ZenUnit
{
   template<typename TestClassType, size_t N, typename... TestCaseArgTypes>
   class TestNXN : public Test
   {
      friend class TestNXNTests;
      static_assert(sizeof...(TestCaseArgTypes) > 0, "NumberOfTestCaseArgs > 0");
   private:
      const size_t NumberOfTestCaseArgs = sizeof...(TestCaseArgTypes);
      std::unique_ptr<const Console> _console;
      std::unique_ptr<TestClassType> _testClass;
      const char* const _testCaseArgsText;
      size_t _testCaseArgsIndex;
      std::vector<std::string> _testCaseArgStrings;
   protected:
      std::tuple<typename std::decay<TestCaseArgTypes>::type...> _testCaseArgs;
   public:
      TestNXN(
         const char* testClassName,
         const char* testName,
         const char* testCaseArgsText,
         TestCaseArgTypes&&... testCaseArgs)
         : Test(testClassName, testName)
         , _console(new Console)
         , _testCaseArgsText(testCaseArgsText)
         , _testCaseArgsIndex(0)
         , _testCaseArgStrings(String::CommaSplitExceptQuotedCommas(testCaseArgsText))
         , _testCaseArgs(std::forward<TestCaseArgTypes>(testCaseArgs)...)
      {
      }

      size_t NumberOfTestCases() const final
      {
         size_t numberOfTestCases = NumberOfTestCaseArgs / N;
         return numberOfTestCases;
      }

      std::vector<TestResult> Run() final
      {
         std::vector<TestResult> testResults;
         size_t numberOfTestCases = NumberOfTestCases();
         testResults.reserve(numberOfTestCases);
         assert_true(_testCaseArgsIndex == 0);
         for (int testCaseIndex = 0;
              _testCaseArgsIndex < NumberOfTestCaseArgs;
              _testCaseArgsIndex += N, ++testCaseIndex)
         {
            PrintTestCaseNumberArgsArrow(testCaseIndex);
            TestResult testResult = MockableCallBaseRunTestCase();
            testResult.testCaseIndex = testCaseIndex;
            testResults.push_back(testResult);
            PrintTestResultOutcome(testResult);
         }
         _testCaseArgsIndex = 0;
         return testResults;
      }

      void NewTestClass() final
      {
         _testClass = std::make_unique<TestClassType>();
      }

      void Startup() final
      {
         _testClass->Startup();
      }

      void TestBody() final
      {
         NXNTestBody(_testClass.get(), _testCaseArgsIndex);
      }
      virtual void NXNTestBody(TestClassType*, size_t) { throw std::logic_error("N/A"); }

      void Cleanup() final
      {
         _testClass->Cleanup();
      }

      void DeleteTestClass() final
      {
         _testClass.reset();
      }
   private:
      virtual TestResult MockableCallBaseRunTestCase()
      {
         TestResult testResult = RunTestCase();
         return testResult;
      }

      virtual void PrintTestCaseNumberArgsArrow(int testCaseIndex) const
      {
         assert_true(testCaseIndex >= 0);
         _console->WriteColor(" [", Color::Green);
         std::string testCaseNumber = std::to_string(testCaseIndex + 1);
         _console->Write(testCaseNumber);
         _console->WriteColor("]", Color::Green);
         _console->Write(" (");
         size_t testCaseArgsPrintingStartIndex = static_cast<size_t>(testCaseIndex) * N;
         _console->PrintStringsCommaSeparated(_testCaseArgStrings, testCaseArgsPrintingStartIndex, N);
         _console->Write(") -> ");
      }

      virtual void PrintTestResultOutcome(const TestResult& testResult) const
      {
         testResult.PrintTestOutcome(_console.get());
      }
   };
}
