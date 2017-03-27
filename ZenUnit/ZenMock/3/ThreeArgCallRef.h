#pragma once
#include "ZenUnit/ZenMock/3/ThreeArgCall.h"

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
   struct ThreeArgCallRef
   {
      const Arg1Type& arg1;
      const Arg2Type& arg2;
      const Arg3Type& arg3;

      ThreeArgCallRef(const Arg1Type& arg1, const Arg2Type& arg2, const Arg3Type& arg3)
         : arg1(arg1)
         , arg2(arg2)
         , arg3(arg3)
      {
      }

      ThreeArgCallRef(const ThreeArgCall<Arg1Type, Arg2Type, Arg3Type>& threeArgCall)
         : arg1(threeArgCall.arg1)
         , arg2(threeArgCall.arg2)
         , arg3(threeArgCall.arg3)
      {
      }
   };
}

template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
struct ZenUnitEqualizer<ZenMock::ThreeArgCallRef<Arg1Type, Arg2Type, Arg3Type>>
{
   static void AssertEqual(
      const ZenMock::ThreeArgCallRef<Arg1Type, Arg2Type, Arg3Type>& expectedThreeArgCall,
      const ZenMock::ThreeArgCallRef<Arg1Type, Arg2Type, Arg3Type>& actualThreeArgCall)
   {
      ARE_EQUAL(expectedThreeArgCall.arg1, actualThreeArgCall.arg1);
      ARE_EQUAL(expectedThreeArgCall.arg2, actualThreeArgCall.arg2);
      ARE_EQUAL(expectedThreeArgCall.arg3, actualThreeArgCall.arg3);
   }
};

template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
struct ZenUnitPrinter<ZenMock::ThreeArgCallRef<Arg1Type, Arg2Type, Arg3Type>>
{
   static void Print(std::ostream& os, const ZenMock::ThreeArgCallRef<
      Arg1Type, Arg2Type, Arg3Type>& threeArgCallRef)
   {
      const std::string toStringedArg1 = ZenUnit::ToStringer::ToString(threeArgCallRef.arg1);
      const std::string toStringedArg2 = ZenUnit::ToStringer::ToString(threeArgCallRef.arg2);
      const std::string toStringedArg3 = ZenUnit::ToStringer::ToString(threeArgCallRef.arg3);
      os << "ZenMock::ThreeArgCall:\n"
            "Arg1: " << toStringedArg1 << '\n' <<
            "Arg2: " << toStringedArg2 << '\n' <<
            "Arg3: " << toStringedArg3;
   }
};
