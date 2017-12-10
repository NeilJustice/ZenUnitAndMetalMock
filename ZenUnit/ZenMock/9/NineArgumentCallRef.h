#pragma once
#include "ZenUnit/ZenMock/9/NineArgumentCall.h"

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
   struct NineArgumentCallRef
   {
      const Arg1Type& firstArgument;
      const Arg2Type& secondArgument;
      const Arg3Type& thirdArgument;
      const Arg4Type& fourthArgument;
      const Arg5Type& fifthArgument;
      const Arg6Type& sixthArgument;
      const Arg7Type& seventhArgument;
      const Arg8Type& eigthArgument;
      const Arg9Type& ninthArgument;

      NineArgumentCallRef(
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

      explicit NineArgumentCallRef(const NineArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& nineArgumentCall) noexcept
         : firstArgument(nineArgumentCall.firstArgument)
         , secondArgument(nineArgumentCall.secondArgument)
         , thirdArgument(nineArgumentCall.thirdArgument)
         , fourthArgument(nineArgumentCall.fourthArgument)
         , fifthArgument(nineArgumentCall.fifthArgument)
         , sixthArgument(nineArgumentCall.sixthArgument)
         , seventhArgument(nineArgumentCall.seventhArgument)
         , eigthArgument(nineArgumentCall.eigthArgument)
         , ninthArgument(nineArgumentCall.ninthArgument)
      {
      }
   };
}

namespace ZenUnit
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type>
   struct Equalizer<ZenMock::NineArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>
   {
      static void AssertEqual(
         const ZenMock::NineArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& expectedNineArgumentCall,
         const ZenMock::NineArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& actualNineArgumentCall)
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

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type,typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type>
   struct Printer<ZenMock::NineArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>
   {
      static void Print(std::ostream& os, const ZenMock::NineArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& nineArgumentCallRef)
      {
         const std::string toStringedArg1 = ZenUnit::ToStringer::ToString(nineArgumentCallRef.firstArgument);
         const std::string toStringedArg2 = ZenUnit::ToStringer::ToString(nineArgumentCallRef.secondArgument);
         const std::string toStringedArg3 = ZenUnit::ToStringer::ToString(nineArgumentCallRef.thirdArgument);
         const std::string toStringedArg4 = ZenUnit::ToStringer::ToString(nineArgumentCallRef.fourthArgument);
         const std::string toStringedArg5 = ZenUnit::ToStringer::ToString(nineArgumentCallRef.fifthArgument);
         const std::string toStringedArg6 = ZenUnit::ToStringer::ToString(nineArgumentCallRef.sixthArgument);
         const std::string toStringedArg7 = ZenUnit::ToStringer::ToString(nineArgumentCallRef.seventhArgument);
         const std::string toStringedArg8 = ZenUnit::ToStringer::ToString(nineArgumentCallRef.eigthArgument);
         const std::string toStringedArg9 = ZenUnit::ToStringer::ToString(nineArgumentCallRef.ninthArgument);
         os << "ZenMock::NineArgumentCall:\n"
               "Arg1: " << toStringedArg1 << '\n' <<
               "Arg2: " << toStringedArg2 << '\n' <<
               "Arg3: " << toStringedArg3 << '\n' <<
               "Arg4: " << toStringedArg4 << '\n' <<
               "Arg5: " << toStringedArg5 << '\n' <<
               "Arg6: " << toStringedArg6 << '\n' <<
               "Arg7: " << toStringedArg7 << '\n' <<
               "Arg8: " << toStringedArg8 << '\n' <<
               "Arg9: " << toStringedArg9;
      }
   };
}
