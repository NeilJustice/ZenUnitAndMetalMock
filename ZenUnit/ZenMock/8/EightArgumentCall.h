#pragma once
#include "ZenUnit/Macros/ARE_EQUAL.h"
#include "ZenUnit/ToStringer/ToStringer.h"

namespace ZenMock
{
   template<
      typename Arg1Type,
      typename Arg2Type,
      typename Arg3Type,
      typename Arg4Type,
      typename Arg5Type,
      typename Arg6Type,
      typename Arg7Type,
      typename Arg8Type>
   struct EightArgumentCall
   {
      typename std::decay<Arg1Type>::type argument1;
      typename std::decay<Arg2Type>::type argument2;
      typename std::decay<Arg3Type>::type argument3;
      typename std::decay<Arg4Type>::type argument4;
      typename std::decay<Arg5Type>::type argument5;
      typename std::decay<Arg6Type>::type argument6;
      typename std::decay<Arg7Type>::type argument7;
      typename std::decay<Arg8Type>::type argument8;

      EightArgumentCall()
         : argument1()
         , argument2()
         , argument3()
         , argument4()
         , argument5()
         , argument6()
         , argument7()
         , argument8()
      {
      }

      EightArgumentCall(
         const Arg1Type& argument1,
         const Arg2Type& argument2,
         const Arg3Type& argument3,
         const Arg4Type& argument4,
         const Arg5Type& argument5,
         const Arg6Type& argument6,
         const Arg7Type& argument7,
         const Arg8Type& argument8)
         : argument1(argument1)
         , argument2(argument2)
         , argument3(argument3)
         , argument4(argument4)
         , argument5(argument5)
         , argument6(argument6)
         , argument7(argument7)
         , argument8(argument8)
      {
      }
   };
}

template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type>
struct ZenUnitEqualizer<ZenMock::EightArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>>
{
   static void AssertEqual(
      const ZenMock::EightArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>& expectedEightArgumentCall,
      const ZenMock::EightArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>& actualEightArgumentCall)
   {
      ARE_EQUAL(expectedEightArgumentCall.argument1, actualEightArgumentCall.argument1);
      ARE_EQUAL(expectedEightArgumentCall.argument2, actualEightArgumentCall.argument2);
      ARE_EQUAL(expectedEightArgumentCall.argument3, actualEightArgumentCall.argument3);
      ARE_EQUAL(expectedEightArgumentCall.argument4, actualEightArgumentCall.argument4);
      ARE_EQUAL(expectedEightArgumentCall.argument5, actualEightArgumentCall.argument5);
      ARE_EQUAL(expectedEightArgumentCall.argument6, actualEightArgumentCall.argument6);
      ARE_EQUAL(expectedEightArgumentCall.argument7, actualEightArgumentCall.argument7);
      ARE_EQUAL(expectedEightArgumentCall.argument8, actualEightArgumentCall.argument8);
   }
};
