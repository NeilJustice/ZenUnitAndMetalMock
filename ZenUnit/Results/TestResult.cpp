//#ifdef __linux__
//#include "ZenUnit/pch.h"
//#elif defined(_WIN64)
#include "pch.h"
//#endif
#include "ZenUnit/Console/Console.h"
#include "ZenUnit/Enums/TestOutcome.h"
#include "ZenUnit/Macros/ARE_EQUAL.h"
#include "ZenUnit/Results/AnomalyOrException.h"
#include "ZenUnit/Results/TestFailureNumberer.h"
#include "ZenUnit/Results/TestPhaseSuffixer.h"
#include "ZenUnit/Results/TestResult.h"
#include "ZenUnit/TestRunners/TestRunner.h"

namespace ZenUnit
{
   INLINE TestResult::TestResult()
      : responsibleCallResultField(nullptr)
      , testOutcome(TestOutcome::Unset)
      , milliseconds(0)
      , testCaseIndex(std::numeric_limits<unsigned short>::max())
   {
   }

   INLINE TestResult TestResult::ConstructorFail(
      const FullTestName& fullTestName,
      const CallResult& constructorCallResult)
   {
      TestResult constructorFailTestResult;
      constructorFailTestResult.fullTestName = fullTestName;
      constructorFailTestResult.constructorCallResult = constructorCallResult;
      constructorFailTestResult.testOutcome = constructorCallResult.testOutcome;
      constructorFailTestResult.milliseconds = constructorCallResult.milliseconds;
      constructorFailTestResult.responsibleCallResultField = &TestResult::constructorCallResult;
      return constructorFailTestResult;
   }

   INLINE TestResult TestResult::StartupFail(
      const FullTestName& fullTestName,
      const CallResult& constructorCallResult,
      const CallResult& startupCallResult,
      const CallResult& destructorCallResult)
   {
      assert_true(constructorCallResult.testOutcome == TestOutcome::Success);
      assert_true(destructorCallResult.testOutcome == TestOutcome::Success);
      TestResult startupFail;
      startupFail.fullTestName = fullTestName;
      startupFail.testOutcome = startupCallResult.testOutcome;
      startupFail.constructorCallResult = constructorCallResult;
      startupFail.startupCallResult = startupCallResult;
      startupFail.destructorCallResult = destructorCallResult;
      startupFail.milliseconds =
         constructorCallResult.milliseconds + startupCallResult.milliseconds + destructorCallResult.milliseconds;
      startupFail.responsibleCallResultField = &TestResult::startupCallResult;
      return startupFail;
   }

   INLINE TestResult TestResult::CtorDtorSuccess(
      const FullTestName& fullTestName,
      const CallResult& constructorCallResult,
      const CallResult& destructorCallResult)
   {
      assert_true(constructorCallResult.testOutcome == TestOutcome::Success);
      assert_true(destructorCallResult.testOutcome == TestOutcome::Success);
      TestResult ctorDtorSuccess;
      ctorDtorSuccess.fullTestName = fullTestName;
      ctorDtorSuccess.testOutcome = TestOutcome::Success;
      ctorDtorSuccess.constructorCallResult = constructorCallResult;
      ctorDtorSuccess.destructorCallResult = destructorCallResult;
      ctorDtorSuccess.milliseconds = constructorCallResult.milliseconds + destructorCallResult.milliseconds;
      ctorDtorSuccess.responsibleCallResultField = nullptr;
      return ctorDtorSuccess;
   }

   INLINE TestResult::TestResult(
      const FullTestName& fullTestName,
      const CallResult& constructorCallResult,
      const CallResult& startupCallResult,
      const CallResult& testBodyCallResult,
      const CallResult& cleanupCallResult,
      const CallResult& destructorCallResult,
      const std::function<const ZenUnitArgs&()>& getArgs)
      : fullTestName(fullTestName)
      , constructorCallResult(constructorCallResult)
      , startupCallResult(startupCallResult)
      , testBodyCallResult(testBodyCallResult)
      , cleanupCallResult(cleanupCallResult)
      , destructorCallResult(destructorCallResult)
      , responsibleCallResultField(nullptr)
      , testOutcome(TestOutcome::Unset)
      , milliseconds(0)
      , testCaseIndex(std::numeric_limits<unsigned short>::max())
   {
      assert_true(constructorCallResult.testOutcome == TestOutcome::Success);
      assert_true(startupCallResult.testOutcome == TestOutcome::Success);
      assert_true(destructorCallResult.testOutcome == TestOutcome::Success);
      milliseconds =
         constructorCallResult.milliseconds +
         startupCallResult.milliseconds +
         testBodyCallResult.milliseconds +
         cleanupCallResult.milliseconds +
         destructorCallResult.milliseconds;
      if (testBodyCallResult.testOutcome == TestOutcome::Exception)
      {
         testOutcome = TestOutcome::Exception;
         responsibleCallResultField = &TestResult::testBodyCallResult;
      }
      else if (cleanupCallResult.testOutcome == TestOutcome::Exception)
      {
         testOutcome = TestOutcome::Exception;
         responsibleCallResultField = &TestResult::cleanupCallResult;
      }
      else if (testBodyCallResult.testOutcome == TestOutcome::Anomaly)
      {
         testOutcome = TestOutcome::Anomaly;
         responsibleCallResultField = &TestResult::testBodyCallResult;
      }
      else if (cleanupCallResult.testOutcome == TestOutcome::Anomaly)
      {
         testOutcome = TestOutcome::Anomaly;
         responsibleCallResultField = &TestResult::cleanupCallResult;
      }
      else
      {
         assert_true(constructorCallResult.testOutcome == TestOutcome::Success);
         assert_true(startupCallResult.testOutcome == TestOutcome::Success);
         assert_true(testBodyCallResult.testOutcome == TestOutcome::Success);
         assert_true(cleanupCallResult.testOutcome == TestOutcome::Success);
         assert_true(destructorCallResult.testOutcome == TestOutcome::Success);
         const ZenUnitArgs& args = getArgs();
         if (args.maxtestmilliseconds == 0 || milliseconds <= args.maxtestmilliseconds)
         {
            testOutcome = TestOutcome::Success;
         }
         else
         {
            testOutcome = TestOutcome::SuccessButPastDeadline;
         }
      }
   }

   INLINE void TestResult::NonMinimalWriteLineOKIfSuccess(const Console* console, PrintMode printMode) const
   {
      if (printMode != PrintMode::Minimalist && testOutcome == TestOutcome::Success)
      {
         console->WriteLineColor("OK", Color::White);
      }
   }

   INLINE void TestResult::PrintIfFailure(const Console* console, TestFailureNumberer* testFailureNumberer) const
   {
      switch (testOutcome)
      {
      case TestOutcome::Success:
      {
         break;
      }
      case TestOutcome::Anomaly:
      {
         const std::string testFailureNumber = testFailureNumberer->Next();
         console->WriteLineColor(testFailureNumber, Color::Red);
         console->Write(fullTestName.Value());
         const CallResult& responsibleCallResult = (this->*responsibleCallResultField);
         const char* const responsibleTestPhaseSuffix =
            TestPhaseSuffixer::DoTestPhaseToTestPhaseSuffix(responsibleCallResult.testPhase);
         console->Write(responsibleTestPhaseSuffix);
         WriteTestCaseNumberIfAny(console, testCaseIndex);
         responsibleCallResult.anomalyOrException->anomaly->WriteLineWhy(console);
         console->WriteNewLine();
         break;
      }
      case TestOutcome::Exception:
      {
         const std::string testFailureNumber = testFailureNumberer->Next();
         console->WriteLineColor(testFailureNumber, Color::Red);
         console->Write(fullTestName.Value());
         const CallResult& responsibleCallResult = this->*responsibleCallResultField;
         const char* const responsibleTestPhaseSuffix =
            TestPhaseSuffixer::DoTestPhaseToTestPhaseSuffix(responsibleCallResult.testPhase);
         console->Write(responsibleTestPhaseSuffix);
         WriteTestCaseNumberIfAny(console, testCaseIndex);
         console->WriteLineColor("\nUncaught Exception", Color::Red);
         const std::string exceptionTypeAndWhatLines = String::Concat(
            "  Type: ", *responsibleCallResult.anomalyOrException->exceptionTypeName, '\n',
            "what(): \"", *responsibleCallResult.anomalyOrException->exceptionWhat, "\"");
         console->WriteLine(exceptionTypeAndWhatLines);
         console->WriteNewLine();
         break;
      }
      default:
      {
         assert_true(testOutcome == TestOutcome::SuccessButPastDeadline);
         const std::string testFailureNumber = testFailureNumberer->Next();
         console->WriteLineColor(testFailureNumber, Color::Red);
         console->WriteLine(fullTestName.Value());
         WriteTestCaseNumberIfAny(console, testCaseIndex);
         console->WriteLine(String::Concat(
            "\nFailed because test took longer than -maxtestms= (", milliseconds, " ms)"));
         console->WriteNewLine();
         break;
      }
      }
   }

   INLINE void TestResult::WriteTestCaseNumberIfAny(
      const Console* console, unsigned short testCaseIndexArgument) const
   {
      if (testCaseIndexArgument != std::numeric_limits<unsigned short>::max())
      {
         console->Write(" test case " + std::to_string(testCaseIndexArgument + 1));
      }
   }

   INLINE const TestResult TestResult::TestingNonDefault()
   {
      return TestResult::ConstructorFail(FullTestName("Non", "Default", 0), CallResult());
   }
}

INLINE void ZenUnitEqualizer<ZenUnit::TestResult>::
AssertEqual(const ZenUnit::TestResult& expectedTestResult, const ZenUnit::TestResult& actualTestResult)
{
   ARE_EQUAL(expectedTestResult.fullTestName, actualTestResult.fullTestName);
   ARE_EQUAL(expectedTestResult.constructorCallResult, actualTestResult.constructorCallResult);
   ARE_EQUAL(expectedTestResult.startupCallResult, actualTestResult.startupCallResult);
   ARE_EQUAL(expectedTestResult.testBodyCallResult, actualTestResult.testBodyCallResult);
   ARE_EQUAL(expectedTestResult.cleanupCallResult, actualTestResult.cleanupCallResult);
   ARE_EQUAL(expectedTestResult.destructorCallResult, actualTestResult.destructorCallResult);
   ARE_EQUAL(expectedTestResult.responsibleCallResultField, actualTestResult.responsibleCallResultField);
   ARE_EQUAL(expectedTestResult.testOutcome, actualTestResult.testOutcome);
   ARE_EQUAL(expectedTestResult.testCaseIndex, actualTestResult.testCaseIndex);
   ARE_EQUAL(expectedTestResult.milliseconds, actualTestResult.milliseconds);
}
