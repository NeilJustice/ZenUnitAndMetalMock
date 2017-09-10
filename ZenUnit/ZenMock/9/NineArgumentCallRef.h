#pragma once
#include "ZenUnit/ZenMock/9/NineArgumentCall.h"

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
      typename Arg8Type,
      typename Arg9Type>
   struct NineArgumentCallRef
   {
      const Arg1Type& argument1;
      const Arg2Type& argument2;
      const Arg3Type& argument3;
      const Arg4Type& argument4;
      const Arg5Type& argument5;
      const Arg6Type& argument6;
      const Arg7Type& argument7;
      const Arg8Type& argument8;
      const Arg9Type& argument9;

      NineArgumentCallRef(
         const Arg1Type& argument1,
         const Arg2Type& argument2,
         const Arg3Type& argument3,
         const Arg4Type& argument4,
         const Arg5Type& argument5,
         const Arg6Type& argument6,
         const Arg7Type& argument7,
         const Arg8Type& argument8,
         const Arg9Type& argument9)
         : argument1(argument1)
         , argument2(argument2)
         , argument3(argument3)
         , argument4(argument4)
         , argument5(argument5)
         , argument6(argument6)
         , argument7(argument7)
         , argument8(argument8)
         , argument9(argument9)
      {
      }

      explicit NineArgumentCallRef(const NineArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& nineArgumentCall)
         : argument1(nineArgumentCall.argument1)
         , argument2(nineArgumentCall.argument2)
         , argument3(nineArgumentCall.argument3)
         , argument4(nineArgumentCall.argument4)
         , argument5(nineArgumentCall.argument5)
         , argument6(nineArgumentCall.argument6)
         , argument7(nineArgumentCall.argument7)
         , argument8(nineArgumentCall.argument8)
         , argument9(nineArgumentCall.argument9)
      {
      }
   };
}

template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type>
struct ZenUnitEqualizer<ZenMock::NineArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>
{
   static void AssertEqual(
      const ZenMock::NineArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& expectedNineArgumentCall,
      const ZenMock::NineArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& actualNineArgumentCall)
   {
      ARE_EQUAL(expectedNineArgumentCall.argument1, actualNineArgumentCall.argument1);
      ARE_EQUAL(expectedNineArgumentCall.argument2, actualNineArgumentCall.argument2);
      ARE_EQUAL(expectedNineArgumentCall.argument3, actualNineArgumentCall.argument3);
      ARE_EQUAL(expectedNineArgumentCall.argument4, actualNineArgumentCall.argument4);
      ARE_EQUAL(expectedNineArgumentCall.argument5, actualNineArgumentCall.argument5);
      ARE_EQUAL(expectedNineArgumentCall.argument6, actualNineArgumentCall.argument6);
      ARE_EQUAL(expectedNineArgumentCall.argument7, actualNineArgumentCall.argument7);
      ARE_EQUAL(expectedNineArgumentCall.argument8, actualNineArgumentCall.argument8);
      ARE_EQUAL(expectedNineArgumentCall.argument9, actualNineArgumentCall.argument9);
   }
};

template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type,typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type>
struct ZenUnitPrinter<ZenMock::NineArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>
{
   static void Print(std::ostream& os, const ZenMock::NineArgumentCallRef<
      Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& nineArgumentCallRef)
   {
      const std::string toStringedArg1 = ZenUnit::ToStringer::ToString(nineArgumentCallRef.argument1);
      const std::string toStringedArg2 = ZenUnit::ToStringer::ToString(nineArgumentCallRef.argument2);
      const std::string toStringedArg3 = ZenUnit::ToStringer::ToString(nineArgumentCallRef.argument3);
      const std::string toStringedArg4 = ZenUnit::ToStringer::ToString(nineArgumentCallRef.argument4);
      const std::string toStringedArg5 = ZenUnit::ToStringer::ToString(nineArgumentCallRef.argument5);
      const std::string toStringedArg6 = ZenUnit::ToStringer::ToString(nineArgumentCallRef.argument6);
      const std::string toStringedArg7 = ZenUnit::ToStringer::ToString(nineArgumentCallRef.argument7);
      const std::string toStringedArg8 = ZenUnit::ToStringer::ToString(nineArgumentCallRef.argument8);
      const std::string toStringedArg9 = ZenUnit::ToStringer::ToString(nineArgumentCallRef.argument9);
      os << "ZenMock::NineArgumentCall:\n"
            "Arg1: " << toStringedArg1 << '\n' <<
            "Arg2: " << toStringedArg2 << '\n' <<
            "Arg3: " << toStringedArg3 << '\n' <<
            "Arg4: " << toStringedArg4 << '\n' <<
            "Arg5: " << toStringedArg5 << '\n' <<
            "Arg6: " << toStringedArg6 << '\n' <<
            "Arg7: " << toStringedArg7 << '\n' <<
            "Arg8: " << toStringedArg8 << '\n' <<
            "Arg9: " << toStringedArg9;
   }
};
