#include "pch.h"
#include "MetalMockTests/MetalMock/T.h"

namespace MetalMock
{
   void AssertARE_EQUALThrowsAnomalyContaining(const function<void()>& areEqualCall, const char* expectedWhatContains)
   {
      try
      {
         areEqualCall();
      }
      catch (const Anomaly& anomaly)
      {
         IS_TRUE(String::Contains(anomaly.what(), expectedWhatContains));
      }
   }
}
