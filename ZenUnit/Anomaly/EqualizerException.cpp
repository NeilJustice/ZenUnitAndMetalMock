#include "pch.h"
#include "ZenUnit/Anomaly/EqualizerException.h"

namespace ZenUnit
{
   INLINE EqualizerException::EqualizerException() noexcept
   {
   }

   INLINE const char* EqualizerException::what() const noexcept
   {
      return "";
   }
}
