#pragma once
#include "ZenUnit/Macros/ARE_EQUAL.h"
#include "ZenUnit/ToStringer/ToStringer.h"

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
   struct TenArgumentCall
   {
      typename std::decay<Arg1Type>::type firstArgument;
      typename std::decay<Arg2Type>::type secondArgument;
      typename std::decay<Arg3Type>::type thirdArgument;
      typename std::decay<Arg4Type>::type fourthArgument;
      typename std::decay<Arg5Type>::type fifthArgument;
      typename std::decay<Arg6Type>::type sixthArgument;
      typename std::decay<Arg7Type>::type seventhArgument;
      typename std::decay<Arg8Type>::type eigthArgument;
      typename std::decay<Arg9Type>::type ninthArgument;
      typename std::decay<Arg10Type>::type tenthArgument;

      TenArgumentCall()
         : firstArgument()
         , secondArgument()
         , thirdArgument()
         , fourthArgument()
         , fifthArgument()
         , sixthArgument()
         , seventhArgument()
         , eigthArgument()
         , ninthArgument()
         , tenthArgument()
      {
      }

      TenArgumentCall(
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
   };
}

namespace ZenUnit
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, typename Arg5Type, typename Arg6Type, typename Arg7Type, typename Arg8Type, typename Arg9Type, typename Arg10Type>
   struct Equalizer<ZenMock::TenArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>>
   {
      static void AssertEqual(
         const ZenMock::TenArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>& expectedTenArgumentCall,
         const ZenMock::TenArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type>& actualTenArgumentCall)
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
}
