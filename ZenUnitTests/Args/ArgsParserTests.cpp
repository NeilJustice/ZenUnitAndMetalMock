#include "pch.h"
#include "ZenUnit/Args/ArgsParser.h"
#include "ZenUnit/Utils/Vector.h"
#include "ZenUnitTests/Args/Mock/RunFilterParserMock.h"
#include "ZenUnitTests/Console/Mock/ConsoleMock.h"

namespace ZenUnit
{
   TESTS(ArgsParserTests)
   AFACT(DefaultConstructor_NewsCompnents_SetsStringToUnsignedFunction)
   AFACT(Parse_ArgsOnlyExePath_ReturnsDefaultZenUnitArgsWithCommandLineAndTestProgramNameSet)
   FACTS(Parse_ArgsSizeGreaterThanOnePlusNumberOfValidArgs_PrintsErrorMessageAndUsageAndExits1)
   FACTS(Parse_InvalidArg_PrintsErrorMessageAndUsageAndExits1)
   FACTS(Parse_DashhelpOrDashDashhelp_PrintsUsageAndExits0)
   AFACT(Parse_AllArgsSpecified_ReturnsZenUnitArgsWithAllFieldsSets)
   FACTS(Parse_MinimalistOrDetailed_ReturnsExpectedZenUnitArgs)
   AFACT(Parse_Run_ReturnsExpectedZenUnitArgs)
   AFACT(Parse_Random_SetsRandomToTrue)
   AFACT(Parse_ValidBoolArg_ReturnsExpectedZenUnitArgs)
   AFACT(Parse_ValidBoolArgSpecifiedTwice_ReturnsExpectedZenUnitArgs)
   FACTS(Parse_EqualsSignContainingArg_EmptyValue_PrintsErrorMessageAndUsageAndExits1)
   AFACT(Parse_TimesEqualsArg_StringToUnsignedThrowsInvalidArgumentWhenProcessingValue_PrintsErrorMessageAndUsageAndExits1)
   AFACT(Parse_TimesEqualsArg_ValidUnsignedValue_ReturnsExpectedZenUnitArgs)
   AFACT(Parse_RandomEqualsArg_ValidRandomUnsignedValue_ReturnsExpectedZenUnitArgs)
   FACTS(Parse_RandomEqualsArg_ValidUnsignedValue_DowncastsValueToUnsignedShort_ReturnsExpectedZenUnitArgs)
   AFACT(Parse_UnrecognizedEqualsSignArgName_PrintsUsageAndExits1)
   EVIDENCE

   const string TestProgramPath = Random<string>();
   const string ExpectedUsage = R"(ZenUnit v0.1.0
Usage: <TestsBinaryName> [Options...]

Options:

None
   Run all non-skipped tests while printing detailed information.
-minimalist
   Print only preamble, any test failure details, and conclusion.
-run=<TestClassName[.TestName],TestClassName[.TestName]...>
   Run only specified case-insensitive test classes and/or tests.
-pause
   Wait for input before running tests to allow attaching a profiler or debugger.
-wait
   Wait for input before closing console window.
-exit0
   Always exit 0 regardless of test run outcome.
   Useful option for never blocking the launch of the Visual Studio debugger
   when running ZenUnit tests as a post-build event.
-failskips
   Exit 1 regardless of test run outcome if any tests are skipped.
   Useful option for continuous integration servers to reduce
   the probability of a quality-compromising culture of complacency
   developing around skipped tests.
-random[=Seed]
   Run test classes in a random order and run tests in a random order.
   Useful option for increasing testing rigor.
-testruns=<N>
   Repeat the running of all non-skipped tests N times.
   Useful option for increasing testing rigor, especially when used with -random.)";

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
      vector<string> args { TestProgramPath };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(args);
      //
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = TestProgramPath;
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST1X1(Parse_ArgsSizeGreaterThanOnePlusNumberOfValidArgs_PrintsErrorMessageAndUsageAndExits1,
      size_t numberOfArgs,
      10,
      11)
   {
      _consoleMock->WriteLineMock.Expect();
      _consoleMock->WriteLineAndExitMock.ExpectAndThrow<WriteLineAndExitException>();
      const vector<string> Args(numberOfArgs);
      //
      THROWS(_argsParser.Parse(Args), WriteLineAndExitException, "");
      //
      ZEN(_consoleMock->WriteLineMock.AssertCalledOnceWith("ZenUnit argument error. Too many arguments.\n"));
      ZEN(_consoleMock->WriteLineAndExitMock.AssertCalledOnceWith(ExpectedUsage, 1));
   }

   TEST1X1(Parse_InvalidArg_PrintsErrorMessageAndUsageAndExits1,
      const string& invalidArg,
      "--exit0",
      "-Exit0",
      "-testruns")
   {
      _consoleMock->WriteLineMock.Expect();
      _consoleMock->WriteLineAndExitMock.ExpectAndThrow<WriteLineAndExitException>();
      const vector<string> Args { TestProgramPath, invalidArg };
      //
      THROWS(_argsParser.Parse(Args), WriteLineAndExitException, "");
      //
      ZEN(_consoleMock->WriteLineMock.AssertCalledOnceWith(
         "ZenUnit argument error. Invalid argument \"" + invalidArg + "\"\n"));
      ZEN(_consoleMock->WriteLineAndExitMock.AssertCalledOnceWith(ExpectedUsage, 1));
   }

   TEST1X1(Parse_DashhelpOrDashDashhelp_PrintsUsageAndExits0,
      const string& helpArg,
      "-help",
      "--help")
   {
      _consoleMock->WriteLineAndExitMock.ExpectAndThrow<WriteLineAndExitException>();
      //
      THROWS(_argsParser.Parse({TestProgramPath, helpArg}), WriteLineAndExitException, "");
      //
      ZEN(_consoleMock->WriteLineAndExitMock.AssertCalledOnceWith(ExpectedUsage, 0));
   }

   TEST(Parse_AllArgsSpecified_ReturnsZenUnitArgsWithAllFieldsSets)
   {
      const unsigned testruns = ZenUnit::Random<unsigned>();
      const unsigned randomseed = ZenUnit::Random<unsigned>();
      ToUnsigned_ZenMock.ExpectAndReturnValues(testruns, randomseed);
      const vector<string> Args
      {
         TestProgramPath,
         "-minimalist",
         "-detailed",
         "-pause",
         "-wait",
         "-exit0",
         "-failskips",
         "-testruns=" + to_string(testruns),
         "-random=" + to_string(randomseed)
      };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(Args);
      //
      ZEN(ToUnsigned_ZenMock.AssertCalls(
      {
         to_string(testruns),
         to_string(randomseed)
      }));
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = Vector::Join(Args, ' ');
      expectedZenUnitArgs.printMode = PrintMode::Detailed;
      expectedZenUnitArgs.pause = true;
      expectedZenUnitArgs.wait = true;
      expectedZenUnitArgs.exit0 = true;
      expectedZenUnitArgs.failskips = true;
      expectedZenUnitArgs.testruns = 1;
      expectedZenUnitArgs.random = true;
      expectedZenUnitArgs.testruns = testruns;
      expectedZenUnitArgs.randomseed = static_cast<unsigned short>(randomseed);
      expectedZenUnitArgs.randomseedsetbyuser = true;
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST2X2(Parse_MinimalistOrDetailed_ReturnsExpectedZenUnitArgs,
      const vector<string>& args, PrintMode expectedPrintMode,
      vector<string>{ "ExePath" }, PrintMode::Normal,
      vector<string>{ "ExePath", "-minimalist" }, PrintMode::Minimalist,
      vector<string>{ "ExePath", "-detailed" }, PrintMode::Detailed)
   {
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(args);
      //
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = Vector::Join(args, ' ');
      expectedZenUnitArgs.printMode = expectedPrintMode;
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST(Parse_Run_ReturnsExpectedZenUnitArgs)
   {
      const vector<RunFilter> runFilters = { ZenUnit::Random<RunFilter>() };
      _runFilterParserMock->ParseMock.ExpectAndReturn(runFilters);

      const string runArgument = ZenUnit::Random<string>();
      const vector<string> args = { "ExePath", "-run=" + runArgument };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(args);
      //
      const vector<string> splitRunArgument = String::Split(runArgument, ',');
      ZEN(_runFilterParserMock->ParseMock.AssertCalledOnceWith(splitRunArgument));

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
      AssertArgSetsBoolField("-failskips", &ZenUnitArgs::failskips);
   }
   void AssertArgSetsBoolField(const string& arg, bool ZenUnitArgs::* expectedFieldToBeSet)
   {
      const vector<string> Args { TestProgramPath, arg };
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
      const vector<string> Args { TestProgramPath, "-exit0", "-exit0" };
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
      _consoleMock->WriteLineAndExitMock.ExpectAndThrow<WriteLineAndExitException>();
      const vector<string> Args { TestProgramPath, arg };
      //
      THROWS(_argsParser.Parse(Args), WriteLineAndExitException, "");
      //
      ZEN(_consoleMock->WriteLineMock.AssertCalledOnceWith(
         "ZenUnit argument error. Invalid -name=value argument value: " + arg + "\n"));
      ZEN(_consoleMock->WriteLineAndExitMock.AssertCalledOnceWith(ExpectedUsage, 1));
   }

   TEST(Parse_TimesEqualsArg_StringToUnsignedThrowsInvalidArgumentWhenProcessingValue_PrintsErrorMessageAndUsageAndExits1)
   {
      _consoleMock->WriteLineMock.Expect();
      _consoleMock->WriteLineAndExitMock.ExpectAndThrow<WriteLineAndExitException>();
      ToUnsigned_ZenMock.ExpectAndThrow<invalid_argument>("");
      const string InvalidTimesArg = "-testruns=-1_for_example";
      const vector<string> Args { TestProgramPath, InvalidTimesArg };
      //
      THROWS(_argsParser.Parse(Args), WriteLineAndExitException, "");
      //
      ZEN(ToUnsigned_ZenMock.AssertCalledOnceWith("-1_for_example"));
      ZEN(_consoleMock->WriteLineMock.AssertCalledOnceWith(
         "ZenUnit argument error. Invalid -name=value argument value: " + InvalidTimesArg + "\n"));
      ZEN(_consoleMock->WriteLineAndExitMock.AssertCalledOnceWith(ExpectedUsage, 1));
   }

   TEST(Parse_TimesEqualsArg_ValidUnsignedValue_ReturnsExpectedZenUnitArgs)
   {
      const unsigned timesArgValue = Random<unsigned>();
      ToUnsigned_ZenMock.ExpectAndReturn(timesArgValue);
      const vector<string> Args { TestProgramPath, "-testruns=" + to_string(timesArgValue) };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(Args);
      //
      ZEN(ToUnsigned_ZenMock.AssertCalledOnceWith(to_string(timesArgValue)));
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = Vector::Join(Args, ' ');
      expectedZenUnitArgs.testruns = timesArgValue;
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST(Parse_RandomEqualsArg_ValidRandomUnsignedValue_ReturnsExpectedZenUnitArgs)
   {
      const unsigned randomSeedArgValue = Random<unsigned>();
      ToUnsigned_ZenMock.ExpectAndReturn(randomSeedArgValue);
      const vector<string> Args{ TestProgramPath, "-random=" + to_string(randomSeedArgValue) };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(Args);
      //
      ZEN(ToUnsigned_ZenMock.AssertCalledOnceWith(to_string(randomSeedArgValue)));
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = Vector::Join(Args, ' ');
      expectedZenUnitArgs.random = true;
      expectedZenUnitArgs.randomseed = static_cast<unsigned short>(randomSeedArgValue);
      expectedZenUnitArgs.randomseedsetbyuser = true;
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST2X2(Parse_RandomEqualsArg_ValidUnsignedValue_DowncastsValueToUnsignedShort_ReturnsExpectedZenUnitArgs,
      unsigned randomSeedArgValue, unsigned short expectedZenUnitArgsRandomseedValue,
      numeric_limits<unsigned short>::max(), numeric_limits<unsigned short>::max(),
      numeric_limits<unsigned short>::max() + 1, static_cast<unsigned short>(0),
      numeric_limits<unsigned short>::max() + 2, static_cast<unsigned short>(1))
   {
      ToUnsigned_ZenMock.ExpectAndReturn(randomSeedArgValue);
      const vector<string> Args{ TestProgramPath, "-random=" + to_string(randomSeedArgValue) };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(Args);
      //
      ZEN(ToUnsigned_ZenMock.AssertCalledOnceWith(to_string(randomSeedArgValue)));
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = Vector::Join(Args, ' ');
      expectedZenUnitArgs.random = true;
      expectedZenUnitArgs.randomseed = expectedZenUnitArgsRandomseedValue;
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
      ZEN(_consoleMock->WriteLineMock.AssertCalledOnceWith(
         "ZenUnit argument error. Unrecognized -name=value argument: " + UnrecognizedNameArg + "\n"));
      ZEN(_consoleMock->WriteLineAndExitMock.AssertCalledOnceWith(ExpectedUsage, 1));
   }

   }; RUNTESTS(ArgsParserTests)
}
