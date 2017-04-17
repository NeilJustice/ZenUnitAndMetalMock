#pragma once
#include <exception>

namespace ZenUnit
{
   class EqualizerException : public std::exception
   {
   public:
      EqualizerException() {}
      virtual const char* what() const noexcept override { return ""; }
   };
}
