#include "pch.h"
#include "T.h"

namespace ZenMock
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
