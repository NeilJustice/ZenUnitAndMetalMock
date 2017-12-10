#pragma once
#include "ZenUnit/Macros/ARE_EQUAL.h"
#include "ZenUnit/ToStringer/ToStringer.h"

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   struct SixArgumentCall
   {
      typename std::decay<Arg1Type>::type firstArgument;
      typename std::decay<Arg2Type>::type secondArgument;
      typename std::decay<Arg3Type>::type thirdArgument;
      typename std::decay<Arg4Type>::type fourthArgument;
      typename std::decay<Arg5Type>::type fifthArgument;
      typename std::decay<Arg6Type>::type sixthArgument;

      SixArgumentCall() noexcept
         : firstArgument()
         , secondArgument()
         , thirdArgument()
         , fourthArgument()
         , fifthArgument()
         , sixthArgument()
      {
      }

      SixArgumentCall(
         const Arg1Type& firstArgument,
         const Arg2Type& secondArgument,
         const Arg3Type& thirdArgument,
         const Arg4Type& fourthArgument,
         const Arg5Type& fifthArgument,
         const Arg6Type& sixthArgument) noexcept
         : firstArgument(firstArgument)
         , secondArgument(secondArgument)
         , thirdArgument(thirdArgument)
         , fourthArgument(fourthArgument)
         , fifthArgument(fifthArgument)
         , sixthArgument(sixthArgument)
      {
      }
   };
}

namespace ZenUnit
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   struct Equalizer<ZenMock::SixArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>
   {
      static void AssertEqual(
         const ZenMock::SixArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& expectedSixArgumentCall,
         const ZenMock::SixArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& actualSixArgumentCall)
      {
         ARE_EQUAL(expectedSixArgumentCall.firstArgument, actualSixArgumentCall.firstArgument);
         ARE_EQUAL(expectedSixArgumentCall.secondArgument, actualSixArgumentCall.secondArgument);
         ARE_EQUAL(expectedSixArgumentCall.thirdArgument, actualSixArgumentCall.thirdArgument);
         ARE_EQUAL(expectedSixArgumentCall.fourthArgument, actualSixArgumentCall.fourthArgument);
         ARE_EQUAL(expectedSixArgumentCall.fifthArgument, actualSixArgumentCall.fifthArgument);
         ARE_EQUAL(expectedSixArgumentCall.sixthArgument, actualSixArgumentCall.sixthArgument);
      }
   };
}
