#pragma once
#include "ZenUnit/ZenMock/8/EightArgCall.h"

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
   struct EightArgCallRef
   {
      const Arg1Type& arg1;
      const Arg2Type& arg2;
      const Arg3Type& arg3;
      const Arg4Type& arg4;
      const Arg5Type& arg5;
      const Arg6Type& arg6;
      const Arg7Type& arg7;
      const Arg8Type& arg8;

      EightArgCallRef(
         const Arg1Type& arg1,
         const Arg2Type& arg2,
         const Arg3Type& arg3,
         const Arg4Type& arg4,
         const Arg5Type& arg5,
         const Arg6Type& arg6,
         const Arg7Type& arg7,
         const Arg8Type& arg8)
         : arg1(arg1)
         , arg2(arg2)
         , arg3(arg3)
         , arg4(arg4)
         , arg5(arg5)
         , arg6(arg6)
         , arg7(arg7)
         , arg8(arg8)
      {
      }

      explicit EightArgCallRef(const EightArgCall<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type,
         Arg5Type, Arg6Type, Arg7Type, Arg8Type>& eightArgCall)
         : arg1(eightArgCall.arg1)
         , arg2(eightArgCall.arg2)
         , arg3(eightArgCall.arg3)
         , arg4(eightArgCall.arg4)
         , arg5(eightArgCall.arg5)
         , arg6(eightArgCall.arg6)
         , arg7(eightArgCall.arg7)
         , arg8(eightArgCall.arg8)
      {
      }
   };
}

template<
   typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type,
   typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type>
struct ZenUnitEqualizer<ZenMock::EightArgCallRef<
   Arg1Type, Arg2Type, Arg3Type, Arg4Type,
   Arg5Type, Arg6Type, Arg7Type, Arg8Type>>
{
   static void AssertEqual(
      const ZenMock::EightArgCallRef<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type,
         Arg5Type, Arg6Type, Arg7Type, Arg8Type>& expectedEightArgCall,
      const ZenMock::EightArgCallRef<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type,
         Arg5Type, Arg6Type, Arg7Type, Arg8Type>& actualEightArgCall)
   {
      ARE_EQUAL(expectedEightArgCall.arg1, actualEightArgCall.arg1);
      ARE_EQUAL(expectedEightArgCall.arg2, actualEightArgCall.arg2);
      ARE_EQUAL(expectedEightArgCall.arg3, actualEightArgCall.arg3);
      ARE_EQUAL(expectedEightArgCall.arg4, actualEightArgCall.arg4);
      ARE_EQUAL(expectedEightArgCall.arg5, actualEightArgCall.arg5);
      ARE_EQUAL(expectedEightArgCall.arg6, actualEightArgCall.arg6);
      ARE_EQUAL(expectedEightArgCall.arg7, actualEightArgCall.arg7);
      ARE_EQUAL(expectedEightArgCall.arg8, actualEightArgCall.arg8);
   }
};

template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type>
struct ZenUnitPrinter<ZenMock::EightArgCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>>
{
   static void Print(std::ostream& os, const ZenMock::EightArgCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>& eightArgCallRef)
   {
      const std::string toStringedArg1 = ZenUnit::ToStringer::ToString(eightArgCallRef.arg1);
      const std::string toStringedArg2 = ZenUnit::ToStringer::ToString(eightArgCallRef.arg2);
      const std::string toStringedArg3 = ZenUnit::ToStringer::ToString(eightArgCallRef.arg3);
      const std::string toStringedArg4 = ZenUnit::ToStringer::ToString(eightArgCallRef.arg4);
      const std::string toStringedArg5 = ZenUnit::ToStringer::ToString(eightArgCallRef.arg5);
      const std::string toStringedArg6 = ZenUnit::ToStringer::ToString(eightArgCallRef.arg6);
      const std::string toStringedArg7 = ZenUnit::ToStringer::ToString(eightArgCallRef.arg7);
      const std::string toStringedArg8 = ZenUnit::ToStringer::ToString(eightArgCallRef.arg8);
      os << "ZenMock::EightArgCall:\n"
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
