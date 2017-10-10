#pragma once

struct ConsoleMock : public Zen::Mock<Console>
{
   ZENMOCK_VOID1_CONST(Write, const string&)
   ZENMOCK_VOID2_CONST(NonMinimalWrite, const string&, PrintMode)
   ZENMOCK_VOID2_CONST(WriteColor, const string&, Color)
   ZENMOCK_VOID3_CONST(NonMinimalWriteColor, const string&, Color, PrintMode)
   ZENMOCK_VOID1_CONST(WriteLine, const string&)
   ZENMOCK_VOID2_CONST(NonMinimalWriteLine, const string&, PrintMode)
   ZENMOCK_VOID2_CONST(WriteLineColor, const string&, Color)
   ZENMOCK_VOID0_CONST(WriteNewLine)
   ZENMOCK_VOID1_CONST(NonMinimalWriteNewLine, PrintMode)
   ZENMOCK_VOID2_CONST(WriteLineAndExit, const string&, int)
   ZENMOCK_VOID4_CONST(NonMinimalWriteStringsCommaSeparated, const vector<string>&, size_t, size_t, PrintMode)
   ZENMOCK_VOID1_CONST(WaitForEnterKeyIfDebuggerPresentOrValueTrue, bool)
   ZENMOCK_VOID0_CONST(WaitForEnterKey)
   ZENMOCK_NONVOID0_CONST(bool, DebuggerIsPresent)
};

class WriteLineAndExitException : public exception
{
public:
   const char* what() const noexcept override { return ""; }
};
