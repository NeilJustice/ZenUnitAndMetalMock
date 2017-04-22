#include "pch.h"
#include "TestResult.h"
#include "ZenUnit/Console/Console.h"
#include "ZenUnit/Macros/ARE_EQUAL.h"
#include "ZenUnit/Results/TestFailureNumberer.h"
#include "ZenUnit/TestRunners/TestRunner.h"

namespace ZenUnit
{
   TestResult::TestResult()
      : testCaseIndex(-1)
      , responsibleCallResultField(nullptr)
      , testOutcome(TestOutcome::Unset)
      , milliseconds(0)
   {
   }

   TestResult TestResult::ConstructorFail(
      const FullName& fullName,
      const CallResult& constructorCallResult)
   {
      TestResult constructorFailTestResult;
      constructorFailTestResult.fullName = fullName;
      constructorFailTestResult.constructorCallResult = constructorCallResult;
      constructorFailTestResult.testOutcome = constructorCallResult.testOutcome;
      constructorFailTestResult.milliseconds = constructorCallResult.milliseconds;
      constructorFailTestResult.responsibleCallResultField = &TestResult::constructorCallResult;
      return constructorFailTestResult;
   }

   TestResult TestResult::StartupFail(
      const FullName& fullName,
      const CallResult& constructorCallResult,
      const CallResult& startupCallResult,
      const CallResult& destructorCallResult)
   {
      assert_true(constructorCallResult.testOutcome == TestOutcome::Success);
      assert_true(destructorCallResult.testOutcome == TestOutcome::Success);
      TestResult startupFail;
      startupFail.fullName = fullName;
      startupFail.testOutcome = startupCallResult.testOutcome;
      startupFail.constructorCallResult = constructorCallResult;
      startupFail.startupCallResult = startupCallResult;
      startupFail.destructorCallResult = destructorCallResult;
      startupFail.milliseconds =
         constructorCallResult.milliseconds + startupCallResult.milliseconds + destructorCallResult.milliseconds;
      startupFail.responsibleCallResultField = &TestResult::startupCallResult;
      return startupFail;
   }

   TestResult TestResult::CtorDtorSuccess(
      const FullName& fullName,
      const CallResult& constructorCallResult,
      const CallResult& destructorCallResult)
   {
      assert_true(constructorCallResult.testOutcome == TestOutcome::Success);
      assert_true(destructorCallResult.testOutcome == TestOutcome::Success);
      TestResult ctorDtorSuccess;
      ctorDtorSuccess.fullName = fullName;
      ctorDtorSuccess.testOutcome = TestOutcome::Success;
      ctorDtorSuccess.constructorCallResult = constructorCallResult;
      ctorDtorSuccess.destructorCallResult = destructorCallResult;
      ctorDtorSuccess.milliseconds = constructorCallResult.milliseconds + destructorCallResult.milliseconds;
      ctorDtorSuccess.responsibleCallResultField = nullptr;
      return ctorDtorSuccess;
   }

   TestResult::TestResult(
      const FullName& fullName,
      const CallResult& constructorCallResult,
      const CallResult& startupCallResult,
      const CallResult& testBodyCallResult,
      const CallResult& cleanupCallResult,
      const CallResult& destructorCallResult,
      const function<ZenUnitArgs()>& getArgs)
      : fullName(fullName)
      , testCaseIndex(-1)
      , constructorCallResult(constructorCallResult)
      , startupCallResult(startupCallResult)
      , testBodyCallResult(testBodyCallResult)
      , cleanupCallResult(cleanupCallResult)
      , destructorCallResult(destructorCallResult)
      , responsibleCallResultField(nullptr)
      , testOutcome(TestOutcome::Unset)
      , milliseconds(0)
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
         const ZenUnitArgs args = getArgs();
         if (args.maxtestmilliseconds == 0 || milliseconds <= args.maxtestmilliseconds)
         {
            testOutcome = TestOutcome::Success;
         }
         else
         {
            testOutcome = TestOutcome::SuccessButMissedDeadline;
         }
      }
   }

   void TestResult::PrintTestOutcome(const Console* console) const
   {
      switch (testOutcome)
      {
      case TestOutcome::Success:
      {
         console->WriteLineColor("OK", Color::White);
         break;
      }
      case TestOutcome::Anomaly:
      {
         console->WriteLineColor("Anomaly", Color::Red);
         break;
      }
      case TestOutcome::Exception:
      {
         console->WriteLineColor("Exception", Color::Red);
         break;
      }
      default:
      {
         assert_true(testOutcome == TestOutcome::SuccessButMissedDeadline);
         console->WriteLineColor("SuccessButMissedDeadline", Color::Red);
      }
      }
   }

   void TestResult::PrintIfFailure(const Console* console, TestFailureNumberer* testFailureNumberer) const
   {
      switch (testOutcome)
      {
      case TestOutcome::Success:
      {
         break;
      }
      case TestOutcome::Anomaly:
      {
         const string testFailureNumber = testFailureNumberer->Next();
         console->WriteLine(testFailureNumber);
         console->Write(fullName.TestsAndTestLines());
         WriteTestCaseNumberIfAny(console, testCaseIndex);
         const CallResult& responsibleCallResult = (this->*responsibleCallResultField);
         const string responsibleTestPhaseSuffix = TestPhaseToTestPhaseSuffix(responsibleCallResult.testPhase);
         console->Write(responsibleTestPhaseSuffix);
         console->WriteLine(responsibleCallResult.anomaly->why);
         console->WriteNewline();
         break;
      }
      case TestOutcome::Exception:
      {
         const string testFailureNumber = testFailureNumberer->Next();
         console->WriteLine(testFailureNumber);
         console->Write(fullName.TestsAndTestLines());
         WriteTestCaseNumberIfAny(console, testCaseIndex);
         const CallResult& responsibleCallResult = this->*responsibleCallResultField;
         const string responsibleTestPhaseSuffix = TestPhaseToTestPhaseSuffix(responsibleCallResult.testPhase);
         const string uncaughtExceptionTypeLine = String::Concat(
            "Threw exception: ", *responsibleCallResult.exceptionTypeName);
         const string exceptionwWhatLine = String::Concat(
            "what(): \"", *responsibleCallResult.exceptionWhat, "\"");
         console->WriteLine(responsibleTestPhaseSuffix);
         console->WriteLine(uncaughtExceptionTypeLine);
         console->WriteLine(exceptionwWhatLine);
         console->WriteNewline();
         break;
      }
      default:
      {
         assert_true(testOutcome == TestOutcome::SuccessButMissedDeadline);
         const string testFailureNumber = testFailureNumberer->Next();
         console->WriteLine(testFailureNumber);
         console->WriteLine(fullName.TestsAndTestLines());
         WriteTestCaseNumberIfAny(console, testCaseIndex);
         console->WriteLine(String::Concat(
            "Failed because test took longer than maxtestmilliseconds= (", milliseconds, " ms)"));
         console->WriteNewline();
         break;
      }
      }
   }

   void TestResult::WriteTestCaseNumberIfAny(const Console* console, int testCaseIndexArgument) const
   {
      assert_true(testCaseIndexArgument >= -1);
      if (testCaseIndexArgument != -1)
      {
         console->Write(" test case " + to_string(testCaseIndexArgument + 1));
      }
   }

   const TestResult TestResult::TestingNonDefault =
      TestResult::ConstructorFail(FullName("Non", "Default"), CallResult());
}

void ZenUnitEqualizer<ZenUnit::TestResult>::
AssertEqual(const ZenUnit::TestResult& expectedTestResult, const ZenUnit::TestResult& actualTestResult)
{
   ARE_EQUAL(expectedTestResult.fullName, actualTestResult.fullName);
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
