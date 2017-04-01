#pragma once
#include "Color.h"
#include <functional>
#include <memory>

namespace ZenUnit
{
   class ConsoleColorer;

   class Console
   {
      friend class ConsoleTests;
   private:
      std::unique_ptr<const ConsoleColorer> _consoleColorer;
      std::function<void(int)> exit_ZenMockable;
      std::function<int()> IsDebuggerPresent_ZenMockable;
   public:
      Console();
      virtual ~Console();
      virtual void Write(const std::string& message) const;
      virtual void WriteColor(const std::string& message, Color color) const;
      virtual void WriteLine(const std::string& message) const;
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
