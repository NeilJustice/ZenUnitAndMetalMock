#pragma once
#include "ZenUnit/ZenMock/2/TwoArgumentCall.h"

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type>
   struct TwoArgumentCallRef
   {
      const Arg1Type& firstArgument;
      const Arg2Type& secondArgument;

      TwoArgumentCallRef(const Arg1Type& firstArgument, const Arg2Type& secondArgument) noexcept
         : firstArgument(firstArgument)
         , secondArgument(secondArgument)
      {
      }

      explicit TwoArgumentCallRef(const TwoArgumentCall<Arg1Type, Arg2Type>& twoArgumentCall) noexcept
         : firstArgument(twoArgumentCall.firstArgument)
         , secondArgument(twoArgumentCall.secondArgument)
      {
      }
   };
}

namespace ZenUnit
{

   template<typename Arg1Type, typename Arg2Type>
   struct Equalizer<ZenMock::TwoArgumentCallRef<Arg1Type, Arg2Type>>
   {
      static void AssertEqual(
         const ZenMock::TwoArgumentCallRef<Arg1Type, Arg2Type>& expectedTwoArgumentCall,
         const ZenMock::TwoArgumentCallRef<Arg1Type, Arg2Type>& actualTwoArgumentCall)
      {
         ARE_EQUAL(expectedTwoArgumentCall.firstArgument, actualTwoArgumentCall.firstArgument);
         ARE_EQUAL(expectedTwoArgumentCall.secondArgument, actualTwoArgumentCall.secondArgument);
      }
   };

   template<typename Arg1Type, typename Arg2Type>
   struct Printer<ZenMock::TwoArgumentCallRef<Arg1Type, Arg2Type>>
   {
      static void Print(std::ostream& os, const ZenMock::TwoArgumentCallRef<Arg1Type, Arg2Type>& twoArgumentCallRef)
      {
         const std::string toStringedArg1 = ZenUnit::ToStringer::ToString(twoArgumentCallRef.firstArgument);
         const std::string toStringedArg2 = ZenUnit::ToStringer::ToString(twoArgumentCallRef.secondArgument);
         os << "ZenMock::TwoArgumentCall:\n"
            "Arg1: " << toStringedArg1 << '\n' <<
            "Arg2: " << toStringedArg2;
      }
   };
}
