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
   struct EightArgumentCall
   {
      typename std::decay<Arg1Type>::type firstArgument;
      typename std::decay<Arg2Type>::type secondArgument;
      typename std::decay<Arg3Type>::type thirdArgument;
      typename std::decay<Arg4Type>::type fourthArgument;
      typename std::decay<Arg5Type>::type fifthArgument;
      typename std::decay<Arg6Type>::type sixthArgument;
      typename std::decay<Arg7Type>::type seventhArgument;
      typename std::decay<Arg8Type>::type eigthArgument;

      EightArgumentCall() noexcept
         : firstArgument()
         , secondArgument()
         , thirdArgument()
         , fourthArgument()
         , fifthArgument()
         , sixthArgument()
         , seventhArgument()
         , eigthArgument()
      {
      }

      EightArgumentCall(
         const Arg1Type& firstArgument,
         const Arg2Type& secondArgument,
         const Arg3Type& thirdArgument,
         const Arg4Type& fourthArgument,
         const Arg5Type& fifthArgument,
         const Arg6Type& sixthArgument,
         const Arg7Type& seventhArgument,
         const Arg8Type& eigthArgument) noexcept
         : firstArgument(firstArgument)
         , secondArgument(secondArgument)
         , thirdArgument(thirdArgument)
         , fourthArgument(fourthArgument)
         , fifthArgument(fifthArgument)
         , sixthArgument(sixthArgument)
         , seventhArgument(seventhArgument)
         , eigthArgument(eigthArgument)
      {
      }
   };
}

namespace ZenUnit
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type>
   struct Equalizer<ZenMock::EightArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>>
   {
      static void AssertEqual(
         const ZenMock::EightArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>& expectedEightArgumentCall,
         const ZenMock::EightArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>& actualEightArgumentCall)
      {
         ARE_EQUAL(expectedEightArgumentCall.firstArgument, actualEightArgumentCall.firstArgument);
         ARE_EQUAL(expectedEightArgumentCall.secondArgument, actualEightArgumentCall.secondArgument);
         ARE_EQUAL(expectedEightArgumentCall.thirdArgument, actualEightArgumentCall.thirdArgument);
         ARE_EQUAL(expectedEightArgumentCall.fourthArgument, actualEightArgumentCall.fourthArgument);
         ARE_EQUAL(expectedEightArgumentCall.fifthArgument, actualEightArgumentCall.fifthArgument);
         ARE_EQUAL(expectedEightArgumentCall.sixthArgument, actualEightArgumentCall.sixthArgument);
         ARE_EQUAL(expectedEightArgumentCall.seventhArgument, actualEightArgumentCall.seventhArgument);
         ARE_EQUAL(expectedEightArgumentCall.eigthArgument, actualEightArgumentCall.eigthArgument);
      }
   };
}
