#include "pch.h"
#include "ZenUnitLibraryTests/Components/Args/MetalMock/TestNameFilterStringParserMock.h"
#include "ZenUnitLibraryTests/Components/Console/MetalMock/ConsoleMock.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestNameFilterEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/ZenUnitArgsEqualizerAndRandom.h"
#include "ZenUnitUtilsAndAssertionTests/Components/FunctionCallers/MetalMock/VoidOneArgMemberFunctionCallerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/Time/MetalMock/WatchMock.h"

namespace ZenUnit
{
   TESTS(ArgsParserTests)
   AFACT(DefaultConstructor_NewsComponents_SetsStringToUnsignedFunction)
   AFACT(Parse_ArgsOnlyExePath_ReturnsDefaultZenUnitArgsWithCommandLineAndTestProgramNameSet)
   FACTS(Parse_ArgsSizeGreaterThanOrEqualTo13_PrintsTooManyArgumentsErrorMessageAndCommandLineUsageAndExits1)
   FACTS(Parse_InvalidArgument_PrintsErrorMessageAndCommandLineUsageAndExits1)
   AFACT(Parse_DashDashHelp_PrintsCommandLineUsageAndExits0)
   AFACT(Parse_DashDashVersion_PrintsVersionAndExits0)
   AFACT(Parse_AllArgumentsSpecifiedExpectForTestNameFilter_ReturnsZenUnitArgsWithAllFieldsSet)
   AFACT(Parse_DashDashRun_ReturnsZenUnitArgsWithExpectedTestNameFilters)
   AFACT(Parse_ValidBoolArg_ReturnsExpectedZenUnitArgs)
   AFACT(Parse_ValidBoolArgSpecifiedTwice_ReturnsExpectedZenUnitArgs)
   FACTS(Parse_ArgContainsEqualsSign_ValueIsEmptyString_PrintsErrorMessageAndCommandLineUsageAndExits1)
   AFACT(Parse_TimesEqualsArg_StringToUnsignedThrowsInvalidArgumentWhenProcessingValue_PrintsErrorMessageAndCommandLineUsageAndExits1)
   AFACT(Parse_TimesEqualsArg_ValidUnsignedValue_ReturnsExpectedZenUnitArgs)
   AFACT(Parse_RandomEqualsArg_ValidRandomUnsignedValue_ReturnsExpectedZenUnitArgs)
   AFACT(Parse_UnrecognizedEqualsSignArgName_PrintsCommandLineUsageAndExits1)
   AFACT(SetRandomSeedIfNotSetByUser_RandomSeedSetByUser_DoesNothing)
   AFACT(SetRandomSeedIfNotSetByUser_RandomSeedNotSetByUser_SetsRandomSeedToSecondsSince1970)
   EVIDENCE

   const string _testProgramPath = Random<string>();
   const string _expectedCommandLineUsage = "C++ Unit Testing Framework ZenUnit v" + std::string(Version::Number()) + R"(
https://github.com/NeilJustice/ZenUnitAndMetalMock
Usage: <ZenUnitTestsBinaryName> [Options...]

Testing Rigorousness:

--test-runs=<N>
   Repeat N times the running of all tests.
   Specify -1 to repeat forever the running of all tests.
--random-test-ordering
   Run test classes, tests, and value-parameterized test cases in a random order.
--random-seed=<32BitUnsignedInteger>
   Sets the random seed which sets the test ordering for --random-test-ordering and
   sets the sequence of values returned by the ZenUnit::Random<T>
   family of random-value-generating functions.
   The default random seed is the number of seconds since 1970-01-01 00:00:00 UTC.
--exit-1-if-tests-skipped
   After having run all tests, exit with code 1 if any tests were skipped.

Testing Filtration:

--run=<TestClassName>[::TestName][/TestCaseNumber][,...]
   Run only specified case-insensitive test classes, tests, and/or test case numbers.
   Add a '*' character to the end of a test class name or test name to indicate name-starts-with.
 Example 1: --run=APITests
   Run only test class APITests.
 Example 2: --run=APITests::FunctionUnderTest*
   Run only tests in APITests that start with "FunctionUnderTest".
 Example 3: --run=APITests::FunctionUnderTest_ArgumentsUnderTest_ExpectedReturnValue/3
   Run only the third test case of the value-parameterized test named
   APITests::FunctionUnderTest_ArgumentsUnderTest_ExpectedReturnValue
--fail-fast
   Call exit(1) if a test fails.

Testing Utility:

--pause-before
   Wait for any key before running tests to allow for attaching a debugger or performance profiler.
--pause-after
   Wait for any key after running tests.
--always-exit-0
   Always exit with code 0.
--help
   Print this command line usage message.
--version
   Print the ZenUnit version number.

Example ZenUnit command line arguments:

./SafetyCriticalUnitTests --test-runs=5 --random-test-ordering --exit-1-if-tests-skipped
./FinanciallyCriticalUnitTests --run=MarketDataDispatcherTests --fail-fast
)";

   ArgsParser _argsParser;
   METALMOCK_NONVOID1_STATIC(int, ZenUnit::String, ToInt, std::string_view)
   METALMOCK_NONVOID1_STATIC(unsigned, ZenUnit::String, ToUnsigned, std::string_view)
   VoidOneArgMemberFunctionCallerMock<ArgsParser, ZenUnitArgs&>* _caller_SetRandomSeedIfNotSetByUserMock = nullptr;
   ConsoleMock* _consoleMock = nullptr;
   TestNameFilterStringParserMock* _testNameFilterStringParserMock = nullptr;
   WatchMock* _watchMock = nullptr;

   STARTUP
   {
      _argsParser._call_String_ToInt = BIND_1ARG_METALMOCK_OBJECT(ToIntMock);
      _argsParser._call_String_ToUnsigned = BIND_1ARG_METALMOCK_OBJECT(ToUnsignedMock);
      _argsParser._caller_SetRandomSeedIfNotSetByUser.reset(
         _caller_SetRandomSeedIfNotSetByUserMock = new VoidOneArgMemberFunctionCallerMock<ArgsParser, ZenUnitArgs&>);
      _argsParser._console.reset(_consoleMock = new ConsoleMock);
      _argsParser._testNameFilterStringParser.reset(_testNameFilterStringParserMock = new TestNameFilterStringParserMock);
      _argsParser._watch.reset(_watchMock = new WatchMock);
   }

   TEST(DefaultConstructor_NewsComponents_SetsStringToUnsignedFunction)
   {
      ArgsParser argsParser;
      STD_FUNCTION_TARGETS(String::ToInt, argsParser._call_String_ToInt);
      STD_FUNCTION_TARGETS(String::ToUnsigned, argsParser._call_String_ToUnsigned);
      DELETE_TO_ASSERT_NEWED(argsParser._caller_SetRandomSeedIfNotSetByUser);
      DELETE_TO_ASSERT_NEWED(argsParser._console);
      DELETE_TO_ASSERT_NEWED(argsParser._testNameFilterStringParser);
      DELETE_TO_ASSERT_NEWED(argsParser._watch);
   }

   void ExpectCallToSetRandomSeedIfNotSetByUser()
   {
      _caller_SetRandomSeedIfNotSetByUserMock->ConstCallMock.Expect();
   }

   void AssertCallToSetRandomSeedIfNotSetByUser(ZenUnitArgs& expectedZenUnitArgsArg)
   {
      METALMOCK(_caller_SetRandomSeedIfNotSetByUserMock->ConstCallMock.CalledOnceWith(
         &_argsParser, &ArgsParser::SetRandomSeedIfNotSetByUser, expectedZenUnitArgsArg));
   }

   TEST(Parse_ArgsOnlyExePath_ReturnsDefaultZenUnitArgsWithCommandLineAndTestProgramNameSet)
   {
      const string startDateTime = _watchMock->DateTimeNowMock.ReturnRandom();
      ExpectCallToSetRandomSeedIfNotSetByUser();
      vector<string> stringArgs{ _testProgramPath };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(stringArgs);
      //
      METALMOCK(_watchMock->DateTimeNowMock.CalledOnce());
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = _testProgramPath;
      expectedZenUnitArgs.startDateTime = startDateTime;
      AssertCallToSetRandomSeedIfNotSetByUser(expectedZenUnitArgs);
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST1X1(Parse_ArgsSizeGreaterThanOrEqualTo13_PrintsTooManyArgumentsErrorMessageAndCommandLineUsageAndExits1,
      size_t numberOfStringArgs,
      13ull,
      14ull)
   {
      _consoleMock->WriteLineMock.Expect();
      _consoleMock->WriteLineAndExitMock.ThrowExceptionWhenCalled<WriteLineAndExitException>();
      const vector<string> stringArgs(numberOfStringArgs);
      //
      THROWS_EXCEPTION(const ZenUnitArgs zenUnitArgs = _argsParser.Parse(stringArgs), WriteLineAndExitException, "");
      //
      METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith("ZenUnit command line usage error: Too many arguments.\n"));
      METALMOCK(_consoleMock->WriteLineAndExitMock.CalledOnceWith(_expectedCommandLineUsage, 1));
   }

   TEST1X1(Parse_InvalidArgument_PrintsErrorMessageAndCommandLineUsageAndExits1,
      const string& invalidArgument,
      "--abc",
      "--Always-exit-0",
      "--test-runs")
   {
      _consoleMock->WriteLineMock.Expect();
      _consoleMock->WriteLineAndExitMock.ThrowExceptionWhenCalled<WriteLineAndExitException>();
      const vector<string> stringArgs { _testProgramPath, invalidArgument };
      //
      THROWS_EXCEPTION(const ZenUnitArgs zenUnitArgs = _argsParser.Parse(stringArgs), WriteLineAndExitException, "");
      //
      METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith(
         "ZenUnit command line usage error: Invalid argument \"" + invalidArgument + "\"\n"));
      METALMOCK(_consoleMock->WriteLineAndExitMock.CalledOnceWith(_expectedCommandLineUsage, 1));
   }

   TEST(Parse_DashDashHelp_PrintsCommandLineUsageAndExits0)
   {
      _consoleMock->WriteLineAndExitMock.ThrowExceptionWhenCalled<WriteLineAndExitException>();
      const vector<string> stringArgs { _testProgramPath, "--help" };
      //
      THROWS_EXCEPTION(const ZenUnitArgs zenUnitArgs = _argsParser.Parse(stringArgs), WriteLineAndExitException, "");
      //
      METALMOCK(_consoleMock->WriteLineAndExitMock.CalledOnceWith(_expectedCommandLineUsage, 0));
   }

   TEST(Parse_DashDashVersion_PrintsVersionAndExits0)
   {
      _consoleMock->WriteLineAndExitMock.ThrowExceptionWhenCalled<WriteLineAndExitException>();
      const vector<string> stringArgs { _testProgramPath, "--version" };
      //
      THROWS_EXCEPTION(const ZenUnitArgs zenUnitArgs = _argsParser.Parse(stringArgs), WriteLineAndExitException, "");
      //
      METALMOCK(_consoleMock->WriteLineAndExitMock.CalledOnceWith("0.7.1", 0));
   }

   TEST(Parse_AllArgumentsSpecifiedExpectForTestNameFilter_ReturnsZenUnitArgsWithAllFieldsSet)
   {
      const int testruns = ToIntMock.ReturnRandom();
      const unsigned randomSeed = ToUnsignedMock.ReturnRandom();
      _caller_SetRandomSeedIfNotSetByUserMock->ConstCallMock.Expect();
      const string startDateTime = _watchMock->DateTimeNowMock.ReturnRandom();
      const vector<string> stringArgs
      {
         _testProgramPath,
         "--pause-before",
         "--pause-after",
         "--always-exit-0",
         "--fail-fast",
         "--exit-1-if-tests-skipped",
         "--random-test-ordering",
         "--test-runs=" + to_string(testruns),
         "--random-seed=" + to_string(randomSeed)
      };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(stringArgs);
      //
      METALMOCK(ToIntMock.CalledOnceWith(to_string(testruns)));
      METALMOCK(ToUnsignedMock.CalledOnceWith(to_string(randomSeed)));
      METALMOCK(_watchMock->DateTimeNowMock.CalledOnce());
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = VectorUtils::JoinWithSeparator(stringArgs, ' ');
      expectedZenUnitArgs.pauseBefore = true;
      expectedZenUnitArgs.pauseAfter = true;
      expectedZenUnitArgs.alwaysExit0 = true;
      expectedZenUnitArgs.failFast = true;
      expectedZenUnitArgs.exit1IfTestsSkipped = true;
      expectedZenUnitArgs.randomTestOrdering = true;
      expectedZenUnitArgs.testRuns = testruns;
      expectedZenUnitArgs.randomSeed = randomSeed;
      expectedZenUnitArgs.randomSeedSetByUser = true;
      expectedZenUnitArgs.startDateTime = startDateTime;
      AssertCallToSetRandomSeedIfNotSetByUser(expectedZenUnitArgs);
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST(Parse_DashDashRun_ReturnsZenUnitArgsWithExpectedTestNameFilters)
   {
      _caller_SetRandomSeedIfNotSetByUserMock->ConstCallMock.Expect();

      const vector<TestNameFilter> testNameFilters = { Random<TestNameFilter>() };
      _testNameFilterStringParserMock->ParseTestNameFilterStringsMock.Return(testNameFilters);

      const string unusedDateTimeNow = _watchMock->DateTimeNowMock.ReturnRandom();

      const string runArgument = ZenUnit::Random<string>();
      const vector<string> stringArgs { ZenUnit::Random<string>(), "--run=" + runArgument };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(stringArgs);
      //
      const vector<string> splitRunArgument = String::Split(runArgument, ',');
      METALMOCK(_testNameFilterStringParserMock->ParseTestNameFilterStringsMock.CalledOnceWith(splitRunArgument));

      METALMOCK(_watchMock->DateTimeNowMock.CalledOnce());

      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = VectorUtils::JoinWithSeparator(stringArgs, ' ');
      expectedZenUnitArgs.testNameFilters = testNameFilters;
      AssertCallToSetRandomSeedIfNotSetByUser(expectedZenUnitArgs);
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST(Parse_ValidBoolArg_ReturnsExpectedZenUnitArgs)
   {
      AssertArgSetsBoolField("--pause-before", &ZenUnitArgs::pauseBefore);
      Startup();

      AssertArgSetsBoolField("--pause-after", &ZenUnitArgs::pauseAfter);
      Startup();

      AssertArgSetsBoolField("--always-exit-0", &ZenUnitArgs::alwaysExit0);
      Startup();

      AssertArgSetsBoolField("--fail-fast", &ZenUnitArgs::failFast);
      Startup();

      AssertArgSetsBoolField("--exit-1-if-tests-skipped", &ZenUnitArgs::exit1IfTestsSkipped);
      Startup();

      AssertArgSetsBoolField("--random-test-ordering", &ZenUnitArgs::randomTestOrdering);
      Startup();
   }
   void AssertArgSetsBoolField(const string& arg, bool ZenUnitArgs::* expectedFieldToBeSet)
   {
      const string dateTimeNow = _watchMock->DateTimeNowMock.ReturnRandom();
      ExpectCallToSetRandomSeedIfNotSetByUser();
      const vector<string> stringArgs { _testProgramPath, arg };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(stringArgs);
      //
      METALMOCK(_watchMock->DateTimeNowMock.CalledOnce());
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
      const vector<string> stringArgs { _testProgramPath, "--always-exit-0", "--always-exit-0" };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(stringArgs);
      //
      METALMOCK(_watchMock->DateTimeNowMock.CalledOnce());
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = VectorUtils::JoinWithSeparator(stringArgs, ' ');
      expectedZenUnitArgs.alwaysExit0 = true;
      AssertCallToSetRandomSeedIfNotSetByUser(expectedZenUnitArgs);
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST1X1(Parse_ArgContainsEqualsSign_ValueIsEmptyString_PrintsErrorMessageAndCommandLineUsageAndExits1,
      const string& arg,
      "--test-runs=",
      "--test-runs===",
      "--random-seed=",
      "--random-seed===")
   {
      _consoleMock->WriteLineMock.Expect();
      _consoleMock->WriteLineAndExitMock.ThrowExceptionWhenCalled<WriteLineAndExitException>();
      const vector<string> stringArgs { _testProgramPath, arg };
      //
      THROWS_EXCEPTION(const ZenUnitArgs zenUnitArgs = _argsParser.Parse(stringArgs), WriteLineAndExitException, "");
      //
      const string expectedErrorMessage =
         "ZenUnit command line usage error: " + string("String::Split(arg, '=') unexpectedly returned not 2 for arg = \"" + arg + "\"") + "\n";
      METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith(expectedErrorMessage));
      METALMOCK(_consoleMock->WriteLineAndExitMock.CalledOnceWith(_expectedCommandLineUsage, 1));
   }

   TEST(Parse_TimesEqualsArg_StringToUnsignedThrowsInvalidArgumentWhenProcessingValue_PrintsErrorMessageAndCommandLineUsageAndExits1)
   {
      _consoleMock->WriteLineMock.Expect();
      _consoleMock->WriteLineAndExitMock.ThrowExceptionWhenCalled<WriteLineAndExitException>();
      ToIntMock.ThrowExceptionWhenCalled<invalid_argument>("");
      const string InvalidTimesArg = "--test-runs=-1_for_example";
      const vector<string> stringArgs { _testProgramPath, InvalidTimesArg };
      //
      THROWS_EXCEPTION(const ZenUnitArgs zenUnitArgs = _argsParser.Parse(stringArgs), WriteLineAndExitException, "");
      //
      METALMOCK(ToIntMock.CalledOnceWith("-1_for_example"));
      METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith(
         "ZenUnit command line usage error: Invalid --name=value argument value: " + InvalidTimesArg + "\n"));
      METALMOCK(_consoleMock->WriteLineAndExitMock.CalledOnceWith(_expectedCommandLineUsage, 1));
   }

   TEST(Parse_TimesEqualsArg_ValidUnsignedValue_ReturnsExpectedZenUnitArgs)
   {
      const string dateTimeNow = _watchMock->DateTimeNowMock.ReturnRandom();

      ExpectCallToSetRandomSeedIfNotSetByUser();

      const int testRuns = ToIntMock.ReturnRandom();
      const vector<string> stringArgs{ _testProgramPath, "--test-runs=" + to_string(testRuns) };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(stringArgs);
      //
      METALMOCK(ToIntMock.CalledOnceWith(to_string(testRuns)));
      METALMOCK(_watchMock->DateTimeNowMock.CalledOnce());
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = VectorUtils::JoinWithSeparator(stringArgs, ' ');
      expectedZenUnitArgs.testRuns = testRuns;
      AssertCallToSetRandomSeedIfNotSetByUser(expectedZenUnitArgs);
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST(Parse_RandomEqualsArg_ValidRandomUnsignedValue_ReturnsExpectedZenUnitArgs)
   {
      const string dateTimeNow = _watchMock->DateTimeNowMock.ReturnRandom();
      ExpectCallToSetRandomSeedIfNotSetByUser();
      const unsigned randomSeed = ToUnsignedMock.ReturnRandom();
      const vector<string> stringArgs{ _testProgramPath, "--random-seed=" + to_string(randomSeed) };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(stringArgs);
      //
      METALMOCK(ToUnsignedMock.CalledOnceWith(to_string(randomSeed)));
      METALMOCK(_watchMock->DateTimeNowMock.CalledOnce());
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = VectorUtils::JoinWithSeparator(stringArgs, ' ');
      expectedZenUnitArgs.randomTestOrdering = false;
      expectedZenUnitArgs.randomSeed = randomSeed;
      expectedZenUnitArgs.randomSeedSetByUser = true;
      AssertCallToSetRandomSeedIfNotSetByUser(expectedZenUnitArgs);
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST(Parse_UnrecognizedEqualsSignArgName_PrintsCommandLineUsageAndExits1)
   {
      _consoleMock->WriteLineMock.Expect();
      _consoleMock->WriteLineAndExitMock.ThrowExceptionWhenCalled<WriteLineAndExitException>();
      const string unrecognizedNameArg = "-" + ZenUnit::Random<string>() + "=" + ZenUnit::Random<string>();
      const vector<string> stringArgs{ _testProgramPath, unrecognizedNameArg };
      //
      THROWS_EXCEPTION(const ZenUnitArgs zenUnitArgs = _argsParser.Parse(stringArgs), WriteLineAndExitException, "");
      //
      METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith(
         "ZenUnit command line usage error: Unrecognized --name=value argument: " + unrecognizedNameArg + "\n"));
      METALMOCK(_consoleMock->WriteLineAndExitMock.CalledOnceWith(_expectedCommandLineUsage, 1));
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
      METALMOCK(_watchMock->SecondsSince1970Mock.CalledOnce());
      expectedResultingZenUnitArgs.randomSeed = static_cast<unsigned>(secondsSince1970);
      ARE_EQUAL(expectedResultingZenUnitArgs, zenUnitArgs);
   }

   RUN_TESTS(ArgsParserTests)
}
