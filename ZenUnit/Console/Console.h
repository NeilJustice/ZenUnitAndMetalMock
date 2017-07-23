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
      std::function<void(int)> _exit_ZenMockable;
      std::function<int()> _IsDebuggerPresent_ZenMockable;
   public:
      Console();
      virtual ~Console();
      virtual void Write(const std::string& message) const;
      virtual void NonLaconicWrite(const std::string& message, PrintMode printMode) const;
      virtual void WriteColor(const std::string& message, Color color) const;
      virtual void NonLaconicWriteColor(const std::string& message, Color color, PrintMode printMode) const;
      virtual void WriteLine(const std::string& message) const;
      virtual void NonLaconicWriteLine(const std::string& message, PrintMode printMode) const;
      virtual void WriteLineColor(const std::string& message, Color color) const;
      virtual void WriteNewLine() const;
      virtual void NonLaconicWriteNewLine(PrintMode printMode) const;
      virtual void WriteLineAndExit(const std::string& message, int exitCode) const;
      virtual void NonLaconicWriteStringsCommaSeparated(
         const std::vector<std::string>& strings, size_t startIndex, size_t numberOfElements, PrintMode printMode) const;
      virtual void PauseForAnyKeyIfDebuggerIsPresent() const;
      virtual bool DebuggerIsPresent() const;
      virtual void GetLine() const;
   };
}
