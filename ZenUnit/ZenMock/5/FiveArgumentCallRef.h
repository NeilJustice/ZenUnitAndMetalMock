#pragma once
#include "ZenUnit/ZenMock/5/FiveArgumentCall.h"

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   struct FiveArgumentCallRef
   {
      const Arg1Type& argument1;
      const Arg2Type& argument2;
      const Arg3Type& argument3;
      const Arg4Type& argument4;
      const Arg5Type& argument5;

      FiveArgumentCallRef(
         const Arg1Type& argument1,
         const Arg2Type& argument2,
         const Arg3Type& argument3,
         const Arg4Type& argument4,
         const Arg5Type& argument5)
         : argument1(argument1)
         , argument2(argument2)
         , argument3(argument3)
         , argument4(argument4)
         , argument5(argument5)
      {
      }

      explicit FiveArgumentCallRef(const FiveArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& fiveArgumentCall)
         : argument1(fiveArgumentCall.argument1)
         , argument2(fiveArgumentCall.argument2)
         , argument3(fiveArgumentCall.argument3)
         , argument4(fiveArgumentCall.argument4)
         , argument5(fiveArgumentCall.argument5)
      {
      }
   };
}

template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
struct ZenUnitEqualizer<ZenMock::FiveArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>
{
   static void AssertEqual(
      const ZenMock::FiveArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& expectedFiveArgumentCall,
      const ZenMock::FiveArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& actualFiveArgumentCall)
   {
      ARE_EQUAL(expectedFiveArgumentCall.argument1, actualFiveArgumentCall.argument1);
      ARE_EQUAL(expectedFiveArgumentCall.argument2, actualFiveArgumentCall.argument2);
      ARE_EQUAL(expectedFiveArgumentCall.argument3, actualFiveArgumentCall.argument3);
      ARE_EQUAL(expectedFiveArgumentCall.argument4, actualFiveArgumentCall.argument4);
      ARE_EQUAL(expectedFiveArgumentCall.argument5, actualFiveArgumentCall.argument5);
   }
};

template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
struct ZenUnitPrinter<ZenMock::FiveArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>
{
   static void Print(std::ostream& os, const ZenMock::FiveArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& fiveArgumentCallRef)
   {
      const std::string toStringedArg1 = ZenUnit::ToStringer::ToString(fiveArgumentCallRef.argument1);
      const std::string toStringedArg2 = ZenUnit::ToStringer::ToString(fiveArgumentCallRef.argument2);
      const std::string toStringedArg3 = ZenUnit::ToStringer::ToString(fiveArgumentCallRef.argument3);
      const std::string toStringedArg4 = ZenUnit::ToStringer::ToString(fiveArgumentCallRef.argument4);
      const std::string toStringedArg5 = ZenUnit::ToStringer::ToString(fiveArgumentCallRef.argument5);
      os << "ZenMock::FiveArgumentCall:\n"
            "Arg1: " << toStringedArg1 << '\n' <<
            "Arg2: " << toStringedArg2 << '\n' <<
            "Arg3: " << toStringedArg3 << '\n' <<
            "Arg4: " << toStringedArg4 << '\n' <<
            "Arg5: " << toStringedArg5;
   }
};
