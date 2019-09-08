#include "pch.h"
#include "ZenUnitLibraryTests/Args/ZenMock/RunFilterParserMock.h"
#include "ZenUnitLibraryTests/Console/ZenMock/ConsoleMock.h"
#include "ZenUnitLibraryTests/Random/RandomRunFilter.h"
#include "ZenUnitTestUtils/Equalizers/ZenUnitArgsEqualizer.h"

namespace ZenUnit
{
   TESTS(ArgsParserTests)
   AFACT(DefaultConstructor_NewsComponents_SetsStringToUnsignedFunction)
   AFACT(Parse_ArgsOnlyExePath_ReturnsDefaultZenUnitArgsWithCommandLineAndTestProgramNameSet)
   FACTS(Parse_ArgsSizeGreaterThanOrEqualTo13_PrintsTooManyArgumentsErrorMessageAndUsageAndExits1)
   FACTS(Parse_InvalidArg_PrintsErrorMessageAndUsageAndExits1)
   FACTS(Parse_DashHelpOrDashDashHelp_PrintsUsageAndExits0)
	FACTS(Parse_DashVersionOrDashDashVersion_PrintsVersionAndExits0)
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
   const string _expectedUsage = "C++ Unit Testing Framework ZenUnit " + std::string(Version::Number()) + R"(
https://github.com/NeilJustice/ZenUnit
Usage: <ZenUnitTestsBinaryName> [Options...]

Testing Rigor Options:

--random
   Run test classes, tests, and value-parameterized test cases in a random order.
--seed=<Value>
   Set to Value the random seed used by --random and
   the ZenUnit::Random<T> family of random value generating functions.
   The default random seed is the number of seconds since 1970-01-01 00:00:00 UTC.
--test-runs=<N>
   Repeat the running of all tests N times. Use a negative number to repeat forever.
   For five random test run orderings on a CI/CD server to exercise the robustness of commits
   with respect to test run ordering, specify --random --test-runs=5.
--no-skips
   Exit with code 1 after running all tests if any tests are skipped. Useful option for CI/CD servers.

Testing Filtration Options:

--run=<TestClassName>[::TestName][/TestCaseNumber][,...]
   Run only specified case-insensitive test classes, tests, and/or test cases.
   Add a '*' character to the end of a test class name or test name
   filter string to specify name-starts-with filtration.
 Example 1: --run=WidgetTests
   Run only test class WidgetTests.
 Example 2: --run=WidgetTests::FunctionUnderTest*
   Run all tests in WidgetTests that start with "FunctionUnderTest".
 Example 3: --run=WidgetTests::FunctionUnderTest_ScenarioUnderTest_ExpectedBehavior/3
   Run the third test case of value-parameterized test
   WidgetTests::FunctionUnderTest_ScenarioUnderTest_ExpectedBehavior.
--fail-fast
   Immediately call exit(1) if a test fails.

Testing Utility Options:

--help or -help
   Print this help message.
--version or -version
	Print the ZenUnit version number.
--pause
   Wait for any key before running tests to allow attaching a debugger or profiler.
--exit-zero
   Always exit with code 0.
--wait
   Wait for any key at the end of the test run.)";

   ArgsParser _argsParser;
   ConsoleMock* _consoleMock = nullptr;
   RunFilterParserMock* _runFilterParserMock = nullptr;
   VoidOneArgMemberFunctionCallerMock<ArgsParser, ZenUnitArgs&>* _callerOfSetRandomSeedIfNotSetByUserMock = nullptr;
   WatchMock* _watchMock = nullptr;
   ZENMOCK_NONVOID1_STATIC(int, ZenUnit::String, ToInt, std::string_view)
   ZENMOCK_NONVOID1_STATIC(unsigned, ZenUnit::String, ToUnsigned, std::string_view)

   STARTUP
   {
      _argsParser._console.reset(_consoleMock = new ConsoleMock);
      _argsParser._runFilterParser.reset(_runFilterParserMock = new RunFilterParserMock);
      _argsParser._callerOfSetRandomSeedIfNotSetByUser.reset(
         _callerOfSetRandomSeedIfNotSetByUserMock = new VoidOneArgMemberFunctionCallerMock<ArgsParser, ZenUnitArgs&>);
      _argsParser._watch.reset(_watchMock = new WatchMock);
      _argsParser._call_String_ToInt = BIND_1ARG_ZENMOCK_OBJECT(ToInt_ZenMockObject);
      _argsParser._call_String_ToUnsigned = BIND_1ARG_ZENMOCK_OBJECT(ToUnsigned_ZenMockObject);
   }

   TEST(DefaultConstructor_NewsComponents_SetsStringToUnsignedFunction)
   {
      ArgsParser argsParser;
      POINTER_WAS_NEWED(argsParser._console);
      POINTER_WAS_NEWED(argsParser._runFilterParser);
      POINTER_WAS_NEWED(argsParser._callerOfSetRandomSeedIfNotSetByUser);
      POINTER_WAS_NEWED(argsParser._watch);
      STD_FUNCTION_TARGETS(String::ToInt, argsParser._call_String_ToInt);
      STD_FUNCTION_TARGETS(String::ToUnsigned, argsParser._call_String_ToUnsigned);
   }

   void ExpectCallToSetRandomSeedIfNotSetByUser()
   {
      _callerOfSetRandomSeedIfNotSetByUserMock->ConstCallMock.Expect();
   }

   void AssertCallToSetRandomSeedIfNotSetByUser(ZenUnitArgs& expectedZenUnitArgsArg)
   {
      ZENMOCK(_callerOfSetRandomSeedIfNotSetByUserMock->ConstCallMock.CalledOnceWith(
         &_argsParser, &ArgsParser::SetRandomSeedIfNotSetByUser, expectedZenUnitArgsArg));
   }

   TEST(Parse_ArgsOnlyExePath_ReturnsDefaultZenUnitArgsWithCommandLineAndTestProgramNameSet)
   {
      const string startTime = _watchMock->DateTimeNowMock.ReturnRandom();
      ExpectCallToSetRandomSeedIfNotSetByUser();
      vector<string> stringArgs{ _testProgramPath };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(stringArgs);
      //
      ZENMOCK(_watchMock->DateTimeNowMock.CalledOnce());
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = _testProgramPath;
      expectedZenUnitArgs.startTime = startTime;
      AssertCallToSetRandomSeedIfNotSetByUser(expectedZenUnitArgs);
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST1X1(Parse_ArgsSizeGreaterThanOrEqualTo13_PrintsTooManyArgumentsErrorMessageAndUsageAndExits1,
      size_t numberOfArgs,
      13,
      14)
   {
      _consoleMock->WriteLineMock.Expect();
      _consoleMock->WriteLineAndExitMock.Throw<WriteLineAndExitException>();
      const vector<string> stringArgs(numberOfArgs);
      //
      THROWS(const ZenUnitArgs zenUnitArgs = _argsParser.Parse(stringArgs), WriteLineAndExitException, "");
      //
      ZENMOCK(_consoleMock->WriteLineMock.CalledOnceWith("ZenUnit command line usage error: Too many arguments.\n"));
      ZENMOCK(_consoleMock->WriteLineAndExitMock.CalledOnceWith(_expectedUsage, 1));
   }

   TEST1X1(Parse_InvalidArg_PrintsErrorMessageAndUsageAndExits1,
      const string& invalidArgument,
      "--abc",
      "--Exit-zero",
      "--test-runs")
   {
      _consoleMock->WriteLineMock.Expect();
      _consoleMock->WriteLineAndExitMock.Throw<WriteLineAndExitException>();
      const vector<string> stringArgs { _testProgramPath, invalidArgument };
      //
      THROWS(const ZenUnitArgs zenUnitArgs = _argsParser.Parse(stringArgs), WriteLineAndExitException, "");
      //
      ZENMOCK(_consoleMock->WriteLineMock.CalledOnceWith(
         "ZenUnit command line usage error: Invalid argument \"" + invalidArgument + "\"\n"));
      ZENMOCK(_consoleMock->WriteLineAndExitMock.CalledOnceWith(_expectedUsage, 1));
   }

   TEST1X1(Parse_DashHelpOrDashDashHelp_PrintsUsageAndExits0,
      const string& helpArgument,
		"--help",
      "-help")
   {
      _consoleMock->WriteLineAndExitMock.Throw<WriteLineAndExitException>();
      const vector<string> stringArgs { _testProgramPath, helpArgument };
      //
      THROWS(const ZenUnitArgs zenUnitArgs = _argsParser.Parse(stringArgs), WriteLineAndExitException, "");
      //
      ZENMOCK(_consoleMock->WriteLineAndExitMock.CalledOnceWith(_expectedUsage, 0));
   }

	TEST1X1(Parse_DashVersionOrDashDashVersion_PrintsVersionAndExits0,
		const string& versionArgument,
		"--version",
		"-version")
	{
		_consoleMock->WriteLineAndExitMock.Throw<WriteLineAndExitException>();
      const vector<string> stringArgs { _testProgramPath, versionArgument };
      //
      THROWS(const ZenUnitArgs zenUnitArgs = _argsParser.Parse(stringArgs), WriteLineAndExitException, "");
      //
      ZENMOCK(_consoleMock->WriteLineAndExitMock.CalledOnceWith("0.5.0", 0));
	}

   TEST(Parse_AllArgsSpecifiedExpectForRunFilter_ReturnsZenUnitArgsWithAllFieldsSets)
   {
      const int testruns = ToInt_ZenMockObject.ReturnRandom();
      const unsigned randomSeed = ToUnsigned_ZenMockObject.ReturnRandom();
		_callerOfSetRandomSeedIfNotSetByUserMock->ConstCallMock.Expect();
		const string startTime = _watchMock->DateTimeNowMock.ReturnRandom();
      const vector<string> stringArgs
      {
         _testProgramPath,
         "--pause",
         "--wait",
         "--exit-zero",
         "--fail-fast",
         "--no-skips",
         "--random",
         "--test-runs=" + to_string(testruns),
         "--seed=" + to_string(randomSeed)
      };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(stringArgs);
      //
      ZENMOCK(ToInt_ZenMockObject.CalledOnceWith(to_string(testruns)));
      ZENMOCK(ToUnsigned_ZenMockObject.CalledOnceWith(to_string(randomSeed)));
		ZENMOCK(_watchMock->DateTimeNowMock.CalledOnce());
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = Vector::Join(stringArgs, ' ');
      expectedZenUnitArgs.pause = true;
      expectedZenUnitArgs.wait = true;
      expectedZenUnitArgs.exitZero = true;
      expectedZenUnitArgs.failFast = true;
      expectedZenUnitArgs.noSkips = true;
      expectedZenUnitArgs.random = true;
      expectedZenUnitArgs.testRuns = testruns;
      expectedZenUnitArgs.randomSeed = randomSeed;
      expectedZenUnitArgs.randomSeedSetByUser = true;
		expectedZenUnitArgs.startTime = startTime;
      AssertCallToSetRandomSeedIfNotSetByUser(expectedZenUnitArgs);
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST(Parse_RunArgument_ReturnsExpectedZenUnitArgs)
   {
      _callerOfSetRandomSeedIfNotSetByUserMock->ConstCallMock.Expect();

      const vector<RunFilter> runFilters = { Random<RunFilter>() };
      _runFilterParserMock->ParseMock.Return(runFilters);

      const string unusedDateTimeNow = _watchMock->DateTimeNowMock.ReturnRandom();

      const string runArgument = ZenUnit::Random<string>();
      const vector<string> stringArgs { ZenUnit::Random<string>(), "--run=" + runArgument };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(stringArgs);
      //
      const vector<string> splitRunArgument = String::Split(runArgument, ',');
      ZENMOCK(_runFilterParserMock->ParseMock.CalledOnceWith(splitRunArgument));

      ZENMOCK(_watchMock->DateTimeNowMock.CalledOnce());

      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = Vector::Join(stringArgs, ' ');
      expectedZenUnitArgs.runFilters = runFilters;
      AssertCallToSetRandomSeedIfNotSetByUser(expectedZenUnitArgs);
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST(Parse_random_SetsrandomToTrue)
   {
      const string dateTimeNow = _watchMock->DateTimeNowMock.ReturnRandom();
      ExpectCallToSetRandomSeedIfNotSetByUser();
      const vector<string> stringArgs { ZenUnit::Random<string>(), "--random" };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(stringArgs);
      //
      ZENMOCK(_watchMock->DateTimeNowMock.CalledOnce());
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = Vector::Join(stringArgs, ' ');
      expectedZenUnitArgs.random = true;
      AssertCallToSetRandomSeedIfNotSetByUser(expectedZenUnitArgs);
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST(Parse_ValidBoolArg_ReturnsExpectedZenUnitArgs)
   {
      AssertArgSetsBoolField("--pause", &ZenUnitArgs::pause);
      Startup();
      AssertArgSetsBoolField("--wait", &ZenUnitArgs::wait);
      Startup();
      AssertArgSetsBoolField("--exit-zero", &ZenUnitArgs::exitZero);
      Startup();
      AssertArgSetsBoolField("--fail-fast", &ZenUnitArgs::failFast);
      Startup();
      AssertArgSetsBoolField("--no-skips", &ZenUnitArgs::noSkips);
   }
   void AssertArgSetsBoolField(const string& arg, bool ZenUnitArgs::* expectedFieldToBeSet)
   {
      const string dateTimeNow = _watchMock->DateTimeNowMock.ReturnRandom();
      ExpectCallToSetRandomSeedIfNotSetByUser();
      const vector<string> stringArgs { _testProgramPath, arg };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(stringArgs);
      //
      ZENMOCK(_watchMock->DateTimeNowMock.CalledOnce());
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = _testProgramPath + " " + arg;
      (expectedZenUnitArgs.*expectedFieldToBeSet) = true;
      AssertCallToSetRandomSeedIfNotSetByUser(expectedZenUnitArgs);
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST(Parse_ValidBoolArgSpecifiedTwice_ReturnsExpectedZenUnitArgs)
   {
      const string dateTimeNow = _watchMock->DateTimeNowMock.ReturnRandom();
      ExpectCallToSetRandomSeedIfNotSetByUser();
      const vector<string> stringArgs { _testProgramPath, "--exit-zero", "--exit-zero" };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(stringArgs);
      //
      ZENMOCK(_watchMock->DateTimeNowMock.CalledOnce());
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = Vector::Join(stringArgs, ' ');
      expectedZenUnitArgs.exitZero = true;
      AssertCallToSetRandomSeedIfNotSetByUser(expectedZenUnitArgs);
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST1X1(Parse_EqualsSignContainingArg_EmptyValue_PrintsErrorMessageAndUsageAndExits1,
      const string& arg,
      "--test-runs=",
      "--test-runs===",
      "--seed=",
      "--seed===")
   {
      _consoleMock->WriteLineMock.Expect();
      _consoleMock->WriteLineAndExitMock.Throw<WriteLineAndExitException>();
      const vector<string> stringArgs { _testProgramPath, arg };
      //
      THROWS(const ZenUnitArgs zenUnitArgs = _argsParser.Parse(stringArgs), WriteLineAndExitException, "");
      //
      ZENMOCK(_consoleMock->WriteLineMock.CalledOnceWith(
         "ZenUnit command line usage error: Invalid --name=value argument value: " + arg + "\n"));
      ZENMOCK(_consoleMock->WriteLineAndExitMock.CalledOnceWith(_expectedUsage, 1));
   }

   TEST(Parse_TimesEqualsArg_StringToUnsignedThrowsInvalidArgumentWhenProcessingValue_PrintsErrorMessageAndUsageAndExits1)
   {
      _consoleMock->WriteLineMock.Expect();
      _consoleMock->WriteLineAndExitMock.Throw<WriteLineAndExitException>();
      ToInt_ZenMockObject.Throw<invalid_argument>("");
      const string InvalidTimesArg = "--test-runs=-1_for_example";
      const vector<string> stringArgs { _testProgramPath, InvalidTimesArg };
      //
      THROWS(const ZenUnitArgs zenUnitArgs = _argsParser.Parse(stringArgs), WriteLineAndExitException, "");
      //
      ZENMOCK(ToInt_ZenMockObject.CalledOnceWith("-1_for_example"));
      ZENMOCK(_consoleMock->WriteLineMock.CalledOnceWith(
         "ZenUnit command line usage error: Invalid --name=value argument value: " + InvalidTimesArg + "\n"));
      ZENMOCK(_consoleMock->WriteLineAndExitMock.CalledOnceWith(_expectedUsage, 1));
   }

   TEST(Parse_TimesEqualsArg_ValidUnsignedValue_ReturnsExpectedZenUnitArgs)
   {
      const string dateTimeNow = _watchMock->DateTimeNowMock.ReturnRandom();
      ExpectCallToSetRandomSeedIfNotSetByUser();
      const unsigned timesArgValue = ToInt_ZenMockObject.ReturnRandom();
      const vector<string> stringArgs{ _testProgramPath, "--test-runs=" + to_string(timesArgValue) };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(stringArgs);
      //
      ZENMOCK(ToInt_ZenMockObject.CalledOnceWith(to_string(timesArgValue)));
      ZENMOCK(_watchMock->DateTimeNowMock.CalledOnce());
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = Vector::Join(stringArgs, ' ');
      expectedZenUnitArgs.testRuns = timesArgValue;
      AssertCallToSetRandomSeedIfNotSetByUser(expectedZenUnitArgs);
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST(Parse_RandomEqualsArg_ValidRandomUnsignedValue_ReturnsExpectedZenUnitArgs)
   {
      const string dateTimeNow = _watchMock->DateTimeNowMock.ReturnRandom();
      ExpectCallToSetRandomSeedIfNotSetByUser();
      const unsigned randomSeed = ToUnsigned_ZenMockObject.ReturnRandom();
      const vector<string> stringArgs{ _testProgramPath, "--seed=" + to_string(randomSeed) };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(stringArgs);
      //
      ZENMOCK(ToUnsigned_ZenMockObject.CalledOnceWith(to_string(randomSeed)));
      ZENMOCK(_watchMock->DateTimeNowMock.CalledOnce());
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = Vector::Join(stringArgs, ' ');
      expectedZenUnitArgs.random = false;
      expectedZenUnitArgs.randomSeed = randomSeed;
      expectedZenUnitArgs.randomSeedSetByUser = true;
      AssertCallToSetRandomSeedIfNotSetByUser(expectedZenUnitArgs);
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST(Parse_UnrecognizedEqualsSignArgName_PrintsUsageAndExits1)
   {
      _consoleMock->WriteLineMock.Expect();
      _consoleMock->WriteLineAndExitMock.Throw<WriteLineAndExitException>();
      const string unrecognizedNameArg = "-" + ZenUnit::Random<string>() + "=" + ZenUnit::Random<string>();
      const vector<string> stringArgs{ _testProgramPath, unrecognizedNameArg };
      //
      THROWS(const ZenUnitArgs zenUnitArgs = _argsParser.Parse(stringArgs), WriteLineAndExitException, "");
      //
      ZENMOCK(_consoleMock->WriteLineMock.CalledOnceWith(
         "ZenUnit command line usage error: Unrecognized --name=value argument: " + unrecognizedNameArg + "\n"));
      ZENMOCK(_consoleMock->WriteLineAndExitMock.CalledOnceWith(_expectedUsage, 1));
   }

   TEST(SetRandomSeedIfNotSetByUser_RandomSeedSetByUser_DoesNothing)
   {
      ZenUnitArgs zenUnitArgs = ZenUnit::Random<ZenUnitArgs>();
      zenUnitArgs.randomSeedSetByUser = true;
      ZenUnitArgs expectedResultingZenUnitArgs = zenUnitArgs;
      //
      _argsParser.SetRandomSeedIfNotSetByUser(zenUnitArgs);
      //
      ARE_EQUAL(expectedResultingZenUnitArgs, zenUnitArgs);
   }

   TEST(SetRandomSeedIfNotSetByUser_RandomSeedNotSetByUser_SetsRandomSeedToSecondsSince1970)
   {
      ZenUnitArgs zenUnitArgs = ZenUnit::Random<ZenUnitArgs>();
      zenUnitArgs.randomSeedSetByUser = false;

      ZenUnitArgs expectedResultingZenUnitArgs = zenUnitArgs;
      const long long secondsSince1970 = _watchMock->SecondsSince1970Mock.ReturnRandom();
      //
      _argsParser.SetRandomSeedIfNotSetByUser(zenUnitArgs);
      //
      ZENMOCK(_watchMock->SecondsSince1970Mock.CalledOnce());
      expectedResultingZenUnitArgs.randomSeed = static_cast<unsigned>(secondsSince1970);
      ARE_EQUAL(expectedResultingZenUnitArgs, zenUnitArgs);
   }

   RUN_TESTS(ArgsParserTests)
}
