#pragma once
#include "ZenUnit/ZenMock/10/TenArgumentCall.h"

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
      typename Arg8Type,
      typename Arg9Type,
      typename Arg10Type>
   struct TenArgumentCallRef
   {
      const Arg1Type& firstArgument;
      const Arg2Type& secondArgument;
      const Arg3Type& thirdArgument;
      const Arg4Type& fourthArgument;
      const Arg5Type& fifthArgument;
      const Arg6Type& sixthArgument;
      const Arg7Type& seventhArgument;
      const Arg8Type& eigthArgument;
      const Arg9Type& ninthArgument;
      const Arg10Type& tenthArgument;

      TenArgumentCallRef(
         const Arg1Type& firstArgument,
         const Arg2Type& secondArgument,
         const Arg3Type& thirdArgument,
         const Arg4Type& fourthArgument,
         const Arg5Type& fifthArgument,
         const Arg6Type& sixthArgument,
         const Arg7Type& seventhArgument,
         const Arg8Type& eigthArgument,
         const Arg9Type& ninthArgument,
         const Arg10Type& tenthArgument)
         : firstArgument(firstArgument)
         , secondArgument(secondArgument)
         , thirdArgument(thirdArgument)
         , fourthArgument(fourthArgument)
         , fifthArgument(fifthArgument)
         , sixthArgument(sixthArgument)
         , seventhArgument(seventhArgument)
         , eigthArgument(eigthArgument)
         , ninthArgument(ninthArgument)
         , tenthArgument(tenthArgument)
      {
      }

      explicit TenArgumentCallRef(const TenArgumentCall<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type,
         Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>& tenArgumentCall)
         : firstArgument(tenArgumentCall.firstArgument)
         , secondArgument(tenArgumentCall.secondArgument)
         , thirdArgument(tenArgumentCall.thirdArgument)
         , fourthArgument(tenArgumentCall.fourthArgument)
         , fifthArgument(tenArgumentCall.fifthArgument)
         , sixthArgument(tenArgumentCall.sixthArgument)
         , seventhArgument(tenArgumentCall.seventhArgument)
         , eigthArgument(tenArgumentCall.eigthArgument)
         , ninthArgument(tenArgumentCall.ninthArgument)
         , tenthArgument(tenArgumentCall.tenthArgument)
      {
      }
   };
}

template<
   typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type,
   typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename Arg10Type>
struct ZenUnitEqualizer<ZenMock::TenArgumentCallRef<
   Arg1Type, Arg2Type, Arg3Type, Arg4Type,
   Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>>
{
   static void AssertEqual(
      const ZenMock::TenArgumentCallRef<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type,
         Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>& expectedTenArgumentCall,
      const ZenMock::TenArgumentCallRef<
         Arg1Type, Arg2Type, Arg3Type, Arg4Type,
         Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>& actualTenArgumentCall)
   {
      ARE_EQUAL(expectedTenArgumentCall.firstArgument, actualTenArgumentCall.firstArgument);
      ARE_EQUAL(expectedTenArgumentCall.secondArgument, actualTenArgumentCall.secondArgument);
      ARE_EQUAL(expectedTenArgumentCall.thirdArgument, actualTenArgumentCall.thirdArgument);
      ARE_EQUAL(expectedTenArgumentCall.fourthArgument, actualTenArgumentCall.fourthArgument);
      ARE_EQUAL(expectedTenArgumentCall.fifthArgument, actualTenArgumentCall.fifthArgument);
      ARE_EQUAL(expectedTenArgumentCall.sixthArgument, actualTenArgumentCall.sixthArgument);
      ARE_EQUAL(expectedTenArgumentCall.seventhArgument, actualTenArgumentCall.seventhArgument);
      ARE_EQUAL(expectedTenArgumentCall.eigthArgument, actualTenArgumentCall.eigthArgument);
      ARE_EQUAL(expectedTenArgumentCall.ninthArgument, actualTenArgumentCall.ninthArgument);
      ARE_EQUAL(expectedTenArgumentCall.tenthArgument, actualTenArgumentCall.tenthArgument);
   }
};

template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename Arg10Type>
struct ZenUnitPrinter<ZenMock::TenArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>>
{
   static void Print(std::ostream& os, const ZenMock::TenArgumentCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>& tenArgumentCallRef)
   {
      const std::string toStringedArg1 = ZenUnit::ToStringer::ToString(tenArgumentCallRef.firstArgument);
      const std::string toStringedArg2 = ZenUnit::ToStringer::ToString(tenArgumentCallRef.secondArgument);
      const std::string toStringedArg3 = ZenUnit::ToStringer::ToString(tenArgumentCallRef.thirdArgument);
      const std::string toStringedArg4 = ZenUnit::ToStringer::ToString(tenArgumentCallRef.fourthArgument);
      const std::string toStringedArg5 = ZenUnit::ToStringer::ToString(tenArgumentCallRef.fifthArgument);
      const std::string toStringedArg6 = ZenUnit::ToStringer::ToString(tenArgumentCallRef.sixthArgument);
      const std::string toStringedArg7 = ZenUnit::ToStringer::ToString(tenArgumentCallRef.seventhArgument);
      const std::string toStringedArg8 = ZenUnit::ToStringer::ToString(tenArgumentCallRef.eigthArgument);
      const std::string toStringedArg9 = ZenUnit::ToStringer::ToString(tenArgumentCallRef.ninthArgument);
      const std::string toStringedArg10 = ZenUnit::ToStringer::ToString(tenArgumentCallRef.tenthArgument);
      os << "ZenMock::TenArgumentCall:\n"
            " Arg1: " << toStringedArg1 << '\n' <<
            " Arg2: " << toStringedArg2 << '\n' <<
            " Arg3: " << toStringedArg3 << '\n' <<
            " Arg4: " << toStringedArg4 << '\n' <<
            " Arg5: " << toStringedArg5 << '\n' <<
            " Arg6: " << toStringedArg6 << '\n' <<
            " Arg7: " << toStringedArg7 << '\n' <<
            " Arg8: " << toStringedArg8 << '\n' <<
            " Arg9: " << toStringedArg9 << '\n' <<
            "Arg10: " << toStringedArg10;
   }
};
