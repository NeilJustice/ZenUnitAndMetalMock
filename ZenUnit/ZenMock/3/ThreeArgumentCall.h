#pragma once
#include "ZenUnit/Macros/ARE_EQUAL.h"
#include "ZenUnit/ToStringer/ToStringer.h"

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
   struct ThreeArgumentCall
   {
      typename std::decay<Arg1Type>::type firstArgument;
      typename std::decay<Arg2Type>::type secondArgument;
      typename std::decay<Arg3Type>::type thirdArgument;

      ThreeArgumentCall()
         : firstArgument()
         , secondArgument()
         , thirdArgument()
      {
      }

      ThreeArgumentCall(const Arg1Type& firstArgument, const Arg2Type& secondArgument, const Arg3Type& thirdArgument)
         : firstArgument(firstArgument)
         , secondArgument(secondArgument)
         , thirdArgument(thirdArgument)
      {
      }
   };
}

template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
struct ZenUnitEqualizer<ZenMock::ThreeArgumentCall<Arg1Type, Arg2Type, Arg3Type>>
{
   static void AssertEqual(
      const ZenMock::ThreeArgumentCall<Arg1Type, Arg2Type, Arg3Type>& expectedThreeArgumentCall,
      const ZenMock::ThreeArgumentCall<Arg1Type, Arg2Type, Arg3Type>& actualThreeArgumentCall)
   {
      ARE_EQUAL(expectedThreeArgumentCall.firstArgument, actualThreeArgumentCall.firstArgument);
      ARE_EQUAL(expectedThreeArgumentCall.secondArgument, actualThreeArgumentCall.secondArgument);
      ARE_EQUAL(expectedThreeArgumentCall.thirdArgument, actualThreeArgumentCall.thirdArgument);
   }
};
