#include "pch.h"
#include "ZenUnit/Anomaly/EqualizerException.h"

namespace ZenUnit
{
   ZENUNIT(EqualizerException_what_ReturnsEmptyString)
   {
      EqualizerException equalizerException;
      ARE_EQUAL("", equalizerException.what());
   }
}
