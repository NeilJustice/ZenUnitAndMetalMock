#pragma once
#include "ZenUnit/ZenMock/ZenMocker.h"
#include "ZenUnit/ZenMock/3/ThreeArgCall.h"
#include "ZenUnit/ZenMock/3/ThreeArgCallRef.h"
#include "ZenUnit/ZenMock/Exceptions/UnexpectedCallException.h"
#include "ZenUnit/Macros/VECTORS_EQUAL.h"

#define ZENBIND3(FunctionName_ZenMock) \
   std::bind(&decltype(FunctionName_ZenMock)::PrivateZenMockFunctionPointer, &FunctionName_ZenMock, \
   std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)

namespace ZenMock
{
   template<
      typename Arg1Type,
      typename Arg2Type,
      typename Arg3Type,
      typename MockableExceptionThrowerType = ExceptionThrower>
   class ThreeArgMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class ThreeArgMockerTests;
   private:
      std::vector<ThreeArgCall<Arg1Type, Arg2Type, Arg3Type>> threeArgCalls;
   public:
      ThreeArgMocker(const std::string& zenMockedFunctionSignature)
         : ZenMocker<MockableExceptionThrowerType>(zenMockedFunctionSignature)
      {
      }

      void PrivateZenMock(const Arg1Type& arg1, const Arg2Type& arg2, const Arg3Type& arg3)
      {
         this->ThrowIfNotExpected(arg1, arg2, arg3);
         threeArgCalls.emplace_back(arg1, arg2, arg3);
         this->ThrowIfExceptionSet();
      }

      void AssertCalledOnceWith(
         const Arg1Type& expectedArg1,
         const Arg2Type& expectedArg2,
         const Arg3Type& expectedArg3)
      {
         this->SetAsserted();
         size_t expectedNumberOfCalls = 1;
         size_t numberOfCalls = threeArgCalls.size();
         ARE_EQUAL(expectedNumberOfCalls, numberOfCalls, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg1, threeArgCalls[0].arg1, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg2, threeArgCalls[0].arg2, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg3, threeArgCalls[0].arg3, this->ZenMockedFunctionSignature);
      }

      void AssertCalledNTimesWith(
         size_t expectedNumberOfCalls,
         const Arg1Type& expectedArg1,
         const Arg2Type& expectedArg2,
         const Arg3Type& expectedArg3)
      {
         this->ThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->SetAsserted();
         size_t numberOfCalls = threeArgCalls.size();
         ARE_EQUAL(expectedNumberOfCalls, numberOfCalls, this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            std::string zenMockedFunctionSignatureAndCallIndex
               = ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedArg1, threeArgCalls[i].arg1, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg2, threeArgCalls[i].arg2, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg3, threeArgCalls[i].arg3, zenMockedFunctionSignatureAndCallIndex);
         }
      }

      void AssertCalls(const std::vector<
         ThreeArgCallRef<Arg1Type, Arg2Type, Arg3Type>>& expectedThreeArgCalls)
      {
         this->ThrowIfExpectedCallsSizeIsZero(expectedThreeArgCalls.size());
         this->SetAsserted();
         std::vector<ThreeArgCallRef<Arg1Type, Arg2Type, Arg3Type>>
            actualThreeArgCalls = PrivateCallsToCallRefs(threeArgCalls);
         VECTORS_EQUAL(expectedThreeArgCalls, actualThreeArgCalls, this->ZenMockedFunctionSignature);
      }

   private:
      static std::vector<ThreeArgCallRef<Arg1Type, Arg2Type, Arg3Type>>
         PrivateCallsToCallRefs(const std::vector<ThreeArgCall<Arg1Type, Arg2Type, Arg3Type>>& threeArgCalls)
      {
         std::vector<ThreeArgCallRef<Arg1Type, Arg2Type, Arg3Type>> threeArgCallRefs;
         threeArgCallRefs.reserve(threeArgCalls.size());
         std::for_each(threeArgCalls.cbegin(), threeArgCalls.cend(),
            [&](const ThreeArgCall<Arg1Type, Arg2Type, Arg3Type>& threeArgCall)
            {
               threeArgCallRefs.emplace_back(threeArgCall);
            });
         return threeArgCallRefs;
      }
   };
}
