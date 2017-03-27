#pragma once
#include "ZenUnit/ZenMock/ZenMocker.h"
#include "ZenUnit/ZenMock/2/TwoArgCall.h"
#include "ZenUnit/ZenMock/2/TwoArgCallRef.h"
#include "ZenUnit/ZenMock/Exceptions/UnexpectedCallException.h"
#include "ZenUnit/Macros/VECTORS_EQUAL.h"

#define ZENBIND2(FunctionName_ZenMock) \
   std::bind(&decltype(FunctionName_ZenMock)::PrivateZenMockFunctionPointer, &FunctionName_ZenMock, \
   std::placeholders::_1, std::placeholders::_2)

namespace ZenMock
{
   template<
      typename Arg1Type,
      typename Arg2Type,
      typename MockableExceptionThrowerType = ExceptionThrower>
   class TwoArgMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class TwoArgMockerTests;
   private:
      std::vector<TwoArgCall<Arg1Type, Arg2Type>> twoArgCalls;
   public:
      TwoArgMocker(const std::string& zenMockedFunctionSignature)
         : ZenMocker<MockableExceptionThrowerType>(zenMockedFunctionSignature)
      {
      }

      void PrivateZenMock(const Arg1Type& arg1, const Arg2Type& arg2)
      {
         this->ThrowIfNotExpected(arg1, arg2);
         twoArgCalls.emplace_back(arg1, arg2);
         this->ThrowIfExceptionSet();
      }

      void AssertCalledOnceWith(
         const Arg1Type& expectedArg1,
         const Arg2Type& expectedArg2)
      {
         this->SetAsserted();
         const size_t expectedNumberOfCalls = 1;
         const size_t numberOfCalls = twoArgCalls.size();
         ARE_EQUAL(expectedNumberOfCalls, numberOfCalls, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg1, twoArgCalls[0].arg1, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg2, twoArgCalls[0].arg2, this->ZenMockedFunctionSignature);
      }

      void AssertCalledNTimesWith(
         size_t expectedNumberOfCalls,
         const Arg1Type& expectedArg1,
         const Arg2Type& expectedArg2)
      {
         this->ThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->SetAsserted();
         const size_t numberOfCalls = twoArgCalls.size();
         ARE_EQUAL(expectedNumberOfCalls, numberOfCalls, this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex
               = ZenUnit::String::Concat(this->ZenMockedFunctionSignature, ", at i=", i);
            ARE_EQUAL(expectedArg1, twoArgCalls[i].arg1, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg2, twoArgCalls[i].arg2, zenMockedFunctionSignatureAndCallIndex);
         }
      }

      void AssertCalls(const std::vector<TwoArgCallRef<Arg1Type, Arg2Type>>& expectedTwoArgCalls)
      {
         this->ThrowIfExpectedCallsSizeIsZero(expectedTwoArgCalls.size());
         this->SetAsserted();
         const std::vector<TwoArgCallRef<Arg1Type, Arg2Type>> 
            actualTwoArgCalls = PrivateCallsToCallRefs(twoArgCalls);
         VECTORS_EQUAL(expectedTwoArgCalls, actualTwoArgCalls, this->ZenMockedFunctionSignature);
      }
   private:
      static std::vector<TwoArgCallRef<Arg1Type, Arg2Type>>
         PrivateCallsToCallRefs(const std::vector<TwoArgCall<Arg1Type, Arg2Type>>& twoArgCalls)
      {
         std::vector<TwoArgCallRef<Arg1Type, Arg2Type>> twoArgCallRefs;
         twoArgCallRefs.reserve(twoArgCalls.size());
         std::for_each(twoArgCalls.cbegin(), twoArgCalls.cend(),
            [&](const TwoArgCall<Arg1Type, Arg2Type>& twoArgCall)
            {
               twoArgCallRefs.emplace_back(twoArgCall);
            });
         return twoArgCallRefs;
      }
   };
}
