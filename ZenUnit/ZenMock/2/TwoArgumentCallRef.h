#pragma once
#include "ZenUnit/ZenMock/2/TwoArgumentCall.h"

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type>
   struct TwoArgumentCallRef
   {
      const Arg1Type& argument1;
      const Arg2Type& argument2;

      TwoArgumentCallRef(const Arg1Type& argument1, const Arg2Type& argument2)
         : argument1(argument1)
         , argument2(argument2)
      {
      }

      explicit TwoArgumentCallRef(const TwoArgumentCall<Arg1Type, Arg2Type>& twoArgumentCall)
         : argument1(twoArgumentCall.argument1)
         , argument2(twoArgumentCall.argument2)
      {
      }
   };
}

template<typename Arg1Type, typename Arg2Type>
struct ZenUnitEqualizer<ZenMock::TwoArgumentCallRef<Arg1Type, Arg2Type>>
{
   static void AssertEqual(
      const ZenMock::TwoArgumentCallRef<Arg1Type, Arg2Type>& expectedTwoArgumentCall,
      const ZenMock::TwoArgumentCallRef<Arg1Type, Arg2Type>& actualTwoArgumentCall)
   {
      ARE_EQUAL(expectedTwoArgumentCall.argument1, actualTwoArgumentCall.argument1);
      ARE_EQUAL(expectedTwoArgumentCall.argument2, actualTwoArgumentCall.argument2);
   }
};

template<typename Arg1Type, typename Arg2Type>
struct ZenUnitPrinter<ZenMock::TwoArgumentCallRef<Arg1Type, Arg2Type>>
{
   static void Print(std::ostream& os, const ZenMock::TwoArgumentCallRef<Arg1Type, Arg2Type>& twoArgumentCallRef)
   {
      const std::string toStringedArg1 = ZenUnit::ToStringer::ToString(twoArgumentCallRef.argument1);
      const std::string toStringedArg2 = ZenUnit::ToStringer::ToString(twoArgumentCallRef.argument2);
      os << "ZenMock::TwoArgumentCall:\n"
         "Arg1: " << toStringedArg1 << '\n' <<
         "Arg2: " << toStringedArg2;
   }
};
