#pragma once

namespace ZenMock
{
   template<typename Arg1Type>
   struct OneArgumentCall
   {
      typename std::decay<Arg1Type>::type argument;

      OneArgumentCall()
         : argument()
      {
      }

      OneArgumentCall(const Arg1Type& argument)
         : argument(argument)
      {
      }
   };
}

namespace ZenUnit
{
   template<typename ArgType>
   struct Equalizer<ZenMock::OneArgumentCall<ArgType>>
   {
      static void AssertEqual(
         const ZenMock::OneArgumentCall<ArgType>& expectedOneArgumentCall,
         const ZenMock::OneArgumentCall<ArgType>& actualOneArgumentCall)
      {
         ARE_EQUAL(expectedOneArgumentCall.argument, actualOneArgumentCall.argument);
      }
   };
}
