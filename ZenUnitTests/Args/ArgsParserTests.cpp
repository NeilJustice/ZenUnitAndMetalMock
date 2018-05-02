#include "pch.h"
#include "ZenUnitTests/Args/Mock/RunFilterParserMock.h"
#include "ZenUnitTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitTests/Random/RandomRunFilter.h"

namespace ZenUnit
{
   TESTS(ArgsParserTests)
   AFACT(DefaultConstructor_NewsCompnents_SetsStringToUnsignedFunction)
   AFACT(Parse_ArgsOnlyExePath_ReturnsDefaultZenUnitArgsWithCommandLineAndTestProgramNameSet)
   FACTS(Parse_ArgsSizeGreaterThanOnePlusNumberOfValidArgs_PrintsErrorMessageAndUsageAndExits1)
   FACTS(Parse_InvalidArg_PrintsErrorMessageAndUsageAndExits1)
   FACTS(Parse_DashhelpOrDashDashhelp_PrintsUsageAndExits0)
   AFACT(Parse_AllArgsSpecified_ReturnsZenUnitArgsWithAllFieldsSets)
   AFACT(Parse_Run_ReturnsExpectedZenUnitArgs)
   AFACT(Parse_Random_SetsRandomToTrue)
   AFACT(Parse_ValidBoolArg_ReturnsExpectedZenUnitArgs)
   AFACT(Parse_ValidBoolArgSpecifiedTwice_ReturnsExpectedZenUnitArgs)
   FACTS(Parse_EqualsSignContainingArg_EmptyValue_PrintsErrorMessageAndUsageAndExits1)
   AFACT(Parse_TimesEqualsArg_StringToUnsignedThrowsInvalidArgumentWhenProcessingValue_PrintsErrorMessageAndUsageAndExits1)
   AFACT(Parse_TimesEqualsArg_ValidUnsignedValue_ReturnsExpectedZenUnitArgs)
   AFACT(Parse_RandomEqualsArg_ValidRandomUnsignedValue_ReturnsExpectedZenUnitArgs)
   AFACT(Parse_UnrecognizedEqualsSignArgName_PrintsUsageAndExits1)
   EVIDENCE

   const string TestProgramPath = Random<string>();
   const string ExpectedUsage = R"(ZenUnit v0.2.1
Usage: <TestsBinaryName> [Options...]

Testing Rigor:

-random[=Seed]
   Run test classes and tests in a random order.
-testruns=<NumberOfTestRuns>
   Repeat the running of all non-skipped tests NumberOfTestRuns times.
   Specify -random -testruns=2 for two random test run orderings.
-failskips
   Exit 1 regardless of test run outcome if any tests are skipped.

Testing Filtration:

-run=<TestClassName>[::TestName][/TestCaseNumber][,...]
   Run only specified case-insensitive test classes, tests, or test cases.
   Add a '*' character to the end of a test class or test name
   filter string to specify name-starts-with filtration.
 Example A: -run=Network*
   Runs all test classes that start with 'Network'.
 Example B: -run=WidgetTests.Serialize*
   Runs all tests in WidgetTests that start with 'Serialize'.
 Example C: -run=MathTests.ComplexCalculation_ValidInputs_ReturnsExpected/3
   Runs the third test case of value-parameterized test
   ComplexCalculation_ValidInputs_ReturnsExpected in test class MathTests.
-failfast
   Immediately exit with exit code 1 if a test fails.

Testing Utility:

-pause
   Wait for any key before running tests to allow attaching a profiler or debugger.
-exit0
   Always exit 0 regardless of test run outcome.
-wait
   Wait for any key at the end of the test run.)";

   ArgsParser _argsParser;
   ConsoleMock* _consoleMock;
   RunFilterParserMock* _runFilterParserMock = nullptr;
   ZENMOCK_NONVOID1_STATIC(unsigned, ZenUnit::String, ToUnsigned, const string&)

   STARTUP
   {
      _argsParser._console.reset(_consoleMock = new ConsoleMock);
      _argsParser._runFilterParser.reset(_runFilterParserMock = new RunFilterParserMock);
      _argsParser.call_String_ToUnsigned = ZENMOCK_BIND1(ToUnsigned_ZenMock);
   }

   TEST(DefaultConstructor_NewsCompnents_SetsStringToUnsignedFunction)
   {
      ArgsParser argsParser;
      POINTER_WAS_NEWED(argsParser._console);
      POINTER_WAS_NEWED(argsParser._runFilterParser);
      STD_FUNCTION_TARGETS(String::ToUnsigned, argsParser.call_String_ToUnsigned);
   }

   TEST(Parse_ArgsOnlyExePath_ReturnsDefaultZenUnitArgsWithCommandLineAndTestProgramNameSet)
   {
      vector<string> args{ TestProgramPath };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(args);
      //
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = TestProgramPath;
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST1X1(Parse_ArgsSizeGreaterThanOnePlusNumberOfValidArgs_PrintsErrorMessageAndUsageAndExits1,
      size_t numberOfArgs,
      11,
      12)
   {
      _consoleMock->WriteLineMock.Expect();
      _consoleMock->WriteLineAndExitMock.Throw<WriteLineAndExitException>();
      const vector<string> Args(numberOfArgs);
      //
      THROWS(_argsParser.Parse(Args), WriteLineAndExitException, "");
      //
      ZEN(_consoleMock->WriteLineMock.CalledOnceWith("ZenUnit command line usage error: Too many arguments.\n"));
      ZEN(_consoleMock->WriteLineAndExitMock.CalledOnceWith(ExpectedUsage, 1));
   }

   TEST1X1(Parse_InvalidArg_PrintsErrorMessageAndUsageAndExits1,
      const string& invalidArg,
      "--exit0",
      "-Exit0",
      "-testruns")
   {
      _consoleMock->WriteLineMock.Expect();
      _consoleMock->WriteLineAndExitMock.Throw<WriteLineAndExitException>();
      const vector<string> Args{ TestProgramPath, invalidArg };
      //
      THROWS(_argsParser.Parse(Args), WriteLineAndExitException, "");
      //
      ZEN(_consoleMock->WriteLineMock.CalledOnceWith(
         "ZenUnit command line usage error: Invalid argument \"" + invalidArg + "\"\n"));
      ZEN(_consoleMock->WriteLineAndExitMock.CalledOnceWith(ExpectedUsage, 1));
   }

   TEST1X1(Parse_DashhelpOrDashDashhelp_PrintsUsageAndExits0,
      const string& helpArg,
      "-help",
      "--help")
   {
      _consoleMock->WriteLineAndExitMock.Throw<WriteLineAndExitException>();
      //
      THROWS(_argsParser.Parse({ TestProgramPath, helpArg }), WriteLineAndExitException, "");
      //
      ZEN(_consoleMock->WriteLineAndExitMock.CalledOnceWith(ExpectedUsage, 0));
   }

   TEST(Parse_AllArgsSpecified_ReturnsZenUnitArgsWithAllFieldsSets)
   {
      const unsigned testruns = ZenUnit::Random<unsigned>();
      const unsigned randomseed = ZenUnit::Random<unsigned>();
      ToUnsigned_ZenMock.ReturnValues(testruns, randomseed);
      const vector<string> Args
      {
         TestProgramPath,
         "-pause",
         "-wait",
         "-exit0",
         "-failfast",
         "-failskips",
         "-testruns=" + to_string(testruns),
         "-random=" + to_string(randomseed)
      };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(Args);
      //
      ZEN(ToUnsigned_ZenMock.CalledAsFollows(
         {
            to_string(testruns),
            to_string(randomseed)
         }));
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = Vector::Join(Args, ' ');
      expectedZenUnitArgs.pause = true;
      expectedZenUnitArgs.wait = true;
      expectedZenUnitArgs.exit0 = true;
      expectedZenUnitArgs.failfast = true;
      expectedZenUnitArgs.failskips = true;
      expectedZenUnitArgs.testruns = 1;
      expectedZenUnitArgs.random = true;
      expectedZenUnitArgs.testruns = testruns;
      expectedZenUnitArgs.randomseed = randomseed;
      expectedZenUnitArgs.randomseedsetbyuser = true;
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST(Parse_Run_ReturnsExpectedZenUnitArgs)
   {
      const vector<RunFilter> runFilters = { Random<RunFilter>() };
      _runFilterParserMock->ParseMock.Return(runFilters);

      const string runArgument = ZenUnit::Random<string>();
      const vector<string> args = { "ExePath", "-run=" + runArgument };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(args);
      //
      const vector<string> splitRunArgument = String::Split(runArgument, ',');
      ZEN(_runFilterParserMock->ParseMock.CalledOnceWith(splitRunArgument));

      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = Vector::Join(args, ' ');
      expectedZenUnitArgs.runFilters = runFilters;
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST(Parse_Random_SetsRandomToTrue)
   {
      const vector<string> args = { "ExePath", "-random" };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(args);
      //
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = Vector::Join(args, ' ');
      expectedZenUnitArgs.random = true;
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST(Parse_ValidBoolArg_ReturnsExpectedZenUnitArgs)
   {
      AssertArgSetsBoolField("-pause", &ZenUnitArgs::pause);
      AssertArgSetsBoolField("-wait", &ZenUnitArgs::wait);
      AssertArgSetsBoolField("-exit0", &ZenUnitArgs::exit0);
      AssertArgSetsBoolField("-failfast", &ZenUnitArgs::failfast);
      AssertArgSetsBoolField("-failskips", &ZenUnitArgs::failskips);
   }
   void AssertArgSetsBoolField(const string& arg, bool ZenUnitArgs::* expectedFieldToBeSet)
   {
      const vector<string> Args{ TestProgramPath, arg };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(Args);
      //
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = TestProgramPath + " " + arg;
      (expectedZenUnitArgs.*expectedFieldToBeSet) = true;
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST(Parse_ValidBoolArgSpecifiedTwice_ReturnsExpectedZenUnitArgs)
   {
      const vector<string> Args{ TestProgramPath, "-exit0", "-exit0" };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(Args);
      //
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = Vector::Join(Args, ' ');
      expectedZenUnitArgs.exit0 = true;
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST1X1(Parse_EqualsSignContainingArg_EmptyValue_PrintsErrorMessageAndUsageAndExits1,
      const string& arg,
      "-testruns=",
      "-testruns===",
      "-random=",
      "-random===")
   {
      _consoleMock->WriteLineMock.Expect();
      _consoleMock->WriteLineAndExitMock.Throw<WriteLineAndExitException>();
      const vector<string> Args{ TestProgramPath, arg };
      //
      THROWS(_argsParser.Parse(Args), WriteLineAndExitException, "");
      //
      ZEN(_consoleMock->WriteLineMock.CalledOnceWith(
         "ZenUnit command line usage error: Invalid -name=value argument value: " + arg + "\n"));
      ZEN(_consoleMock->WriteLineAndExitMock.CalledOnceWith(ExpectedUsage, 1));
   }

   TEST(Parse_TimesEqualsArg_StringToUnsignedThrowsInvalidArgumentWhenProcessingValue_PrintsErrorMessageAndUsageAndExits1)
   {
      _consoleMock->WriteLineMock.Expect();
      _consoleMock->WriteLineAndExitMock.Throw<WriteLineAndExitException>();
      ToUnsigned_ZenMock.Throw<invalid_argument>("");
      const string InvalidTimesArg = "-testruns=-1_for_example";
      const vector<string> Args{ TestProgramPath, InvalidTimesArg };
      //
      THROWS(_argsParser.Parse(Args), WriteLineAndExitException, "");
      //
      ZEN(ToUnsigned_ZenMock.CalledOnceWith("-1_for_example"));
      ZEN(_consoleMock->WriteLineMock.CalledOnceWith(
         "ZenUnit command line usage error: Invalid -name=value argument value: " + InvalidTimesArg + "\n"));
      ZEN(_consoleMock->WriteLineAndExitMock.CalledOnceWith(ExpectedUsage, 1));
   }

   TEST(Parse_TimesEqualsArg_ValidUnsignedValue_ReturnsExpectedZenUnitArgs)
   {
      const unsigned timesArgValue = ToUnsigned_ZenMock.ReturnRandom();
      const vector<string> Args{ TestProgramPath, "-testruns=" + to_string(timesArgValue) };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(Args);
      //
      ZEN(ToUnsigned_ZenMock.CalledOnceWith(to_string(timesArgValue)));
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = Vector::Join(Args, ' ');
      expectedZenUnitArgs.testruns = timesArgValue;
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST(Parse_RandomEqualsArg_ValidRandomUnsignedValue_ReturnsExpectedZenUnitArgs)
   {
      const unsigned randomSeedArgValue = ToUnsigned_ZenMock.ReturnRandom();
      const vector<string> Args{ TestProgramPath, "-random=" + to_string(randomSeedArgValue) };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(Args);
      //
      ZEN(ToUnsigned_ZenMock.CalledOnceWith(to_string(randomSeedArgValue)));
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = Vector::Join(Args, ' ');
      expectedZenUnitArgs.random = true;
      expectedZenUnitArgs.randomseed = randomSeedArgValue;
      expectedZenUnitArgs.randomseedsetbyuser = true;
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST(Parse_UnrecognizedEqualsSignArgName_PrintsUsageAndExits1)
   {
      _consoleMock->WriteLineMock.Expect();
      _consoleMock->WriteLineAndExitMock.Expect();
      const string UnrecognizedNameArg = "-invalid_name=123";
      const vector<string> Args{ TestProgramPath, UnrecognizedNameArg };
      //
      _argsParser.Parse(Args);
      //
      ZEN(_consoleMock->WriteLineMock.CalledOnceWith(
         "ZenUnit command line usage error: Unrecognized -name=value argument: " + UnrecognizedNameArg + "\n"));
      ZEN(_consoleMock->WriteLineAndExitMock.CalledOnceWith(ExpectedUsage, 1));
   }

   RUN_TESTS(ArgsParserTests)
}
