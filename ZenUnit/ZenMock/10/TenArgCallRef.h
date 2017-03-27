#pragma once
#include "ZenUnit/ZenMock/10/TenArgCall.h"

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
   struct TenArgCallRef
   {
      const Arg1Type& arg1;
      const Arg2Type& arg2;
      const Arg3Type& arg3;
      const Arg4Type& arg4;
      const Arg5Type& arg5;
      const Arg6Type& arg6;
      const Arg7Type& arg7;
      const Arg8Type& arg8;
      const Arg9Type& arg9;
      const Arg9Type& arg10;

      TenArgCallRef(
         const Arg1Type& arg1,
         const Arg2Type& arg2,
         const Arg3Type& arg3,
         const Arg4Type& arg4,
         const Arg5Type& arg5,
         const Arg6Type& arg6,
         const Arg7Type& arg7,
         const Arg8Type& arg8,
         const Arg8Type& arg9,
         const Arg8Type& arg10)
         : arg1(arg1)
         , arg2(arg2)
         , arg3(arg3)
         , arg4(arg4)
         , arg5(arg5)
         , arg6(arg6)
         , arg7(arg7)
         , arg8(arg8)
         , arg9(arg9)
         , arg10(arg10)
      {
      }

      TenArgCallRef(const TenArgCall<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type,
         Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>& tenArgCall)
         : arg1(nineArgCall.arg1)
         , arg2(nineArgCall.arg2)
         , arg3(nineArgCall.arg3)
         , arg4(nineArgCall.arg4)
         , arg5(nineArgCall.arg5)
         , arg6(nineArgCall.arg6)
         , arg7(nineArgCall.arg7)
         , arg8(nineArgCall.arg8)
         , arg9(nineArgCall.arg9)
         , arg10(nineArgCall.arg10)
      {
      }
   };
}

template<
   typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, 
   typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename Arg10Type>
struct ZenUnitEqualizer<ZenMock::TenArgCallRef<
   Arg1Type, Arg2Type, Arg3Type, Arg4Type, 
   Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>>
{
   static void AssertEqual(
      const ZenMock::TenArgCallRef<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type, 
         Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>& expectedTenArgCall,
      const ZenMock::TenArgCallRef<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type, 
         Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>& actualTenArgCall)
   {
      ARE_EQUAL(expectedTenArgCall.arg1, actualTenArgCall.arg1);
      ARE_EQUAL(expectedTenArgCall.arg2, actualTenArgCall.arg2);
      ARE_EQUAL(expectedTenArgCall.arg3, actualTenArgCall.arg3);
      ARE_EQUAL(expectedTenArgCall.arg4, actualTenArgCall.arg4);
      ARE_EQUAL(expectedTenArgCall.arg5, actualTenArgCall.arg5);
      ARE_EQUAL(expectedTenArgCall.arg6, actualTenArgCall.arg6);
      ARE_EQUAL(expectedTenArgCall.arg7, actualTenArgCall.arg7);
      ARE_EQUAL(expectedTenArgCall.arg8, actualTenArgCall.arg8);
      ARE_EQUAL(expectedTenArgCall.arg9, actualTenArgCall.arg9);
      ARE_EQUAL(expectedTenArgCall.arg10, actualTenArgCall.arg10);
   }
};

template<
   typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, 
   typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename Arg10Type>
struct ZenUnitPrinter<ZenMock::TenArgCallRef<
   Arg1Type, Arg2Type, Arg3Type, Arg4Type, 
   Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>>
{
   static void Print(std::ostream& os, const ZenMock::TenArgCallRef<
      Arg1Type, Arg2Type, Arg3Type, Arg4Type, 
      Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>& tenArgCallRef)
   {
      const std::string toStringedArg1 = ZenUnit::ToStringer::ToString(nineArgCallRef.arg1);
      const std::string toStringedArg2 = ZenUnit::ToStringer::ToString(nineArgCallRef.arg2);
      const std::string toStringedArg3 = ZenUnit::ToStringer::ToString(nineArgCallRef.arg3);
      const std::string toStringedArg4 = ZenUnit::ToStringer::ToString(nineArgCallRef.arg4);
      const std::string toStringedArg5 = ZenUnit::ToStringer::ToString(nineArgCallRef.arg5);
      const std::string toStringedArg6 = ZenUnit::ToStringer::ToString(nineArgCallRef.arg6);
      const std::string toStringedArg7 = ZenUnit::ToStringer::ToString(nineArgCallRef.arg7);
      const std::string toStringedArg8 = ZenUnit::ToStringer::ToString(nineArgCallRef.arg8);
      const std::string toStringedArg9 = ZenUnit::ToStringer::ToString(nineArgCallRef.arg9);
      const std::string toStringedArg10 = ZenUnit::ToStringer::ToString(nineArgCallRef.arg10);
      os << "ZenMock::TenArgCall:\n"
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
