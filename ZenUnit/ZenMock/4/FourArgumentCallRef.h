#pragma once
#include "ZenUnit/ZenMock/4/FourArgumentCall.h"

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   struct FourArgumentCallRef
   {
      const Arg1Type& argument1;
      const Arg2Type& argument2;
      const Arg3Type& argument3;
      const Arg4Type& argument4;

      FourArgumentCallRef(const Arg1Type& argument1, const Arg2Type& argument2, const Arg3Type& argument3, const Arg4Type& argument4)
         : argument1(argument1)
         , argument2(argument2)
         , argument3(argument3)
         , argument4(argument4)
      {
      }

      explicit FourArgumentCallRef(const FourArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& fourArgumentCall)
         : argument1(fourArgumentCall.argument1)
         , argument2(fourArgumentCall.argument2)
         , argument3(fourArgumentCall.argument3)
         , argument4(fourArgumentCall.argument4)
      {
      }
   };
}

template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
struct ZenUnitEqualizer<ZenMock::FourArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>
{
   static void AssertEqual(
      const ZenMock::FourArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& expectedFourArgumentCall,
      const ZenMock::FourArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& actualFourArgumentCall)
   {
      ARE_EQUAL(expectedFourArgumentCall.argument1, actualFourArgumentCall.argument1);
      ARE_EQUAL(expectedFourArgumentCall.argument2, actualFourArgumentCall.argument2);
      ARE_EQUAL(expectedFourArgumentCall.argument3, actualFourArgumentCall.argument3);
      ARE_EQUAL(expectedFourArgumentCall.argument4, actualFourArgumentCall.argument4);
   }
};

template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
struct ZenUnitPrinter<ZenMock::FourArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>
{
   static void Print(std::ostream& os, const ZenMock::FourArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& fourArgumentCallRef)
   {
      const std::string toStringedArg1 = ZenUnit::ToStringer::ToString(fourArgumentCallRef.argument1);
      const std::string toStringedArg2 = ZenUnit::ToStringer::ToString(fourArgumentCallRef.argument2);
      const std::string toStringedArg3 = ZenUnit::ToStringer::ToString(fourArgumentCallRef.argument3);
      const std::string toStringedArg4 = ZenUnit::ToStringer::ToString(fourArgumentCallRef.argument4);
      os << "ZenMock::FourArgumentCall:\n"
            "Arg1: " << toStringedArg1 << '\n' <<
            "Arg2: " << toStringedArg2 << '\n' <<
            "Arg3: " << toStringedArg3 << '\n' <<
            "Arg4: " << toStringedArg4;
   }
};
