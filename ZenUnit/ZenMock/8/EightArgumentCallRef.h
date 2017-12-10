#pragma once
#include "ZenUnit/ZenMock/8/EightArgumentCall.h"

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
   struct EightArgumentCallRef
   {
      const Arg1Type& firstArgument;
      const Arg2Type& secondArgument;
      const Arg3Type& thirdArgument;
      const Arg4Type& fourthArgument;
      const Arg5Type& fifthArgument;
      const Arg6Type& sixthArgument;
      const Arg7Type& seventhArgument;
      const Arg8Type& eigthArgument;

      EightArgumentCallRef(
         const Arg1Type& firstArgument,
         const Arg2Type& secondArgument,
         const Arg3Type& thirdArgument,
         const Arg4Type& fourthArgument,
         const Arg5Type& fifthArgument,
         const Arg6Type& sixthArgument,
         const Arg7Type& seventhArgument,
         const Arg8Type& eigthArgument) noexcept
         : firstArgument(firstArgument)
         , secondArgument(secondArgument)
         , thirdArgument(thirdArgument)
         , fourthArgument(fourthArgument)
         , fifthArgument(fifthArgument)
         , sixthArgument(sixthArgument)
         , seventhArgument(seventhArgument)
         , eigthArgument(eigthArgument)
      {
      }

      explicit EightArgumentCallRef(const EightArgumentCall<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>& eightArgumentCall) noexcept
         : firstArgument(eightArgumentCall.firstArgument)
         , secondArgument(eightArgumentCall.secondArgument)
         , thirdArgument(eightArgumentCall.thirdArgument)
         , fourthArgument(eightArgumentCall.fourthArgument)
         , fifthArgument(eightArgumentCall.fifthArgument)
         , sixthArgument(eightArgumentCall.sixthArgument)
         , seventhArgument(eightArgumentCall.seventhArgument)
         , eigthArgument(eightArgumentCall.eigthArgument)
      {
      }
   };
}

namespace ZenUnit
{
   template<
      typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type,
      typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type>
   struct Equalizer<ZenMock::EightArgumentCallRef<
      Arg1Type, Arg2Type, Arg3Type, Arg4Type,
      Arg5Type, Arg6Type, Arg7Type, Arg8Type>>
   {
      static void AssertEqual(
         const ZenMock::EightArgumentCallRef<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type,
            Arg5Type, Arg6Type, Arg7Type, Arg8Type>& expectedEightArgumentCall,
         const ZenMock::EightArgumentCallRef<
            Arg1Type, Arg2Type, Arg3Type, Arg4Type,
            Arg5Type, Arg6Type, Arg7Type, Arg8Type>& actualEightArgumentCall)
      {
         ARE_EQUAL(expectedEightArgumentCall.firstArgument, actualEightArgumentCall.firstArgument);
         ARE_EQUAL(expectedEightArgumentCall.secondArgument, actualEightArgumentCall.secondArgument);
         ARE_EQUAL(expectedEightArgumentCall.thirdArgument, actualEightArgumentCall.thirdArgument);
         ARE_EQUAL(expectedEightArgumentCall.fourthArgument, actualEightArgumentCall.fourthArgument);
         ARE_EQUAL(expectedEightArgumentCall.fifthArgument, actualEightArgumentCall.fifthArgument);
         ARE_EQUAL(expectedEightArgumentCall.sixthArgument, actualEightArgumentCall.sixthArgument);
         ARE_EQUAL(expectedEightArgumentCall.seventhArgument, actualEightArgumentCall.seventhArgument);
         ARE_EQUAL(expectedEightArgumentCall.eigthArgument, actualEightArgumentCall.eigthArgument);
      }
   };

   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type>
   struct Printer<ZenMock::EightArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>>
   {
      static void Print(std::ostream& os, const ZenMock::EightArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type>& eightArgumentCallRef)
      {
         const std::string toStringedArg1 = ZenUnit::ToStringer::ToString(eightArgumentCallRef.firstArgument);
         const std::string toStringedArg2 = ZenUnit::ToStringer::ToString(eightArgumentCallRef.secondArgument);
         const std::string toStringedArg3 = ZenUnit::ToStringer::ToString(eightArgumentCallRef.thirdArgument);
         const std::string toStringedArg4 = ZenUnit::ToStringer::ToString(eightArgumentCallRef.fourthArgument);
         const std::string toStringedArg5 = ZenUnit::ToStringer::ToString(eightArgumentCallRef.fifthArgument);
         const std::string toStringedArg6 = ZenUnit::ToStringer::ToString(eightArgumentCallRef.sixthArgument);
         const std::string toStringedArg7 = ZenUnit::ToStringer::ToString(eightArgumentCallRef.seventhArgument);
         const std::string toStringedArg8 = ZenUnit::ToStringer::ToString(eightArgumentCallRef.eigthArgument);
         os << "ZenMock::EightArgumentCall:\n"
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
}
