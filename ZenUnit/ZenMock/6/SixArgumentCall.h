#pragma once
#include "ZenUnit/Macros/ARE_EQUAL.h"
#include "ZenUnit/ToStringer/ToStringer.h"

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   struct SixArgumentCall
   {
      typename std::decay<Arg1Type>::type argument1;
      typename std::decay<Arg2Type>::type argument2;
      typename std::decay<Arg3Type>::type argument3;
      typename std::decay<Arg4Type>::type argument4;
      typename std::decay<Arg5Type>::type argument5;
      typename std::decay<Arg6Type>::type argument6;

      SixArgumentCall()
         : argument1()
         , argument2()
         , argument3()
         , argument4()
         , argument5()
         , argument6()
      {
      }

      SixArgumentCall(
         const Arg1Type& argument1,
         const Arg2Type& argument2,
         const Arg3Type& argument3,
         const Arg4Type& argument4,
         const Arg5Type& argument5,
         const Arg6Type& argument6)
         : argument1(argument1)
         , argument2(argument2)
         , argument3(argument3)
         , argument4(argument4)
         , argument5(argument5)
         , argument6(argument6)
      {
      }
   };
}

template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
struct ZenUnitEqualizer<ZenMock::SixArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>
{
   static void AssertEqual(
      const ZenMock::SixArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& expectedSixArgumentCall,
      const ZenMock::SixArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& actualSixArgumentCall)
   {
      ARE_EQUAL(expectedSixArgumentCall.argument1, actualSixArgumentCall.argument1);
      ARE_EQUAL(expectedSixArgumentCall.argument2, actualSixArgumentCall.argument2);
      ARE_EQUAL(expectedSixArgumentCall.argument3, actualSixArgumentCall.argument3);
      ARE_EQUAL(expectedSixArgumentCall.argument4, actualSixArgumentCall.argument4);
      ARE_EQUAL(expectedSixArgumentCall.argument5, actualSixArgumentCall.argument5);
      ARE_EQUAL(expectedSixArgumentCall.argument6, actualSixArgumentCall.argument6);
   }
};
