#pragma once
#include "ZenUnit/Macros/ARE_EQUAL.h"
#include "ZenUnit/ToStringer/ToStringer.h"

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   struct FourArgumentCall
   {
      typename std::decay<Arg1Type>::type argument1;
      typename std::decay<Arg2Type>::type argument2;
      typename std::decay<Arg3Type>::type argument3;
      typename std::decay<Arg4Type>::type argument4;

      FourArgumentCall()
         : argument1()
         , argument2()
         , argument3()
         , argument4()
      {
      }

      FourArgumentCall(const Arg1Type& argument1, const Arg2Type& argument2, const Arg3Type& argument3, const Arg4Type& argument4)
         : argument1(argument1)
         , argument2(argument2)
         , argument3(argument3)
         , argument4(argument4)
      {
      }
   };
}

template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
struct ZenUnitEqualizer<ZenMock::FourArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>
{
   static void AssertEqual(
      const ZenMock::FourArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& expectedFourArgumentCall,
      const ZenMock::FourArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& actualFourArgumentCall)
    {
       ARE_EQUAL(expectedFourArgumentCall.argument1, actualFourArgumentCall.argument1);
       ARE_EQUAL(expectedFourArgumentCall.argument2, actualFourArgumentCall.argument2);
       ARE_EQUAL(expectedFourArgumentCall.argument3, actualFourArgumentCall.argument3);
       ARE_EQUAL(expectedFourArgumentCall.argument4, actualFourArgumentCall.argument4);
    }
};
