#pragma once

namespace ZenUnit
{
   enum class TestOutcome : unsigned char
   {
      Unset,
      Success,
      SuccessButMissedDeadline,
      Anomaly,
      Exception
   };
}
