#pragma once

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type>
   struct TwoArgumentCall
   {
      typename std::decay<Arg1Type>::type firstArgument;
      typename std::decay<Arg2Type>::type secondArgument;

      TwoArgumentCall()
         : firstArgument()
         , secondArgument()
      {
      }

      TwoArgumentCall(const Arg1Type& firstArgument, const Arg2Type& secondArgument)
         : firstArgument(firstArgument)
         , secondArgument(secondArgument)
      {
      }
   };
}

namespace ZenUnit
{
   template<typename Arg1Type, typename Arg2Type>
   struct Equalizer<ZenMock::TwoArgumentCall<Arg1Type, Arg2Type>>
   {
      static void AssertEqual(
         const ZenMock::TwoArgumentCall<Arg1Type, Arg2Type>& expectedTwoArgumentCall,
         const ZenMock::TwoArgumentCall<Arg1Type, Arg2Type>& actualTwoArgumentCall)
      {
         ARE_EQUAL(expectedTwoArgumentCall.firstArgument, actualTwoArgumentCall.firstArgument);
         ARE_EQUAL(expectedTwoArgumentCall.secondArgument, actualTwoArgumentCall.secondArgument);
      }
   };
}
