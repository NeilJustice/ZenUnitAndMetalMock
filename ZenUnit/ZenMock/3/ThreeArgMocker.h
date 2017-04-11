#pragma once
#include "ZenUnit/Macros/VECTORS_EQUAL.h"
#include "ZenUnit/ZenMock/3/ThreeArgCall.h"
#include "ZenUnit/ZenMock/3/ThreeArgCallRef.h"
#include "ZenUnit/ZenMock/Exceptions/UnexpectedCallException.h"
#include "ZenUnit/ZenMock/ZenMocker.h"

#define ZENBIND3(FunctionName_ZenMock) \
   std::bind(&decltype(FunctionName_ZenMock)::ZenMockItFunctionPointer, &(FunctionName_ZenMock), \
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
      std::vector<ThreeArgCall<Arg1Type, Arg2Type, Arg3Type>> _threeArgCalls;
   public:
      explicit ThreeArgMocker(const std::string& zenMockedFunctionSignature)
         : ZenMocker<MockableExceptionThrowerType>(zenMockedFunctionSignature)
      {
      }

      void ZenMockIt(const Arg1Type& arg1, const Arg2Type& arg2, const Arg3Type& arg3)
      {
         this->ZenMockThrowIfNotExpected(arg1, arg2, arg3);
         _threeArgCalls.emplace_back(arg1, arg2, arg3);
         this->ZenMockThrowIfExceptionSet();
      }

      void AssertCalledOnceWith(
         const Arg1Type& expectedArg1,
         const Arg2Type& expectedArg2,
         const Arg3Type& expectedArg3)
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, _threeArgCalls.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg1, _threeArgCalls[0].arg1, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg2, _threeArgCalls[0].arg2, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArg3, _threeArgCalls[0].arg3, this->ZenMockedFunctionSignature);
      }

      void AssertCalledNTimesWith(
         size_t expectedNumberOfCalls,
         const Arg1Type& expectedArg1,
         const Arg2Type& expectedArg2,
         const Arg3Type& expectedArg3)
      {
         this->ZenMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->ZenMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCalls, _threeArgCalls.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex
               = ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedArg1, _threeArgCalls[i].arg1, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg2, _threeArgCalls[i].arg2, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArg3, _threeArgCalls[i].arg3, zenMockedFunctionSignatureAndCallIndex);
         }
      }

      void AssertCalls(const std::vector<
         ThreeArgCallRef<Arg1Type, Arg2Type, Arg3Type>>& expectedThreeArgCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedThreeArgCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<ThreeArgCallRef<Arg1Type, Arg2Type, Arg3Type>>
            actualThreeArgCalls = PrivateCallsToCallRefs(_threeArgCalls);
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
