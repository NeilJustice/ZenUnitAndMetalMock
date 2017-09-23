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

   void Console::Write(const std::string& message) const
   {
      WriteColor(message, Color::White);
   }

   void Console::NonMinimalWrite(const std::string& message, PrintMode printMode) const
   {
      if (printMode != PrintMode::Minimalist)
      {
         Write(message);
      }
   }

   void Console::WriteColor(const std::string& message, Color color) const
   {
      const bool didSetColor = _consoleColorer->SetColor(color);
      printf("%s", message.data());
      std::cout.flush(); // Explicit flush needed on Linux to show test run progress output immediately
      _consoleColorer->UnsetColor(didSetColor);
   }

   void Console::NonMinimalWriteColor(const std::string& message, Color color, PrintMode printMode) const
   {
      if (printMode != PrintMode::Minimalist)
      {
         WriteColor(message, color);
      }
   }

   void Console::WriteLine(const std::string& message) const
   {
      WriteLineColor(message, Color::White);
   }

   void Console::NonMinimalWriteLine(const std::string& message, PrintMode printMode) const
   {
      if (printMode != PrintMode::Minimalist)
      {
         WriteLine(message);
      }
   }

   void Console::WriteLineColor(const std::string& message, Color color) const
   {
      const bool didSetColor = _consoleColorer->SetColor(color);
      // With VS2017 15.2 Debug and Release mode, printf("%s\n") measured as ~15% faster
      // and with less speed variance relative to "cout << message << '\n'".
      // On Linux + Clang, no significant difference measured between printf and cout.
      printf("%s\n", message.data());
      std::cout.flush(); // Explicit flush needed on Linux to show test run output as it happens in VS Code
      _consoleColorer->UnsetColor(didSetColor);
   }

   void Console::WriteNewLine() const
   {
      printf("\n");
   }

   void Console::NonMinimalWriteNewLine(PrintMode printMode) const
   {
      if (printMode != PrintMode::Minimalist)
      {
         WriteNewLine();
      }
   }

   void Console::WriteLineAndExit(const std::string& message, int exitCode) const
   {
      std::cout << message << '\n';
      _exit_ZenMockable(exitCode);
   }

   void Console::NonMinimalWriteStringsCommaSeparated(
      const std::vector<std::string>& strings, size_t startIndex, size_t numberOfStringsToWrite, PrintMode printMode) const
   {
      if (printMode != PrintMode::Minimalist)
      {
         DoWriteStringsCommaSeparated(strings, startIndex, numberOfStringsToWrite);
      }
   }

   void Console::DoWriteStringsCommaSeparated(
      const std::vector<std::string>& strings, size_t startIndex, size_t numberOfStringsToWrite) const
   {
      const size_t endIndex = startIndex + numberOfStringsToWrite - 1;
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
      std::string devNull;
      std::getline(std::cin, devNull);
   }
}
