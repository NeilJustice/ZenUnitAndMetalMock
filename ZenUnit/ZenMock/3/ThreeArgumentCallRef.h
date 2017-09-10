#pragma once
#include "ZenUnit/ZenMock/3/ThreeArgumentCall.h"

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
   struct ThreeArgumentCallRef
   {
      const Arg1Type& argument1;
      const Arg2Type& argument2;
      const Arg3Type& argument3;

      ThreeArgumentCallRef(const Arg1Type& argument1, const Arg2Type& argument2, const Arg3Type& argument3)
         : argument1(argument1)
         , argument2(argument2)
         , argument3(argument3)
      {
      }

      explicit ThreeArgumentCallRef(const ThreeArgumentCall<Arg1Type, Arg2Type, Arg3Type>& threeArgumentCall)
         : argument1(threeArgumentCall.argument1)
         , argument2(threeArgumentCall.argument2)
         , argument3(threeArgumentCall.argument3)
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
      ARE_EQUAL(expectedThreeArgumentCall.argument1, actualThreeArgumentCall.argument1);
      ARE_EQUAL(expectedThreeArgumentCall.argument2, actualThreeArgumentCall.argument2);
      ARE_EQUAL(expectedThreeArgumentCall.argument3, actualThreeArgumentCall.argument3);
   }
};

template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
struct ZenUnitPrinter<ZenMock::ThreeArgumentCallRef<Arg1Type, Arg2Type, Arg3Type>>
{
   static void Print(std::ostream& os, const ZenMock::ThreeArgumentCallRef<Arg1Type, Arg2Type, Arg3Type>& threeArgumentCallRef)
   {
      const std::string toStringedArg1 = ZenUnit::ToStringer::ToString(threeArgumentCallRef.argument1);
      const std::string toStringedArg2 = ZenUnit::ToStringer::ToString(threeArgumentCallRef.argument2);
      const std::string toStringedArg3 = ZenUnit::ToStringer::ToString(threeArgumentCallRef.argument3);
      os << "ZenMock::ThreeArgumentCall:\n"
            "Arg1: " << toStringedArg1 << '\n' <<
            "Arg2: " << toStringedArg2 << '\n' <<
            "Arg3: " << toStringedArg3;
   }
};
