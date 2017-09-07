#pragma once
#include "ZenUnit/ZenMock/5/FiveArgCall.h"

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   struct FiveArgCallRef
   {
      const Arg1Type& arg1;
      const Arg2Type& arg2;
      const Arg3Type& arg3;
      const Arg4Type& arg4;
      const Arg5Type& arg5;

      FiveArgCallRef(
         const Arg1Type& arg1,
         const Arg2Type& arg2,
         const Arg3Type& arg3,
         const Arg4Type& arg4,
         const Arg5Type& arg5)
         : arg1(arg1)
         , arg2(arg2)
         , arg3(arg3)
         , arg4(arg4)
         , arg5(arg5)
      {
      }

      explicit FiveArgCallRef(const FiveArgCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& fiveArgCall)
         : arg1(fiveArgCall.arg1)
         , arg2(fiveArgCall.arg2)
         , arg3(fiveArgCall.arg3)
         , arg4(fiveArgCall.arg4)
         , arg5(fiveArgCall.arg5)
      {
      }
   };
}

template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
struct ZenUnitEqualizer<ZenMock::FiveArgCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>
{
   static void AssertEqual(
      const ZenMock::FiveArgCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& expectedFiveArgCall,
      const ZenMock::FiveArgCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& actualFiveArgCall)
   {
      ARE_EQUAL(expectedFiveArgCall.arg1, actualFiveArgCall.arg1);
      ARE_EQUAL(expectedFiveArgCall.arg2, actualFiveArgCall.arg2);
      ARE_EQUAL(expectedFiveArgCall.arg3, actualFiveArgCall.arg3);
      ARE_EQUAL(expectedFiveArgCall.arg4, actualFiveArgCall.arg4);
      ARE_EQUAL(expectedFiveArgCall.arg5, actualFiveArgCall.arg5);
   }
};

template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
struct ZenUnitPrinter<ZenMock::FiveArgCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>
{
   static void Print(std::ostream& os, const ZenMock::FiveArgCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& fiveArgCallRef)
   {
      const std::string toStringedArg1 = ZenUnit::ToStringer::ToString(fiveArgCallRef.arg1);
      const std::string toStringedArg2 = ZenUnit::ToStringer::ToString(fiveArgCallRef.arg2);
      const std::string toStringedArg3 = ZenUnit::ToStringer::ToString(fiveArgCallRef.arg3);
      const std::string toStringedArg4 = ZenUnit::ToStringer::ToString(fiveArgCallRef.arg4);
      const std::string toStringedArg5 = ZenUnit::ToStringer::ToString(fiveArgCallRef.arg5);
      os << "ZenMock::FiveArgCall:\n"
            "Arg1: " << toStringedArg1 << '\n' <<
            "Arg2: " << toStringedArg2 << '\n' <<
            "Arg3: " << toStringedArg3 << '\n' <<
            "Arg4: " << toStringedArg4 << '\n' <<
            "Arg5: " << toStringedArg5;
   }
};
