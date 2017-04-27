#pragma once
#include "ZenUnit/ZenMock/4/FourArgCall.h"

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   struct FourArgCallRef
   {
      const Arg1Type& arg1;
      const Arg2Type& arg2;
      const Arg3Type& arg3;
      const Arg4Type& arg4;

      FourArgCallRef(const Arg1Type& arg1, const Arg2Type& arg2, const Arg3Type& arg3, const Arg4Type& arg4)
         : arg1(arg1)
         , arg2(arg2)
         , arg3(arg3)
         , arg4(arg4)
      {
      }

      explicit FourArgCallRef(const FourArgCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& fourArgCall)
         : arg1(fourArgCall.arg1)
         , arg2(fourArgCall.arg2)
         , arg3(fourArgCall.arg3)
         , arg4(fourArgCall.arg4)
      {
      }
   };
}

template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
struct ZenUnitEqualizer<ZenMock::FourArgCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>
{
   static void AssertEqual(
      const ZenMock::FourArgCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& expectedFourArgCall,
      const ZenMock::FourArgCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& actualFourArgCall)
   {
      ARE_EQUAL(expectedFourArgCall.arg1, actualFourArgCall.arg1);
      ARE_EQUAL(expectedFourArgCall.arg2, actualFourArgCall.arg2);
      ARE_EQUAL(expectedFourArgCall.arg3, actualFourArgCall.arg3);
      ARE_EQUAL(expectedFourArgCall.arg4, actualFourArgCall.arg4);
   }
};

template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
struct ZenUnitPrinter<ZenMock::FourArgCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>
{
   static void Print(std::ostream& os, const ZenMock::FourArgCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& fourArgCallRef)
   {
      const std::string toStringedArg1 = ZenUnit::ToStringer::ToString(fourArgCallRef.arg1);
      const std::string toStringedArg2 = ZenUnit::ToStringer::ToString(fourArgCallRef.arg2);
      const std::string toStringedArg3 = ZenUnit::ToStringer::ToString(fourArgCallRef.arg3);
      const std::string toStringedArg4 = ZenUnit::ToStringer::ToString(fourArgCallRef.arg4);
      os << "ZenMock::FourArgCall:\n"
            "Arg1: " << toStringedArg1 << '\n' <<
            "Arg2: " << toStringedArg2 << '\n' <<
            "Arg3: " << toStringedArg3 << '\n' <<
            "Arg4: " << toStringedArg4;
   }
};
