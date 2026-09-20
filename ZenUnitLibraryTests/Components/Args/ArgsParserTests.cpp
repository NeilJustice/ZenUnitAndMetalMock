#include "pch.h"
#include "ZenUnitLibraryTests/ValueTypes/Args/ExpectedCommandLineUsage.h"
#include "ZenUnitLibraryTests/Components/Args/MetalMock/TestNameFilterStringParserMock.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/TestNameFilterEqualizerAndRandom.h"
#include "ZenUnitTestUtils/EqualizersAndRandoms/ZenUnitArgsEqualizerAndRandom.h"
#include "ZenUnitUtilsAndAssertionTests/Components/FunctionCallers/MetalMock/NonVoidOneArgMemberFunctionCallerMock.h"
#include "ZenUnitUtilsAndAssertionTests/Components/Time/MetalMock/WatchMock.h"

namespace ZenUnit
{
   TESTS(ArgsParserTests)
   AFACT(ParseStringArgs_ArgsOnlyExePath_ReturnsDefaultZenUnitArgsWithCommandLineAndTestProgramNameSet)
   FACTS(ParseStringArgs_InvalidArgument_PrintsErrorMessageAndCommandLineUsageAndExits1)
   AFACT(ParseStringArgs_DashDashHelp_PrintsCommandLineUsageAndExits0)
   AFACT(ParseStringArgs_DashDashVersion_PrintsVersionAndExits0)
   AFACT(ParseStringArgs_AllArgumentsSpecifiedExpectForTestNameFilter_ReturnsZenUnitArgsWithAllFieldsSet)
   AFACT(ParseStringArgs_DashDashRun_ReturnsZenUnitArgsWithExpectedTestNameFilters)
   AFACT(ParseStringArgs_ValidBoolArg_ReturnsExpectedZenUnitArgs)
   AFACT(ParseStringArgs_ValidBoolArgSpecifiedTwice_ReturnsExpectedZenUnitArgs)
   FACTS(ParseStringArgs_ArgContainsEqualsSign_ValueIsEmptyString_PrintsErrorMessageAndCommandLineUsageAndExits1)
   AFACT(ParseStringArgs_TimesEqualsArg_StringToUnsignedThrowsInvalidArgumentWhenProcessingValue_PrintsErrorMessageAndCommandLineUsageAndExits1)
   AFACT(ParseStringArgs_TimesEqualsArg_ValidUnsignedValue_ReturnsExpectedZenUnitArgs)
   AFACT(ParseStringArgs_RandomEqualsArg_ValidRandomUnsignedValue_ReturnsExpectedZenUnitArgs)
   AFACT(ParseStringArgs_UnrecognizedEqualsSignArgName_PrintsCommandLineUsageAndExits1)
   AFACT(GetSecondsSince1970RandomSeedIfNotSetByUser_RandomSeedCommandLineArgumentIsNotUnsignedMaxValue_ReturnsRandomSeedPotentiallySetByUser)
   AFACT(GetSecondsSince1970RandomSeedIfNotSetByUser_RandomSeedCommandLineArgumentIsUnsignedMaxValue_ReturnsSecondsSince1970)
   EVIDENCE

   const string _testProgramPath = Random<string>();

   ArgsParser _argsParser;
   // Function Pointers
   METALMOCK_NONVOID1_STATIC_OR_FREE(int, _call_String_ToInt, std::string_view)
   METALMOCK_NONVOID1_STATIC_OR_FREE(unsigned short, _call_String_ToUnsignedShort, std::string_view)
   // Function Callers
   using _caller_GetSecondsSince1970RandomSeedIfNotSetByUserMockType = NonVoidOneArgMemberFunctionCallerMock<unsigned short, ArgsParser, unsigned short>;
   _caller_GetSecondsSince1970RandomSeedIfNotSetByUserMockType* _caller_GetSecondsSince1970RandomSeedIfNotSetByUserMock = nullptr;
   // Constant Components
   ConsoleMock* _consoleMock = nullptr;
   TestNameFilterStringParserMock* _testNameFilterStringParserMock = nullptr;
   WatchMock* _watchMock = nullptr;

   STARTUP
   {
      // Function Pointers
      _argsParser._call_String_ToInt = BIND_1ARG_METALMOCK_OBJECT(_call_String_ToIntMock);
      _argsParser._call_String_ToUnsignedShort = BIND_1ARG_METALMOCK_OBJECT(_call_String_ToUnsignedShortMock);
      // Function Callers
      _argsParser._caller_GetSecondsSince1970RandomSeedIfNotSetByUser.reset(_caller_GetSecondsSince1970RandomSeedIfNotSetByUserMock = new _caller_GetSecondsSince1970RandomSeedIfNotSetByUserMockType);
      // Constant Components
      _argsParser._console.reset(_consoleMock = new ConsoleMock);
      _argsParser._testNameFilterStringParser.reset(_testNameFilterStringParserMock = new TestNameFilterStringParserMock);
      _argsParser._watch.reset(_watchMock = new WatchMock);
   }

   unsigned short ExpectCallToGetSecondsSince1970RandomSeedIfNotSetByUser()
   {
      const unsigned short randomSeed = ZenUnit::Random<unsigned short>();
      _caller_GetSecondsSince1970RandomSeedIfNotSetByUserMock->CallConstMemberFunctionMock.Return(randomSeed);
      return randomSeed;
   }

   void AssertCallToGetSecondsSince1970RandomSeedIfNotSetByUser(unsigned short expectedRandomSeedPotentiallySetByUser)
   {
      METALMOCK(_caller_GetSecondsSince1970RandomSeedIfNotSetByUserMock->CallConstMemberFunctionMock.CalledOnceWith(
         &_argsParser, &ArgsParser::GetSecondsSince1970RandomSeedIfNotSetByUser, expectedRandomSeedPotentiallySetByUser));
   }

   TEST(ParseStringArgs_ArgsOnlyExePath_ReturnsDefaultZenUnitArgsWithCommandLineAndTestProgramNameSet)
   {
      const string startDateTime = _watchMock->DateTimeNowMock.ReturnRandom();
      const unsigned short randomSeed = ExpectCallToGetSecondsSince1970RandomSeedIfNotSetByUser();
      vector<string> stringArgs{ _testProgramPath };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.ParseStringArgs(stringArgs);
      //
      METALMOCK(_watchMock->DateTimeNowMock.CalledOnce());
      AssertCallToGetSecondsSince1970RandomSeedIfNotSetByUser(numeric_limits<unsigned short>::max());
      ZenUnitArgs expectedZenUnitArgs{};
      expectedZenUnitArgs.commandLine = _testProgramPath;
      expectedZenUnitArgs.startDateTime = startDateTime;
      ARE_EQUAL(randomSeed, globalZenUnitMode.randomSeed);
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST1X1(ParseStringArgs_InvalidArgument_PrintsErrorMessageAndCommandLineUsageAndExits1,
      const string& invalidArgument,
      "--abc",
      "--Always-exit-0",
      "--test-runs")
   {
      _consoleMock->WriteLineMock.Expect();
      _consoleMock->WriteLineAndExitMock.ThrowExceptionWhenCalled<WriteLineAndExitException>();
      const vector<string> stringArgs { _testProgramPath, invalidArgument };
      //
      THROWS_EXCEPTION(_argsParser.ParseStringArgs(stringArgs),
         WriteLineAndExitException, "");
      //
      METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith(
         "ZenUnit command line usage error: Invalid argument \"" + invalidArgument + "\"\n"));
      METALMOCK(_consoleMock->WriteLineAndExitMock.CalledOnceWith(ExpectedCommandLineUsage, 1));
   }

   TEST(ParseStringArgs_DashDashHelp_PrintsCommandLineUsageAndExits0)
   {
      _consoleMock->WriteLineAndExitMock.ThrowExceptionWhenCalled<WriteLineAndExitException>();
      const vector<string> stringArgs { _testProgramPath, "--help" };
      //
      THROWS_EXCEPTION(_argsParser.ParseStringArgs(stringArgs),
         WriteLineAndExitException, "");
      //
      METALMOCK(_consoleMock->WriteLineAndExitMock.CalledOnceWith(ExpectedCommandLineUsage, 0));
   }

   TEST(ParseStringArgs_DashDashVersion_PrintsVersionAndExits0)
   {
      _consoleMock->WriteLineAndExitMock.ThrowExceptionWhenCalled<WriteLineAndExitException>();
      const vector<string> stringArgs { _testProgramPath, "--version" };
      //
      THROWS_EXCEPTION(_argsParser.ParseStringArgs(stringArgs),
         WriteLineAndExitException, "");
      //
      METALMOCK(_consoleMock->WriteLineAndExitMock.CalledOnceWith("v1.0.0", 0));
   }

   TEST(ParseStringArgs_AllArgumentsSpecifiedExpectForTestNameFilter_ReturnsZenUnitArgsWithAllFieldsSet)
   {
      const int testruns = _call_String_ToIntMock.ReturnRandom();

      const unsigned short randomSeedToUnsignedShortReturnValue = ZenUnit::Random<unsigned short>();
      const unsigned short maxTestMilliseconds = ZenUnit::Random<unsigned short>();
      _call_String_ToUnsignedShortMock.ReturnValues(
         randomSeedToUnsignedShortReturnValue,
         maxTestMilliseconds);

      const unsigned short randomSeed = ExpectCallToGetSecondsSince1970RandomSeedIfNotSetByUser();
      const string startDateTime = _watchMock->DateTimeNowMock.ReturnRandom();
      const vector<string> stringArgs =
      {
         _testProgramPath,
         "--pause-before",
         "--pause-after",
         "--always-exit-0",
         "--fail-fast",
         "--exit-1-if-tests-skipped",
         "--random",
         "--test-runs=" + to_string(testruns),
         "--random-seed=" + to_string(randomSeed),
         "--max-test-milliseconds=" + to_string(maxTestMilliseconds)
      };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.ParseStringArgs(stringArgs);
      //
      METALMOCK(_call_String_ToUnsignedShortMock.CalledNTimes(2));
      METALMOCKTHEN(_call_String_ToIntMock.CalledOnceWith(to_string(testruns))).Then(
      METALMOCKTHEN(_call_String_ToUnsignedShortMock.CalledWith(to_string(randomSeed)))).Then(
      METALMOCKTHEN(_call_String_ToUnsignedShortMock.CalledWith(to_string(maxTestMilliseconds)))).Then(
      METALMOCKTHEN(_watchMock->DateTimeNowMock.CalledOnce()));
      AssertCallToGetSecondsSince1970RandomSeedIfNotSetByUser(randomSeedToUnsignedShortReturnValue);
      ZenUnitArgs expectedZenUnitArgs{};
      expectedZenUnitArgs.commandLine = VectorUtils::JoinWithSeparator(stringArgs, ' ');
      expectedZenUnitArgs.pauseBefore = true;
      expectedZenUnitArgs.pauseAfter = true;
      expectedZenUnitArgs.alwaysExit0 = true;
      expectedZenUnitArgs.failFast = true;
      expectedZenUnitArgs.exit1IfTestsSkipped = true;
      expectedZenUnitArgs.randomTestOrdering = true;
      expectedZenUnitArgs.globalRandomSeedSetByUser = true;
      expectedZenUnitArgs.testRuns = testruns;
      expectedZenUnitArgs.startDateTime = startDateTime;
      expectedZenUnitArgs.maxTestMilliseconds = maxTestMilliseconds;
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
      ARE_EQUAL(randomSeed, ZenUnit::globalZenUnitMode.randomSeed);
   }

   TEST(ParseStringArgs_DashDashRun_ReturnsZenUnitArgsWithExpectedTestNameFilters)
   {
      const unsigned short randomSeed =
         _caller_GetSecondsSince1970RandomSeedIfNotSetByUserMock->CallConstMemberFunctionMock.ReturnRandom();

      const vector<TestNameFilter> testNameFilters = { Random<TestNameFilter>() };
      _testNameFilterStringParserMock->ParseTestNameFilterStringsMock.Return(testNameFilters);

      const string unusedDateTimeNow = _watchMock->DateTimeNowMock.ReturnRandom();

      const string runArgument = ZenUnit::Random<string>();
      const vector<string> stringArgs { ZenUnit::Random<string>(), "--run=" + runArgument };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.ParseStringArgs(stringArgs);
      //
      METALMOCK(_watchMock->DateTimeNowMock.CalledOnce());
      const vector<string> splitRunArgument = String::Split(runArgument, ',');
      METALMOCK(_testNameFilterStringParserMock->ParseTestNameFilterStringsMock.CalledOnceWith(splitRunArgument));
      AssertCallToGetSecondsSince1970RandomSeedIfNotSetByUser(numeric_limits<unsigned short>::max());
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = VectorUtils::JoinWithSeparator(stringArgs, ' ');
      expectedZenUnitArgs.testNameFilters = testNameFilters;
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
      ARE_EQUAL(randomSeed, ZenUnit::globalZenUnitMode.randomSeed);
   }

   TEST(ParseStringArgs_ValidBoolArg_ReturnsExpectedZenUnitArgs)
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

      AssertArgSetsBoolField("--random", &ZenUnitArgs::randomTestOrdering);
      Startup();
   }
   void AssertArgSetsBoolField(const string& arg, bool ZenUnitArgs::* expectedFieldToBeSet)
   {
      _watchMock->DateTimeNowMock.ReturnRandom();
      const unsigned short randomSeed = ExpectCallToGetSecondsSince1970RandomSeedIfNotSetByUser();
      const vector<string> stringArgs { _testProgramPath, arg };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.ParseStringArgs(stringArgs);
      //
      METALMOCK(_watchMock->DateTimeNowMock.CalledOnce());
      AssertCallToGetSecondsSince1970RandomSeedIfNotSetByUser(numeric_limits<unsigned short>::max());
      ZenUnitArgs expectedZenUnitArgs{};
      expectedZenUnitArgs.commandLine = _testProgramPath + " " + arg;
      (expectedZenUnitArgs.*expectedFieldToBeSet) = true;
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
      ARE_EQUAL(randomSeed, ZenUnit::globalZenUnitMode.randomSeed);
   }

   TEST(ParseStringArgs_ValidBoolArgSpecifiedTwice_ReturnsExpectedZenUnitArgs)
   {
      _watchMock->DateTimeNowMock.ReturnRandom();
      const unsigned short randomSeed = ExpectCallToGetSecondsSince1970RandomSeedIfNotSetByUser();
      const vector<string> stringArgs { _testProgramPath, "--always-exit-0", "--always-exit-0" };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.ParseStringArgs(stringArgs);
      //
      METALMOCK(_watchMock->DateTimeNowMock.CalledOnce());
      AssertCallToGetSecondsSince1970RandomSeedIfNotSetByUser(numeric_limits<unsigned short>::max());
      ZenUnitArgs expectedZenUnitArgs{};
      expectedZenUnitArgs.commandLine = VectorUtils::JoinWithSeparator(stringArgs, ' ');
      expectedZenUnitArgs.alwaysExit0 = true;
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
      ARE_EQUAL(randomSeed, ZenUnit::globalZenUnitMode.randomSeed);
   }

   TEST1X1(ParseStringArgs_ArgContainsEqualsSign_ValueIsEmptyString_PrintsErrorMessageAndCommandLineUsageAndExits1,
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
      THROWS_EXCEPTION(_argsParser.ParseStringArgs(stringArgs),
         WriteLineAndExitException, "");
      //
      const string expectedErrorMessage =
         "ZenUnit command line usage error: " + string("String::Split(arg, '=') unexpectedly returned not 2 for arg = \"" + arg + "\"") + "\n";
      METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith(expectedErrorMessage));
      METALMOCK(_consoleMock->WriteLineAndExitMock.CalledOnceWith(ExpectedCommandLineUsage, 1));
   }

   TEST(ParseStringArgs_TimesEqualsArg_StringToUnsignedThrowsInvalidArgumentWhenProcessingValue_PrintsErrorMessageAndCommandLineUsageAndExits1)
   {
      _consoleMock->WriteLineMock.Expect();
      _consoleMock->WriteLineAndExitMock.ThrowExceptionWhenCalled<WriteLineAndExitException>();
      _call_String_ToIntMock.ThrowExceptionWhenCalled<invalid_argument>("");
      const string invalidTestRunsArg = "--test-runs=-1_for_example";
      const vector<string> stringArgs { _testProgramPath, invalidTestRunsArg };
      //
      THROWS_EXCEPTION(_argsParser.ParseStringArgs(stringArgs),
         WriteLineAndExitException, "");
      //
      METALMOCKTHEN(_call_String_ToIntMock.CalledOnceWith("-1_for_example")).Then(
      METALMOCKTHEN(_consoleMock->WriteLineMock.CalledOnceWith(
         "ZenUnit command line usage error: Invalid --name=value argument value: " + invalidTestRunsArg + "\n"))).Then(
      METALMOCKTHEN(_consoleMock->WriteLineAndExitMock.CalledOnceWith(ExpectedCommandLineUsage, 1)));
   }

   TEST(ParseStringArgs_TimesEqualsArg_ValidUnsignedValue_ReturnsExpectedZenUnitArgs)
   {
      _watchMock->DateTimeNowMock.ReturnRandom();
      const unsigned short randomSeed = ExpectCallToGetSecondsSince1970RandomSeedIfNotSetByUser();
      const int testRuns = _call_String_ToIntMock.ReturnRandom();
      const vector<string> stringArgs{ _testProgramPath, "--test-runs=" + to_string(testRuns) };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.ParseStringArgs(stringArgs);
      //
      METALMOCK(_watchMock->DateTimeNowMock.CalledOnce());
      METALMOCK(_call_String_ToIntMock.CalledOnceWith(to_string(testRuns)));
      AssertCallToGetSecondsSince1970RandomSeedIfNotSetByUser(numeric_limits<unsigned short>::max());
      ZenUnitArgs expectedZenUnitArgs{};
      expectedZenUnitArgs.commandLine = VectorUtils::JoinWithSeparator(stringArgs, ' ');
      expectedZenUnitArgs.testRuns = testRuns;
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
      ARE_EQUAL(randomSeed, ZenUnit::globalZenUnitMode.randomSeed);
   }

   TEST(ParseStringArgs_RandomEqualsArg_ValidRandomUnsignedValue_ReturnsExpectedZenUnitArgs)
   {
      _watchMock->DateTimeNowMock.ReturnRandom();
      const unsigned short randomSeed = ExpectCallToGetSecondsSince1970RandomSeedIfNotSetByUser();
      const unsigned short randomSeedToUnsignedReturnValue = _call_String_ToUnsignedShortMock.ReturnRandom();
      const vector<string> stringArgs{ _testProgramPath, "--random-seed=" + to_string(randomSeed) };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.ParseStringArgs(stringArgs);
      //
      METALMOCK(_call_String_ToUnsignedShortMock.CalledOnceWith(to_string(randomSeed)));
      METALMOCK(_watchMock->DateTimeNowMock.CalledOnce());
      ZenUnitArgs expectedZenUnitArgs{};
      expectedZenUnitArgs.commandLine = VectorUtils::JoinWithSeparator(stringArgs, ' ');
      expectedZenUnitArgs.randomTestOrdering = false;
      expectedZenUnitArgs.globalRandomSeedSetByUser = true;
      AssertCallToGetSecondsSince1970RandomSeedIfNotSetByUser(randomSeedToUnsignedReturnValue);
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
      ARE_EQUAL(randomSeed, ZenUnit::globalZenUnitMode.randomSeed);
   }

   TEST(ParseStringArgs_UnrecognizedEqualsSignArgName_PrintsCommandLineUsageAndExits1)
   {
      _consoleMock->WriteLineMock.Expect();
      _consoleMock->WriteLineAndExitMock.ThrowExceptionWhenCalled<WriteLineAndExitException>();
      const string unrecognizedNameArg = String::ConcatStrings("-", ZenUnit::Random<string>(), "=", ZenUnit::Random<string>());
      const vector<string> stringArgs{ _testProgramPath, unrecognizedNameArg };
      //
      THROWS_EXCEPTION(_argsParser.ParseStringArgs(stringArgs),
         WriteLineAndExitException, "");
      //
      const string expectedErrorMessage = String::ConcatStrings(
         "ZenUnit command line usage error: Unrecognized --name=value argument: ", unrecognizedNameArg, "\n");
      METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith(expectedErrorMessage));
      METALMOCK(_consoleMock->WriteLineAndExitMock.CalledOnceWith(ExpectedCommandLineUsage, 1));
   }

   TEST(GetSecondsSince1970RandomSeedIfNotSetByUser_RandomSeedCommandLineArgumentIsNotUnsignedMaxValue_ReturnsRandomSeedPotentiallySetByUser)
   {
      const unsigned short randomSeedCommandLineArgument = ZenUnit::RandomNotEqualTo<unsigned short>(numeric_limits<unsigned short>::max());
      //
      const unsigned short randomSeed = _argsParser.GetSecondsSince1970RandomSeedIfNotSetByUser(randomSeedCommandLineArgument);
      //
      ARE_EQUAL(randomSeedCommandLineArgument, randomSeed);
   }

   TEST(GetSecondsSince1970RandomSeedIfNotSetByUser_RandomSeedCommandLineArgumentIsUnsignedMaxValue_ReturnsSecondsSince1970)
   {
      const unsigned short secondsSince1970 = _watchMock->SecondsSince1970StaticCastToUnsignedShortMock.ReturnRandom();
      constexpr unsigned short randomSeedCommandLineArgument = numeric_limits<unsigned short>::max();
      //
      const unsigned short randomSeed = _argsParser.GetSecondsSince1970RandomSeedIfNotSetByUser(randomSeedCommandLineArgument);
      //
      METALMOCK(_watchMock->SecondsSince1970StaticCastToUnsignedShortMock.CalledOnce());
      ARE_EQUAL(secondsSince1970, randomSeed);
   }

   RUN_TESTS(ArgsParserTests)
}
