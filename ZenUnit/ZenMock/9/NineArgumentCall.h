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
   struct NineArgumentCall
   {
      typename std::decay<Arg1Type>::type firstArgument;
      typename std::decay<Arg2Type>::type secondArgument;
      typename std::decay<Arg3Type>::type thirdArgument;
      typename std::decay<Arg4Type>::type fourthArgument;
      typename std::decay<Arg5Type>::type fifthArgument;
      typename std::decay<Arg6Type>::type sixthArgument;
      typename std::decay<Arg7Type>::type seventhArgument;
      typename std::decay<Arg8Type>::type eigthArgument;
      typename std::decay<Arg9Type>::type ninthArgument;

      NineArgumentCall() noexcept
         : firstArgument()
         , secondArgument()
         , thirdArgument()
         , fourthArgument()
         , fifthArgument()
         , sixthArgument()
         , seventhArgument()
         , eigthArgument()
         , ninthArgument()
      {
      }

      NineArgumentCall(
         const Arg1Type& firstArgument,
         const Arg2Type& secondArgument,
         const Arg3Type& thirdArgument,
         const Arg4Type& fourthArgument,
         const Arg5Type& fifthArgument,
         const Arg6Type& sixthArgument,
         const Arg7Type& seventhArgument,
         const Arg8Type& eigthArgument,
         const Arg9Type& ninthArgument) noexcept
         : firstArgument(firstArgument)
         , secondArgument(secondArgument)
         , thirdArgument(thirdArgument)
         , fourthArgument(fourthArgument)
         , fifthArgument(fifthArgument)
         , sixthArgument(sixthArgument)
         , seventhArgument(seventhArgument)
         , eigthArgument(eigthArgument)
         , ninthArgument(ninthArgument)
      {
      }
   };
}

namespace ZenUnit
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type>
   struct Equalizer<ZenMock::NineArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>
   {
      static void AssertEqual(
         const ZenMock::NineArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& expectedNineArgumentCall,
         const ZenMock::NineArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& actualNineArgumentCall)
      {
         ARE_EQUAL(expectedNineArgumentCall.firstArgument, actualNineArgumentCall.firstArgument);
         ARE_EQUAL(expectedNineArgumentCall.secondArgument, actualNineArgumentCall.secondArgument);
         ARE_EQUAL(expectedNineArgumentCall.thirdArgument, actualNineArgumentCall.thirdArgument);
         ARE_EQUAL(expectedNineArgumentCall.fourthArgument, actualNineArgumentCall.fourthArgument);
         ARE_EQUAL(expectedNineArgumentCall.fifthArgument, actualNineArgumentCall.fifthArgument);
         ARE_EQUAL(expectedNineArgumentCall.sixthArgument, actualNineArgumentCall.sixthArgument);
         ARE_EQUAL(expectedNineArgumentCall.seventhArgument, actualNineArgumentCall.seventhArgument);
         ARE_EQUAL(expectedNineArgumentCall.eigthArgument, actualNineArgumentCall.eigthArgument);
         ARE_EQUAL(expectedNineArgumentCall.ninthArgument, actualNineArgumentCall.ninthArgument);
      }
   };
}
