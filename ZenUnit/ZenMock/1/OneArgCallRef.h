#pragma once
#include "ZenUnit/ZenMock/1/OneArgCall.h"

namespace ZenMock
{
   template<typename ArgType>
   struct OneArgCallRef
   {
      const ArgType& arg1;

      OneArgCallRef(const ArgType& arg1)
         : arg1(arg1)
      {
      }

      explicit OneArgCallRef(const OneArgCall<ArgType>& oneArgCall)
         : arg1(oneArgCall.arg1)
      {
      }
   };
}

template<typename ArgType>
struct ZenUnitEqualizer<ZenMock::OneArgCallRef<ArgType>>
{
   static void AssertEqual(
      const ZenMock::OneArgCallRef<ArgType>& expectedOneArgCall,
      const ZenMock::OneArgCallRef<ArgType>& actualOneArgCall)
   {
      ARE_EQUAL(expectedOneArgCall.arg1, actualOneArgCall.arg1);
   }
};

template<typename ArgType>
struct ZenUnitPrinter<ZenMock::OneArgCallRef<ArgType>>
{
   static void Print(std::ostream& os, const ZenMock::OneArgCallRef<ArgType>& oneArgCall)
   {
      const std::string toStringedArg = ZenUnit::ToStringer::ToString(oneArgCall.arg1);
      os << "ZenMock::OneArgCall:\n"
         << "Arg: " << toStringedArg;
   }
};
