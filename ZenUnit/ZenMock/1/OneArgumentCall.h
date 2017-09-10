#pragma once
#include "ZenUnit/Macros/ARE_EQUAL.h"
#include "ZenUnit/ToStringer/ToStringer.h"

namespace ZenMock
{
   template<typename Arg1Type>
   struct OneArgumentCall
   {
      typename std::decay<Arg1Type>::type argument;

      OneArgumentCall()
         : argument()
      {
      }

      OneArgumentCall(const Arg1Type& argument)
         : argument(argument)
      {
      }
   };
}

template<typename ArgType>
struct ZenUnitEqualizer<ZenMock::OneArgumentCall<ArgType>>
{
   static void AssertEqual(
      const ZenMock::OneArgumentCall<ArgType>& expectedOneArgumentCall,
      const ZenMock::OneArgumentCall<ArgType>& actualOneArgumentCall)
   {
      ARE_EQUAL(expectedOneArgumentCall.argument, actualOneArgumentCall.argument);
   }
};
