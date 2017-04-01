#pragma once
#include "ZenUnit/Console/Color.h"
#include <functional>

namespace ZenUnit
{
   class ConsoleColorer
   {
      friend class ConsoleColorerTests;
   private:
      std::function<int(FILE*)> fileno_ZenMockable;
      std::function<int(int)> isatty_ZenMockable;
#ifdef _WIN32
      std::function<HANDLE(DWORD)> GetStdHandle_ZenMockable;
      std::function<BOOL(HANDLE, WORD)> SetConsoleTextAttribute_ZenMockable;
#endif
   public:
      ConsoleColorer();
      virtual ~ConsoleColorer() = default;
      virtual bool SetColor(Color color) const;
      virtual void UnsetColor(bool didSetTextColor) const;
   private:
      virtual bool SupportsColor() const;
      virtual void SetTextColor(Color color) const;
   };
}
