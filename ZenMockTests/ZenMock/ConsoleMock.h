#pragma once

struct ConsoleMock : public Zen::Mock<Console>
{
   ZENMOCK_VOID1_CONST(Write, string_view)
   ZENMOCK_VOID2_CONST(WriteColor, string_view, Color)
   ZENMOCK_VOID1_CONST(WriteLine, string_view)
   ZENMOCK_VOID2_CONST(WriteLineColor, string_view, Color)
   ZENMOCK_VOID0_CONST(WriteNewLine)
   ZENMOCK_VOID2_CONST(WriteLineAndExit, string_view, int)
   ZENMOCK_VOID3_CONST(WriteStringsCommaSeparated, const vector<string>&, size_t, size_t)
   ZENMOCK_VOID1_CONST(WaitForAnyKeyIfDebuggerPresentOrValueTrue, bool)
   ZENMOCK_VOID0_CONST(WaitForAnyKey)
   ZENMOCK_NONVOID0_CONST(bool, DebuggerIsPresent)
};

class WriteLineAndExitException : public exception
{
public:
   const char* what() const noexcept override
   {
      return "";
   }
};
