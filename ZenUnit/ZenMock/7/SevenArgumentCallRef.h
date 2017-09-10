#pragma once
#include "ZenUnit/ZenMock/7/SevenArgumentCall.h"

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
   struct SevenArgumentCallRef
   {
      const Arg1Type& argument1;
      const Arg2Type& argument2;
      const Arg3Type& argument3;
      const Arg4Type& argument4;
      const Arg5Type& argument5;
      const Arg6Type& argument6;
      const Arg7Type& argument7;

      SevenArgumentCallRef(
         const Arg1Type& argument1,
         const Arg2Type& argument2,
         const Arg3Type& argument3,
         const Arg4Type& argument4,
         const Arg5Type& argument5,
         const Arg6Type& argument6,
         const Arg7Type& argument7)
         : argument1(argument1)
         , argument2(argument2)
         , argument3(argument3)
         , argument4(argument4)
         , argument5(argument5)
         , argument6(argument6)
         , argument7(argument7)
      {
      }

      explicit SevenArgumentCallRef(const SevenArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& sevenArgumentCall)
         : argument1(sevenArgumentCall.argument1)
         , argument2(sevenArgumentCall.argument2)
         , argument3(sevenArgumentCall.argument3)
         , argument4(sevenArgumentCall.argument4)
         , argument5(sevenArgumentCall.argument5)
         , argument6(sevenArgumentCall.argument6)
         , argument7(sevenArgumentCall.argument7)
      {
      }
   };
}

template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
struct ZenUnitEqualizer<ZenMock::SevenArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>
{
   static void AssertEqual(
      const ZenMock::SevenArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& expectedSevenArgumentCall,
      const ZenMock::SevenArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& actualSevenArgumentCall)
   {
      ARE_EQUAL(expectedSevenArgumentCall.argument1, actualSevenArgumentCall.argument1);
      ARE_EQUAL(expectedSevenArgumentCall.argument2, actualSevenArgumentCall.argument2);
      ARE_EQUAL(expectedSevenArgumentCall.argument3, actualSevenArgumentCall.argument3);
      ARE_EQUAL(expectedSevenArgumentCall.argument4, actualSevenArgumentCall.argument4);
      ARE_EQUAL(expectedSevenArgumentCall.argument5, actualSevenArgumentCall.argument5);
      ARE_EQUAL(expectedSevenArgumentCall.argument6, actualSevenArgumentCall.argument6);
      ARE_EQUAL(expectedSevenArgumentCall.argument7, actualSevenArgumentCall.argument7);
   }
};

template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
struct ZenUnitPrinter<ZenMock::SevenArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>
{
   static void Print(std::ostream& os, const ZenMock::SevenArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& sevenArgumentCallRef)
   {
      const std::string toStringedArg1 = ZenUnit::ToStringer::ToString(sevenArgumentCallRef.argument1);
      const std::string toStringedArg2 = ZenUnit::ToStringer::ToString(sevenArgumentCallRef.argument2);
      const std::string toStringedArg3 = ZenUnit::ToStringer::ToString(sevenArgumentCallRef.argument3);
      const std::string toStringedArg4 = ZenUnit::ToStringer::ToString(sevenArgumentCallRef.argument4);
      const std::string toStringedArg5 = ZenUnit::ToStringer::ToString(sevenArgumentCallRef.argument5);
      const std::string toStringedArg6 = ZenUnit::ToStringer::ToString(sevenArgumentCallRef.argument6);
      const std::string toStringedArg7 = ZenUnit::ToStringer::ToString(sevenArgumentCallRef.argument7);
      os << "ZenMock::SevenArgumentCall:\n"
            "Arg1: " << toStringedArg1 << '\n' <<
            "Arg2: " << toStringedArg2 << '\n' <<
            "Arg3: " << toStringedArg3 << '\n' <<
            "Arg4: " << toStringedArg4 << '\n' <<
            "Arg5: " << toStringedArg5 << '\n' <<
            "Arg6: " << toStringedArg6 << '\n' <<
            "Arg7: " << toStringedArg7;
   }
};
