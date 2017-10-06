#pragma once
#include "ZenUnit/Enums/Color.h"
#include <functional>
#include <memory>
#include <vector>

namespace ZenUnit
{
   class ConsoleColorer;
   enum class PrintMode : unsigned char;

   class Console
   {
      friend class ConsoleTests;
   private:
      std::unique_ptr<ConsoleColorer> _consoleColorer;
      std::function<void(int)> call_exit;
      std::function<int()> call_IsDebuggerPresent;
   public:
      Console();
      virtual ~Console();
      virtual void Write(const std::string& message) const;
      virtual void NonMinimalWrite(const std::string& message, PrintMode printMode) const;
      virtual void WriteColor(const std::string& message, Color color) const;
      virtual void NonMinimalWriteColor(const std::string& message, Color color, PrintMode printMode) const;
      virtual void WriteLine(const std::string& message) const;
      virtual void NonMinimalWriteLine(const std::string& message, PrintMode printMode) const;
      virtual void WriteLineColor(const std::string& message, Color color) const;
      virtual void WriteNewLine() const;
      virtual void NonMinimalWriteNewLine(PrintMode printMode) const;
      virtual void WriteLineAndExit(const std::string& message, int exitCode) const;
      virtual void NonMinimalWriteStringsCommaSeparated(
         const std::vector<std::string>& strings, size_t startIndex, size_t numberOfStringsToWrite, PrintMode printMode) const;
      virtual void PauseForAnyKeyIfDebuggerIsPresent() const;
      virtual bool DebuggerIsPresent() const;
      virtual void GetLine() const;
   private:
      virtual void DoWriteStringsCommaSeparated(
         const std::vector<std::string>& strings, size_t startIndex, size_t numberOfStringsToWrite) const;
   };
}
