#include "pch.h"
#include "ZenUnitTests/Random/RandomPrintMode.h"

namespace ZenUnit
{
   template<>
   PrintMode Random<PrintMode>()
   {
      return Random<PrintMode>(static_cast<int>(PrintMode::Unset), static_cast<int>(PrintMode::Detailed));
   }
}
