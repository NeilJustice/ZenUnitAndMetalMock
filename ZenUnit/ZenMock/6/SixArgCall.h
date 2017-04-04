#pragma once
#include "ZenUnit/Macros/ARE_EQUAL.h"
#include "ZenUnit/ToStringer/ToStringer.h"

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   struct SixArgCall
   {
      typename std::decay<Arg1Type>::type arg1;
      typename std::decay<Arg2Type>::type arg2;
      typename std::decay<Arg3Type>::type arg3;
      typename std::decay<Arg4Type>::type arg4;
      typename std::decay<Arg5Type>::type arg5;
      typename std::decay<Arg6Type>::type arg6;

      SixArgCall()
         : arg1()
         , arg2()
         , arg3()
         , arg4()
         , arg5()
         , arg6()
      {
      }

      SixArgCall(
         Arg1Type arg1,
         Arg2Type arg2,
         Arg3Type arg3,
         Arg4Type arg4,
         Arg5Type arg5,
         Arg6Type arg6)
         : arg1(std::move(arg1))
         , arg2(std::move(arg2))
         , arg3(std::move(arg3))
         , arg4(std::move(arg4))
         , arg5(std::move(arg5))
         , arg6(std::move(arg6))
      {
      }
   };
}

template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
struct ZenUnitEqualizer<ZenMock::SixArgCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>
{
   static void AssertEqual(
      const ZenMock::SixArgCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& expectedSixArgCall,
      const ZenMock::SixArgCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& actualSixArgCall)
   {
      ARE_EQUAL(expectedSixArgCall.arg1, actualSixArgCall.arg1);
      ARE_EQUAL(expectedSixArgCall.arg2, actualSixArgCall.arg2);
      ARE_EQUAL(expectedSixArgCall.arg3, actualSixArgCall.arg3);
      ARE_EQUAL(expectedSixArgCall.arg4, actualSixArgCall.arg4);
      ARE_EQUAL(expectedSixArgCall.arg5, actualSixArgCall.arg5);
      ARE_EQUAL(expectedSixArgCall.arg6, actualSixArgCall.arg6);
   }
};
