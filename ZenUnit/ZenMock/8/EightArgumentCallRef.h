#pragma once
#include "ZenUnit/ZenMock/8/EightArgumentCall.h"

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
      typename Arg8Type>
   struct EightArgumentCallRef
   {
      const Arg1Type& argument1;
      const Arg2Type& argument2;
      const Arg3Type& argument3;
      const Arg4Type& argument4;
      const Arg5Type& argument5;
      const Arg6Type& argument6;
      const Arg7Type& argument7;
      const Arg8Type& argument8;

      EightArgumentCallRef(
         const Arg1Type& argument1,
         const Arg2Type& argument2,
         const Arg3Type& argument3,
         const Arg4Type& argument4,
         const Arg5Type& argument5,
         const Arg6Type& argument6,
         const Arg7Type& argument7,
         const Arg8Type& argument8)
         : argument1(argument1)
         , argument2(argument2)
         , argument3(argument3)
         , argument4(argument4)
         , argument5(argument5)
         , argument6(argument6)
         , argument7(argument7)
         , argument8(argument8)
      {
      }

      explicit EightArgumentCallRef(const EightArgumentCall<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type,
         Arg5Type, Arg6Type, Arg7Type, Arg8Type>& eightArgumentCall)
         : argument1(eightArgumentCall.argument1)
         , argument2(eightArgumentCall.argument2)
         , argument3(eightArgumentCall.argument3)
         , argument4(eightArgumentCall.argument4)
         , argument5(eightArgumentCall.argument5)
         , argument6(eightArgumentCall.argument6)
         , argument7(eightArgumentCall.argument7)
         , argument8(eightArgumentCall.argument8)
      {
      }
   };
}

template<
   typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type,
   typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type>
struct ZenUnitEqualizer<ZenMock::EightArgumentCallRef<
   Arg1Type, Arg2Type, Arg3Type, Arg4Type,
   Arg5Type, Arg6Type, Arg7Type, Arg8Type>>
{
   static void AssertEqual(
      const ZenMock::EightArgumentCallRef<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type,
         Arg5Type, Arg6Type, Arg7Type, Arg8Type>& expectedEightArgumentCall,
      const ZenMock::EightArgumentCallRef<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type,
         Arg5Type, Arg6Type, Arg7Type, Arg8Type>& actualEightArgumentCall)
   {
      ARE_EQUAL(expectedEightArgumentCall.argument1, actualEightArgumentCall.argument1);
      ARE_EQUAL(expectedEightArgumentCall.argument2, actualEightArgumentCall.argument2);
      ARE_EQUAL(expectedEightArgumentCall.argument3, actualEightArgumentCall.argument3);
      ARE_EQUAL(expectedEightArgumentCall.argument4, actualEightArgumentCall.argument4);
      ARE_EQUAL(expectedEightArgumentCall.argument5, actualEightArgumentCall.argument5);
      ARE_EQUAL(expectedEightArgumentCall.argument6, actualEightArgumentCall.argument6);
      ARE_EQUAL(expectedEightArgumentCall.argument7, actualEightArgumentCall.argument7);
      ARE_EQUAL(expectedEightArgumentCall.argument8, actualEightArgumentCall.argument8);
   }
};

template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type>
struct ZenUnitPrinter<ZenMock::EightArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>>
{
   static void Print(std::ostream& os, const ZenMock::EightArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>& eightArgumentCallRef)
   {
      const std::string toStringedArg1 = ZenUnit::ToStringer::ToString(eightArgumentCallRef.argument1);
      const std::string toStringedArg2 = ZenUnit::ToStringer::ToString(eightArgumentCallRef.argument2);
      const std::string toStringedArg3 = ZenUnit::ToStringer::ToString(eightArgumentCallRef.argument3);
      const std::string toStringedArg4 = ZenUnit::ToStringer::ToString(eightArgumentCallRef.argument4);
      const std::string toStringedArg5 = ZenUnit::ToStringer::ToString(eightArgumentCallRef.argument5);
      const std::string toStringedArg6 = ZenUnit::ToStringer::ToString(eightArgumentCallRef.argument6);
      const std::string toStringedArg7 = ZenUnit::ToStringer::ToString(eightArgumentCallRef.argument7);
      const std::string toStringedArg8 = ZenUnit::ToStringer::ToString(eightArgumentCallRef.argument8);
      os << "ZenMock::EightArgumentCall:\n"
            "Arg1: " << toStringedArg1 << '\n' <<
            "Arg2: " << toStringedArg2 << '\n' <<
            "Arg3: " << toStringedArg3 << '\n' <<
            "Arg4: " << toStringedArg4 << '\n' <<
            "Arg5: " << toStringedArg5 << '\n' <<
            "Arg6: " << toStringedArg6 << '\n' <<
            "Arg7: " << toStringedArg7 << '\n' <<
            "Arg8: " << toStringedArg8;
   }
};
