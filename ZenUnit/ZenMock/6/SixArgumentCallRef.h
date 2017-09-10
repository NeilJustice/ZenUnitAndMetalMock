#pragma once
#include "ZenUnit/ZenMock/6/SixArgumentCall.h"

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   struct SixArgumentCallRef
   {
      const Arg1Type& argument1;
      const Arg2Type& argument2;
      const Arg3Type& argument3;
      const Arg4Type& argument4;
      const Arg5Type& argument5;
      const Arg6Type& argument6;

      SixArgumentCallRef(
         const Arg1Type& argument1,
         const Arg2Type& argument2,
         const Arg3Type& argument3,
         const Arg4Type& argument4,
         const Arg5Type& argument5,
         const Arg6Type& argument6)
         : argument1(argument1)
         , argument2(argument2)
         , argument3(argument3)
         , argument4(argument4)
         , argument5(argument5)
         , argument6(argument6)
      {
      }

      explicit SixArgumentCallRef(const SixArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& sixArgumentCall)
         : argument1(sixArgumentCall.argument1)
         , argument2(sixArgumentCall.argument2)
         , argument3(sixArgumentCall.argument3)
         , argument4(sixArgumentCall.argument4)
         , argument5(sixArgumentCall.argument5)
         , argument6(sixArgumentCall.argument6)
      {
      }
   };
}

template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
struct ZenUnitEqualizer<ZenMock::SixArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>
{
   static void AssertEqual(
      const ZenMock::SixArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& expectedSixArgumentCall,
      const ZenMock::SixArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& actualSixArgumentCall)
   {
      ARE_EQUAL(expectedSixArgumentCall.argument1, actualSixArgumentCall.argument1);
      ARE_EQUAL(expectedSixArgumentCall.argument2, actualSixArgumentCall.argument2);
      ARE_EQUAL(expectedSixArgumentCall.argument3, actualSixArgumentCall.argument3);
      ARE_EQUAL(expectedSixArgumentCall.argument4, actualSixArgumentCall.argument4);
      ARE_EQUAL(expectedSixArgumentCall.argument5, actualSixArgumentCall.argument5);
      ARE_EQUAL(expectedSixArgumentCall.argument6, actualSixArgumentCall.argument6);
   }
};

template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
struct ZenUnitPrinter<ZenMock::SixArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>
{
   static void Print(std::ostream& os, const ZenMock::SixArgumentCallRef<
      Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& sixArgumentCallRef)
   {
      const std::string toStringedArg1 = ZenUnit::ToStringer::ToString(sixArgumentCallRef.argument1);
      const std::string toStringedArg2 = ZenUnit::ToStringer::ToString(sixArgumentCallRef.argument2);
      const std::string toStringedArg3 = ZenUnit::ToStringer::ToString(sixArgumentCallRef.argument3);
      const std::string toStringedArg4 = ZenUnit::ToStringer::ToString(sixArgumentCallRef.argument4);
      const std::string toStringedArg5 = ZenUnit::ToStringer::ToString(sixArgumentCallRef.argument5);
      const std::string toStringedArg6 = ZenUnit::ToStringer::ToString(sixArgumentCallRef.argument6);
      os << "ZenMock::SixArgumentCall:\n"
            "Arg1: " << toStringedArg1 << '\n' <<
            "Arg2: " << toStringedArg2 << '\n' <<
            "Arg3: " << toStringedArg3 << '\n' <<
            "Arg4: " << toStringedArg4 << '\n' <<
            "Arg5: " << toStringedArg5 << '\n' <<
            "Arg6: " << toStringedArg6;
   }
};
