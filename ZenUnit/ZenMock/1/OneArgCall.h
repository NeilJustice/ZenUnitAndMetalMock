#pragma once
#include "ZenUnit/Macros/ARE_EQUAL.h"
#include "ZenUnit/ToStringer/ToStringer.h"

namespace ZenMock
{
   template<typename Arg1Type>
   struct OneArgCall
   {
      typename std::decay<Arg1Type>::type arg1;

      OneArgCall()
         : arg1()
      {
      }

      OneArgCall(const Arg1Type& arg1)
         : arg1(arg1)
      {
      }
   };
}

template<typename ArgType>
struct ZenUnitEqualizer<ZenMock::OneArgCall<ArgType>>
{
   static void AssertEqual(
      const ZenMock::OneArgCall<ArgType>& expectedOneArgCall,
      const ZenMock::OneArgCall<ArgType>& actualOneArgCall)
   {
      ARE_EQUAL(expectedOneArgCall.arg1, actualOneArgCall.arg1);
   }
};
