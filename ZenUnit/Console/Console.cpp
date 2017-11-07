#include "pch.h"
#include "ZenUnit/Console/Console.h"
#include "ZenUnit/Console/ConsoleColorer.h"
#include "ZenUnit/Enums/PrintMode.h"
#include "ZenUnit/Utils/AssertTrue.h"

namespace ZenUnit
{
   INLINE Console::Console()
      : _consoleColorer(new ConsoleColorer)
      , call_exit(::exit)
#ifdef _WIN32
      , call_IsDebuggerPresent(::IsDebuggerPresent)
#endif
   {
   }

   INLINE Console::~Console() = default;

   INLINE void Console::Write(const std::string& message) const
   {
      WriteColor(message, Color::White);
   }

   INLINE void Console::NonMinimalWrite(const std::string& message, PrintMode printMode) const
   {
      if (printMode != PrintMode::Minimalist)
      {
         Write(message);
      }
   }

   INLINE void Console::WriteColor(const std::string& message, Color color) const
   {
      const bool didSetColor = _consoleColorer->SetColor(color);
      printf("%s", message.data());
      std::cout.flush(); // Explicit flush needed on Linux to show test run progress output immediately
      _consoleColorer->UnsetColor(didSetColor);
   }

   INLINE void Console::NonMinimalWriteColor(const std::string& message, Color color, PrintMode printMode) const
   {
      if (printMode != PrintMode::Minimalist)
      {
         WriteColor(message, color);
      }
   }

   INLINE void Console::WriteLine(const std::string& message) const
   {
      WriteLineColor(message, Color::White);
   }

   INLINE void Console::NonMinimalWriteLine(const std::string& message, PrintMode printMode) const
   {
      if (printMode != PrintMode::Minimalist)
      {
         WriteLine(message);
      }
   }

   INLINE void Console::WriteLineColor(const std::string& message, Color color) const
   {
      const bool didSetColor = _consoleColorer->SetColor(color);
      // With VS2017 15.2 Debug and Release mode, printf("%s\n") measured as ~15% faster
      // and with less speed variance relative to "cout << message << '\n'".
      // On Linux + Clang, no significant difference measured between printf and cout.
      printf("%s\n", message.data());
      std::cout.flush(); // Explicit flush needed on Linux to show test run output as it happens in VS Code
      _consoleColorer->UnsetColor(didSetColor);
   }

   INLINE void Console::WriteNewLine() const
   {
      printf("\n");
   }

   INLINE void Console::NonMinimalWriteNewLine(PrintMode printMode) const
   {
      if (printMode != PrintMode::Minimalist)
      {
         WriteNewLine();
      }
   }

   INLINE void Console::WriteLineAndExit(const std::string& message, int exitCode) const
   {
      std::cout << message << '\n';
      call_exit(exitCode);
   }

   INLINE void Console::NonMinimalWriteStringsCommaSeparated(
      const std::vector<std::string>& strings, size_t startIndex, size_t numberOfStringsToWrite, PrintMode printMode) const
   {
      if (printMode != PrintMode::Minimalist)
      {
         DoWriteStringsCommaSeparated(strings, startIndex, numberOfStringsToWrite);
      }
   }

   INLINE void Console::DoWriteStringsCommaSeparated(
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

   INLINE void Console::WaitForEnterKeyIfDebuggerPresentOrValueTrue(bool doWait) const
   {
      if (doWait || DebuggerIsPresent())
      {
         WriteLine("Press Enter to continue . . .");
         WaitForEnterKey();
      }
   }

   INLINE void Console::WaitForEnterKey() const
   {
      std::string devNull;
      std::getline(std::cin, devNull);
   }

   INLINE bool Console::DebuggerIsPresent() const
   {
#ifdef __linux__
      return false;
#elif _WIN32
      const int isDebuggerPresentReturnValue = call_IsDebuggerPresent();
      const bool isDebuggerPresent = isDebuggerPresentReturnValue == 1;
      return isDebuggerPresent;
#endif
   }
}
