#include "pch.h"
#include "ZenUnit/Args/ArgsParser.h"
#include "ZenUnit/Utils/Vector.h"
#include "Console/Mock/ConsoleMock.h"

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
   ConsoleMock* _consoleMock;
   const string TestProgramPath = "Folder/TestProgramName";
   const string ExpectedUsage = R"(ZenUnit and ZenMock
Usage: ./<TestsBinaryName> [Options]

Options:

None
   Run all non-skipped tests
-exit0
   Always exit 0 regardless of test run outcome.
   This setting is useful for not preventing the launch of a debugger
   after running tests in a post-build step.
-noskips
   Exit 1 regardless of test run outcome if any tests are skipped.
   This setting is useful for continuous integration servers
   to ensure a culture of complacency with respect to committed
   skipped tests being OK is programatically prevented from taking hold.
-help or --help
   Display this message)";

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
      ZenUnitArgs zenUnitArgs = _argsParser.Parse(args);
      //
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = TestProgramPath;
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST(Parse_ArgsSizeGreaterThanOnePlusNumberOfValidArgs_WritesErrorMessageAndUsageAndExits2)
   {
      _consoleMock->WriteLineMock.Expect();
      _consoleMock->WriteLineAndExitMock.ExpectAndThrow<WriteLineAndExitException>();
      vector<string> args(1 + ZenUnitArgs::ValidArgs.size() + 1);
      //
      THROWS(_argsParser.Parse(args), WriteLineAndExitException, "");
      //
      ZEN(_consoleMock->WriteLineMock.AssertCalledOnceWith(
         "ZenUnit argument error: Too many arguments"));
      ZEN(_consoleMock->WriteLineAndExitMock.AssertCalledOnceWith(ExpectedUsage, 2));
   }

   TEST(Parse_InvalidArg_WritesErrorMessageAndUsageAndExits2)
   {
      _consoleMock->WriteLineMock.Expect();
      _consoleMock->WriteLineAndExitMock.ExpectAndThrow<WriteLineAndExitException>();
      vector<string> args = { TestProgramPath, "-Exit0" };
      //
      THROWS(_argsParser.Parse(args), WriteLineAndExitException, "");
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
      vector<string> args =
      {
         TestProgramPath,
         "-exit0",
         "-noskips"
      };
      //
      ZenUnitArgs zenUnitArgs = _argsParser.Parse(args);
      //
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = Vector::Join(args, ' ');
      expectedZenUnitArgs.exit0 = true;
      expectedZenUnitArgs.noskips = true;
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST(Parse_ValidSingleArgs_ReturnsZenUnitArgs)
   {
      AssertArgSetsField("-exit0", &ZenUnitArgs::exit0);
   }

   void AssertArgSetsField(string arg, bool ZenUnitArgs::* expectedFieldToBeSet)
   {
      vector<string> args = { TestProgramPath, arg };
      //
      ZenUnitArgs zenUnitArgs = _argsParser.Parse(args);
      //
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = TestProgramPath + " " + arg;
      (expectedZenUnitArgs.*expectedFieldToBeSet) = true;
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   TEST(Parse_ValidFlagArgSpecifiedTwice_ReturnsZenUnitArgs)
   {
      vector<string> args =
      {
         TestProgramPath,
         "-exit0",
         "-exit0"
      };
      //
      ZenUnitArgs zenUnitArgs = _argsParser.Parse(args);
      //
      ZenUnitArgs expectedZenUnitArgs;
      expectedZenUnitArgs.commandLine = Vector::Join(args, ' ');
      expectedZenUnitArgs.exit0 = true;
      ARE_EQUAL(expectedZenUnitArgs, zenUnitArgs);
   }

   }; RUN(ArgsParserTests)
}
