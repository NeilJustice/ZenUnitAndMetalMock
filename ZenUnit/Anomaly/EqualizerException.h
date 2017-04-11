#pragma once

namespace ZenUnit
{
   class EqualizerException : public std::exception
   {
   public:
      EqualizerException() {}
      const char* what() const noexcept final { return ""; }
   };
}
