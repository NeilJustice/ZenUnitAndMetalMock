#include "pch.h"
#include "Console.h"
#include "Console/ConsoleColorer.h"

namespace ZenUnit
{
   Console::Console()
      : _consoleColorer(new ConsoleColorer)
      , exit_ZenMockable(::exit)
#ifdef _WIN32
      , IsDebuggerPresent_ZenMockable(::IsDebuggerPresent)
#endif
   {
   }

   Console::~Console() = default;

   void Console::Write(const string& message) const
   {
      WriteColor(message, Color::White);
   }

   void Console::WriteColor(const string& message, Color color) const
   {
      const bool didSetColor = _consoleColorer->SetColor(color);
      printf("%s", message.c_str());
      cout.flush(); // Explicit flush needed on Linux to show test run progress output immediately
      _consoleColorer->UnsetColor(didSetColor);
   }

   void Console::WriteLine(const string& message) const
   {
      WriteLineColor(message, Color::White);
   }

   void Console::WriteLineColor(const string& message, Color color) const
   {
      const bool didSetColor = _consoleColorer->SetColor(color);
      // With VS2015.3 debug and release mode, printf("%s\n") measured as ~15% faster
      // and with less speed variance relative to "cout << message << '\n'".
      // On Linux, no significant difference measured between printf and cout.
      printf("%s\n", message.c_str());
      cout.flush(); // Explicit flush needed on Linux to show test run progress output immediately
      _consoleColorer->UnsetColor(didSetColor);
   }

   void Console::WriteNewline() const
   {
      cout << endl;
   }

   void Console::WriteLineAndExit(const std::string& message, int exitCode) const
   {
      cout << message << endl;
      exit_ZenMockable(exitCode);
   }

   void Console::PrintStringsCommaSeparated(
      const std::vector<std::string>& strings, size_t startIndex, size_t numberOfElements) const
   {
      if (startIndex >= strings.size())
      {
         throw invalid_argument(
            "Console::PrintVectorValuesCommaSeparated(): startIndex must be < strings.size(). startIndex=" +
            to_string(startIndex) + ", strings.size(): " + to_string(strings.size()));
      }
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
      const int isDebuggerPresentReturnValue = IsDebuggerPresent_ZenMockable();
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
