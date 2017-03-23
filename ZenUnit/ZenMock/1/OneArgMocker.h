#pragma once
#include "ZenUnit/ZenMock/ZenMocker.h"
#include "ZenUnit/ZenMock/1/OneArgCall.h"
#include "ZenUnit/ZenMock/1/OneArgCallRef.h"
#include "ZenUnit/ZenMock/Exceptions/UnexpectedCallException.h"
#include "ZenUnit/ZenMock/Exceptions/FunctionAlreadyExpectedException.h"
#include "ZenUnit/ZenMock/Exceptions/UnsupportedAssertCalledZeroTimesException.h"
#include "ZenUnit/Macros/VECTORS_EQUAL.h"

#define ZENBIND1(FunctionName_ZenMock) \
   std::bind(&decltype(FunctionName_ZenMock)::PrivateZenMockFunctionPointer, &FunctionName_ZenMock, \
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
      std::vector<OneArgCall<ArgType>> oneArgCalls;
   public:
      OneArgMocker(const std::string& zenMockedFunctionSignature)
         : ZenMocker<MockableExceptionThrowerType>(zenMockedFunctionSignature)
      {
      }

      void PrivateZenMock(const ArgType& arg)
      {
         this->ThrowIfNotExpected(arg);
         oneArgCalls.emplace_back(arg);
         this->ThrowIfExceptionSet();
      }

      void AssertCalledOnceWith(const ArgType& expectedArg)
      {
         this->SetAsserted();
         size_t expectedNumberOfCalls = 1;
         size_t numberOfCalls = oneArgCalls.size();
         ARE_EQUAL(expectedNumberOfCalls, numberOfCalls, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg, oneArgCalls[0].arg, this->ZenMockedFunctionSignature);
      }

      void AssertCalledNTimesWith(size_t expectedNumberOfCalls, const ArgType& expectedArg)
      {
         this->ThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->SetAsserted();
         size_t numberOfCalls = oneArgCalls.size();
         ARE_EQUAL(expectedNumberOfCalls, numberOfCalls, this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            std::string zenMockedFunctionSignatureAndCallIndex
               = ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedArg, oneArgCalls[i].arg, zenMockedFunctionSignatureAndCallIndex);
         }
      }

      void AssertCalls(const std::vector<OneArgCallRef<ArgType>>& expectedOneArgCalls)
      {
         this->ThrowIfExpectedCallsSizeIsZero(expectedOneArgCalls.size());
         this->SetAsserted();
         std::vector<OneArgCallRef<ArgType>> actualOneArgCalls = PrivateCallsToCallRefs(oneArgCalls);
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
