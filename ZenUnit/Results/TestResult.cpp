#include "pch.h"
#include "Results/TestResult.h"
#include "ZenUnit/Console/Console.h"
#include "ZenUnit/Macros/ARE_EQUAL.h"
#include "ZenUnit/Results/AnomalyOrException.h"
#include "ZenUnit/Results/TestFailureNumberer.h"
#include "ZenUnit/TestRunners/TestRunner.h"

namespace ZenUnit
{
   TestResult::TestResult()
      : responsibleCallResultField(nullptr)
      , testOutcome(TestOutcome::Unset)
      , milliseconds(0)
      , testCaseIndex(numeric_limits<unsigned short>::max())
   {
   }

   TestResult TestResult::ConstructorFail(
      const ClassNameTestName& classNameTestName,
      const CallResult& constructorCallResult)
   {
      TestResult constructorFailTestResult;
      constructorFailTestResult.classNameTestName = classNameTestName;
      constructorFailTestResult.constructorCallResult = constructorCallResult;
      constructorFailTestResult.testOutcome = constructorCallResult.testOutcome;
      constructorFailTestResult.milliseconds = constructorCallResult.milliseconds;
      constructorFailTestResult.responsibleCallResultField = &TestResult::constructorCallResult;
      return constructorFailTestResult;
   }

   TestResult TestResult::StartupFail(
      const ClassNameTestName& classNameTestName,
      const CallResult& constructorCallResult,
      const CallResult& startupCallResult,
      const CallResult& destructorCallResult)
   {
      assert_true(constructorCallResult.testOutcome == TestOutcome::Success);
      assert_true(destructorCallResult.testOutcome == TestOutcome::Success);
      TestResult startupFail;
      startupFail.classNameTestName = classNameTestName;
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
      const ClassNameTestName& classNameTestName,
      const CallResult& constructorCallResult,
      const CallResult& destructorCallResult)
   {
      assert_true(constructorCallResult.testOutcome == TestOutcome::Success);
      assert_true(destructorCallResult.testOutcome == TestOutcome::Success);
      TestResult ctorDtorSuccess;
      ctorDtorSuccess.classNameTestName = classNameTestName;
      ctorDtorSuccess.testOutcome = TestOutcome::Success;
      ctorDtorSuccess.constructorCallResult = constructorCallResult;
      ctorDtorSuccess.destructorCallResult = destructorCallResult;
      ctorDtorSuccess.milliseconds = constructorCallResult.milliseconds + destructorCallResult.milliseconds;
      ctorDtorSuccess.responsibleCallResultField = nullptr;
      return ctorDtorSuccess;
   }

   TestResult::TestResult(
      const ClassNameTestName& classNameTestName,
      const CallResult& constructorCallResult,
      const CallResult& startupCallResult,
      const CallResult& testBodyCallResult,
      const CallResult& cleanupCallResult,
      const CallResult& destructorCallResult,
      const function<ZenUnitArgs()>& getArgs)
      : classNameTestName(classNameTestName)
      , constructorCallResult(constructorCallResult)
      , startupCallResult(startupCallResult)
      , testBodyCallResult(testBodyCallResult)
      , cleanupCallResult(cleanupCallResult)
      , destructorCallResult(destructorCallResult)
      , responsibleCallResultField(nullptr)
      , testOutcome(TestOutcome::Unset)
      , milliseconds(0)
      , testCaseIndex(numeric_limits<unsigned short>::max())
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
            testOutcome = TestOutcome::SuccessButPastDeadline;
         }
      }
   }

   void TestResult::PrintOKIfTestPassed(const Console* console) const
   {
      if (testOutcome == TestOutcome::Success)
      {
         console->WriteLineColor("OK", Color::White);
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
         console->Write(classNameTestName.TestsAndTestLines());
         const CallResult& responsibleCallResult = (this->*responsibleCallResultField);
         const char* const responsibleTestPhaseSuffix = 
            TestPhaseToTestPhaseSuffix(responsibleCallResult.testPhase);
         console->Write(responsibleTestPhaseSuffix);
         WriteTestCaseNumberIfAny(console, testCaseIndex);
         console->WriteLine(responsibleCallResult.anomalyOrException->anomaly->why);
         console->WriteNewline();
         break;
      }
      case TestOutcome::Exception:
      {
         const string testFailureNumber = testFailureNumberer->Next();
         console->WriteLine(testFailureNumber);
         console->Write(classNameTestName.TestsAndTestLines());
         const CallResult& responsibleCallResult = this->*responsibleCallResultField;
         const char* const responsibleTestPhaseSuffix = 
            TestPhaseToTestPhaseSuffix(responsibleCallResult.testPhase);
         console->Write(responsibleTestPhaseSuffix);
         WriteTestCaseNumberIfAny(console, testCaseIndex);
         console->WriteLineColor("\nUncaught Exception", Color::Red);
         const string exceptionTypeAndWhatLines = String::Concat(
            "  Type: ", *responsibleCallResult.anomalyOrException->exceptionTypeName, '\n',
            "what(): \"", *responsibleCallResult.anomalyOrException->exceptionWhat, "\"");
         console->WriteLine(exceptionTypeAndWhatLines);
         console->WriteNewline();
         break;
      }
      default:
      {
         assert_true(testOutcome == TestOutcome::SuccessButPastDeadline);
         const string testFailureNumber = testFailureNumberer->Next();
         console->WriteLine(testFailureNumber);
         console->WriteLine(classNameTestName.TestsAndTestLines());
         WriteTestCaseNumberIfAny(console, testCaseIndex);
         console->WriteLine(String::Concat(
            "\nFailed because test took longer than -maxtestms= (", milliseconds, " ms)"));
         console->WriteNewline();
         break;
      }
      }
   }

   void TestResult::WriteTestCaseNumberIfAny(
      const Console* console, unsigned short testCaseIndexArgument) const
   {
      if (testCaseIndexArgument != numeric_limits<unsigned short>::max())
      {
         console->Write(" test case " + to_string(testCaseIndexArgument + 1));
      }
   }

   const TestResult TestResult::TestingNonDefault =
      TestResult::ConstructorFail(ClassNameTestName("Non", "Default"), CallResult());
}

void ZenUnitEqualizer<ZenUnit::TestResult>::
AssertEqual(const ZenUnit::TestResult& expectedTestResult, const ZenUnit::TestResult& actualTestResult)
{
   ARE_EQUAL(expectedTestResult.classNameTestName, actualTestResult.classNameTestName);
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
