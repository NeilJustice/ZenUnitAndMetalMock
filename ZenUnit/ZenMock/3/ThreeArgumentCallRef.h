#pragma once
#include "ZenUnit/ZenMock/3/ThreeArgumentCall.h"

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
   struct ThreeArgumentCallRef
   {
      const Arg1Type& firstArgument;
      const Arg2Type& secondArgument;
      const Arg3Type& thirdArgument;

      ThreeArgumentCallRef(const Arg1Type& firstArgument, const Arg2Type& secondArgument, const Arg3Type& thirdArgument)
         : firstArgument(firstArgument)
         , secondArgument(secondArgument)
         , thirdArgument(thirdArgument)
      {
      }

      explicit ThreeArgumentCallRef(const ThreeArgumentCall<Arg1Type, Arg2Type, Arg3Type>& threeArgumentCall)
         : firstArgument(threeArgumentCall.firstArgument)
         , secondArgument(threeArgumentCall.secondArgument)
         , thirdArgument(threeArgumentCall.thirdArgument)
      {
      }
   };
}

template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
struct ZenUnitEqualizer<ZenMock::ThreeArgumentCallRef<Arg1Type, Arg2Type, Arg3Type>>
{
   static void AssertEqual(
      const ZenMock::ThreeArgumentCallRef<Arg1Type, Arg2Type, Arg3Type>& expectedThreeArgumentCall,
      const ZenMock::ThreeArgumentCallRef<Arg1Type, Arg2Type, Arg3Type>& actualThreeArgumentCall)
   {
      ARE_EQUAL(expectedThreeArgumentCall.firstArgument, actualThreeArgumentCall.firstArgument);
      ARE_EQUAL(expectedThreeArgumentCall.secondArgument, actualThreeArgumentCall.secondArgument);
      ARE_EQUAL(expectedThreeArgumentCall.thirdArgument, actualThreeArgumentCall.thirdArgument);
   }
};

template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
struct ZenUnitPrinter<ZenMock::ThreeArgumentCallRef<Arg1Type, Arg2Type, Arg3Type>>
{
   static void Print(std::ostream& os, const ZenMock::ThreeArgumentCallRef<Arg1Type, Arg2Type, Arg3Type>& threeArgumentCallRef)
   {
      const std::string toStringedArg1 = ZenUnit::ToStringer::ToString(threeArgumentCallRef.firstArgument);
      const std::string toStringedArg2 = ZenUnit::ToStringer::ToString(threeArgumentCallRef.secondArgument);
      const std::string toStringedArg3 = ZenUnit::ToStringer::ToString(threeArgumentCallRef.thirdArgument);
      os << "ZenMock::ThreeArgumentCall:\n"
            "Arg1: " << toStringedArg1 << '\n' <<
            "Arg2: " << toStringedArg2 << '\n' <<
            "Arg3: " << toStringedArg3;
   }
};
