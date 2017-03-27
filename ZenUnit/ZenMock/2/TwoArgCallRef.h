#pragma once
#include "ZenUnit/ZenMock/2/TwoArgCall.h"

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type>
   struct TwoArgCallRef
   {
      const Arg1Type& arg1;
      const Arg2Type& arg2;

      TwoArgCallRef(const Arg1Type& arg1, const Arg2Type& arg2)
         : arg1(arg1)
         , arg2(arg2)
      {
      }

      TwoArgCallRef(const TwoArgCall<Arg1Type, Arg2Type>& twoArgCall)
         : arg1(twoArgCall.arg1)
         , arg2(twoArgCall.arg2)
      {
      }
   };
}

template<typename Arg1Type, typename Arg2Type>
struct ZenUnitEqualizer<ZenMock::TwoArgCallRef<Arg1Type, Arg2Type>>
{
   static void AssertEqual(
      const ZenMock::TwoArgCallRef<Arg1Type, Arg2Type>& expectedTwoArgCall,
      const ZenMock::TwoArgCallRef<Arg1Type, Arg2Type>& actualTwoArgCall)
   {
      ARE_EQUAL(expectedTwoArgCall.arg1, actualTwoArgCall.arg1);
      ARE_EQUAL(expectedTwoArgCall.arg2, actualTwoArgCall.arg2);
   }
};

template<typename Arg1Type, typename Arg2Type>
struct ZenUnitPrinter<ZenMock::TwoArgCallRef<Arg1Type, Arg2Type>>
{
   static void Print(std::ostream& os, const ZenMock::TwoArgCallRef<Arg1Type, Arg2Type>& twoArgCallRef)
   {
      const std::string toStringedArg1 = ZenUnit::ToStringer::ToString(twoArgCallRef.arg1);
      const std::string toStringedArg2 = ZenUnit::ToStringer::ToString(twoArgCallRef.arg2);
      os << "ZenMock::TwoArgCall:\n"
         "Arg1: " << toStringedArg1 << '\n' <<
         "Arg2: " << toStringedArg2;
   }
};
