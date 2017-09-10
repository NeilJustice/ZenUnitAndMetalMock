#pragma once
#include "ZenUnit/ZenMock/10/TenArgumentCall.h"

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
      typename Arg9Type,
      typename Arg10Type>
   struct TenArgumentCallRef
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
      const Arg10Type& argument10;

      TenArgumentCallRef(
         const Arg1Type& argument1,
         const Arg2Type& argument2,
         const Arg3Type& argument3,
         const Arg4Type& argument4,
         const Arg5Type& argument5,
         const Arg6Type& argument6,
         const Arg7Type& argument7,
         const Arg8Type& argument8,
         const Arg9Type& argument9,
         const Arg10Type& argument10)
         : argument1(argument1)
         , argument2(argument2)
         , argument3(argument3)
         , argument4(argument4)
         , argument5(argument5)
         , argument6(argument6)
         , argument7(argument7)
         , argument8(argument8)
         , argument9(argument9)
         , argument10(argument10)
      {
      }

      explicit TenArgumentCallRef(const TenArgumentCall<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type,
         Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>& tenArgumentCall)
         : argument1(tenArgumentCall.argument1)
         , argument2(tenArgumentCall.argument2)
         , argument3(tenArgumentCall.argument3)
         , argument4(tenArgumentCall.argument4)
         , argument5(tenArgumentCall.argument5)
         , argument6(tenArgumentCall.argument6)
         , argument7(tenArgumentCall.argument7)
         , argument8(tenArgumentCall.argument8)
         , argument9(tenArgumentCall.argument9)
         , argument10(tenArgumentCall.argument10)
      {
      }
   };
}

template<
   typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type,
   typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename Arg10Type>
struct ZenUnitEqualizer<ZenMock::TenArgumentCallRef<
   Arg1Type, Arg2Type, Arg3Type, Arg4Type,
   Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>>
{
   static void AssertEqual(
      const ZenMock::TenArgumentCallRef<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type,
         Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>& expectedTenArgumentCall,
      const ZenMock::TenArgumentCallRef<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type,
         Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>& actualTenArgumentCall)
   {
      ARE_EQUAL(expectedTenArgumentCall.argument1, actualTenArgumentCall.argument1);
      ARE_EQUAL(expectedTenArgumentCall.argument2, actualTenArgumentCall.argument2);
      ARE_EQUAL(expectedTenArgumentCall.argument3, actualTenArgumentCall.argument3);
      ARE_EQUAL(expectedTenArgumentCall.argument4, actualTenArgumentCall.argument4);
      ARE_EQUAL(expectedTenArgumentCall.argument5, actualTenArgumentCall.argument5);
      ARE_EQUAL(expectedTenArgumentCall.argument6, actualTenArgumentCall.argument6);
      ARE_EQUAL(expectedTenArgumentCall.argument7, actualTenArgumentCall.argument7);
      ARE_EQUAL(expectedTenArgumentCall.argument8, actualTenArgumentCall.argument8);
      ARE_EQUAL(expectedTenArgumentCall.argument9, actualTenArgumentCall.argument9);
      ARE_EQUAL(expectedTenArgumentCall.argument10, actualTenArgumentCall.argument10);
   }
};

template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename Arg10Type>
struct ZenUnitPrinter<ZenMock::TenArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>>
{
   static void Print(std::ostream& os, const ZenMock::TenArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>& tenArgumentCallRef)
   {
      const std::string toStringedArg1 = ZenUnit::ToStringer::ToString(tenArgumentCallRef.argument1);
      const std::string toStringedArg2 = ZenUnit::ToStringer::ToString(tenArgumentCallRef.argument2);
      const std::string toStringedArg3 = ZenUnit::ToStringer::ToString(tenArgumentCallRef.argument3);
      const std::string toStringedArg4 = ZenUnit::ToStringer::ToString(tenArgumentCallRef.argument4);
      const std::string toStringedArg5 = ZenUnit::ToStringer::ToString(tenArgumentCallRef.argument5);
      const std::string toStringedArg6 = ZenUnit::ToStringer::ToString(tenArgumentCallRef.argument6);
      const std::string toStringedArg7 = ZenUnit::ToStringer::ToString(tenArgumentCallRef.argument7);
      const std::string toStringedArg8 = ZenUnit::ToStringer::ToString(tenArgumentCallRef.argument8);
      const std::string toStringedArg9 = ZenUnit::ToStringer::ToString(tenArgumentCallRef.argument9);
      const std::string toStringedArg10 = ZenUnit::ToStringer::ToString(tenArgumentCallRef.argument10);
      os << "ZenMock::TenArgumentCall:\n"
            " Arg1: " << toStringedArg1 << '\n' <<
            " Arg2: " << toStringedArg2 << '\n' <<
            " Arg3: " << toStringedArg3 << '\n' <<
            " Arg4: " << toStringedArg4 << '\n' <<
            " Arg5: " << toStringedArg5 << '\n' <<
            " Arg6: " << toStringedArg6 << '\n' <<
            " Arg7: " << toStringedArg7 << '\n' <<
            " Arg8: " << toStringedArg8 << '\n' <<
            " Arg9: " << toStringedArg9 << '\n' <<
            "Arg10: " << toStringedArg10;
   }
};
