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
   struct EightArgCall
   {
      typename std::decay<Arg1Type>::type arg1;
      typename std::decay<Arg2Type>::type arg2;
      typename std::decay<Arg3Type>::type arg3;
      typename std::decay<Arg4Type>::type arg4;
      typename std::decay<Arg5Type>::type arg5;
      typename std::decay<Arg6Type>::type arg6;
      typename std::decay<Arg6Type>::type arg7;
      typename std::decay<Arg6Type>::type arg8;

      EightArgCall()
         : arg1(0)
         , arg2(0)
         , arg3(0)
         , arg4(0)
         , arg5(0)
         , arg6(0)
         , arg7(0)
         , arg8(0)
      {
      }

      EightArgCall(
         Arg1Type arg1,
         Arg2Type arg2,
         Arg3Type arg3,
         Arg4Type arg4,
         Arg5Type arg5,
         Arg6Type arg6,
         Arg7Type arg7,
         Arg8Type arg8)
         : arg1(std::move(arg1))
         , arg2(std::move(arg2))
         , arg3(std::move(arg3))
         , arg4(std::move(arg4))
         , arg5(std::move(arg5))
         , arg6(std::move(arg6))
         , arg7(std::move(arg7))
         , arg8(std::move(arg8))
      {
      }
   };
}

template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type>
struct ZenUnitEqualizer<ZenMock::EightArgCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>>
{
   static void AssertEqual(
      const ZenMock::EightArgCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>& expectedEightArgCall,
      const ZenMock::EightArgCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>& actualEightArgCall)
   {
      ARE_EQUAL(expectedEightArgCall.arg1, actualEightArgCall.arg1);
      ARE_EQUAL(expectedEightArgCall.arg2, actualEightArgCall.arg2);
      ARE_EQUAL(expectedEightArgCall.arg3, actualEightArgCall.arg3);
      ARE_EQUAL(expectedEightArgCall.arg4, actualEightArgCall.arg4);
      ARE_EQUAL(expectedEightArgCall.arg5, actualEightArgCall.arg5);
      ARE_EQUAL(expectedEightArgCall.arg6, actualEightArgCall.arg6);
      ARE_EQUAL(expectedEightArgCall.arg7, actualEightArgCall.arg7);
      ARE_EQUAL(expectedEightArgCall.arg8, actualEightArgCall.arg8);
   }
};
