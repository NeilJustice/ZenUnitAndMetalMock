#pragma once
#include "ZenUnit/Macros/VECTORS_EQUAL.h"
#include "ZenUnit/ZenMock/2/TwoArgumentCall.h"
#include "ZenUnit/ZenMock/2/TwoArgumentCallRef.h"
#include "ZenUnit/ZenMock/Exceptions/UnexpectedCallException.h"
#include "ZenUnit/ZenMock/ZenMocker.h"
#include "ZenUnit/ZenMock/ZENAssertionToken.h"

#define ZENMOCK_BIND2(FunctionName_ZenMock) \
   std::bind(&decltype(FunctionName_ZenMock)::ZenMockItFunctionPointer, &(FunctionName_ZenMock), \
   std::placeholders::_1, std::placeholders::_2)

namespace ZenMock
{
   template<
      typename Arg1Type,
      typename Arg2Type,
      typename MockableExceptionThrowerType = ExceptionThrower>
   class TwoArgumentMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class TwoArgumentMockerTests;
   private:
      std::vector<TwoArgumentCall<Arg1Type, Arg2Type>> callHistory;
   public:
      explicit TwoArgumentMocker(const std::string& zenMockedFunctionSignature)
         : ZenMocker<MockableExceptionThrowerType>(zenMockedFunctionSignature)
      {
      }

      void ZenMockIt(const Arg1Type& firstArgument, const Arg2Type& secondArgument)
      {
         this->ZenMockThrowIfNotExpected(firstArgument, secondArgument);
         callHistory.emplace_back(firstArgument, secondArgument);
         this->ZenMockThrowIfExceptionSet();
      }

      ZENAssertionToken AssertCalledOnceWith(
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument)
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, callHistory.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFirstArgument, callHistory[0].firstArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSecondArgument, callHistory[0].secondArgument, this->ZenMockedFunctionSignature);
         return ZENAssertionToken::NoDiscard();
      }

      ZENAssertionToken AssertCalledNTimesWith(
         size_t expectedNumberOfCalls,
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument)
      {
         this->ZenMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->ZenMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCalls, callHistory.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex
               = ZenUnit::String::Concat(this->ZenMockedFunctionSignature, ", at i=", i);
            ARE_EQUAL(expectedFirstArgument, callHistory[i].firstArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSecondArgument, callHistory[i].secondArgument, zenMockedFunctionSignatureAndCallIndex);
         }
         return ZENAssertionToken::NoDiscard();
      }

      ZENAssertionToken AssertCalls(const std::vector<TwoArgumentCallRef<Arg1Type, Arg2Type>>& expectedTwoArgumentCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedTwoArgumentCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<TwoArgumentCallRef<Arg1Type, Arg2Type>>
            actualTwoArgumentCalls = PrivateCallsToCallRefs(callHistory);
         VECTORS_EQUAL(expectedTwoArgumentCalls, actualTwoArgumentCalls, this->ZenMockedFunctionSignature);
         return ZENAssertionToken::NoDiscard();
      }
   private:
      static std::vector<TwoArgumentCallRef<Arg1Type, Arg2Type>>
         PrivateCallsToCallRefs(const std::vector<TwoArgumentCall<Arg1Type, Arg2Type>>& callHistory)
      {
         std::vector<TwoArgumentCallRef<Arg1Type, Arg2Type>> twoArgumentCallRefs;
         twoArgumentCallRefs.reserve(callHistory.size());
         std::for_each(callHistory.cbegin(), callHistory.cend(),
            [&](const TwoArgumentCall<Arg1Type, Arg2Type>& twoArgumentCall)
            {
               twoArgumentCallRefs.emplace_back(twoArgumentCall);
            });
         return twoArgumentCallRefs;
      }
   };
}
