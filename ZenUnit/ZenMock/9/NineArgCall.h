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
   struct NineArgCall
   {
      typename std::decay<Arg1Type>::type arg1;
      typename std::decay<Arg2Type>::type arg2;
      typename std::decay<Arg3Type>::type arg3;
      typename std::decay<Arg4Type>::type arg4;
      typename std::decay<Arg5Type>::type arg5;
      typename std::decay<Arg6Type>::type arg6;
      typename std::decay<Arg6Type>::type arg7;
      typename std::decay<Arg6Type>::type arg8;
      typename std::decay<Arg6Type>::type arg9;

      NineArgCall()
         : arg1()
         , arg2()
         , arg3()
         , arg4()
         , arg5()
         , arg6()
         , arg7()
         , arg8()
         , arg9()
      {
      }

      NineArgCall(
         Arg1Type arg1,
         Arg2Type arg2,
         Arg3Type arg3,
         Arg4Type arg4,
         Arg5Type arg5,
         Arg6Type arg6,
         Arg7Type arg7,
         Arg8Type arg8,
         Arg9Type arg9)
         : arg1(std::move(arg1))
         , arg2(std::move(arg2))
         , arg3(std::move(arg3))
         , arg4(std::move(arg4))
         , arg5(std::move(arg5))
         , arg6(std::move(arg6))
         , arg7(std::move(arg7))
         , arg8(std::move(arg8))
         , arg9(std::move(arg9))
      {
      }
   };
}

template<
   typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type,
   typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type>
struct ZenUnitEqualizer<ZenMock::NineArgCall<
   Arg1Type, Arg2Type, Arg3Type, Arg4Type,
   Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>
{
   static void AssertEqual(
      const ZenMock::NineArgCall<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type,
         Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& expectedNineArgCall,
      const ZenMock::NineArgCall<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type,
         Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& actualNineArgCall)
   {
      ARE_EQUAL(expectedNineArgCall.arg1, actualNineArgCall.arg1);
      ARE_EQUAL(expectedNineArgCall.arg2, actualNineArgCall.arg2);
      ARE_EQUAL(expectedNineArgCall.arg3, actualNineArgCall.arg3);
      ARE_EQUAL(expectedNineArgCall.arg4, actualNineArgCall.arg4);
      ARE_EQUAL(expectedNineArgCall.arg5, actualNineArgCall.arg5);
      ARE_EQUAL(expectedNineArgCall.arg6, actualNineArgCall.arg6);
      ARE_EQUAL(expectedNineArgCall.arg7, actualNineArgCall.arg7);
      ARE_EQUAL(expectedNineArgCall.arg8, actualNineArgCall.arg8);
      ARE_EQUAL(expectedNineArgCall.arg9, actualNineArgCall.arg9);
   }
};
