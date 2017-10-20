#pragma once
#include "ZenUnit/ZenMock/7/SevenArgumentCall.h"

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
   struct SevenArgumentCallRef
   {
      const Arg1Type& firstArgument;
      const Arg2Type& secondArgument;
      const Arg3Type& thirdArgument;
      const Arg4Type& fourthArgument;
      const Arg5Type& fifthArgument;
      const Arg6Type& sixthArgument;
      const Arg7Type& seventhArgument;

      SevenArgumentCallRef(
         const Arg1Type& firstArgument,
         const Arg2Type& secondArgument,
         const Arg3Type& thirdArgument,
         const Arg4Type& fourthArgument,
         const Arg5Type& fifthArgument,
         const Arg6Type& sixthArgument,
         const Arg7Type& seventhArgument)
         : firstArgument(firstArgument)
         , secondArgument(secondArgument)
         , thirdArgument(thirdArgument)
         , fourthArgument(fourthArgument)
         , fifthArgument(fifthArgument)
         , sixthArgument(sixthArgument)
         , seventhArgument(seventhArgument)
      {
      }

      explicit SevenArgumentCallRef(const SevenArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& sevenArgumentCall)
         : firstArgument(sevenArgumentCall.firstArgument)
         , secondArgument(sevenArgumentCall.secondArgument)
         , thirdArgument(sevenArgumentCall.thirdArgument)
         , fourthArgument(sevenArgumentCall.fourthArgument)
         , fifthArgument(sevenArgumentCall.fifthArgument)
         , sixthArgument(sevenArgumentCall.sixthArgument)
         , seventhArgument(sevenArgumentCall.seventhArgument)
      {
      }
   };
}

template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
struct ZenUnitEqualizer<ZenMock::SevenArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>
{
   static void AssertEqual(
      const ZenMock::SevenArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& expectedSevenArgumentCall,
      const ZenMock::SevenArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& actualSevenArgumentCall)
   {
      ARE_EQUAL(expectedSevenArgumentCall.firstArgument, actualSevenArgumentCall.firstArgument);
      ARE_EQUAL(expectedSevenArgumentCall.secondArgument, actualSevenArgumentCall.secondArgument);
      ARE_EQUAL(expectedSevenArgumentCall.thirdArgument, actualSevenArgumentCall.thirdArgument);
      ARE_EQUAL(expectedSevenArgumentCall.fourthArgument, actualSevenArgumentCall.fourthArgument);
      ARE_EQUAL(expectedSevenArgumentCall.fifthArgument, actualSevenArgumentCall.fifthArgument);
      ARE_EQUAL(expectedSevenArgumentCall.sixthArgument, actualSevenArgumentCall.sixthArgument);
      ARE_EQUAL(expectedSevenArgumentCall.seventhArgument, actualSevenArgumentCall.seventhArgument);
   }
};

template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type>
struct ZenUnitPrinter<ZenMock::SevenArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>>
{
   static void Print(std::ostream& os, const ZenMock::SevenArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type>& sevenArgumentCallRef)
   {
      const std::string toStringedArg1 = ZenUnit::ToStringer::ToString(sevenArgumentCallRef.firstArgument);
      const std::string toStringedArg2 = ZenUnit::ToStringer::ToString(sevenArgumentCallRef.secondArgument);
      const std::string toStringedArg3 = ZenUnit::ToStringer::ToString(sevenArgumentCallRef.thirdArgument);
      const std::string toStringedArg4 = ZenUnit::ToStringer::ToString(sevenArgumentCallRef.fourthArgument);
      const std::string toStringedArg5 = ZenUnit::ToStringer::ToString(sevenArgumentCallRef.fifthArgument);
      const std::string toStringedArg6 = ZenUnit::ToStringer::ToString(sevenArgumentCallRef.sixthArgument);
      const std::string toStringedArg7 = ZenUnit::ToStringer::ToString(sevenArgumentCallRef.seventhArgument);
      os << "ZenMock::SevenArgumentCall:\n"
            "Arg1: " << toStringedArg1 << '\n' <<
            "Arg2: " << toStringedArg2 << '\n' <<
            "Arg3: " << toStringedArg3 << '\n' <<
            "Arg4: " << toStringedArg4 << '\n' <<
            "Arg5: " << toStringedArg5 << '\n' <<
            "Arg6: " << toStringedArg6 << '\n' <<
            "Arg7: " << toStringedArg7;
   }
};
