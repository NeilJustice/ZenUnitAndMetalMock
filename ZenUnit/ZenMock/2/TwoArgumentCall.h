#pragma once
#include "ZenUnit/Macros/ARE_EQUAL.h"

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type>
   struct TwoArgumentCall
   {
      typename std::decay<Arg1Type>::type argument1;
      typename std::decay<Arg2Type>::type argument2;

      TwoArgumentCall()
         : argument1()
         , argument2()
      {
      }

      TwoArgumentCall(const Arg1Type& argument1, const Arg2Type& argument2)
         : argument1(argument1)
         , argument2(argument2)
      {
      }
   };
}

template<typename Arg1Type, typename Arg2Type>
struct ZenUnitEqualizer<ZenMock::TwoArgumentCall<Arg1Type, Arg2Type>>
{
   static void AssertEqual(
      const ZenMock::TwoArgumentCall<Arg1Type, Arg2Type>& expectedTwoArgumentCall,
      const ZenMock::TwoArgumentCall<Arg1Type, Arg2Type>& actualTwoArgumentCall)
   {
      ARE_EQUAL(expectedTwoArgumentCall.argument1, actualTwoArgumentCall.argument1);
      ARE_EQUAL(expectedTwoArgumentCall.argument2, actualTwoArgumentCall.argument2);
   }
};
