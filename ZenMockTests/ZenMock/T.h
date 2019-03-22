#pragma once

namespace ZenMock
{
   template<size_t Value>
   struct T
   {
      bool flag;

      T() noexcept
         : flag(false)
      {
      }

      explicit T(bool flag)
         : flag(flag)
      {
      }

      friend bool operator==(const T<Value>& lhs, const T<Value>& rhs)
      {
         return lhs.flag == rhs.flag;
      }
   };

   const string S1 = "1", S2 = "2", S3 = "3", S4 = "4", S5 = "5", S6 = "6", S7 = "7", S8 = "8", S9 = "9", S10 = "10";

   void AssertARE_EQUALThrowsAnomalyContaining(const function<void()>& areEqualCall, const char* expectedWhatContains);
}
