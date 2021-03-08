#pragma once

struct ConsoleMock : public Metal::Mock<Console>
{
   METALMOCK_VOID1_CONST(Write, string_view)
   METALMOCK_VOID2_CONST(WriteColor, string_view, Color)
   METALMOCK_VOID1_CONST(WriteLine, string_view)
   METALMOCK_VOID2_CONST(WriteLineColor, string_view, Color)
   METALMOCK_VOID0_CONST(WriteNewLine)
   METALMOCK_VOID2_CONST(WriteLineAndExit, string_view, int)
   METALMOCK_VOID3_CONST(WriteStringsCommaSeparated, const vector<string>&, size_t, size_t)
   METALMOCK_VOID1_CONST(WaitForEnterKeyIfDebuggerPresentOrValueTrue, bool)
   METALMOCK_VOID0_CONST(WaitForEnterKey)
   METALMOCK_NONVOID0_CONST(bool, DebuggerIsPresent)
};

class WriteLineAndExitException : public exception
{
public:
   const char* what() const noexcept override
   {
      return "";
   }
};
