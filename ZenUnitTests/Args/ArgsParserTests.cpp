#include "pch.h"
#include "ZenUnit/Args/ArgsParser.h"
#include "ZenUnit/Utils/Vector.h"
#include "ZenUnitTests/Console/Mock/ConsoleMock.h"

namespace ZenUnit
{
   TESTS(ArgsParserTests)
   SPEC(DefaultConstructor_NewsConsole)
   SPEC(Parse_ArgsOnlyExePath_ReturnsDefaultZenUnitArgsWithCommandLineAndTestProgramNameSet)
   SPEC(Parse_ArgsSizeGreaterThanOnePlusNumberOfValidArgs_PrintsErrorMessageAndUsageAndExits1)
   SPECX(Parse_InvalidArg_PrintsErrorMessageAndUsageAndExits1)
   SPECX(Parse_DashhelpOrDashDashhelp_PrintsUsageAndExits0)
   SPEC(Parse_AllArgsSpecified_ReturnsZenUnitArgsWithAllFieldsSets)
   SPEC(Parse_ValidBoolArg_ReturnsExpectedZenUnitArgs)
   SPEC(Parse_ValidBoolArgSpecifiedTwice_ReturnsExpectedZenUnitArgs)
   SPECX(Parse_TimesArg_EmptyValue_PrintsErrorMessageAndUsageAndExits1)
   SKIPSPECX("In progress", Parse_TimesArg_NonUnsignedValue_PrintsErrorMessageAndUsageAndExits1)
   SPEC(Parse_TimesArg_TwoEqualsSignsAndAPositiveValue_PrintsErrorMessageAndUsageAndExits1)
   SPEC(Parse_TimesArg_PositiveValue_ReturnsExpectedZenUnitArgs)
   SPECEND

   ArgsParser _argsParser;
   const ConsoleMock* _consoleMock;
   const string TestProgramPath = "Folder/TestProgramName";
   const string ExpectedUsage = R"(C++ unit testing framework ZenUnit and C++ mocking framework ZenMock
Version 0.1.1
Usage: <TestsBinaryName> [Options...]

Options:

None
   Run all non-skipped tests.
-times=N
   Run tests N times. Specify N as 0 to run forever.
-exit0
   Always exit 0 regardless of test run outcome.
   This option is useful for always allowing the launch of a debugger
   or non-debugging console window after running tests in a post-build step.
-noskips
   Exit 1 regardless of test run outcome if any tests are skipped.
   This option is useful for continuous integration servers
   to defend against the possibility of a quality-compromising
   culture of complacency developing around committed skipped tests.
-help or --help
   Display this help.)";

   STARTUP
   {
      _argsParser._console.reset(_consoleMock = new ConsoleMock);
   }

   TEST(DefaultConstructor_NewsConsole)
   {
      ArgsParser argsParser;
      WAS_NEWED(argsParser._console);
   }

   TEST(Parse_ArgsOnlyExePath_ReturnsDefaultZenUnitArgsWithCommandLineAndTestProgramNameSet)
   {
      vector<string> args = { TestProgramPath };
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
      "-times")
   {
      _consoleMock->WriteLineMock.Expect();
      _consoleMock->WriteLineAndExitMock.ExpectAndThrow<WriteLineAndExitException>();
      const vector<string> Args = { TestProgramPath, invalidArg };
      //
      THROWS(_argsParser.Parse(Args), WriteLineAndExitException, "");
      //
      ZEN(_consoleMock->WriteLineMock.AssertCalledOnceWith(
         "ZenUnit argument error: Invalid argument \"" + invalidArg + "\""));
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
      const vector<string> Args 
      { 
         TestProgramPath, 
         "-times=0",
         "-exit0",
         "-noskips"
      };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(Args);
      //
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = Vector::Join(Args, ' ');
      expectedZenUnitArgs.times = 0;
      expectedZenUnitArgs.exit0 = true;
      expectedZenUnitArgs.noskips = true;
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST(Parse_ValidBoolArg_ReturnsExpectedZenUnitArgs)
   {
      AssertArgSetsBoolField("-exit0", &ZenUnitArgs::exit0);
      AssertArgSetsBoolField("-noskips", &ZenUnitArgs::noskips);
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
      "-times=",
      "-times===")
   {
      _consoleMock->WriteLineMock.Expect();
      _consoleMock->WriteLineAndExitMock.ExpectAndThrow<WriteLineAndExitException>();
      const vector<string> Args { TestProgramPath, arg };
      //
      THROWS(_argsParser.Parse(Args), WriteLineAndExitException, "");
      //
      ZEN(_consoleMock->WriteLineMock.AssertCalledOnceWith(
         "ZenUnit argument error: Illformed -name=value argument: " + arg));
      ZEN(_consoleMock->WriteLineAndExitMock.AssertCalledOnceWith(ExpectedUsage, 1));
   }

   TEST1X1(Parse_TimesArg_NonUnsignedValue_PrintsErrorMessageAndUsageAndExits1,
      const string& arg,
      "-times=-1")
      //"-times=abc",
      //"-times=1u")
   {
      _consoleMock->WriteLineMock.Expect();
      _consoleMock->WriteLineAndExitMock.ExpectAndThrow<WriteLineAndExitException>();
      const vector<string> Args { TestProgramPath, arg };
      //
      THROWS(_argsParser.Parse(Args), WriteLineAndExitException, "");
      //
      ZEN(_consoleMock->WriteLineMock.AssertCalledOnceWith(
         "ZenUnit argument error: Illformed -name=value argument. Not-a-number value: " + arg));
      ZEN(_consoleMock->WriteLineAndExitMock.AssertCalledOnceWith(ExpectedUsage, 1));
   }

   TEST(Parse_TimesArg_TwoEqualsSignsAndAPositiveValue_PrintsErrorMessageAndUsageAndExits1)
   {

   }

   TEST(Parse_TimesArg_PositiveValue_ReturnsExpectedZenUnitArgs)
   {

   }

   }; RUN(ArgsParserTests)
}
