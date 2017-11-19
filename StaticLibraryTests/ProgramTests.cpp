#include "pch.h"
#include "StaticLibrary/Program.h"
#include "StaticLibraryTests/Mock/ConsoleMock.h"

TESTS(ProgramTests)
AFACT(Constructor_NewsComponents)
FACTS(Main_ConvertsArgcArgvToStringVector_CallsVectorMain)
AFACT(VectorMain_Returns0)
EVIDENCE

Program _program;
ConsoleMock* _consoleMock;

const string ExpectedCommandLineUsage = R"(ProgramName v0.1.0)";

STARTUP
{
   _program._console.reset(_consoleMock = new ConsoleMock);
}

TEST(Constructor_NewsComponents)
{
   Program program;
   POINTER_WAS_NEWED(program._console);
}

TEST2X2(Main_ConvertsArgcArgvToStringVector_CallsVectorMain,
   int expectedExitCode, int vectorMainReturnValue,
   0, 0,
   1, 1)
{
   struct ProgramSelfMocked : public Zen::Mock<Program>
   {
      ZENMOCK_NONVOID1_CONST(int, VectorMain, const vector<string>&)
   } program_VectorMainMocked;
   program_VectorMainMocked.VectorMainMock.ExpectAndReturn(vectorMainReturnValue);

   const char* argv[] = { "BinaryPath" };
   //
   const int exitCode = program_VectorMainMocked.Main(1, const_cast<char**>(argv));
   //
   ZEN(program_VectorMainMocked.VectorMainMock.AssertCalledOnceWith({ "BinaryPath" }));
   ARE_EQUAL(expectedExitCode, exitCode);
}

TEST(VectorMain_Returns0)
{
   const vector<string> args = { "BinaryPath" };
   //
   const int exitCode = _program.VectorMain(args);
   //
   ARE_EQUAL(0, exitCode);
}

}; RUNTESTS(ProgramTests)
