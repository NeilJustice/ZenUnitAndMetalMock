#pragma once
#include "ZenUnit/Macros/ARE_EQUAL.h"
#include "ZenUnit/ToStringer/ToStringer.h"

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
   struct SevenArgumentCall
   {
      typename std::decay<Arg1Type>::type firstArgument;
      typename std::decay<Arg2Type>::type secondArgument;
      typename std::decay<Arg3Type>::type thirdArgument;
      typename std::decay<Arg4Type>::type fourthArgument;
      typename std::decay<Arg5Type>::type fifthArgument;
      typename std::decay<Arg6Type>::type sixthArgument;
      typename std::decay<Arg7Type>::type seventhArgument;

      SevenArgumentCall()
         : firstArgument()
         , secondArgument()
         , thirdArgument()
         , fourthArgument()
         , fifthArgument()
         , sixthArgument()
         , seventhArgument()
      {
      }

      SevenArgumentCall(
         const Arg1Type& firstArgument,
         const Arg2Type& secondArgument,
         const Arg3Type& thirdArgument,
         const Arg4Type& fourthArgument,
         const Arg5Type& fifthArgument,
         const Arg6Type& sixthArgument,
         const Arg7Type& seventhArgument)
         : firstArgument(firstArgument)
         , secondArgument(secondArgument)
         , thirdArgument(thirdArgument)
         , fourthArgument(fourthArgument)
         , fifthArgument(fifthArgument)
         , sixthArgument(sixthArgument)
         , seventhArgument(seventhArgument)
      {
      }
   };
}

namespace ZenUnit
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
   struct Equalizer<ZenMock::SevenArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>
   {
      static void AssertEqual(
         const ZenMock::SevenArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& expectedSevenArgumentCall,
         const ZenMock::SevenArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& actualSevenArgumentCall)
      {
         ARE_EQUAL(expectedSevenArgumentCall.firstArgument, actualSevenArgumentCall.firstArgument);
         ARE_EQUAL(expectedSevenArgumentCall.secondArgument, actualSevenArgumentCall.secondArgument);
         ARE_EQUAL(expectedSevenArgumentCall.thirdArgument, actualSevenArgumentCall.thirdArgument);
         ARE_EQUAL(expectedSevenArgumentCall.fourthArgument, actualSevenArgumentCall.fourthArgument);
         ARE_EQUAL(expectedSevenArgumentCall.fifthArgument, actualSevenArgumentCall.fifthArgument);
         ARE_EQUAL(expectedSevenArgumentCall.sixthArgument, actualSevenArgumentCall.sixthArgument);
         ARE_EQUAL(expectedSevenArgumentCall.seventhArgument, actualSevenArgumentCall.seventhArgument);
      }
   };
}
