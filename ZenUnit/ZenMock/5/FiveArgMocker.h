#pragma once
#include "ZenUnit/ZenMock/ZenMocker.h"
#include "ZenUnit/ZenMock/5/FiveArgCall.h"
#include "ZenUnit/ZenMock/5/FiveArgCallRef.h"
#include "ZenUnit/ZenMock/Exceptions/UnexpectedCallException.h"
#include "ZenUnit/Macros/VECTORS_EQUAL.h"

#define ZENBIND5(FunctionName_ZenMock) \
   std::bind(&decltype(FunctionName_ZenMock)::PrivateZenMockFunctionPointer, &FunctionName_ZenMock, \
   std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5)

namespace ZenMock
{
   template<
      typename Arg1Type,
      typename Arg2Type,
      typename Arg3Type,
      typename Arg4Type,
      typename Arg5Type,
      typename MockableExceptionThrowerType = ExceptionThrower>
   class FiveArgMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class FiveArgMockerTests;
   private:
      std::vector<FiveArgCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>> fiveArgCalls;
   public:
      FiveArgMocker(const std::string& zenMockedFunctionSignature)
         : ZenMocker<MockableExceptionThrowerType>(zenMockedFunctionSignature)
      {
      }

      void PrivateZenMock(
         const Arg1Type& arg1,
         const Arg2Type& arg2,
         const Arg3Type& arg3,
         const Arg4Type& arg4,
         const Arg5Type& arg5)
      {
         this->ThrowIfNotExpected(arg1, arg2, arg3, arg4, arg5);
         fiveArgCalls.emplace_back(arg1, arg2, arg3, arg4, arg5);
         this->ThrowIfExceptionSet();
      }

      void AssertCalledOnceWith(
         const Arg1Type& expectedArg1,
         const Arg2Type& expectedArg2,
         const Arg3Type& expectedArg3,
         const Arg4Type& expectedArg4,
         const Arg5Type& expectedArg5)
      {
         this->SetAsserted();
         const size_t expectedNumberOfCalls = 1;
         const size_t numberOfCalls = fiveArgCalls.size();
         ARE_EQUAL(expectedNumberOfCalls, numberOfCalls, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg1, fiveArgCalls[0].arg1, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg2, fiveArgCalls[0].arg2, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg3, fiveArgCalls[0].arg3, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg4, fiveArgCalls[0].arg4, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg5, fiveArgCalls[0].arg5, this->ZenMockedFunctionSignature);
      }

      void AssertCalledNTimesWith(
         size_t expectedNumberOfCalls,
         const Arg1Type& expectedArg1,
         const Arg2Type& expectedArg2,
         const Arg3Type& expectedArg3,
         const Arg4Type& expectedArg4,
         const Arg5Type& expectedArg5)
      {
         this->ThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->SetAsserted();
         const size_t numberOfCalls = fiveArgCalls.size();
         ARE_EQUAL(expectedNumberOfCalls, numberOfCalls, this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            std::string zenMockedFunctionSignatureAndCallIndex
               = ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedArg1, fiveArgCalls[i].arg1, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg2, fiveArgCalls[i].arg2, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg3, fiveArgCalls[i].arg3, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg4, fiveArgCalls[i].arg4, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg5, fiveArgCalls[i].arg5, zenMockedFunctionSignatureAndCallIndex);
         }
      }

      void AssertCalls(const std::vector<
         FiveArgCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>& expectedFiveArgCalls)
      {
         this->ThrowIfExpectedCallsSizeIsZero(expectedFiveArgCalls.size());
         this->SetAsserted();
         const std::vector<FiveArgCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>> 
            actualFiveArgCalls = PrivateCallsToCallRefs(fiveArgCalls);
         VECTORS_EQUAL(expectedFiveArgCalls, actualFiveArgCalls, this->ZenMockedFunctionSignature);
      }

   private:
      static std::vector<FiveArgCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>
         PrivateCallsToCallRefs(const std::vector<FiveArgCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>>& fiveArgCalls)
      {
         std::vector<FiveArgCallRef<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>> fiveArgCallRefs;
         fiveArgCallRefs.reserve(fiveArgCalls.size());
         std::for_each(fiveArgCalls.cbegin(), fiveArgCalls.cend(),
            [&](const FiveArgCall<Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type>& fiveArgCall)
            {
               fiveArgCallRefs.emplace_back(fiveArgCall);
            });
         return fiveArgCallRefs;
      }
   };
}
