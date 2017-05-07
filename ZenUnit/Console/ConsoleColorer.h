#pragma once

namespace ZenUnit
{
   enum class Color : unsigned char;

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
      bool _supportsColor;
      bool _supportsColorSet;
   public:
      ConsoleColorer();
      virtual ~ConsoleColorer() = default;
      virtual bool SetColor(Color color);
      virtual void UnsetColor(bool didPreviouslySetTextColor) const;
   private:
      virtual void SetSupportsColorIfUnset();
      virtual bool SupportsColor() const;
      virtual void SetTextColor(Color color) const;
   };
}
