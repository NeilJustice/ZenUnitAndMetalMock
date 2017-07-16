#pragma once
#include "ZenUnit/Console/Console.h"

struct ConsoleMock : public Zen::Mock<Console>
{
   ZENMOCK_VOID1_CONST(Write, const string&)
   ZENMOCK_VOID2_CONST(OptionallyWrite, const string&, bool)
   ZENMOCK_VOID2_CONST(WriteColor, const string&, Color)
   ZENMOCK_VOID3_CONST(OptionallyWriteColor, const string&, Color, bool)
   ZENMOCK_VOID1_CONST(WriteLine, const string&)
   ZENMOCK_VOID2_CONST(OptionallyWriteLine, const string&, bool)
   ZENMOCK_VOID2_CONST(WriteLineColor, const string&, Color)
   ZENMOCK_VOID0_CONST(WriteNewline)
   ZENMOCK_VOID2_CONST(WriteLineAndExit, const string&, int)
   ZENMOCK_VOID0_CONST(GetLine)
   ZENMOCK_VOID3_CONST(PrintStringsCommaSeparated, const std::vector<std::string>&, size_t, size_t)
   ZENMOCK_VOID0_CONST(PauseForAnyKeyIfDebuggerIsPresent)
   ZENMOCK_NONVOID0_CONST(bool, DebuggerIsPresent)
};

class WriteLineAndExitException : public exception
{
public:
   const char* what() const noexcept override { return ""; }
};
