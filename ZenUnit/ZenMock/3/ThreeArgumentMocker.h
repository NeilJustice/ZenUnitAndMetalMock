#pragma once
#include "ZenUnit/Macros/VECTORS_EQUAL.h"
#include "ZenUnit/ZenMock/3/ThreeArgumentCall.h"
#include "ZenUnit/ZenMock/3/ThreeArgumentCallRef.h"
#include "ZenUnit/ZenMock/Exceptions/UnexpectedCallException.h"
#include "ZenUnit/ZenMock/ZenMocker.h"

#define ZENMOCK_BIND3(FunctionName_ZenMock) \
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

      void ZenMockIt(const Arg1Type& firstArgument, const Arg2Type& secondArgument, const Arg3Type& thirdArgument)
      {
         this->ZenMockThrowIfNotExpected(firstArgument, secondArgument, thirdArgument);
         threeArgumentCalls.emplace_back(firstArgument, secondArgument, thirdArgument);
         this->ZenMockThrowIfExceptionSet();
      }

      void AssertCalledOnceWith(
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument)
      {
         this->ZenMockSetAsserted();
         const size_t expectedNumberOfCalls = 1;
         ARE_EQUAL(expectedNumberOfCalls, threeArgumentCalls.size(), this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedFirstArgument, threeArgumentCalls[0].firstArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedSecondArgument, threeArgumentCalls[0].secondArgument, this->ZenMockedFunctionSignature);
         ARE_EQUAL(expectedThirdArgument, threeArgumentCalls[0].thirdArgument, this->ZenMockedFunctionSignature);
      }

      void AssertCalledNTimesWith(
         size_t expectedNumberOfCalls,
         const Arg1Type& expectedFirstArgument,
         const Arg2Type& expectedSecondArgument,
         const Arg3Type& expectedThirdArgument)
      {
         this->ZenMockThrowIfExpectedNumberOfCalls0(expectedNumberOfCalls);
         this->ZenMockSetAsserted();
         ARE_EQUAL(expectedNumberOfCalls, threeArgumentCalls.size(), this->ZenMockedFunctionSignature);
         for (size_t i = 0; i < expectedNumberOfCalls; ++i)
         {
            const std::string zenMockedFunctionSignatureAndCallIndex
               = ZenUnit::String::Concat(this->ZenMockedFunctionSignature, " at i=", i);
            ARE_EQUAL(expectedFirstArgument, threeArgumentCalls[i].firstArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedSecondArgument, threeArgumentCalls[i].secondArgument, zenMockedFunctionSignatureAndCallIndex);
            ARE_EQUAL(expectedThirdArgument, threeArgumentCalls[i].thirdArgument, zenMockedFunctionSignatureAndCallIndex);
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
