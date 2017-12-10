#pragma once
#include "ZenUnit/ZenMock/6/SixArgumentCall.h"

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   struct SixArgumentCallRef
   {
      const Arg1Type& firstArgument;
      const Arg2Type& secondArgument;
      const Arg3Type& thirdArgument;
      const Arg4Type& fourthArgument;
      const Arg5Type& fifthArgument;
      const Arg6Type& sixthArgument;

      SixArgumentCallRef(
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

      explicit SixArgumentCallRef(const SixArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& sixArgumentCall) noexcept
         : firstArgument(sixArgumentCall.firstArgument)
         , secondArgument(sixArgumentCall.secondArgument)
         , thirdArgument(sixArgumentCall.thirdArgument)
         , fourthArgument(sixArgumentCall.fourthArgument)
         , fifthArgument(sixArgumentCall.fifthArgument)
         , sixthArgument(sixArgumentCall.sixthArgument)
      {
      }
   };
}

namespace ZenUnit
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   struct Equalizer<ZenMock::SixArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>
   {
      static void AssertEqual(
         const ZenMock::SixArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& expectedSixArgumentCall,
         const ZenMock::SixArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& actualSixArgumentCall)
      {
         ARE_EQUAL(expectedSixArgumentCall.firstArgument, actualSixArgumentCall.firstArgument);
         ARE_EQUAL(expectedSixArgumentCall.secondArgument, actualSixArgumentCall.secondArgument);
         ARE_EQUAL(expectedSixArgumentCall.thirdArgument, actualSixArgumentCall.thirdArgument);
         ARE_EQUAL(expectedSixArgumentCall.fourthArgument, actualSixArgumentCall.fourthArgument);
         ARE_EQUAL(expectedSixArgumentCall.fifthArgument, actualSixArgumentCall.fifthArgument);
         ARE_EQUAL(expectedSixArgumentCall.sixthArgument, actualSixArgumentCall.sixthArgument);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   struct Printer<ZenMock::SixArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>
   {
      static void Print(std::ostream& os, const ZenMock::SixArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& sixArgumentCallRef)
      {
         const std::string toStringedArg1 = ZenUnit::ToStringer::ToString(sixArgumentCallRef.firstArgument);
         const std::string toStringedArg2 = ZenUnit::ToStringer::ToString(sixArgumentCallRef.secondArgument);
         const std::string toStringedArg3 = ZenUnit::ToStringer::ToString(sixArgumentCallRef.thirdArgument);
         const std::string toStringedArg4 = ZenUnit::ToStringer::ToString(sixArgumentCallRef.fourthArgument);
         const std::string toStringedArg5 = ZenUnit::ToStringer::ToString(sixArgumentCallRef.fifthArgument);
         const std::string toStringedArg6 = ZenUnit::ToStringer::ToString(sixArgumentCallRef.sixthArgument);
         os << "ZenMock::SixArgumentCall:\n"
               "Arg1: " << toStringedArg1 << '\n' <<
               "Arg2: " << toStringedArg2 << '\n' <<
               "Arg3: " << toStringedArg3 << '\n' <<
               "Arg4: " << toStringedArg4 << '\n' <<
               "Arg5: " << toStringedArg5 << '\n' <<
               "Arg6: " << toStringedArg6;
      }
   };
}
