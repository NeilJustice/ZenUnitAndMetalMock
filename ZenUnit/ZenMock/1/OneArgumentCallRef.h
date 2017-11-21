#pragma once
#include "ZenUnit/ZenMock/1/OneArgumentCall.h"

namespace ZenMock
{
   template<typename ArgType>
   struct OneArgumentCallRef
   {
      const ArgType& argument;
      OneArgumentCallRef(const ArgType& argument) : argument(argument) {}
      explicit OneArgumentCallRef(const OneArgumentCall<ArgType>& oneArgumentCall) : argument(oneArgumentCall.argument) {}
   };
}

namespace ZenUnit
{
   template<typename ArgType>
   struct Equalizer<ZenMock::OneArgumentCallRef<ArgType>>
   {
      static void AssertEqual(
         const ZenMock::OneArgumentCallRef<ArgType>& expectedOneArgumentCall,
         const ZenMock::OneArgumentCallRef<ArgType>& actualOneArgumentCall)
      {
         ARE_EQUAL(expectedOneArgumentCall.argument, actualOneArgumentCall.argument);
      }
   };

   template<typename ArgType>
   struct Printer<ZenMock::OneArgumentCallRef<ArgType>>
   {
      static void Print(std::ostream& os, const ZenMock::OneArgumentCallRef<ArgType>& oneArgumentCall)
      {
         const std::string toStringedArg = ZenUnit::ToStringer::ToString(oneArgumentCall.argument);
         os << "ZenMock::OneArgumentCall:\n"
            << "Argument: " << toStringedArg;
      }
   };
}
