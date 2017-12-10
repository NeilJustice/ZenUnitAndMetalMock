#pragma once
#include <exception>

namespace ZenUnit
{
   class EqualizerException : public std::exception
   {
   public:
      EqualizerException() noexcept;
      const char* what() const noexcept override;
   };
}
