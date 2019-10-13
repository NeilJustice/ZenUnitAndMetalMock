#pragma once

class ConsoleMock : public Zen::Mock<Console>
{
public:
   ZENMOCK_VOID1_CONST(Write, std::string_view)
   ZENMOCK_VOID2_CONST(WriteColor, std::string_view, Color)
   ZENMOCK_VOID1_CONST(WriteLine, std::string_view)
   ZENMOCK_VOID2_CONST(WriteLineColor, std::string_view, Color)
   ZENMOCK_VOID0_CONST(WriteNewLine)
   ZENMOCK_VOID2_CONST(WriteLineAndExit, std::string_view, int)
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
