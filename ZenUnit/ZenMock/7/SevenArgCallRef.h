#pragma once
#include "ZenUnit/ZenMock/7/SevenArgCall.h"

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
   struct SevenArgCallRef
   {
      const Arg1Type& arg1;
      const Arg2Type& arg2;
      const Arg3Type& arg3;
      const Arg4Type& arg4;
      const Arg5Type& arg5;
      const Arg6Type& arg6;
      const Arg7Type& arg7;

      SevenArgCallRef(
         const Arg1Type& arg1,
         const Arg2Type& arg2,
         const Arg3Type& arg3,
         const Arg4Type& arg4,
         const Arg5Type& arg5,
         const Arg6Type& arg6,
         const Arg7Type& arg7)
         : arg1(arg1)
         , arg2(arg2)
         , arg3(arg3)
         , arg4(arg4)
         , arg5(arg5)
         , arg6(arg6)
         , arg7(arg7)
      {
      }

      SevenArgCallRef(const SevenArgCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& sevenArgCall)
         : arg1(sevenArgCall.arg1)
         , arg2(sevenArgCall.arg2)
         , arg3(sevenArgCall.arg3)
         , arg4(sevenArgCall.arg4)
         , arg5(sevenArgCall.arg5)
         , arg6(sevenArgCall.arg6)
         , arg7(sevenArgCall.arg7)
      {
      }
   };
}

template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
struct ZenUnitEqualizer<ZenMock::SevenArgCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>
{
   static void AssertEqual(
      const ZenMock::SevenArgCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& expectedSevenArgCall,
      const ZenMock::SevenArgCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& actualSevenArgCall)
   {
      ARE_EQUAL(expectedSevenArgCall.arg1, actualSevenArgCall.arg1);
      ARE_EQUAL(expectedSevenArgCall.arg2, actualSevenArgCall.arg2);
      ARE_EQUAL(expectedSevenArgCall.arg3, actualSevenArgCall.arg3);
      ARE_EQUAL(expectedSevenArgCall.arg4, actualSevenArgCall.arg4);
      ARE_EQUAL(expectedSevenArgCall.arg5, actualSevenArgCall.arg5);
      ARE_EQUAL(expectedSevenArgCall.arg6, actualSevenArgCall.arg6);
      ARE_EQUAL(expectedSevenArgCall.arg7, actualSevenArgCall.arg7);
   }
};

template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
struct ZenUnitPrinter<ZenMock::SevenArgCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>
{
   static void Print(std::ostream& os, const ZenMock::SevenArgCallRef<
      Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& sevenArgCallRef)
   {
      std::string toStringedArg1 = ZenUnit::ToStringer::ToString(sevenArgCallRef.arg1);
      std::string toStringedArg2 = ZenUnit::ToStringer::ToString(sevenArgCallRef.arg2);
      std::string toStringedArg3 = ZenUnit::ToStringer::ToString(sevenArgCallRef.arg3);
      std::string toStringedArg4 = ZenUnit::ToStringer::ToString(sevenArgCallRef.arg4);
      std::string toStringedArg5 = ZenUnit::ToStringer::ToString(sevenArgCallRef.arg5);
      std::string toStringedArg6 = ZenUnit::ToStringer::ToString(sevenArgCallRef.arg6);
      std::string toStringedArg7 = ZenUnit::ToStringer::ToString(sevenArgCallRef.arg7);
      os << "ZenMock::SevenArgCall:\n"
            "Arg1: " << toStringedArg1 << '\n' <<
            "Arg2: " << toStringedArg2 << '\n' <<
            "Arg3: " << toStringedArg3 << '\n' <<
            "Arg4: " << toStringedArg4 << '\n' <<
            "Arg5: " << toStringedArg5 << '\n' <<
            "Arg6: " << toStringedArg6 << '\n' <<
            "Arg7: " << toStringedArg7;
   }
};
