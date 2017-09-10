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
      typename Arg8Type,
      typename Arg9Type>
   struct NineArgumentCall
   {
      typename std::decay<Arg1Type>::type argument1;
      typename std::decay<Arg2Type>::type argument2;
      typename std::decay<Arg3Type>::type argument3;
      typename std::decay<Arg4Type>::type argument4;
      typename std::decay<Arg5Type>::type argument5;
      typename std::decay<Arg6Type>::type argument6;
      typename std::decay<Arg7Type>::type argument7;
      typename std::decay<Arg8Type>::type argument8;
      typename std::decay<Arg9Type>::type argument9;

      NineArgumentCall()
         : argument1()
         , argument2()
         , argument3()
         , argument4()
         , argument5()
         , argument6()
         , argument7()
         , argument8()
         , argument9()
      {
      }

      NineArgumentCall(
         const Arg1Type& argument1,
         const Arg2Type& argument2,
         const Arg3Type& argument3,
         const Arg4Type& argument4,
         const Arg5Type& argument5,
         const Arg6Type& argument6,
         const Arg7Type& argument7,
         const Arg8Type& argument8,
         const Arg9Type& argument9)
         : argument1(argument1)
         , argument2(argument2)
         , argument3(argument3)
         , argument4(argument4)
         , argument5(argument5)
         , argument6(argument6)
         , argument7(argument7)
         , argument8(argument8)
         , argument9(argument9)
      {
      }
   };
}

template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type>
struct ZenUnitEqualizer<ZenMock::NineArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>
{
   static void AssertEqual(
      const ZenMock::NineArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& expectedNineArgumentCall,
      const ZenMock::NineArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& actualNineArgumentCall)
   {
      ARE_EQUAL(expectedNineArgumentCall.argument1, actualNineArgumentCall.argument1);
      ARE_EQUAL(expectedNineArgumentCall.argument2, actualNineArgumentCall.argument2);
      ARE_EQUAL(expectedNineArgumentCall.argument3, actualNineArgumentCall.argument3);
      ARE_EQUAL(expectedNineArgumentCall.argument4, actualNineArgumentCall.argument4);
      ARE_EQUAL(expectedNineArgumentCall.argument5, actualNineArgumentCall.argument5);
      ARE_EQUAL(expectedNineArgumentCall.argument6, actualNineArgumentCall.argument6);
      ARE_EQUAL(expectedNineArgumentCall.argument7, actualNineArgumentCall.argument7);
      ARE_EQUAL(expectedNineArgumentCall.argument8, actualNineArgumentCall.argument8);
      ARE_EQUAL(expectedNineArgumentCall.argument9, actualNineArgumentCall.argument9);
   }
};
