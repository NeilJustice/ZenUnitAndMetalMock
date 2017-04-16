#include "pch.h"
#include "StaticLibrary/Program.h"
#include "StaticLibraryTests/Mock/ArgsParserMock.h"

TESTS(ProgramTests)
SPEC(Constructor_NewsComponents)
SPEC(Main_ConvertsArgcArgvToStringVector_CallsVectorMain)
SPEC(VectorMain_ParsesArgs_CallsArgsMain)
SPECEND

Program _program;

TEST(Constructor_NewsComponents)
{
   Program program;
   WAS_NEWED(program._console);
   WAS_NEWED(program._argsParser);
}

TEST(Main_ConvertsArgcArgvToStringVector_CallsVectorMain)
{

}

TEST(VectorMain_ParsesArgs_CallsArgsMain)
{

}

}; RUN(ProgramTests)
