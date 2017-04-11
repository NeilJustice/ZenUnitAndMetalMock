#pragma once
#include "ZenUnit/Macros/VECTORS_EQUAL.h"
#include "ZenUnit/ZenMock/2/TwoArgCall.h"
#include "ZenUnit/ZenMock/2/TwoArgCallRef.h"
#include "ZenUnit/ZenMock/Exceptions/UnexpectedCallException.h"
#include "ZenUnit/ZenMock/ZenMocker.h"

#define ZENBIND2(FunctionName_ZenMock) \
   std::bind(&decltype(FunctionName_ZenMock)::ZenMockItFunctionPointer, &(FunctionName_ZenMock), \
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
      std::vector<TwoArgCall<Arg1Type, Arg2Type>> _twoArgCalls;
   public:
      explicit TwoArgMocker(const std::string& zenMockedFunctionSignature)
         : ZenMocker<MockableExceptionThrowerType>(zenMockedFunctionSignature)
      {
      }

      void ZenMockIt(const Arg1Type& arg1, const Arg2Type& arg2)
      {
         this->ZenMockThrowIfNotExpected(arg1, arg2);
         _twoArgCalls.emplace_back(arg1, arg2);
         this->ZenMockThrowIfExceptionSet();
      }

      void AssertCalledOnceWith(
         const Arg1Type& expectedArg1,
         const Arg2Type& expectedArg2)
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, _twoArgCalls.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg1, _twoArgCalls[0].arg1, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg2, _twoArgCalls[0].arg2, this->ZenMockedFunctionSignature);
      }

      void AssertCalledNTimesWith(
         size_t expectedNumberOfCalls,
         const Arg1Type& expectedArg1,
         const Arg2Type& expectedArg2)
      {
         this->ZenMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->ZenMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCalls, _twoArgCalls.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex
               = ZenUnit::String::Concat(this->ZenMockedFunctionSignature, ", at i=", i);
            ARE_EQUAL(expectedArg1, _twoArgCalls[i].arg1, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg2, _twoArgCalls[i].arg2, zenMockedFunctionSignatureAndCallIndex);
         }
      }

      void AssertCalls(const std::vector<TwoArgCallRef<Arg1Type, Arg2Type>>& expectedTwoArgCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedTwoArgCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<TwoArgCallRef<Arg1Type, Arg2Type>>
            actualTwoArgCalls = PrivateCallsToCallRefs(_twoArgCalls);
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
