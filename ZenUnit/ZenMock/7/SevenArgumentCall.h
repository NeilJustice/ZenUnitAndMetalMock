#pragma once
#include "ZenUnit/Macros/ARE_EQUAL.h"
#include "ZenUnit/ToStringer/ToStringer.h"

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
   struct SevenArgumentCall
   {
      typename std::decay<Arg1Type>::type argument1;
      typename std::decay<Arg2Type>::type argument2;
      typename std::decay<Arg3Type>::type argument3;
      typename std::decay<Arg4Type>::type argument4;
      typename std::decay<Arg5Type>::type argument5;
      typename std::decay<Arg6Type>::type argument6;
      typename std::decay<Arg7Type>::type argument7;

      SevenArgumentCall()
         : argument1()
         , argument2()
         , argument3()
         , argument4()
         , argument5()
         , argument6()
         , argument7()
      {
      }

      SevenArgumentCall(
         const Arg1Type& argument1,
         const Arg2Type& argument2,
         const Arg3Type& argument3,
         const Arg4Type& argument4,
         const Arg5Type& argument5,
         const Arg6Type& argument6,
         const Arg7Type& argument7)
         : argument1(argument1)
         , argument2(argument2)
         , argument3(argument3)
         , argument4(argument4)
         , argument5(argument5)
         , argument6(argument6)
         , argument7(argument7)
      {
      }
   };
}

template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
struct ZenUnitEqualizer<ZenMock::SevenArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>
{
   static void AssertEqual(
      const ZenMock::SevenArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& expectedSevenArgumentCall,
      const ZenMock::SevenArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& actualSevenArgumentCall)
   {
      ARE_EQUAL(expectedSevenArgumentCall.argument1, actualSevenArgumentCall.argument1);
      ARE_EQUAL(expectedSevenArgumentCall.argument2, actualSevenArgumentCall.argument2);
      ARE_EQUAL(expectedSevenArgumentCall.argument3, actualSevenArgumentCall.argument3);
      ARE_EQUAL(expectedSevenArgumentCall.argument4, actualSevenArgumentCall.argument4);
      ARE_EQUAL(expectedSevenArgumentCall.argument5, actualSevenArgumentCall.argument5);
      ARE_EQUAL(expectedSevenArgumentCall.argument6, actualSevenArgumentCall.argument6);
      ARE_EQUAL(expectedSevenArgumentCall.argument7, actualSevenArgumentCall.argument7);
   }
};
