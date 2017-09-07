#pragma once
#include "ZenUnit/Macros/ARE_EQUAL.h"
#include "ZenUnit/ToStringer/ToStringer.h"

namespace ZenMock
{
   template<typename Arg1Type>
   struct OneArgCall
   {
      typename std::decay<Arg1Type>::type arg;

      OneArgCall()
         : arg()
      {
      }

      OneArgCall(const Arg1Type& arg)
         : arg(arg)
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
      ARE_EQUAL(expectedOneArgCall.arg, actualOneArgCall.arg);
   }
};
