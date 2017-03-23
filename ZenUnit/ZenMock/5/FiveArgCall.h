#pragma once
#include "ZenUnit/Macros/ARE_EQUAL.h"
#include "ZenUnit/ToStringer/ToStringer.h"

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   struct FiveArgCall
   {
      typename std::decay<Arg1Type>::type arg1;
      typename std::decay<Arg2Type>::type arg2;
      typename std::decay<Arg3Type>::type arg3;
      typename std::decay<Arg4Type>::type arg4;
      typename std::decay<Arg5Type>::type arg5;

      FiveArgCall()
         : arg1(0)
         , arg2(0)
         , arg3(0)
         , arg4(0)
         , arg5(0)
      {
      }

      FiveArgCall(
         const Arg1Type& arg1,
         const Arg2Type& arg2,
         const Arg3Type& arg3,
         const Arg4Type& arg4,
         const Arg5Type& arg5)
         : arg1(arg1)
         , arg2(arg2)
         , arg3(arg3)
         , arg4(arg4)
         , arg5(arg5)
      {
      }
   };
}

template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
struct ZenUnitEqualizer<ZenMock::FiveArgCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>
{
   static void AssertEqual(
      const ZenMock::FiveArgCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& expectedFiveArgCall,
      const ZenMock::FiveArgCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& actualFiveArgCall)
   {
      ARE_EQUAL(expectedFiveArgCall.arg1, actualFiveArgCall.arg1);
      ARE_EQUAL(expectedFiveArgCall.arg2, actualFiveArgCall.arg2);
      ARE_EQUAL(expectedFiveArgCall.arg3, actualFiveArgCall.arg3);
      ARE_EQUAL(expectedFiveArgCall.arg4, actualFiveArgCall.arg4);
      ARE_EQUAL(expectedFiveArgCall.arg5, actualFiveArgCall.arg5);
   }
};
