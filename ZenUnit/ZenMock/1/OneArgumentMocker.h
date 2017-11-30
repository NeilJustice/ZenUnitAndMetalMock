#pragma once
#include "ZenUnit/Macros/VECTORS_EQUAL.h"
#include "ZenUnit/ZenMock/1/OneArgumentCall.h"
#include "ZenUnit/ZenMock/1/OneArgumentCallRef.h"
#include "ZenUnit/ZenMock/Exceptions/FunctionAlreadyExpectedException.h"
#include "ZenUnit/ZenMock/Exceptions/UnexpectedCallException.h"
#include "ZenUnit/ZenMock/Exceptions/UnsupportedAssertCalledZeroTimesException.h"
#include "ZenUnit/ZenMock/ZenMocker.h"
#include "ZenUnit/ZenMock/ZENAssertionToken.h"

#define ZENMOCK_BIND1(FunctionName_ZenMock) \
   std::bind(&decltype(FunctionName_ZenMock)::ZenMockItFunctionPointer, &(FunctionName_ZenMock), \
   std::placeholders::_1)

namespace ZenMock
{
   template<
      typename ArgType,
      typename MockableExceptionThrowerType = ExceptionThrower>
   class OneArgumentMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class OneArgumentMockerTests;
      template<
         typename ZenMockObjectType,
         typename FreeMockType,
         typename NamespaceMockType,
         typename StaticMockType,
         typename StaticNameClashMockType>
      friend class ZenMock1Tester;
   private:
      std::vector<OneArgumentCall<ArgType>> callHistory;
   public:
      explicit OneArgumentMocker(const std::string& zenMockedFunctionSignature)
         : ZenMocker<MockableExceptionThrowerType>(zenMockedFunctionSignature)
      {
      }

      void ZenMockIt(const ArgType& argument)
      {
         this->ZenMockThrowIfNotExpected(argument);
         callHistory.emplace_back(argument);
         this->ZenMockThrowIfExceptionSet();
      }

      ZENAssertionToken AssertCalledOnceWith(const ArgType& expectedArgument)
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, callHistory.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument, callHistory[0].argument, this->ZenMockedFunctionSignature);
         return ZENAssertionToken::NoDiscard();
      }

      ZENAssertionToken AssertCalledNTimesWith(size_t expectedNumberOfCalls, const ArgType& expectedArgument)
      {
         this->ZenMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->ZenMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCalls, callHistory.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex
               = ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedArgument, callHistory[i].argument, zenMockedFunctionSignatureAndCallIndex);
         }
         return ZENAssertionToken::NoDiscard();
      }

      ZENAssertionToken AssertCalls(const std::vector<OneArgumentCallRef<ArgType>>& expectedOneArgumentCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedOneArgumentCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<OneArgumentCallRef<ArgType>>
            actualOneArgumentCalls = PrivateCallsToCallRefs(callHistory);
         VECTORS_EQUAL(expectedOneArgumentCalls, actualOneArgumentCalls, this->ZenMockedFunctionSignature);
         return ZENAssertionToken::NoDiscard();
      }
   private:
      static std::vector<OneArgumentCallRef<ArgType>>
         PrivateCallsToCallRefs(const std::vector<OneArgumentCall<ArgType>>& callHistory)
      {
         std::vector<OneArgumentCallRef<ArgType>> oneArgumentCallRefs;
         oneArgumentCallRefs.reserve(callHistory.size());
         std::for_each(callHistory.cbegin(), callHistory.cend(),
            [&](const OneArgumentCall<ArgType>& oneArgumentCall)
            {
               oneArgumentCallRefs.emplace_back(oneArgumentCall);
            });
         return oneArgumentCallRefs;
      }
   };
}
