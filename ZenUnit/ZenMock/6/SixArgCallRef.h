#pragma once
#include "ZenUnit/ZenMock/6/SixArgCall.h"

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
   struct SixArgCallRef
   {
      const Arg1Type& arg1;
      const Arg2Type& arg2;
      const Arg3Type& arg3;
      const Arg4Type& arg4;
      const Arg5Type& arg5;
      const Arg6Type& arg6;

      SixArgCallRef(
         const Arg1Type& arg1,
         const Arg2Type& arg2,
         const Arg3Type& arg3,
         const Arg4Type& arg4,
         const Arg5Type& arg5,
         const Arg6Type& arg6)
         : arg1(arg1)
         , arg2(arg2)
         , arg3(arg3)
         , arg4(arg4)
         , arg5(arg5)
         , arg6(arg6)
      {
      }

      explicit SixArgCallRef(const SixArgCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& sixArgCall)
         : arg1(sixArgCall.arg1)
         , arg2(sixArgCall.arg2)
         , arg3(sixArgCall.arg3)
         , arg4(sixArgCall.arg4)
         , arg5(sixArgCall.arg5)
         , arg6(sixArgCall.arg6)
      {
      }
   };
}

template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
struct ZenUnitEqualizer<ZenMock::SixArgCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>
{
   static void AssertEqual(
      const ZenMock::SixArgCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& expectedSixArgCall,
      const ZenMock::SixArgCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& actualSixArgCall)
   {
      ARE_EQUAL(expectedSixArgCall.arg1, actualSixArgCall.arg1);
      ARE_EQUAL(expectedSixArgCall.arg2, actualSixArgCall.arg2);
      ARE_EQUAL(expectedSixArgCall.arg3, actualSixArgCall.arg3);
      ARE_EQUAL(expectedSixArgCall.arg4, actualSixArgCall.arg4);
      ARE_EQUAL(expectedSixArgCall.arg5, actualSixArgCall.arg5);
      ARE_EQUAL(expectedSixArgCall.arg6, actualSixArgCall.arg6);
   }
};

template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type>
struct ZenUnitPrinter<ZenMock::SixArgCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>>
{
   static void Print(std::ostream& os, const ZenMock::SixArgCallRef<
      Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type>& sixArgCallRef)
   {
      const std::string toStringedArg1 = ZenUnit::ToStringer::ToString(sixArgCallRef.arg1);
      const std::string toStringedArg2 = ZenUnit::ToStringer::ToString(sixArgCallRef.arg2);
      const std::string toStringedArg3 = ZenUnit::ToStringer::ToString(sixArgCallRef.arg3);
      const std::string toStringedArg4 = ZenUnit::ToStringer::ToString(sixArgCallRef.arg4);
      const std::string toStringedArg5 = ZenUnit::ToStringer::ToString(sixArgCallRef.arg5);
      const std::string toStringedArg6 = ZenUnit::ToStringer::ToString(sixArgCallRef.arg6);
      os << "ZenMock::SixArgCall:\n"
            "Arg1: " << toStringedArg1 << '\n' <<
            "Arg2: " << toStringedArg2 << '\n' <<
            "Arg3: " << toStringedArg3 << '\n' <<
            "Arg4: " << toStringedArg4 << '\n' <<
            "Arg5: " << toStringedArg5 << '\n' <<
            "Arg6: " << toStringedArg6;
   }
};
