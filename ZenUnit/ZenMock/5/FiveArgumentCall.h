#pragma once
#include "ZenUnit/Macros/ARE_EQUAL.h"
#include "ZenUnit/ToStringer/ToStringer.h"

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   struct FiveArgumentCall
   {
      typename std::decay<Arg1Type>::type argument1;
      typename std::decay<Arg2Type>::type argument2;
      typename std::decay<Arg3Type>::type argument3;
      typename std::decay<Arg4Type>::type argument4;
      typename std::decay<Arg5Type>::type argument5;

      FiveArgumentCall()
         : argument1()
         , argument2()
         , argument3()
         , argument4()
         , argument5()
      {
      }

      FiveArgumentCall(
         const Arg1Type& argument1,
         const Arg2Type& argument2,
         const Arg3Type& argument3,
         const Arg4Type& argument4,
         const Arg5Type& argument5)
         : argument1(argument1)
         , argument2(argument2)
         , argument3(argument3)
         , argument4(argument4)
         , argument5(argument5)
      {
      }
   };
}

template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
struct ZenUnitEqualizer<ZenMock::FiveArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>
{
   static void AssertEqual(
      const ZenMock::FiveArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& expectedFiveArgumentCall,
      const ZenMock::FiveArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& actualFiveArgumentCall)
   {
      ARE_EQUAL(expectedFiveArgumentCall.argument1, actualFiveArgumentCall.argument1);
      ARE_EQUAL(expectedFiveArgumentCall.argument2, actualFiveArgumentCall.argument2);
      ARE_EQUAL(expectedFiveArgumentCall.argument3, actualFiveArgumentCall.argument3);
      ARE_EQUAL(expectedFiveArgumentCall.argument4, actualFiveArgumentCall.argument4);
      ARE_EQUAL(expectedFiveArgumentCall.argument5, actualFiveArgumentCall.argument5);
   }
};
