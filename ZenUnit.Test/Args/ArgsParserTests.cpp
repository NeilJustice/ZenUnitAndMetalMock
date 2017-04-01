#include "pch.h"
#include "ZenUnit.Test/Console/Mock/ConsoleMock.h"
#include "ZenUnit/Args/ArgsParser.h"
#include "ZenUnit/Utils/Vector.h"

namespace ZenUnit
{
   TESTS(ArgsParserTests)
   SPEC(DefaultConstructor_NewsConsole)
   SPEC(Parse_ArgsOnlyExePath_ReturnsDefaultZenUnitArgsWithCommandLineAndTestProgramNameSet)
   SPEC(Parse_ArgsSizeGreaterThanOnePlusNumberOfValidArgs_WritesErrorMessageAndUsageAndExits2)
   SPEC(Parse_InvalidArg_WritesErrorMessageAndUsageAndExits2)
   SPECX(Parse_DashhelpOrDashDashhelp_PrintsUsageAndExits0)
   SPEC(Parse_AllArgsSpecified_ReturnsZenUnitArgsWithAllFieldsSets)
   SPEC(Parse_ValidSingleArgs_ReturnsZenUnitArgs)
   SPEC(Parse_ValidFlagArgSpecifiedTwice_ReturnsZenUnitArgs)
   SPECEND

   ArgsParser _argsParser;
   const ConsoleMock* _consoleMock;
   const string TestProgramPath = "Folder/TestProgramName";
   const string ExpectedUsage = R"(C++ unit testing framework ZenUnit and C++ mocking framework ZenMock
Version 0.1.1 2017-02-14

Usage: ./<TestsBinaryName> [Options...]

Options:

None
   Run all non-skipped tests.
-exit0
   Always exit 0 regardless of test run outcome.
   This option is useful for always allowing the launch of a debugger
   or non-debugging console window after running tests in a post-build step.
-noskips
   Exit 1 regardless of test run outcome if any tests are skipped.
   This option is useful for continuous integration servers
   to defend against the possibility of a quality-compromising
   culture of complacency developing around committed skipped tests.)";

   STARTUP
   {
      _argsParser._console.reset(_consoleMock = new ConsoleMock);
   }

   TEST(DefaultConstructor_NewsConsole)
   {
      ArgsParser argsParser;
      CONFIRM_NEWED(argsParser._console);
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

   TEST(Parse_ArgsSizeGreaterThanOnePlusNumberOfValidArgs_WritesErrorMessageAndUsageAndExits2)
   {
      _consoleMock->WriteLineMock.Expect();
      _consoleMock->WriteLineAndExitMock.ExpectAndThrow<WriteLineAndExitException>();
      const vector<string> Args(1 + ZenUnitArgs::ValidArgs.size() + 1);
      //
      THROWS(_argsParser.Parse(Args), WriteLineAndExitException, "");
      //
      ZEN(_consoleMock->WriteLineMock.AssertCalledOnceWith(
         "ZenUnit argument error: Too many arguments"));
      ZEN(_consoleMock->WriteLineAndExitMock.AssertCalledOnceWith(ExpectedUsage, 2));
   }

   TEST(Parse_InvalidArg_WritesErrorMessageAndUsageAndExits2)
   {
      _consoleMock->WriteLineMock.Expect();
      _consoleMock->WriteLineAndExitMock.ExpectAndThrow<WriteLineAndExitException>();
      const vector<string> Args = { TestProgramPath, "-Exit0" };
      //
      THROWS(_argsParser.Parse(Args), WriteLineAndExitException, "");
      //
      ZEN(_consoleMock->WriteLineMock.AssertCalledOnceWith(
         "ZenUnit argument error: Invalid argument \"-Exit0\""));
      ZEN(_consoleMock->WriteLineAndExitMock.AssertCalledOnceWith(ExpectedUsage, 2));
   }

   TEST1X1(Parse_DashhelpOrDashDashhelp_PrintsUsageAndExits0,
      string helpArg,
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
      const vector<string> Args =
      {
         TestProgramPath,
         "-exit0",
         "-noskips"
      };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(Args);
      //
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = Vector::Join(Args, ' ');
      expectedZenUnitArgs.exit0 = true;
      expectedZenUnitArgs.noskips = true;
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST(Parse_ValidSingleArgs_ReturnsZenUnitArgs)
   {
      AssertArgSetsField("-exit0", &ZenUnitArgs::exit0);
   }

   void AssertArgSetsField(const string& arg, bool ZenUnitArgs::* expectedFieldToBeSet)
   {
      const vector<string> Args = { TestProgramPath, arg };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(Args);
      //
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = TestProgramPath + " " + arg;
      (expectedZenUnitArgs.*expectedFieldToBeSet) = true;
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST(Parse_ValidFlagArgSpecifiedTwice_ReturnsZenUnitArgs)
   {
      const vector<string> Args =
      {
         TestProgramPath,
         "-exit0",
         "-exit0"
      };
      //
      const ZenUnitArgs zenUnitArgs = _argsParser.Parse(Args);
      //
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = Vector::Join(Args, ' ');
      expectedZenUnitArgs.exit0 = true;
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   }; RUN(ArgsParserTests)
}
