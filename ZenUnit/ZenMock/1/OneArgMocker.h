#pragma once
#include "ZenUnit/ZenMock/ZenMocker.h"
#include "ZenUnit/ZenMock/1/OneArgCall.h"
#include "ZenUnit/ZenMock/1/OneArgCallRef.h"
#include "ZenUnit/ZenMock/Exceptions/UnexpectedCallException.h"
#include "ZenUnit/ZenMock/Exceptions/FunctionAlreadyExpectedException.h"
#include "ZenUnit/ZenMock/Exceptions/UnsupportedAssertCalledZeroTimesException.h"
#include "ZenUnit/Macros/VECTORS_EQUAL.h"

#define ZENBIND1(FunctionName_ZenMock) \
   std::bind(&decltype(FunctionName_ZenMock)::ZenMockItFunctionPointer, &(FunctionName_ZenMock), \
   std::placeholders::_1)

namespace ZenMock
{
   template<
      typename ArgType,
      typename MockableExceptionThrowerType = ExceptionThrower>
   class OneArgMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class OneArgMockerTests;
   private:
      std::vector<OneArgCall<ArgType>> _oneArgCalls;
   public:
      explicit OneArgMocker(const std::string& zenMockedFunctionSignature)
         : ZenMocker<MockableExceptionThrowerType>(zenMockedFunctionSignature)
      {
      }

      void ZenMockIt(const ArgType& arg)
      {
         this->ZenMockThrowIfNotExpected(arg);
         _oneArgCalls.emplace_back(arg);
         this->ZenMockThrowIfExceptionSet();
      }

      void AssertCalledOnceWith(const ArgType& expectedArg)
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, _oneArgCalls.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg, _oneArgCalls[0].arg, this->ZenMockedFunctionSignature);
      }

      void AssertCalledNTimesWith(size_t expectedNumberOfCalls, const ArgType& expectedArg)
      {
         this->ZenMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->ZenMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCalls, _oneArgCalls.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex
               = ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedArg, _oneArgCalls[i].arg, zenMockedFunctionSignatureAndCallIndex);
         }
      }

      void AssertCalls(const std::vector<OneArgCallRef<ArgType>>& expectedOneArgCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedOneArgCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<OneArgCallRef<ArgType>>
            actualOneArgCalls = PrivateCallsToCallRefs(_oneArgCalls);
         VECTORS_EQUAL(expectedOneArgCalls, actualOneArgCalls, this->ZenMockedFunctionSignature);
      }
   private:
      static std::vector<OneArgCallRef<ArgType>>
         PrivateCallsToCallRefs(const std::vector<OneArgCall<ArgType>>& oneArgCalls)
      {
         std::vector<OneArgCallRef<ArgType>> oneArgCallRefs;
         oneArgCallRefs.reserve(oneArgCalls.size());
         std::for_each(oneArgCalls.cbegin(), oneArgCalls.cend(),
            [&](const OneArgCall<ArgType>& oneArgCall)
            {
               oneArgCallRefs.emplace_back(oneArgCall);
            });
         return oneArgCallRefs;
      }
   };
}
