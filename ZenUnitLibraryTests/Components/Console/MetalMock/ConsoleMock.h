#pragma once

class ConsoleMock : public Metal::Mock<Console>
{
public:
   METALMOCK_VOID1_CONST(Write, std::string_view)
   METALMOCK_VOID2_CONST(WriteColor, std::string_view, Color)
   METALMOCK_VOID1_CONST(WriteLine, std::string_view)
   METALMOCK_VOID2_CONST(WriteLineColor, std::string_view, Color)
   METALMOCK_VOID0_CONST(WriteNewLine)
   METALMOCK_VOID2_CONST(WriteNewLineIfValuesAreNotEqual, size_t, size_t)
   METALMOCK_VOID2_CONST(WriteLineAndExit, std::string_view, int)
   METALMOCK_VOID3_CONST(WriteStringsCommaSeparated, const vector<string>&, size_t, size_t)
   METALMOCK_VOID1_CONST(WaitForAnyKeyIfDebuggerPresentOrValueTrue, bool)
   METALMOCK_VOID0_CONST(WaitForAnyKey)
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
