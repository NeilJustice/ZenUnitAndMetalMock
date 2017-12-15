#pragma once

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   struct FourArgumentCall
   {
      typename std::decay<Arg1Type>::type firstArgument;
      typename std::decay<Arg2Type>::type secondArgument;
      typename std::decay<Arg3Type>::type thirdArgument;
      typename std::decay<Arg4Type>::type fourthArgument;

      FourArgumentCall()
         : firstArgument()
         , secondArgument()
         , thirdArgument()
         , fourthArgument()
      {
      }

      FourArgumentCall(const Arg1Type& firstArgument, const Arg2Type& secondArgument, const Arg3Type& thirdArgument, const Arg4Type& fourthArgument)
         : firstArgument(firstArgument)
         , secondArgument(secondArgument)
         , thirdArgument(thirdArgument)
         , fourthArgument(fourthArgument)
      {
      }
   };
}

namespace ZenUnit
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
   struct Equalizer<ZenMock::FourArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>>
   {
      static void AssertEqual(
         const ZenMock::FourArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& expectedFourArgumentCall,
         const ZenMock::FourArgumentCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type>& actualFourArgumentCall)
       {
          ARE_EQUAL(expectedFourArgumentCall.firstArgument, actualFourArgumentCall.firstArgument);
          ARE_EQUAL(expectedFourArgumentCall.secondArgument, actualFourArgumentCall.secondArgument);
          ARE_EQUAL(expectedFourArgumentCall.thirdArgument, actualFourArgumentCall.thirdArgument);
          ARE_EQUAL(expectedFourArgumentCall.fourthArgument, actualFourArgumentCall.fourthArgument);
       }
   };
}
