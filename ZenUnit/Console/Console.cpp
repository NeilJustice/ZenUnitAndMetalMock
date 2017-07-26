#include "pch.h"
#include "ZenUnit/Console/Console.h"
#include "ZenUnit/Console/ConsoleColorer.h"
#include "ZenUnit/Enums/PrintMode.h"
#include "ZenUnit/Utils/AssertTrue.h"

namespace ZenUnit
{
   Console::Console()
      : _consoleColorer(new ConsoleColorer)
      , _exit_ZenMockable(::exit)
#ifdef _WIN32
      , _IsDebuggerPresent_ZenMockable(::IsDebuggerPresent)
#endif
   {
   }

   Console::~Console() = default;

   void Console::Write(const string& message) const
   {
      WriteColor(message, Color::White);
   }

   void Console::NonMinimalWrite(const std::string& message, PrintMode printMode) const
   {
      if (printMode != PrintMode::Minimal)
      {
         Write(message);
      }
   }

   void Console::WriteColor(const string& message, Color color) const
   {
      const bool didSetColor = _consoleColorer->SetColor(color);
      printf("%s", message.c_str());
      cout.flush(); // Explicit flush needed on Linux to show test run progress output immediately
      _consoleColorer->UnsetColor(didSetColor);
   }

   void Console::NonMinimalWriteColor(const std::string& message, Color color, PrintMode printMode) const
   {
      if (printMode != PrintMode::Minimal)
      {
         WriteColor(message, color);
      }
   }

   void Console::WriteLine(const string& message) const
   {
      WriteLineColor(message, Color::White);
   }

   void Console::NonMinimalWriteLine(const std::string& message, PrintMode printMode) const
   {
      if (printMode != PrintMode::Minimal)
      {
         WriteLine(message);
      }
   }

   void Console::WriteLineColor(const string& message, Color color) const
   {
      const bool didSetColor = _consoleColorer->SetColor(color);
      // With VS2017 15.2 Debug and Release mode, printf("%s\n") measured as ~15% faster
      // and with less speed variance relative to "cout << message << '\n'".
      // On Linux + Clang, no significant difference measured between printf and cout.
      printf("%s\n", message.c_str());
      cout.flush(); // Explicit flush needed on Linux to show test run output as it happens in VS Code
      _consoleColorer->UnsetColor(didSetColor);
   }

   void Console::WriteNewLine() const
   {
      printf("\n");
   }

   void Console::NonMinimalWriteNewLine(PrintMode printMode) const
   {
      if (printMode != PrintMode::Minimal)
      {
         WriteNewLine();
      }
   }

   void Console::WriteLineAndExit(const std::string& message, int exitCode) const
   {
      cout << message << '\n';
      _exit_ZenMockable(exitCode);
   }

   void Console::NonMinimalWriteStringsCommaSeparated(
      const std::vector<std::string>& strings, size_t startIndex, size_t numberOfElements, PrintMode printMode) const
   {
      assert_true(startIndex < strings.size());
      if (printMode != PrintMode::Minimal)
      {
         const size_t endIndex = startIndex + numberOfElements - 1;
         for (size_t i = startIndex; i <= endIndex; ++i)
         {
            const std::string& str = strings[i];
            Write(str);
            if (i < endIndex)
            {
               Write(", ");
            }
         }
      }
   }

   void Console::PauseForAnyKeyIfDebuggerIsPresent() const
   {
      if (DebuggerIsPresent())
      {
         WriteLine("Press any key to continue...");
         GetLine();
      }
   }

   bool Console::DebuggerIsPresent() const
   {
#ifdef __linux__
      return false;
#elif _WIN32
      const int isDebuggerPresentReturnValue = _IsDebuggerPresent_ZenMockable();
      const bool isDebuggerPresent = isDebuggerPresentReturnValue == 1;
      return isDebuggerPresent;
#endif
   }

   void Console::GetLine() const
   {

      string devNull;
      getline(cin, devNull);
   }
}
