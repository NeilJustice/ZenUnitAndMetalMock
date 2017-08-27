#include "pch.h"
#include "StaticLibrary/Program.h"
#include "StaticLibraryTests/Mock/ConsoleMock.h"
#include "StaticLibraryTests/Mock/ArgsParserMock.h"

#ifdef _WIN32
   #pragma warning(disable: 4100) // '__testCase' unreferenced formal parameter, until [[maybe_unused]]
#endif

TESTS(ProgramTests)
FACT(Constructor_NewsComponents)
FACTS(Main_ConvertsArgcArgvToStringVector_CallsVectorMain)
FACT(VectorMain_EmptyArgsExceptForBinaryPath_PrintsUsage_Returns0)
FACT(VectorMain_NonEmptyArgsWithInvalidArg_WritesInvalidArgMessage_WritesUsage_Returns1)
FACT(VectorMain_NonEmptyValidArgs_Returns0)
EVIDENCE

Program _program;
ConsoleMock* _consoleMock;
ArgsParserMock* _argsParserMock;

const std::string ExpectedCommandLineUsage = R"(ProgramName 0.1.0
Usage: ProgramName <FilePath> [-flag])";

STARTUP
{
   _program._console.reset(_consoleMock = new ConsoleMock);
   _program._argsParser.reset(_argsParserMock = new ArgsParserMock);
}

TEST(Constructor_NewsComponents)
{
   Program program;
   POINTER_WAS_NEWED(program._console);
   POINTER_WAS_NEWED(program._argsParser);
}

TEST2X2(Main_ConvertsArgcArgvToStringVector_CallsVectorMain,
   int expectedExitCode, int vectorMainReturnValue,
   0, 0,
   1, 1)
{
   struct ProgramSelfMocked : public Zen::Mock<Program>
   {
      ZENMOCK_NONVOID1_CONST(int, VectorMain, const std::vector<std::string>&)
   } program_VectorMainMocked;
   program_VectorMainMocked.VectorMainMock.ExpectAndReturn(vectorMainReturnValue);

   const char* argv[] = { "BinaryPath" };
   //
   const int exitCode = program_VectorMainMocked.Main(1, const_cast<char**>(argv));
   //
   ZEN(program_VectorMainMocked.VectorMainMock.AssertCalledOnceWith({ "BinaryPath" }));
   ARE_EQUAL(expectedExitCode, exitCode);
}

TEST(VectorMain_EmptyArgsExceptForBinaryPath_PrintsUsage_Returns0)
{
   _consoleMock->WriteLineMock.Expect();
   //
   const int exitCode = _program.VectorMain({ "BinaryPath" });
   //
   ZEN(_consoleMock->WriteLineMock.AssertCalledOnceWith(ExpectedCommandLineUsage));
   ARE_EQUAL(0, exitCode);
}

TEST(VectorMain_NonEmptyArgsWithInvalidArg_WritesInvalidArgMessage_WritesUsage_Returns1)
{
   const std::string InvalidArgumentWhatText = "Invalid argument: -unknownFlag";
   _argsParserMock->ParseArgsMock.ExpectAndThrow<std::invalid_argument>(InvalidArgumentWhatText);
   _consoleMock->WriteLineMock.Expect();
   _consoleMock->WriteNewlineMock.Expect();
   const std::vector<std::string> Args = { "BinaryPath", "-unknownFlag" };
   //
   const int exitCode = _program.VectorMain(Args);
   //
   ZEN(_argsParserMock->ParseArgsMock.AssertCalledOnceWith(Args));
   ZEN(_consoleMock->WriteLineMock.AssertCalls(
   {
      InvalidArgumentWhatText,
      ExpectedCommandLineUsage
   }));
   ZEN(_consoleMock->WriteNewlineMock.AssertCalledOnce());
   ARE_EQUAL(1, exitCode);
}

TEST(VectorMain_NonEmptyValidArgs_Returns0)
{
   ProgramArgs nonDefaultProgramArgs;
   nonDefaultProgramArgs.flag = true;
   _argsParserMock->ParseArgsMock.ExpectAndReturn(nonDefaultProgramArgs);
   const std::vector<std::string> Args = { "BinaryPath", "-flag" };
   //
   const int exitCode = _program.VectorMain(Args);
   //
   ZEN(_argsParserMock->ParseArgsMock.AssertCalledOnceWith(Args));
   ARE_EQUAL(0, exitCode);
}

}; RUNTESTS(ProgramTests)
