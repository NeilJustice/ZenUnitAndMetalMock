#pragma once
#include "ZenUnit/Macros/VECTORS_EQUAL.h"
#include "ZenUnit/ZenMock/3/ThreeArgumentCall.h"
#include "ZenUnit/ZenMock/3/ThreeArgumentCallRef.h"
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
   class ThreeArgumentMocker : public ZenMocker<MockableExceptionThrowerType>
   {
      friend class ThreeArgumentMockerTests;
   private:
      std::vector<ThreeArgumentCall<Arg1Type, Arg2Type, Arg3Type>> threeArgumentCalls;
   public:
      explicit ThreeArgumentMocker(const std::string& zenMockedFunctionSignature)
         : ZenMocker<MockableExceptionThrowerType>(zenMockedFunctionSignature)
      {
      }

      void ZenMockIt(const Arg1Type& argument1, const Arg2Type& argument2, const Arg3Type& argument3)
      {
         this->ZenMockThrowIfNotExpected(argument1, argument2, argument3);
         threeArgumentCalls.emplace_back(argument1, argument2, argument3);
         this->ZenMockThrowIfExceptionSet();
      }

      void AssertCalledOnceWith(
         const Arg1Type& expectedArgument1,
         const Arg2Type& expectedArgument2,
         const Arg3Type& expectedArgument3)
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, threeArgumentCalls.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument1, threeArgumentCalls[0].argument1, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument2, threeArgumentCalls[0].argument2, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedArgument3, threeArgumentCalls[0].argument3, this->ZenMockedFunctionSignature);
      }

      void AssertCalledNTimesWith(
         size_t expectedNumberOfCalls,
         const Arg1Type& expectedArgument1,
         const Arg2Type& expectedArgument2,
         const Arg3Type& expectedArgument3)
      {
         this->ZenMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->ZenMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCalls, threeArgumentCalls.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex
               = ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedArgument1, threeArgumentCalls[i].argument1, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument2, threeArgumentCalls[i].argument2, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedArgument3, threeArgumentCalls[i].argument3, zenMockedFunctionSignatureAndCallIndex);
         }
      }

      void AssertCalls(const std::vector<
         ThreeArgumentCallRef<Arg1Type, Arg2Type, Arg3Type>>& expectedThreeArgumentCalls)
      {
         this->ZenMockThrowIfExpectedCallsSizeIsZero(expectedThreeArgumentCalls.size());
         this->ZenMockSetAsserted();
         const std::vector<ThreeArgumentCallRef<Arg1Type, Arg2Type, Arg3Type>>
            actualThreeArgumentCalls = PrivateCallsToCallRefs(threeArgumentCalls);
         VECTORS_EQUAL(expectedThreeArgumentCalls, actualThreeArgumentCalls, this->ZenMockedFunctionSignature);
      }

   private:
      static std::vector<ThreeArgumentCallRef<Arg1Type, Arg2Type, Arg3Type>>
         PrivateCallsToCallRefs(const std::vector<ThreeArgumentCall<Arg1Type, Arg2Type, Arg3Type>>& threeArgumentCalls)
      {
         std::vector<ThreeArgumentCallRef<Arg1Type, Arg2Type, Arg3Type>> threeArgumentCallRefs;
         threeArgumentCallRefs.reserve(threeArgumentCalls.size());
         std::for_each(threeArgumentCalls.cbegin(), threeArgumentCalls.cend(),
            [&](const ThreeArgumentCall<Arg1Type, Arg2Type, Arg3Type>& threeArgumentCall)
            {
               threeArgumentCallRefs.emplace_back(threeArgumentCall);
            });
         return threeArgumentCallRefs;
      }
   };
}
