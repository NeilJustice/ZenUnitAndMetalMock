#pragma once
#include "ZenUnit/ZenMock/4/FourArgumentCall.h"

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   struct FourArgumentCallRef
   {
      const Arg1Type& firstArgument;
      const Arg2Type& secondArgument;
      const Arg3Type& thirdArgument;
      const Arg4Type& fourthArgument;

      FourArgumentCallRef(const Arg1Type& firstArgument, const Arg2Type& secondArgument, const Arg3Type& thirdArgument, const Arg4Type& fourthArgument)
         : firstArgument(firstArgument)
         , secondArgument(secondArgument)
         , thirdArgument(thirdArgument)
         , fourthArgument(fourthArgument)
      {
      }

      explicit FourArgumentCallRef(const FourArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& fourArgumentCall)
         : firstArgument(fourArgumentCall.firstArgument)
         , secondArgument(fourArgumentCall.secondArgument)
         , thirdArgument(fourArgumentCall.thirdArgument)
         , fourthArgument(fourArgumentCall.fourthArgument)
      {
      }
   };
}

namespace ZenUnit
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   struct Equalizer<ZenMock::FourArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>
   {
      static void AssertEqual(
         const ZenMock::FourArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& expectedFourArgumentCall,
         const ZenMock::FourArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& actualFourArgumentCall)
      {
         ARE_EQUAL(expectedFourArgumentCall.firstArgument, actualFourArgumentCall.firstArgument);
         ARE_EQUAL(expectedFourArgumentCall.secondArgument, actualFourArgumentCall.secondArgument);
         ARE_EQUAL(expectedFourArgumentCall.thirdArgument, actualFourArgumentCall.thirdArgument);
         ARE_EQUAL(expectedFourArgumentCall.fourthArgument, actualFourArgumentCall.fourthArgument);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   struct Printer<ZenMock::FourArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>
   {
      static void Print(std::ostream& os, const ZenMock::FourArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& fourArgumentCallRef)
      {
         const std::string toStringedArg1 = ZenUnit::ToStringer::ToString(fourArgumentCallRef.firstArgument);
         const std::string toStringedArg2 = ZenUnit::ToStringer::ToString(fourArgumentCallRef.secondArgument);
         const std::string toStringedArg3 = ZenUnit::ToStringer::ToString(fourArgumentCallRef.thirdArgument);
         const std::string toStringedArg4 = ZenUnit::ToStringer::ToString(fourArgumentCallRef.fourthArgument);
         os << "ZenMock::FourArgumentCall:\n"
               "Arg1: " << toStringedArg1 << '\n' <<
               "Arg2: " << toStringedArg2 << '\n' <<
               "Arg3: " << toStringedArg3 << '\n' <<
               "Arg4: " << toStringedArg4;
      }
   };
}
