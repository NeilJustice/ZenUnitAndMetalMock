#pragma once
#include "ZenUnit/Enums/Color.h"
#include <functional>
#include <memory>
#include <vector>

namespace ZenUnit
{
   class ConsoleColorer;

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
      virtual void OptionallyWrite(const std::string& message, bool doWrite) const;
      virtual void WriteColor(const std::string& message, Color color) const;
      virtual void OptionallyWriteColor(const std::string& message, Color color, bool doWriteColor) const;
      virtual void WriteLine(const std::string& message) const;
      virtual void OptionallyWriteLine(const std::string& message, bool doWriteLine) const;
      virtual void WriteLineColor(const std::string& message, Color color) const;
      virtual void WriteNewline() const;
      virtual void WriteLineAndExit(const std::string& message, int exitCode) const;
      virtual void PrintStringsCommaSeparated(
         const std::vector<std::string>& strings, size_t startIndex, size_t numberOfElements) const;
      virtual void PauseForAnyKeyIfDebuggerIsPresent() const;
      virtual bool DebuggerIsPresent() const;
      virtual void GetLine() const;
   };
}
