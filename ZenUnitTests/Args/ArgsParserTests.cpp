#include "pch.h"
#include "ZenUnitTests/Args/Mock/RunFilterParserMock.h"
#include "ZenUnitTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitTests/Random/RandomRunFilter.h"
#include "ZenUnitTests/Utils/Function/Mock/VoidOneArgMemberFunctionCallerMock.h"
#include "ZenUnitTests/Utils/Time/Mock/WatchMock.h"

namespace ZenUnit
{
   TESTS(ArgsParserTests)
   AFACT(DefaultConstructor_NewsComponents_SetsStringToUnsignedFunction)
   AFACT(Parse_ArgsOnlyExePath_ReturnsDefaultZenUnitArgsWithCommandLineAndTestProgramNameSet)
   FACTS(Parse_ArgsSizeGreaterThanOnePlusNumberOfValidArgs_PrintsErrorMessageAndUsageAndExits1)
   FACTS(Parse_InvalidArg_PrintsErrorMessageAndUsageAndExits1)
   FACTS(Parse_DashhelpOrDashDashhelp_PrintsUsageAndExits0)
   AFACT(Parse_AllArgsSpecifiedExpectForRunFilter_ReturnsZenUnitArgsWithAllFieldsSets)
   AFACT(Parse_RunArgument_ReturnsExpectedZenUnitArgs)
   AFACT(Parse_random_SetsrandomToTrue)
   AFACT(Parse_ValidBoolArg_ReturnsExpectedZenUnitArgs)
   AFACT(Parse_ValidBoolArgSpecifiedTwice_ReturnsExpectedZenUnitArgs)
   FACTS(Parse_EqualsSignContainingArg_EmptyValue_PrintsErrorMessageAndUsageAndExits1)
   AFACT(Parse_TimesEqualsArg_StringToUnsignedThrowsInvalidArgumentWhenProcessingValue_PrintsErrorMessageAndUsageAndExits1)
   AFACT(Parse_TimesEqualsArg_ValidUnsignedValue_ReturnsExpectedZenUnitArgs)
   AFACT(Parse_RandomEqualsArg_ValidRandomUnsignedValue_ReturnsExpectedZenUnitArgs)
   AFACT(Parse_UnrecognizedEqualsSignArgName_PrintsUsageAndExits1)
   AFACT(SetRandomSeedIfNotSetByUser_RandomSeedSetByUser_DoesNothing)
   AFACT(SetRandomSeedIfNotSetByUser_RandomSeedNotSetByUser_SetsRandomSeedToSecondsSince1970)
   EVIDENCE

   const string _testProgramPath = Random<string>();
   const string ExpectedUsage = R"(ZenUnit v0.2.2
Usage: <TestsBinaryName> [Options...]

Testing Utility Options:

-pause
   Wait for any key before running tests to allow attaching a debugger or profiler.
-exit0
   Always exit 0 regardless of test run outcome.
   Useful option for never blocking the launch of a ZenUnit tests
   console window when previously running tests in a post-build step.
-wait
   Wait for any key at the end of the test run.

Testing Filtration Options:

-run=<TestClassName>[::TestName][/TestCaseNumber][,...]
   Run only specified case-insensitive test classes, tests, and/or test cases.
   Add a '*' character to the end of a test class name or test name
   filter string to specify name-starts-with filtration.
 Example 1: -run=WidgetTests
   Runs only test class WidgetTests.
 Example 2: -run=WidgetTests::FunctionUnderTest*
   Runs all tests in WidgetTests that start with "FunctionUnderTest".
 Example 3: -run=WidgetTests::FunctionUnderTest_ScenarioUnderTest_ExpectedBehavior/3
   Runs the third test case of value-parameterized test
   WidgetTests::FunctionUnderTest_ScenarioUnderTest_ExpectedBehavior.
-failfast
   Immediately exit with exit code 1 if a test fails.

Testing Rigor Options:

-random
   Run test classes, tests, and value-parameterized test cases in a random order.
-randomseed=<S>
   Set to S the random seed used by -random
   and the ZenUnit::Random<T> family of random value generating functions.
   The default random seed is the number of seconds since 1970-01-01 00:00:00 UTC.
-testruns=<N>
   Repeat the running of all tests N times.
   Specify -testruns=3 -random for three random test run orderings.
   Useful option for continuous integration servers to partially ensure
   that checked-in unit tests are robust with respect to ordering.
-noskips
   Exit 1 regardless of test run outcome if any tests are skipped.
   Useful option for continuous integration servers to partially ensure
   that an organizational culture of "skip it and ship it!" does not take root.)";

   ArgsParser _argsParser;
   ConsoleMock* _consoleMock = nullptr;
   RunFilterParserMock* _runFilterParserMock = nullptr;
   VoidOneArgMemberFunctionCallerMock<ArgsParser, ZenUnitArgs&>* _callerOfSetRandomSeedIfNotSetByUserMock = nullptr;
   WatchMock* _watchMock;
   ZENMOCK_NONVOID1_STATIC(unsigned, ZenUnit::String, ToUnsigned, const string&);

   STARTUP
   {
      _argsParser._console.reset(_consoleMock = new ConsoleMock);
      _argsParser._runFilterParser.reset(_runFilterParserMock = new RunFilterParserMock);
      _argsParser._callerOfSetRandomSeedIfNotSetByUser.reset(
         _callerOfSetRandomSeedIfNotSetByUserMock = new VoidOneArgMemberFunctionCallerMock<ArgsParser, ZenUnitArgs&>);
      _argsParser._watch.reset(_watchMock = new WatchMock);
      _argsParser.call_String_ToUnsigned = BIND_1ARG_ZENMOCK_OBJECT(ToUnsigned_ZenMockObject);
   }

   TEST(DefaultConstructor_NewsComponents_SetsStringToUnsignedFunction)
   {
      ArgsParser argsParser;
      POINTER_WAS_NEWED(argsParser._console);
      POINTER_WAS_NEWED(argsParser._runFilterParser);
      POINTER_WAS_NEWED(argsParser._callerOfSetRandomSeedIfNotSetByUser);
      POINTER_WAS_NEWED(argsParser._watch);
      STD_FUNCTION_TARGETS(String::ToUnsigned, argsParser.call_String_ToUnsigned);
      //STD_FUNCTION_TARGETS(::time, argsParser.call_time);
   }

   void ExpectCallToSetRandomSeedIfNotSetByUser()
   {
      _callerOfSetRandomSeedIfNotSetByUserMock->ConstCallMock.Expect();
   }

   void AssertCallToSetRandomSeedIfNotSetByUser(ZenUnitArgs& expectedZenUnitArgsArg)
   {
      ZEN(_callerOfSetRandomSeedIfNotSetByUserMock->ConstCallMock.CalledOnceWith(
         &_argsParser, &ArgsParser::SetRandomSeedIfNotSetByUser, expectedZenUnitArgsArg));
   }

   TEST(Parse_ArgsOnlyExePath_ReturnsDefaultZenUnitArgsWithCommandLineAndTestProgramNameSet)
   {
      ExpectCallToSetRandomSeedIfNotSetByUser();
      vector<string> args { _testProgramPath };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(args);
      //
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = _testProgramPath;
      AssertCallToSetRandomSeedIfNotSetByUser(expectedZenUnitArgs);
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST1X1(Parse_ArgsSizeGreaterThanOnePlusNumberOfValidArgs_PrintsErrorMessageAndUsageAndExits1,
      size_t numberOfArgs,
      11,
      12)
   {
      _consoleMock->WriteLineMock.Expect();
      _consoleMock->WriteLineAndExitMock.Throw<WriteLineAndExitException>();
      const vector<string> args(numberOfArgs);
      //
      THROWS(_argsParser.Parse(args), WriteLineAndExitException, "");
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
      const vector<string> args { _testProgramPath, invalidArg };
      //
      THROWS(_argsParser.Parse(args), WriteLineAndExitException, "");
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
      const vector<string> args { _testProgramPath, helpArg };
      //
      THROWS(_argsParser.Parse(args), WriteLineAndExitException, "");
      //
      ZEN(_consoleMock->WriteLineAndExitMock.CalledOnceWith(ExpectedUsage, 0));
   }

   TEST(Parse_AllArgsSpecifiedExpectForRunFilter_ReturnsZenUnitArgsWithAllFieldsSets)
   {
      ExpectCallToSetRandomSeedIfNotSetByUser();
      const unsigned testruns = ZenUnit::Random<unsigned>();
      const unsigned randomseed = ZenUnit::Random<unsigned>();
      ToUnsigned_ZenMockObject.ReturnValues(testruns, randomseed);
      const vector<string> args
      {
         _testProgramPath,
         "-pause",
         "-wait",
         "-exit0",
         "-failfast",
         "-noskips",
         "-random",
         "-testruns=" + to_string(testruns),
         "-randomseed=" + to_string(randomseed)
      };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(args);
      //
      ZEN(ToUnsigned_ZenMockObject.CalledAsFollows(
      {
         to_string(testruns),
         to_string(randomseed)
      }));
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = Vector::Join(args, ' ');
      expectedZenUnitArgs.pause = true;
      expectedZenUnitArgs.wait = true;
      expectedZenUnitArgs.exit0 = true;
      expectedZenUnitArgs.failfast = true;
      expectedZenUnitArgs.noskips = true;
      expectedZenUnitArgs.random = true;
      expectedZenUnitArgs.testruns = testruns;
      expectedZenUnitArgs.randomseed = static_cast<unsigned short>(randomseed);
      expectedZenUnitArgs.randomseedsetbyuser = true;
      AssertCallToSetRandomSeedIfNotSetByUser(expectedZenUnitArgs);
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST(Parse_RunArgument_ReturnsExpectedZenUnitArgs)
   {
      ExpectCallToSetRandomSeedIfNotSetByUser();

      const vector<RunFilter> runFilters = { Random<RunFilter>() };
      _runFilterParserMock->ParseMock.Return(runFilters);

      const string runArgument = ZenUnit::Random<string>();
      const vector<string> args { ZenUnit::Random<string>(), "-run=" + runArgument };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(args);
      //
      const vector<string> splitRunArgument = String::Split(runArgument, ',');
      ZEN(_runFilterParserMock->ParseMock.CalledOnceWith(splitRunArgument));

      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = Vector::Join(args, ' ');
      expectedZenUnitArgs.runFilters = runFilters;
      AssertCallToSetRandomSeedIfNotSetByUser(expectedZenUnitArgs);
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST(Parse_random_SetsrandomToTrue)
   {
      ExpectCallToSetRandomSeedIfNotSetByUser();
      const vector<string> args { ZenUnit::Random<string>(), "-random" };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(args);
      //
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = Vector::Join(args, ' ');
      expectedZenUnitArgs.random = true;
      AssertCallToSetRandomSeedIfNotSetByUser(expectedZenUnitArgs);
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST(Parse_ValidBoolArg_ReturnsExpectedZenUnitArgs)
   {
      AssertArgSetsBoolField("-pause", &ZenUnitArgs::pause);
      Startup();
      AssertArgSetsBoolField("-wait", &ZenUnitArgs::wait);
      Startup();
      AssertArgSetsBoolField("-exit0", &ZenUnitArgs::exit0);
      Startup();
      AssertArgSetsBoolField("-failfast", &ZenUnitArgs::failfast);
      Startup();
      AssertArgSetsBoolField("-noskips", &ZenUnitArgs::noskips);
   }
   void AssertArgSetsBoolField(const string& arg, bool ZenUnitArgs::* expectedFieldToBeSet)
   {
      ExpectCallToSetRandomSeedIfNotSetByUser();
      const vector<string> args { _testProgramPath, arg };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(args);
      //
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = _testProgramPath + " " + arg;
      (expectedZenUnitArgs.*expectedFieldToBeSet) = true;
      AssertCallToSetRandomSeedIfNotSetByUser(expectedZenUnitArgs);
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST(Parse_ValidBoolArgSpecifiedTwice_ReturnsExpectedZenUnitArgs)
   {
      ExpectCallToSetRandomSeedIfNotSetByUser();
      const vector<string> args { _testProgramPath, "-exit0", "-exit0" };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(args);
      //
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = Vector::Join(args, ' ');
      expectedZenUnitArgs.exit0 = true;
      AssertCallToSetRandomSeedIfNotSetByUser(expectedZenUnitArgs);
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST1X1(Parse_EqualsSignContainingArg_EmptyValue_PrintsErrorMessageAndUsageAndExits1,
      const string& arg,
      "-testruns=",
      "-testruns===",
      "-randomseed=",
      "-randomseed===")
   {
      _consoleMock->WriteLineMock.Expect();
      _consoleMock->WriteLineAndExitMock.Throw<WriteLineAndExitException>();
      const vector<string> args { _testProgramPath, arg };
      //
      THROWS(_argsParser.Parse(args), WriteLineAndExitException, "");
      //
      ZEN(_consoleMock->WriteLineMock.CalledOnceWith(
         "ZenUnit command line usage error: Invalid -name=value argument value: " + arg + "\n"));
      ZEN(_consoleMock->WriteLineAndExitMock.CalledOnceWith(ExpectedUsage, 1));
   }

   TEST(Parse_TimesEqualsArg_StringToUnsignedThrowsInvalidArgumentWhenProcessingValue_PrintsErrorMessageAndUsageAndExits1)
   {
      _consoleMock->WriteLineMock.Expect();
      _consoleMock->WriteLineAndExitMock.Throw<WriteLineAndExitException>();
      ToUnsigned_ZenMockObject.Throw<invalid_argument>("");
      const string InvalidTimesArg = "-testruns=-1_for_example";
      const vector<string> args { _testProgramPath, InvalidTimesArg };
      //
      THROWS(_argsParser.Parse(args), WriteLineAndExitException, "");
      //
      ZEN(ToUnsigned_ZenMockObject.CalledOnceWith("-1_for_example"));
      ZEN(_consoleMock->WriteLineMock.CalledOnceWith(
         "ZenUnit command line usage error: Invalid -name=value argument value: " + InvalidTimesArg + "\n"));
      ZEN(_consoleMock->WriteLineAndExitMock.CalledOnceWith(ExpectedUsage, 1));
   }

   TEST(Parse_TimesEqualsArg_ValidUnsignedValue_ReturnsExpectedZenUnitArgs)
   {
      ExpectCallToSetRandomSeedIfNotSetByUser();
      const unsigned timesArgValue = ToUnsigned_ZenMockObject.ReturnRandom();
      const vector<string> args { _testProgramPath, "-testruns=" + to_string(timesArgValue) };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(args);
      //
      ZEN(ToUnsigned_ZenMockObject.CalledOnceWith(to_string(timesArgValue)));
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = Vector::Join(args, ' ');
      expectedZenUnitArgs.testruns = timesArgValue;
      AssertCallToSetRandomSeedIfNotSetByUser(expectedZenUnitArgs);
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST(Parse_RandomEqualsArg_ValidRandomUnsignedValue_ReturnsExpectedZenUnitArgs)
   {
      ExpectCallToSetRandomSeedIfNotSetByUser();
      const unsigned randomSeedArgValue = ToUnsigned_ZenMockObject.ReturnRandom();
      const vector<string> args { _testProgramPath, "-randomseed=" + to_string(randomSeedArgValue) };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(args);
      //
      ZEN(ToUnsigned_ZenMockObject.CalledOnceWith(to_string(randomSeedArgValue)));
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = Vector::Join(args, ' ');
      expectedZenUnitArgs.random = false;
      expectedZenUnitArgs.randomseed = static_cast<unsigned short>(randomSeedArgValue);
      expectedZenUnitArgs.randomseedsetbyuser = true;
      AssertCallToSetRandomSeedIfNotSetByUser(expectedZenUnitArgs);
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST(Parse_UnrecognizedEqualsSignArgName_PrintsUsageAndExits1)
   {
      _consoleMock->WriteLineMock.Expect();
      _consoleMock->WriteLineAndExitMock.Throw<WriteLineAndExitException>();
      const string unrecognizedNameArg = "-" + ZenUnit::Random<string>() + "=" + ZenUnit::Random<string>();
      const vector<string> args { _testProgramPath, unrecognizedNameArg };
      //
      THROWS(_argsParser.Parse(args), WriteLineAndExitException, "");
      //
      ZEN(_consoleMock->WriteLineMock.CalledOnceWith(
         "ZenUnit command line usage error: Unrecognized -name=value argument: " + unrecognizedNameArg + "\n"));
      ZEN(_consoleMock->WriteLineAndExitMock.CalledOnceWith(ExpectedUsage, 1));
   }

   TEST(SetRandomSeedIfNotSetByUser_RandomSeedSetByUser_DoesNothing)
   {
      ZenUnitArgs zenUnitArgs = ZenUnit::Random<ZenUnitArgs>();
      zenUnitArgs.randomseedsetbyuser = true;
      ZenUnitArgs expectedResultingZenUnitArgs = zenUnitArgs;
      //
      _argsParser.SetRandomSeedIfNotSetByUser(zenUnitArgs);
      //
      ARE_EQUAL(expectedResultingZenUnitArgs, zenUnitArgs);
   }

   TEST(SetRandomSeedIfNotSetByUser_RandomSeedNotSetByUser_SetsRandomSeedToSecondsSince1970)
   {
      ZenUnitArgs zenUnitArgs = ZenUnit::Random<ZenUnitArgs>();
      zenUnitArgs.randomseedsetbyuser = false;
      ZenUnitArgs expectedResultingZenUnitArgs = zenUnitArgs;
      const unsigned short secondsSince1970CastToUnsignedShort =
         _watchMock->SecondsSince1970CastToUnsignedShortMock.ReturnRandom();
      expectedResultingZenUnitArgs.randomseed = secondsSince1970CastToUnsignedShort;
      //
      _argsParser.SetRandomSeedIfNotSetByUser(zenUnitArgs);
      //
      ZEN(_watchMock->SecondsSince1970CastToUnsignedShortMock.CalledOnce());
      ARE_EQUAL(expectedResultingZenUnitArgs, zenUnitArgs);
   }

   RUN_TESTS(ArgsParserTests)
}
