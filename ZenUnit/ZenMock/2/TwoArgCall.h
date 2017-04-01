#pragma once
#include "ZenUnit/Macros/ARE_EQUAL.h"

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type>
   struct TwoArgCall
   {
      typename std::decay<Arg1Type>::type arg1;
      typename std::decay<Arg2Type>::type arg2;

      TwoArgCall()
         : arg1()
         , arg2()
      {
      }

      TwoArgCall(Arg1Type arg1, Arg2Type arg2)
         : arg1(std::move(arg1))
         , arg2(std::move(arg2))
      {
      }
   };
}

template<typename Arg1Type, typename Arg2Type>
struct ZenUnitEqualizer<ZenMock::TwoArgCall<Arg1Type, Arg2Type>>
{
   static void AssertEqual(
      const ZenMock::TwoArgCall<Arg1Type, Arg2Type>& expectedTwoArgCall,
      const ZenMock::TwoArgCall<Arg1Type, Arg2Type>& actualTwoArgCall)
   {
      ARE_EQUAL(expectedTwoArgCall.arg1, actualTwoArgCall.arg1);
      ARE_EQUAL(expectedTwoArgCall.arg2, actualTwoArgCall.arg2);
   }
};
