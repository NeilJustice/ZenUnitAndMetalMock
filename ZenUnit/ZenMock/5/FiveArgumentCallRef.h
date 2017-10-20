#pragma once
#include "ZenUnit/ZenMock/5/FiveArgumentCall.h"

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
   struct FiveArgumentCallRef
   {
      const Arg1Type& firstArgument;
      const Arg2Type& secondArgument;
      const Arg3Type& thirdArgument;
      const Arg4Type& fourthArgument;
      const Arg5Type& fifthArgument;

      FiveArgumentCallRef(
         const Arg1Type& firstArgument,
         const Arg2Type& secondArgument,
         const Arg3Type& thirdArgument,
         const Arg4Type& fourthArgument,
         const Arg5Type& fifthArgument)
         : firstArgument(firstArgument)
         , secondArgument(secondArgument)
         , thirdArgument(thirdArgument)
         , fourthArgument(fourthArgument)
         , fifthArgument(fifthArgument)
      {
      }

      explicit FiveArgumentCallRef(const FiveArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& fiveArgumentCall)
         : firstArgument(fiveArgumentCall.firstArgument)
         , secondArgument(fiveArgumentCall.secondArgument)
         , thirdArgument(fiveArgumentCall.thirdArgument)
         , fourthArgument(fiveArgumentCall.fourthArgument)
         , fifthArgument(fiveArgumentCall.fifthArgument)
      {
      }
   };
}

template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
struct ZenUnitEqualizer<ZenMock::FiveArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>
{
   static void AssertEqual(
      const ZenMock::FiveArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& expectedFiveArgumentCall,
      const ZenMock::FiveArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& actualFiveArgumentCall)
   {
      ARE_EQUAL(expectedFiveArgumentCall.firstArgument, actualFiveArgumentCall.firstArgument);
      ARE_EQUAL(expectedFiveArgumentCall.secondArgument, actualFiveArgumentCall.secondArgument);
      ARE_EQUAL(expectedFiveArgumentCall.thirdArgument, actualFiveArgumentCall.thirdArgument);
      ARE_EQUAL(expectedFiveArgumentCall.fourthArgument, actualFiveArgumentCall.fourthArgument);
      ARE_EQUAL(expectedFiveArgumentCall.fifthArgument, actualFiveArgumentCall.fifthArgument);
   }
};

template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type>
struct ZenUnitPrinter<ZenMock::FiveArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>
{
   static void Print(std::ostream& os, const ZenMock::FiveArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& fiveArgumentCallRef)
   {
      const std::string toStringedArg1 = ZenUnit::ToStringer::ToString(fiveArgumentCallRef.firstArgument);
      const std::string toStringedArg2 = ZenUnit::ToStringer::ToString(fiveArgumentCallRef.secondArgument);
      const std::string toStringedArg3 = ZenUnit::ToStringer::ToString(fiveArgumentCallRef.thirdArgument);
      const std::string toStringedArg4 = ZenUnit::ToStringer::ToString(fiveArgumentCallRef.fourthArgument);
      const std::string toStringedArg5 = ZenUnit::ToStringer::ToString(fiveArgumentCallRef.fifthArgument);
      os << "ZenMock::FiveArgumentCall:\n"
            "Arg1: " << toStringedArg1 << '\n' <<
            "Arg2: " << toStringedArg2 << '\n' <<
            "Arg3: " << toStringedArg3 << '\n' <<
            "Arg4: " << toStringedArg4 << '\n' <<
            "Arg5: " << toStringedArg5;
   }
};
