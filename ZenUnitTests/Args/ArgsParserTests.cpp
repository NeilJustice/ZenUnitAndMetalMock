#include "pch.h"
#include "ZenUnit/Args/ArgsParser.h"
#include "ZenUnit/Utils/Random.h"
#include "ZenUnit/Utils/Vector.h"
#include "ZenUnitTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitTests/Utils/Time/Mock/WatchMock.h"

namespace ZenUnit
{
   TESTS(ArgsParserTests)
   FACT(DefaultConstructor_NewsCompnents_SetsStringToUnsignedFunction)
   FACT(Parse_ArgsOnlyExePath_ReturnsDefaultZenUnitArgsWithCommandLineAndTestProgramNameSet)
   FACT(Parse_ArgsSizeGreaterThanOnePlusNumberOfValidArgs_PrintsErrorMessageAndUsageAndExits1)
   FACTS(Parse_InvalidArg_PrintsErrorMessageAndUsageAndExits1)
   FACTS(Parse_DashhelpOrDashDashhelp_PrintsUsageAndExits0)
   FACT(Parse_AllArgsSpecified_ReturnsZenUnitArgsWithAllFieldsSets)
   FACTS(Parse_MinimalOrDetailed_ReturnsExpectedZenUnitArgs)
   FACT(Parse_Random_SetsRandomTrueAndRandomSeedToSecondsSince1970CastToUnsignedShort)
   FACT(Parse_ValidBoolArg_ReturnsExpectedZenUnitArgs)
   FACT(Parse_ValidBoolArgSpecifiedTwice_ReturnsExpectedZenUnitArgs)
   FACTS(Parse_TimesArg_EmptyValue_PrintsErrorMessageAndUsageAndExits1)
   FACT(Parse_TimesArg_StringToUnsignedThrowsInvalidArgumentWhenProcessingValue_PrintsErrorMessageAndUsageAndExits1)
   FACTS(Parse_TimesArg_ValidUnsignedValue_ReturnsExpectedZenUnitArgs)
   BEGINPROOF

   const string TestProgramPath = Random<string>();
   const string ExpectedUsage = R"(ZenUnit and ZenMock
Usage: <TestsBinaryName> [Options...]

Options:

None
   Run all non-skipped tests while printing detailed information.
-minimal
   Print only preamble and conclusion instead of detailed information.
-exit0
   Always exit 0 regardless of test run outcome.
   Useful for always allowing the Visual Studio debugger to launch.
-failskips
   Exit 1 regardless of test run outcome if any tests are skipped.
   Useful option for continuous integration servers to guard against
   quality-compromising complacency with respect to skipped tests.
-testruns=<N>
   Repeat the running of all non-skipped tests N times.
   Key option for maximizing testing rigor.
-random[=Seed]
   Run test classes in a random order and run tests in a random order.
   Key option for maximizing testing rigor.
-help or --help
   Display this help.)";

   ArgsParser _argsParser;
   const ConsoleMock* _consoleMock;
   const WatchMock* _watchMock;
   ZENMOCK_NONVOID1_STATIC(unsigned, String, ToUnsigned, const string&)

   STARTUP
   {
      _argsParser._console.reset(_consoleMock = new ConsoleMock);
      _argsParser._watch.reset(_watchMock = new WatchMock);
      _argsParser._String_ToUnsigned = ZENBIND1(ToUnsigned_ZenMock);
   }

   TEST(DefaultConstructor_NewsCompnents_SetsStringToUnsignedFunction)
   {
      ArgsParser argsParser;
      POINTER_WAS_NEWED(argsParser._console);
      POINTER_WAS_NEWED(argsParser._watch);
      STD_FUNCTION_TARGETS(String::ToUnsigned, argsParser._String_ToUnsigned);
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

   TEST(Parse_ArgsSizeGreaterThanOnePlusNumberOfValidArgs_PrintsErrorMessageAndUsageAndExits1)
   {
      _consoleMock->WriteLineMock.Expect();
      _consoleMock->WriteLineAndExitMock.ExpectAndThrow<WriteLineAndExitException>();
      const vector<string> Args(1 + ZenUnitArgs::NumberOfValidArgs + 1);
      //
      THROWS(_argsParser.Parse(Args), WriteLineAndExitException, "");
      //
      ZEN(_consoleMock->WriteLineMock.AssertCalledOnceWith("ZenUnit argument error: Too many arguments.\n"));
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
         "ZenUnit argument error: Invalid argument \"" + invalidArg + "\"\n"));
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
      ToUnsigned_ZenMock.ExpectAndReturn(1);
      unsigned short randomseed = Random<unsigned short>();
      _watchMock->SecondsSince1970CastToUnsignedShortMock.ExpectAndReturn(randomseed);
      const vector<string> Args
      {
         TestProgramPath,
         "-minimal",
         "-detailed",
         "-exit0",
         "-failskips",
         "-testruns=1",
         "-random"
      };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(Args);
      //
      ZEN(ToUnsigned_ZenMock.AssertCalledOnceWith("1"));
      ZEN(_watchMock->SecondsSince1970CastToUnsignedShortMock.AssertCalledOnce());
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = Vector::Join(Args, ' ');
      expectedZenUnitArgs.printMode = PrintMode::Detailed;
      expectedZenUnitArgs.exit0 = true;
      expectedZenUnitArgs.failskips = true;
      expectedZenUnitArgs.testruns = 1;
      expectedZenUnitArgs.random = true;
      expectedZenUnitArgs.randomseed = randomseed;
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST2X2(Parse_MinimalOrDetailed_ReturnsExpectedZenUnitArgs,
      vector<string> args, PrintMode expectedPrintMode,
      vector<string>{ "ExePath" }, PrintMode::Normal,
      vector<string>{ "ExePath", "-minimal" }, PrintMode::Minimal,
      vector<string>{ "ExePath", "-detailed" }, PrintMode::Detailed)
   {
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(args);
      //
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = Vector::Join(args, ' ');
      expectedZenUnitArgs.printMode = expectedPrintMode;
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST(Parse_Random_SetsRandomTrueAndRandomSeedToSecondsSince1970CastToUnsignedShort)
   {
      unsigned short randomseed = Random<unsigned short>();
      _watchMock->SecondsSince1970CastToUnsignedShortMock.ExpectAndReturn(randomseed);
      const vector<string> args = { "ExePath", "-random" };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(args);
      //
      ZEN(_watchMock->SecondsSince1970CastToUnsignedShortMock.AssertCalledOnce());
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = Vector::Join(args, ' ');
      expectedZenUnitArgs.random = true;
      expectedZenUnitArgs.randomseed = randomseed;
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST(Parse_ValidBoolArg_ReturnsExpectedZenUnitArgs)
   {
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

   TEST1X1(Parse_TimesArg_EmptyValue_PrintsErrorMessageAndUsageAndExits1,
      const string& arg,
      "-testruns=",
      "-testruns===")
   {
      _consoleMock->WriteLineMock.Expect();
      _consoleMock->WriteLineAndExitMock.ExpectAndThrow<WriteLineAndExitException>();
      const vector<string> Args { TestProgramPath, arg };
      //
      THROWS(_argsParser.Parse(Args), WriteLineAndExitException, "");
      //
      ZEN(_consoleMock->WriteLineMock.AssertCalledOnceWith(
         "ZenUnit argument error: Malformed -name=value argument: " + arg + "\n"));
      ZEN(_consoleMock->WriteLineAndExitMock.AssertCalledOnceWith(ExpectedUsage, 1));
   }

   TEST(Parse_TimesArg_StringToUnsignedThrowsInvalidArgumentWhenProcessingValue_PrintsErrorMessageAndUsageAndExits1)
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
         "ZenUnit argument error: Malformed -name=value argument: " + InvalidTimesArg + "\n"));
      ZEN(_consoleMock->WriteLineAndExitMock.AssertCalledOnceWith(ExpectedUsage, 1));
   }

   TEST1X1(Parse_TimesArg_ValidUnsignedValue_ReturnsExpectedZenUnitArgs,
      unsigned validTimesValue,
      0u,
      1u)
   {
      ToUnsigned_ZenMock.ExpectAndReturn(validTimesValue);
      const vector<string> Args { TestProgramPath, "-testruns=" + to_string(validTimesValue) };
      //
      ZenUnitArgs zenUnitArgs = _argsParser.Parse(Args);
      //
      ZEN(ToUnsigned_ZenMock.AssertCalledOnceWith(to_string(validTimesValue)));
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = Vector::Join(Args, ' ');
      expectedZenUnitArgs.testruns = validTimesValue;
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   }; RUN(ArgsParserTests)
}
