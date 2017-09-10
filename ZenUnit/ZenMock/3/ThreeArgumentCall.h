#pragma once
#include "ZenUnit/Macros/ARE_EQUAL.h"
#include "ZenUnit/ToStringer/ToStringer.h"

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
   struct ThreeArgumentCall
   {
      typename std::decay<Arg1Type>::type argument1;
      typename std::decay<Arg2Type>::type argument2;
      typename std::decay<Arg3Type>::type argument3;

      ThreeArgumentCall()
         : argument1()
         , argument2()
         , argument3()
      {
      }

      ThreeArgumentCall(const Arg1Type& argument1, const Arg2Type& argument2, const Arg3Type& argument3)
         : argument1(argument1)
         , argument2(argument2)
         , argument3(argument3)
      {
      }
   };
}

template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
struct ZenUnitEqualizer<ZenMock::ThreeArgumentCall<Arg1Type, Arg2Type, Arg3Type>>
{
   static void AssertEqual(
      const ZenMock::ThreeArgumentCall<Arg1Type, Arg2Type, Arg3Type>& expectedThreeArgumentCall,
      const ZenMock::ThreeArgumentCall<Arg1Type, Arg2Type, Arg3Type>& actualThreeArgumentCall)
   {
      ARE_EQUAL(expectedThreeArgumentCall.argument1, actualThreeArgumentCall.argument1);
      ARE_EQUAL(expectedThreeArgumentCall.argument2, actualThreeArgumentCall.argument2);
      ARE_EQUAL(expectedThreeArgumentCall.argument3, actualThreeArgumentCall.argument3);
   }
};
