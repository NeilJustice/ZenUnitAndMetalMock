#pragma once
#include "ZenUnit/ZenMock/9/NineArgCall.h"

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
   struct NineArgCallRef
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

      NineArgCallRef(
         const Arg1Type& arg1,
         const Arg2Type& arg2,
         const Arg3Type& arg3,
         const Arg4Type& arg4,
         const Arg5Type& arg5,
         const Arg6Type& arg6,
         const Arg7Type& arg7,
         const Arg8Type& arg8,
         const Arg8Type& arg9)
         : arg1(arg1)
         , arg2(arg2)
         , arg3(arg3)
         , arg4(arg4)
         , arg5(arg5)
         , arg6(arg6)
         , arg7(arg7)
         , arg8(arg8)
         , arg9(arg9)
      {
      }

      explicit NineArgCallRef(const NineArgCall<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type,
         Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& nineArgCall)
         : arg1(nineArgCall.arg1)
         , arg2(nineArgCall.arg2)
         , arg3(nineArgCall.arg3)
         , arg4(nineArgCall.arg4)
         , arg5(nineArgCall.arg5)
         , arg6(nineArgCall.arg6)
         , arg7(nineArgCall.arg7)
         , arg8(nineArgCall.arg8)
         , arg9(nineArgCall.arg9)
      {
      }
   };
}

template<
   typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type,
   typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type>
struct ZenUnitEqualizer<ZenMock::NineArgCallRef<
   Arg1Type, Arg2Type, Arg3Type, Arg4Type,
   Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>
{
   static void AssertEqual(
      const ZenMock::NineArgCallRef<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type,
         Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& expectedNineArgCall,
      const ZenMock::NineArgCallRef<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type,
         Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& actualNineArgCall)
   {
      ARE_EQUAL(expectedNineArgCall.arg1, actualNineArgCall.arg1);
      ARE_EQUAL(expectedNineArgCall.arg2, actualNineArgCall.arg2);
      ARE_EQUAL(expectedNineArgCall.arg3, actualNineArgCall.arg3);
      ARE_EQUAL(expectedNineArgCall.arg4, actualNineArgCall.arg4);
      ARE_EQUAL(expectedNineArgCall.arg5, actualNineArgCall.arg5);
      ARE_EQUAL(expectedNineArgCall.arg6, actualNineArgCall.arg6);
      ARE_EQUAL(expectedNineArgCall.arg7, actualNineArgCall.arg7);
      ARE_EQUAL(expectedNineArgCall.arg8, actualNineArgCall.arg8);
      ARE_EQUAL(expectedNineArgCall.arg9, actualNineArgCall.arg9);
   }
};

template<
   typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type,
   typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type>
struct ZenUnitPrinter<ZenMock::NineArgCallRef<
   Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>>
{
   static void Print(std::ostream& os, const ZenMock::NineArgCallRef<
      Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type>& nineArgCallRef)
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
      os << "ZenMock::NineArgCall:\n"
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
