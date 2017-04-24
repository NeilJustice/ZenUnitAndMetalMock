#pragma once

namespace ZenUnit
{
   enum class TestOutcome : unsigned char
   {
      Unset,
      Success,
      SuccessButPastDeadline,
      Anomaly,
      Exception
   };
}
