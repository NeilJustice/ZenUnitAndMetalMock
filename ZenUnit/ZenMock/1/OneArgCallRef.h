#pragma once
#include "ZenUnit/ZenMock/1/OneArgCall.h"

namespace ZenMock
{
   template<typename ArgType>
   struct OneArgCallRef
   {
      const ArgType& arg;

      OneArgCallRef(const ArgType& arg) : arg(arg) {}

      explicit OneArgCallRef(const OneArgCall<ArgType>& oneArgCall) : arg(oneArgCall.arg) {}
   };
}

template<typename ArgType>
struct ZenUnitEqualizer<ZenMock::OneArgCallRef<ArgType>>
{
   static void AssertEqual(
      const ZenMock::OneArgCallRef<ArgType>& expectedOneArgCall,
      const ZenMock::OneArgCallRef<ArgType>& actualOneArgCall)
   {
      ARE_EQUAL(expectedOneArgCall.arg, actualOneArgCall.arg);
   }
};

template<typename ArgType>
struct ZenUnitPrinter<ZenMock::OneArgCallRef<ArgType>>
{
   static void Print(std::ostream& os, const ZenMock::OneArgCallRef<ArgType>& oneArgCall)
   {
      const std::string toStringedArg = ZenUnit::ToStringer::ToString(oneArgCall.arg);
      os << "ZenMock::OneArgCall:\n"
         << "Arg: " << toStringedArg;
   }
};
