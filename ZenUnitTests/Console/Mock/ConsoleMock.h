#pragma once
#include "ZenUnit/Console/Console.h"

struct ConsoleMock : public Zen::Mock<Console>
{
   ZENMOCK_VOID1_CONST(Write, const string&)
   ZENMOCK_VOID2_CONST(NonLaconicWrite, const string&, PrintMode)
   ZENMOCK_VOID2_CONST(WriteColor, const string&, Color)
   ZENMOCK_VOID3_CONST(NonLaconicWriteColor, const string&, Color, PrintMode)
   ZENMOCK_VOID1_CONST(WriteLine, const string&)
   ZENMOCK_VOID2_CONST(NonLaconicWriteLine, const string&, PrintMode)
   ZENMOCK_VOID2_CONST(WriteLineColor, const string&, Color)
   ZENMOCK_VOID0_CONST(WriteNewLine)
   ZENMOCK_VOID1_CONST(NonLaconicWriteNewLine, PrintMode)
   ZENMOCK_VOID2_CONST(WriteLineAndExit, const string&, int)
   ZENMOCK_VOID0_CONST(GetLine)
   ZENMOCK_VOID4_CONST(NonLaconicWriteStringsCommaSeparated, const std::vector<std::string>&, size_t, size_t, PrintMode)
   ZENMOCK_VOID0_CONST(PauseForAnyKeyIfDebuggerIsPresent)
   ZENMOCK_NONVOID0_CONST(bool, DebuggerIsPresent)
};

class WriteLineAndExitException : public exception
{
public:
   const char* what() const noexcept override { return ""; }
};
