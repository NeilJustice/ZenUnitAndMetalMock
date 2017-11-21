#pragma once
#include "ZenUnit/Macros/ARE_EQUAL.h"
#include "ZenUnit/ToStringer/ToStringer.h"

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   struct FiveArgumentCall
   {
      typename std::decay<Arg1Type>::type firstArgument;
      typename std::decay<Arg2Type>::type secondArgument;
      typename std::decay<Arg3Type>::type thirdArgument;
      typename std::decay<Arg4Type>::type fourthArgument;
      typename std::decay<Arg5Type>::type fifthArgument;

      FiveArgumentCall()
         : firstArgument()
         , secondArgument()
         , thirdArgument()
         , fourthArgument()
         , fifthArgument()
      {
      }

      FiveArgumentCall(
         const Arg1Type& firstArgument,
         const Arg2Type& secondArgument,
         const Arg3Type& thirdArgument,
         const Arg4Type& fourthArgument,
         const Arg5Type& fifthArgument)
         : firstArgument(firstArgument)
         , secondArgument(secondArgument)
         , thirdArgument(thirdArgument)
         , fourthArgument(fourthArgument)
         , fifthArgument(fifthArgument)
      {
      }
   };
}

namespace ZenUnit
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   struct Equalizer<ZenMock::FiveArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>
   {
      static void AssertEqual(
         const ZenMock::FiveArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& expectedFiveArgumentCall,
         const ZenMock::FiveArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& actualFiveArgumentCall)
      {
         ARE_EQUAL(expectedFiveArgumentCall.firstArgument, actualFiveArgumentCall.firstArgument);
         ARE_EQUAL(expectedFiveArgumentCall.secondArgument, actualFiveArgumentCall.secondArgument);
         ARE_EQUAL(expectedFiveArgumentCall.thirdArgument, actualFiveArgumentCall.thirdArgument);
         ARE_EQUAL(expectedFiveArgumentCall.fourthArgument, actualFiveArgumentCall.fourthArgument);
         ARE_EQUAL(expectedFiveArgumentCall.fifthArgument, actualFiveArgumentCall.fifthArgument);
      }
   };
}
